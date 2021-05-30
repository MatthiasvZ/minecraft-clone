#ifndef CHUNK_H
#define CHUNK_H

#define BLOCK_AIR   0
#define BLOCK_GRASS_TOP 1
#define BLOCK_GRASS 2
#define BLOCK_DIRT  3
#define BLOCK_STONE 4
#define BLOCK_OAK_LOG 5
#define BLOCK_OAK_LOG_OUTSIDE 6
#define BLOCK_OAK_LEAVES 7
#define BLOCK_SAND 8
#define BLOCKS_TOTAL 8.0f

#include <string>


class Positioni
{
    public:
        Positioni(int x, int y, int z)
            : x(x), y(y), z(z) {}
        int x;
        int y;
        int z;

        bool operator==(Positioni* b)
        {
            if (this->x == b->x && this->y == b->y && this->z == b->z)
                return true;
            return false;
        }
};

class Chunk
{
    public:
        unsigned char blockIDs[16][16][16];
        unsigned char biomeIDs[16][16];

        Chunk(int x, int y, int z);
        Positioni* getPos();
        ~Chunk();

    protected:


    private:
        std::string fileName;
        Positioni pos;

        bool chunkExists();
        void readFromFile();
        void saveToFile();
        void generate();
};

#endif // CHUNK_H
