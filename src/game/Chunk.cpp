#include "game/Chunk.h"

#include "game/World.h"

#include <sys/stat.h>
#include <fstream>
#include <GL/glew.h>

#include "vendor/FastNoiseSIMD/FastNoiseSIMD.h"

#ifdef DEBUG
    #include <iostream>
#endif // DEBUG

Chunk::Chunk(int x, int y, int z)
{
    m_FileName = "saves/x" + std::to_string(x) + 'y' + std::to_string(y) + 'z' + std::to_string(z) +".chunk";
    m_PosX = x;
    m_PosY = y;
    m_PosZ = z;
    if (!chunkExists())
        generate();
    else
        readFromFile();
}

bool Chunk::chunkExists()
{
  struct stat buffer;
  return (stat (m_FileName.c_str(), &buffer) == 0);
}

void Chunk::readFromFile()
{
    std::ifstream file(m_FileName, std::ios::in);
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 16; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                m_BlockIDs[ix][iy][iz] = file.get();
            }
        }
    }
}

void Chunk::saveToFile()
{
    std::fstream file(m_FileName, std::ios::out);
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 16; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                file << static_cast<unsigned char>(m_BlockIDs[ix][iy][iz]);
            }
        }
    }
}

Positioni Chunk::getPosition()
{
    return Positioni(m_PosX, m_PosY, m_PosZ);
}

void Chunk::generate()
{
    FastNoiseSIMD* noise = FastNoiseSIMD::NewFastNoiseSIMD(World::getSeed());
    float pnoise[16][20][16];
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 20; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                float* temp = noise->GetPerlinSet(m_PosX*16 + ix, m_PosY*16 + iy, m_PosZ*16 + iz, 1, 1, 1);
                float* temp2 = noise->GetPerlinSet(m_PosX*16 + ix + 420, m_PosY*16 + iy + 420, m_PosZ*16 + iz + 420, 1, 1, 1);
                pnoise[ix][iy][iz] = temp[0]*20 + temp2[0]*20 + 55;
                delete temp;
                delete temp2;
            }
        }
    }


    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 16; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                if (pnoise[ix][iy][iz] > m_PosY*16 + iy)
                {
                    if (pnoise[ix][iy + 1][iz] < m_PosY*16 + iy+1)
                        m_BlockIDs[ix][iy][iz] = BLOCK_GRASS;
                    else if (pnoise[ix][iy + 4][iz] < m_PosY*16 + iy+4.5f)
                        m_BlockIDs[ix][iy][iz] = BLOCK_DIRT;
                    else
                        m_BlockIDs[ix][iy][iz] = BLOCK_STONE;
                }
                else
                    m_BlockIDs[ix][iy][iz] = BLOCK_AIR;
            }
        }
    }
    delete noise;
}

Chunk::~Chunk()
{
    saveToFile();
}
