#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#define BLOCK_SIDE 0
#define BLOCK_TOPSIDE 1
#define BLOCK_BOTTOMSIDE 2

#include <vector>
#include "Petroleum.h"

class ChunkMesh
{
    public:
        ChunkMesh(const unsigned char (&blockIDs)[16][16][16], \
                  const unsigned char (&nbrIDsAbove)[16][16][16], \
                  const unsigned char (&nbrIDsBelow)[16][16][16], \
                  const unsigned char (&nbrIDsLeft)[16][16][16], \
                  const unsigned char (&nbrIDsRight)[16][16][16], \
                  const unsigned char (&nbrIDsInFront)[16][16][16], \
                  const unsigned char (&nbrIDsBehind)[16][16][16], \
                  const int& x, const int& y, const int& z, bool skipGL = false);

        void updateChunkMesh(const unsigned char (&blockIDs)[16][16][16], \
                     const unsigned char (&nbrIDsAbove)[16][16][16], \
                     const unsigned char (&nbrIDsBelow)[16][16][16], \
                     const unsigned char (&nbrIDsLeft)[16][16][16], \
                     const unsigned char (&nbrIDsRight)[16][16][16], \
                     const unsigned char (&nbrIDsInFront)[16][16][16], \
                     const unsigned char (&nbrIDsBehind)[16][16][16],
                     bool skipGL = false);

        void createGLOs();
        inline PT::VertexArray* getVA() { return vao; }
        inline PT::IndexBuffer* getIBO() { return ibo; }
        inline bool isEmpty() { return empty; }

        #ifdef DEBUG
            static void printTimeStats();
        #endif // DEBUG

        void freeMemory();
        ~ChunkMesh();

    protected:

    private:
        std::vector<float>* vertices;
        int vertexCount {0};
        std::vector<unsigned short>* indices;
        PT::VertexArray* vao;
        PT::VertexBuffer* vbo;
        PT::IndexBuffer* ibo;


        int posX;
        int posY;
        int posZ;
        bool empty;
        bool firstrun;
        float getTexCoord(bool leftOrRight, unsigned char side, unsigned char blockID);
        void addVertex(float x, float y, float z, float l, float u, float v);
        void addIndex(unsigned short a, unsigned short b, unsigned short c);
};

#endif // CHUNKMESH_H
