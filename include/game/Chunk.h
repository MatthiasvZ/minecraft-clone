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

#include "Positioni.h"
#include <string>

inline unsigned char voidChunkIDs[16][16][16];

class Chunk
{
    public:
        unsigned char blockIDs[16][16][16];
        unsigned char biomeIDs[16][16];

        Chunk(Positioni pos);
        Positioni& getPos();
        ~Chunk();

        bool meshGenerated;

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
