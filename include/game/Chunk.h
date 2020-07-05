#ifndef CHUNK_H
#define CHUNK_H

#define BLOCK_AIR   0
#define BLOCK_GRASS_TOP 1
#define BLOCK_GRASS 2
#define BLOCK_DIRT  3
#define BLOCK_STONE 4
#define BLOCK_OAK_LOG 5
#define BLOCK_OAK_LOG_OUTSIDE 6

#include "gl/VertexArray.h"
#include "gl/IndexBuffer.h"
#include "gl/Shader.h"
#include <string>


struct Positioni
{
    int x;
    int y;
    int z;
};

class Chunk
{
    public:
        unsigned char m_BlockIDs[16][16][16];

        Chunk(int x, int y, int z);
        Positioni getPosition();
        ~Chunk();

    protected:


    private:
        std::string m_FileName;
        int m_PosX;
        int m_PosY;
        int m_PosZ;


        bool chunkExists();
        void readFromFile();
        void saveToFile();
        void generate();
        float lerp(float a0, float a1, float w);
        float dotGridGradient(int ix, int iy, float x, float y);
        float perlin(float x, float y);
};

#endif // CHUNK_H
