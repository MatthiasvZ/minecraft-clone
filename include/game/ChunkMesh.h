#ifndef CHUNKMESH_H
#define CHUNKMESH_H

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
        ~ChunkMesh();

    protected:

    private:
        int m_PosX;
        int m_PosY;
        int m_PosZ;
        void addVertex(float x, float y, float z, float u, float v);
        void addIndex(unsigned short a, unsigned short b, unsigned short c);
};

#endif // CHUNKMESH_H
