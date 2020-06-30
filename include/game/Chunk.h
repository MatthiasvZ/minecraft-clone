#ifndef CHUNK_H
#define CHUNK_H

#define BLOCK_AIR   0
#define BLOCK_GRASS 1
#define BLOCK_DIRT  2
#define BLOCK_STONE 3

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
        void generate();
        void readFromFile();
        void saveToFile();
};

#endif // CHUNK_H
