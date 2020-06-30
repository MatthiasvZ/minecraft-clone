#include "game/ChunkMesh.h"

#include "game/Chunk.h"
#include "game/TextureCoordinates.h"

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
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TL);
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TR);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BR);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BL);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iy == 0 ? nbrIDsBelow[ix][15][iz] == BLOCK_AIR : 0 || blockIDs[ix][iy - 1][iz] == BLOCK_AIR) // bottom side
                {
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_BOTTOM_TL);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_BOTTOM_TR);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_BOTTOM_BR);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_BOTTOM_BL);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iz == 0 ? nbrIDsBehind[ix][iy][15] == BLOCK_AIR : 0 || blockIDs[ix][iy][iz - 1] == BLOCK_AIR) // back side
                {
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TL);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TR);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BR);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BL);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (ix == 15 ? nbrIDsLeft[0][iy][iz] == BLOCK_AIR : 0 || blockIDs[ix + 1][iy][iz] == BLOCK_AIR) // left side
                {
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TL);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TR);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BR);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BL);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iy == 15 ? nbrIDsAbove[ix][0][iz] == BLOCK_AIR : 0 || blockIDs[ix][iy + 1][iz] == BLOCK_AIR) // top side
                {
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_TOP_TL);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_TOP_TR);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_TOP_BR);
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY, -0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_TOP_BL);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
                if (iz == 15 ? nbrIDsInFront[ix][iy][0] == BLOCK_AIR : 0 || blockIDs[ix][iy][iz + 1] == BLOCK_AIR) // front side
                {
                    addVertex(-0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TL);
                    addVertex( 0.5f + ix + 16*m_PosX,  0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_TR);
                    addVertex( 0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BR);
                    addVertex(-0.5f + ix + 16*m_PosX, -0.5f + iy + 16*m_PosY,  0.5f + iz + 16*m_PosZ, TEXCOORDS_GRASS_SIDE_BL);
                    addIndex(vertexCount - 4, vertexCount - 3, vertexCount - 2);
                    addIndex(vertexCount - 4, vertexCount - 2, vertexCount - 1);
                }
            }
    #ifdef DEBUG
        timeGeneratingMeshes += std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - t_start).count()*1000;
        totalMeshGens++;
    #endif // DEBUG
}

void ChunkMesh::addVertex(float x, float y, float z, float u, float v)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
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
    std::cout << "Average time generating a chunk mesh = " << timeGeneratingMeshes/totalMeshGens << "ms\n";
    std::cout << "Time total spent generating chunk meshes = " << timeGeneratingMeshes << "ms\n";
}
#endif // DEBUG

ChunkMesh::~ChunkMesh()
{
    //dtor
}
