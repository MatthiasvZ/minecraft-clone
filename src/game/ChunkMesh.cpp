#include "game/ChunkMesh.h"

#include "game/Chunk.h"

#ifdef DEBUG
    #include <chrono>
    #include <iostream>
#endif // DEBUG

#ifdef DEBUG
static float timeGeneratingMeshes {0};
static unsigned int totalMeshGens {0};
#endif // DEBUG

ChunkMesh::ChunkMesh(const ChunkBall& cBall, int x, int y, int z, bool skipGL)
    : pos(x, y, z), glosMissing(true)
{
    vertices = new std::vector<float>();
    vertices->reserve(49152);
    indices = new std::vector<unsigned short>();
    indices->reserve(16384);
    vertexCount = 0;

    #ifdef DEBUG
        auto t_start = std::chrono::high_resolution_clock::now();
    #endif // DEBUG
    for (int ix {0}; ix < 16; ix++)
        for (int iy {0}; iy < 16; iy++)
            for (int iz {0}; iz < 16; iz++)
            {
                if ((*cBall.blockIDs)[ix][iy][iz] == BLOCK_AIR)
                    continue;
                if (ix == 0 ? (*cBall.blockIDsRight)[15][iy][iz] == BLOCK_AIR : 0 || (*cBall.blockIDs)[ix - 1][iy][iz] == BLOCK_AIR) // right side
                {
                    addVertex(-0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex(-0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex(-0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addVertex(-0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iy == 0 ? (*cBall.blockIDsBelow)[ix][15][iz] == BLOCK_AIR : 0 || (*cBall.blockIDs)[ix][iy - 1][iz] == BLOCK_AIR) // bottom side
                {
                    addVertex(-0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.4f, getTexCoord(0, BLOCK_BOTTOMSIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.4f, getTexCoord(1, BLOCK_BOTTOMSIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.4f, getTexCoord(1, BLOCK_BOTTOMSIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addVertex(-0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.4f, getTexCoord(0, BLOCK_BOTTOMSIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iz == 0 ? (*cBall.blockIDsBehind)[ix][iy][15] == BLOCK_AIR : 0 || (*cBall.blockIDs)[ix][iy][iz - 1] == BLOCK_AIR) // back side
                {
                    addVertex(-0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.6f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.6f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.6f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addVertex(-0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.6f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (ix == 15 ? (*cBall.blockIDsLeft)[0][iy][iz] == BLOCK_AIR : 0 || (*cBall.blockIDs)[ix + 1][iy][iz] == BLOCK_AIR) // left side
                {
                    addVertex( 0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addVertex( 0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iy == 15 ? (*cBall.blockIDsAbove)[ix][0][iz] == BLOCK_AIR : 0 || (*cBall.blockIDs)[ix][iy + 1][iz] == BLOCK_AIR) // top side
                {
                    addVertex(-0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              1.0f, getTexCoord(0, BLOCK_TOPSIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              1.0f, getTexCoord(1, BLOCK_TOPSIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              1.0f, getTexCoord(1, BLOCK_TOPSIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addVertex(-0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y, -0.5f + iz + 16*pos.z, \
                              1.0f, getTexCoord(0, BLOCK_TOPSIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iz == 15 ? (*cBall.blockIDsInFront)[ix][iy][0] == BLOCK_AIR : 0 || (*cBall.blockIDs)[ix][iy][iz + 1] == BLOCK_AIR) // front side
                {
                    addVertex(-0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.8f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x,  0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.8f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 1);
                    addVertex( 0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.8f, getTexCoord(1, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addVertex(-0.5f + ix + 16*pos.x, -0.5f + iy + 16*pos.y,  0.5f + iz + 16*pos.z, \
                              0.8f, getTexCoord(0, BLOCK_SIDE, (*cBall.blockIDs)[ix][iy][iz]), 0);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
            }
    #ifdef DEBUG
        timeGeneratingMeshes += std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - t_start).count()*1000;
        totalMeshGens++;
    #endif // DEBUG


    if (!skipGL)
        createGLOs();
}

void ChunkMesh::createGLOs()
{
    empty = vertices->empty();

    vao = new PT::VertexArray();
    vbo = new PT::VertexBuffer(*vertices);
    PT::VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3);
    layout.push(GL_FLOAT, 1);
    layout.push(GL_FLOAT, 2);
    vao->addBuffer(*vbo, layout);
    ibo = new PT::IndexBuffer(*indices);

    delete vertices;
    delete indices;
    glosMissing = false;
}

float ChunkMesh::getTexCoord(bool leftOrRight, unsigned char side, unsigned char blockID)
{
    switch (blockID)
    {
    case BLOCK_GRASS:
        if (side == BLOCK_TOPSIDE)
            blockID = BLOCK_GRASS_TOP;
        if (side == BLOCK_BOTTOMSIDE)
            blockID = BLOCK_DIRT;
        break;
    default:
        break;
    }
    if (leftOrRight == 0)
        return (blockID-1.0f) / BLOCKS_TOTAL;
    return blockID / BLOCKS_TOTAL;
}

void ChunkMesh::addVertex(float x, float y, float z, float l, float u, float v)
{
    vertices->push_back(x);
    vertices->push_back(y);
    vertices->push_back(z);
    vertices->push_back(l);
    vertices->push_back(u);
    vertices->push_back(v);
    vertexCount++;
}

void ChunkMesh::addIndex(unsigned short a, unsigned short b, unsigned short c)
{
    indices->push_back(a);
    indices->push_back(b);
    indices->push_back(c);
}

#ifdef DEBUG
void ChunkMesh::printTimeStats()
{
    std::cout << "Debug: Average time generating a chunk mesh = " << timeGeneratingMeshes/totalMeshGens << "ms\n";
    std::cout << "Debug: Total time spent generating chunk meshes = " << timeGeneratingMeshes << "ms\n";
}
#endif // DEBUG

ChunkMesh::~ChunkMesh()
{
    vao->remove();
    vbo->remove();
    ibo->remove();
    delete vao;
    delete vbo;
    delete ibo;
}
