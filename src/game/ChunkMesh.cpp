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

ChunkMesh::ChunkMesh(const unsigned char (&blockIDs)[16][16][16], \
                     const unsigned char (&nbrIDsAbove)[16][16][16], \
                     const unsigned char (&nbrIDsBelow)[16][16][16], \
                     const unsigned char (&nbrIDsLeft)[16][16][16], \
                     const unsigned char (&nbrIDsRight)[16][16][16], \
                     const unsigned char (&nbrIDsInFront)[16][16][16], \
                     const unsigned char (&nbrIDsBehind)[16][16][16], \
                     const int& x, const int& y, const int& z)
{
    m_PosX = x;
    m_PosY = y;
    m_PosZ = z;
    updateChunkMesh(blockIDs, nbrIDsAbove, nbrIDsBelow, nbrIDsLeft, \
                    nbrIDsRight, nbrIDsInFront, nbrIDsBehind);
}


void ChunkMesh::updateChunkMesh(const unsigned char (&blockIDs)[16][16][16], \
                                const unsigned char (&nbrIDsAbove)[16][16][16], \
                                const unsigned char (&nbrIDsBelow)[16][16][16], \
                                const unsigned char (&nbrIDsLeft)[16][16][16], \
                                const unsigned char (&nbrIDsRight)[16][16][16], \
                                const unsigned char (&nbrIDsInFront)[16][16][16], \
                                const unsigned char (&nbrIDsBehind)[16][16][16])
{
    #ifdef DEBUG
        auto t_start = std::chrono::high_resolution_clock::now();
    #endif // DEBUG
    for (int ix {0}; ix < 16; ix++)
        for (int iy {0}; iy < 16; iy++)
            for (int iz {0}; iz < 16; iz++)
            {
                if (blockIDs[ix][iy][iz] == BLOCK_AIR)
                    continue;
                if (ix == 0 ? nbrIDsRight[15][iy][iz] == BLOCK_AIR : 0 || blockIDs[ix - 1][iy][iz] == BLOCK_AIR) // right side
                {
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iy == 0 ? nbrIDsBelow[ix][15][iz] == BLOCK_AIR : 0 || blockIDs[ix][iy - 1][iz] == BLOCK_AIR) // bottom side
                {
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.4f, getTexCoord(0, BLOCK_BOTTOMSIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.4f, getTexCoord(1, BLOCK_BOTTOMSIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.4f, getTexCoord(1, BLOCK_BOTTOMSIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.4f, getTexCoord(0, BLOCK_BOTTOMSIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iz == 0 ? nbrIDsBehind[ix][iy][15] == BLOCK_AIR : 0 || blockIDs[ix][iy][iz - 1] == BLOCK_AIR) // back side
                {
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.6f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.6f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.6f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.6f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (ix == 15 ? nbrIDsLeft[0][iy][iz] == BLOCK_AIR : 0 || blockIDs[ix + 1][iy][iz] == BLOCK_AIR) // left side
                {
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              0.7f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iy == 15 ? nbrIDsAbove[ix][0][iz] == BLOCK_AIR : 0 || blockIDs[ix][iy + 1][iz] == BLOCK_AIR) // top side
                {
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              1.0f, getTexCoord(0, BLOCK_TOPSIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              1.0f, getTexCoord(1, BLOCK_TOPSIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              1.0f, getTexCoord(1, BLOCK_TOPSIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, \
                              1.0f, getTexCoord(0, BLOCK_TOPSIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iz == 15 ? nbrIDsInFront[ix][iy][0] == BLOCK_AIR : 0 || blockIDs[ix][iy][iz + 1] == BLOCK_AIR) // front side
                {
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.8f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.8f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 1.0f);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.8f, getTexCoord(1, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, \
                              0.8f, getTexCoord(0, BLOCK_SIDE, blockIDs[ix][iy][iz]), 0.0f);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
            }
    #ifdef DEBUG
        timeGeneratingMeshes += std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - t_start).count()*1000;
        totalMeshGens++;
    #endif // DEBUG
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
        return (blockID-1.0f)/4.0f;
    return blockID/4.0f;
}

void ChunkMesh::addVertex(float x, float y, float z, float l, float u, float v)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(l);
    vertices.push_back(u);
    vertices.push_back(v);
    vertexCount++;
}

void ChunkMesh::addIndex(unsigned short a, unsigned short b, unsigned short c)
{
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

#ifdef DEBUG
void ChunkMesh::printTimeStats()
{
    std::cout << "Debug: Average time generating a chunk mesh = " << timeGeneratingMeshes/totalMeshGens << "ms\n";
    std::cout << "Debug: Time total spent generating chunk meshes = " << timeGeneratingMeshes << "ms\n";
}
#endif // DEBUG

ChunkMesh::~ChunkMesh()
{
    //dtor
}
