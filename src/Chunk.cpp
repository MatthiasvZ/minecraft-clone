#include "Chunk.h"

#include <sys/stat.h>
#include <fstream>
#include <GL/glew.h>

#ifdef DEBUG
    #include <iostream>
#endif // DEBUG

Chunk::Chunk(int x, int y, int z)
{
    m_FileName = "saves/x" + std::to_string(x) + 'y' + std::to_string(y) + 'z' + std::to_string(z);
    m_PosX = x;
    m_PosY = y;
    m_PosZ = z;
    if (!chunkExists())
        generate();
    readFromFile();
}

bool Chunk::chunkExists()
{
  struct stat buffer;
  return (stat (m_FileName.c_str(), &buffer) == 0);
}

void Chunk::generate()
{
    #ifdef DEBUG
        printf("Generating Chunk \"%s\"\n", m_FileName.c_str());
    #endif // DEBUG

    std::fstream file(m_FileName, std::ios::out);
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 16; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                if (ix > 7 && iy > 7)
                    file << static_cast<char>(0);
                else
                    file << static_cast<char>(1);
            }
        }
    }
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
    #ifdef DEBUG
        printf("Saving Chunk \"%s\"\n", m_FileName.c_str());
    #endif // DEBUG
    std::fstream file(m_FileName, std::ios::out);
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 16; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                file << static_cast<char>(m_BlockIDs[ix][iy][iz]);
            }
        }
    }
}


Positioni Chunk::getPosition()
{
    return Positioni(m_PosX, m_PosY, m_PosZ);
}

Chunk::~Chunk()
{
    saveToFile();
}
