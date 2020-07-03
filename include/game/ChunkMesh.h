#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#define BLOCK_SIDE 0
#define BLOCK_TOPSIDE 1
#define BLOCK_BOTTOMSIDE 2

#include <vector>

class ChunkMesh
{
    public:
        std::vector<float> vertices;
        int vertexCount {0};
        std::vector<unsigned int> indices;

        ChunkMesh(const unsigned char (&blockIDs)[16][16][16], \
                  const unsigned char (&nbrIDsAbove)[16][16][16], \
                  const unsigned char (&nbrIDsBelow)[16][16][16], \
                  const unsigned char (&nbrIDsLeft)[16][16][16], \
                  const unsigned char (&nbrIDsRight)[16][16][16], \
                  const unsigned char (&nbrIDsInFront)[16][16][16], \
                  const unsigned char (&nbrIDsBehind)[16][16][16], \
                  const int& x, const int& y, const int& z);

        void updateChunkMesh(const unsigned char (&blockIDs)[16][16][16], \
                     const unsigned char (&nbrIDsAbove)[16][16][16], \
                     const unsigned char (&nbrIDsBelow)[16][16][16], \
                     const unsigned char (&nbrIDsLeft)[16][16][16], \
                     const unsigned char (&nbrIDsRight)[16][16][16], \
                     const unsigned char (&nbrIDsInFront)[16][16][16], \
                     const unsigned char (&nbrIDsBehind)[16][16][16]);

        #ifdef DEBUG
            static void printTimeStats();
        #endif // DEBUG
        ~ChunkMesh();

    protected:

    private:
        int m_PosX;
        int m_PosY;
        int m_PosZ;
        float getTexCoord(bool leftOrRight, unsigned char side, unsigned char blockID);
        void addVertex(float x, float y, float z, float l, float u, float v);
        void addIndex(unsigned short a, unsigned short b, unsigned short c);
};

#endif // CHUNKMESH_H
