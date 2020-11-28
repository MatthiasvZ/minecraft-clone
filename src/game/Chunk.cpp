#include "game/Chunk.h"

#include "game/World.h"

#include <sys/stat.h>
#include <fstream>
#include <cstdio>
#include <GL/glew.h>

#include <sstream>
#include <zstd.h>

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
    fprintf(stderr, "CHK 1\n");
    fprintf(stderr, "filename = %s\n", m_FileName.c_str());
    struct stat st;
    stat(m_FileName.c_str(), &st);

    FILE* const iFile = fopen(m_FileName.c_str(), "rb");
    assert(iFile != NULL);
    unsigned char fBuff[st.st_size];
    size_t const fileSize = fread(fBuff, 1, st.st_size, iFile);
    fclose(iFile);
    fprintf(stderr, "fileSize = %ld\n", fileSize);


    fprintf(stderr, "CHK 2\n");
    size_t const cBuffSize = ZSTD_compressBound(16 * 16 * 16 * sizeof(unsigned char));
    unsigned char cBuff[cBuffSize];

    fprintf(stderr, "CHK 3\n");
    assert(ZSTD_decompress(cBuff, cBuffSize, fBuff, st.st_size)
           == 16 * 16 * 16 * sizeof(unsigned char));

    fprintf(stderr, "CHK 4\n");
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 16; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                m_BlockIDs[ix][iy][iz] = cBuff[256*ix + 16*iy + iz];
            }
        }
    }
}

void Chunk::saveToFile()
{
    constexpr size_t fSize = 16 * 16 * 16 * sizeof(unsigned char);
    unsigned char fBuff[16 * 16 * 16];

    for (int ix {0}; ix < 16; ix++)
        for (int iy {0}; iy < 16; iy++)
            for (int iz {0}; iz < 16; iz++)
                fBuff[256*ix + 16*iy + iz] = static_cast<unsigned char>(m_BlockIDs[ix][iy][iz]);

    size_t const cBuffSize = ZSTD_compressBound(16 * 16 * 16 * sizeof(unsigned char));
    unsigned char cBuff[cBuffSize];

    size_t const cSize = ZSTD_compress(cBuff, cBuffSize, fBuff, fSize, 1);


    FILE* const oFile = fopen(m_FileName.c_str(), "wb");
    fwrite(cBuff, 1, cSize, oFile);
    fclose(oFile);
}

Positioni Chunk::getPosition()
{
    return Positioni(m_PosX, m_PosY, m_PosZ);
}

Chunk::~Chunk()
{
    fprintf(stderr, "(%ld) Saving Chunk!!\n", time(0));
    saveToFile();
}
