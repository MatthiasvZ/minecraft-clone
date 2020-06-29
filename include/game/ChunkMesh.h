#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <vector>

class ChunkMesh
{
    public:
        std::vector<float> vertices;
        int vertexCount {0};
        std::vector<unsigned int> indices;

        ChunkMesh(unsigned char blockIDs[16][16][16], int x, int y, int z);
        void updateChunkMesh(unsigned char blockIDs[16][16][16]);
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
