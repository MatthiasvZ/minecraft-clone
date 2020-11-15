#ifndef CHUNK_H
#define CHUNK_H

#define BLOCK_AIR   0
#define BLOCK_GRASS_TOP 1
#define BLOCK_GRASS 2
#define BLOCK_DIRT  3
#define BLOCK_STONE 4
#define BLOCK_OAK_LOG 5
#define BLOCK_OAK_LOG_OUTSIDE 6

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
};

#endif // CHUNK_H
