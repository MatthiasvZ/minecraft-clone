#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#define BLOCK_SIDE 0
#define BLOCK_TOPSIDE 1
#define BLOCK_BOTTOMSIDE 2

#include "Positioni.h"
#include <vector>
#include "Petroleum.h"

class ChunkBall
{
    public:
        ChunkBall()
        : blockIDs(nullptr) {}
        unsigned char (*blockIDs)[16][16][16];

        unsigned char (*blockIDsAbove)[16][16][16];
        unsigned char (*blockIDsBelow)[16][16][16];
        unsigned char (*blockIDsLeft)[16][16][16];
        unsigned char (*blockIDsRight)[16][16][16];
        unsigned char (*blockIDsInFront)[16][16][16];
        unsigned char (*blockIDsBehind)[16][16][16];
};

class ChunkMesh
{
    public:
        ChunkMesh(const ChunkBall& cBall, int x, int y, int z);

        void createGLOs();

        inline PT::VertexArray* getVA()          { return vao; }
        inline PT::IndexBuffer* getIBO()         { return ibo; }
        inline bool             isEmpty()        { return empty; }
        inline Positioni        getPos()         { return pos; }
        inline bool             getGLOsMissing() { return glosMissing; }

        bool flaggedForDeletion;

        #ifdef DEBUG
            static void printTimeStats();
        #endif // DEBUG

        ~ChunkMesh();

    protected:

    private:
        std::vector<float>* vertices;
        int vertexCount {0};
        std::vector<unsigned short>* indices;
        PT::VertexArray* vao;
        PT::VertexBuffer* vbo;
        PT::IndexBuffer* ibo;


        Positioni pos;
        bool empty;
        bool glosMissing;
        float getTexCoord(bool leftOrRight, unsigned char side, unsigned char blockID);
        void addVertex(float x, float y, float z, float l, float u, float v);
        void addIndex(unsigned short a, unsigned short b, unsigned short c);
};

#endif // CHUNKMESH_H
