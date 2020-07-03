#include "game/World.h"

#define CHUNKRD 16     // 256 blocks render distance
#define MAXHEIGHT 8    // 128 block height max.

#include "game/Chunk.h"
#include "game/ChunkMesh.h"
#include "gl/VertexArray.h"
#include "gl/VertexBuffer.h"
#include "gl/VertexBufferLayout.h"
#include "gl/IndexBuffer.h"
#include "gl/Renderer.h"

#include <vector>
#include <iostream>


Renderer renderer;
std::vector<std::vector<std::vector<Chunk>>> chunks;
std::vector<std::vector<std::vector<ChunkMesh>>> chunkMeshes;
std::vector<std::vector<std::vector<VertexArray>>> vaos;
std::vector<std::vector<std::vector<VertexBuffer>>> vbos;
std::vector<std::vector<std::vector<IndexBuffer>>> ibos;
VertexBufferLayout layout;

World::World()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    chunks.reserve(CHUNKRD);
    chunkMeshes.reserve(CHUNKRD);
    vaos.reserve(CHUNKRD);
    vbos.reserve(CHUNKRD);
    ibos.reserve(CHUNKRD);

    layout.push(GL_FLOAT, 3); // positions x,y,z
    layout.push(GL_FLOAT, 1); // lighting l
    layout.push(GL_FLOAT, 2); // tex coords u,v

    unsigned char voidChunkIDs[16][16][16];
    for (int ix {0}; ix < 16; ix++)
        for (int iy {0}; iy < 16; iy++)
            for (int iz {0}; iz < 16; iz++)
                voidChunkIDs[ix][iy][iz] = 0;

    // Generate/load the chunks.
    for (int ix {0}; ix < CHUNKRD; ix++)
    {
        chunks.push_back(std::vector<std::vector<Chunk>>());
        chunks[ix].reserve(MAXHEIGHT);
        for (int iy {0}; iy < MAXHEIGHT; iy++)
        {
            chunks[ix].push_back(std::vector<Chunk>());
            chunks[ix][iy].reserve(CHUNKRD);
            for (int iz {0}; iz < CHUNKRD; iz++)
                chunks[ix][iy].push_back(Chunk(ix, iy, iz));
        }
    }

    // Now that that's done, generate the chunk meshes, their vaos and buffer objects.
    for (int ix {0}; ix < CHUNKRD; ix++)
    {
        chunkMeshes.push_back(std::vector<std::vector<ChunkMesh>>());
        vaos.push_back(std::vector<std::vector<VertexArray>>());
        vbos.push_back(std::vector<std::vector<VertexBuffer>>());
        ibos.push_back(std::vector<std::vector<IndexBuffer>>());

        chunkMeshes[ix].reserve(MAXHEIGHT);
        vaos[ix].reserve(MAXHEIGHT);
        vbos[ix].reserve(MAXHEIGHT);
        ibos[ix].reserve(MAXHEIGHT);

        for (int iy {0}; iy < MAXHEIGHT; iy++)
        {
            chunkMeshes[ix].push_back(std::vector<ChunkMesh>());
            vaos[ix].push_back(std::vector<VertexArray>());
            vbos[ix].push_back(std::vector<VertexBuffer>());
            ibos[ix].push_back(std::vector<IndexBuffer>());

            chunkMeshes[ix][iy].reserve(CHUNKRD);
            vaos[ix][iy].reserve(CHUNKRD);
            vbos[ix][iy].reserve(CHUNKRD);
            ibos[ix][iy].reserve(CHUNKRD);

            for (int iz {0}; iz < CHUNKRD; iz++)
            {
                chunkMeshes[ix][iy].push_back(ChunkMesh(chunks[ix][iy][iz].m_BlockIDs, \
                            iy == MAXHEIGHT-1 ? voidChunkIDs : chunks[ix][iy+1][iz].m_BlockIDs, \
                            iy == 0 ? voidChunkIDs : chunks[ix][iy-1][iz].m_BlockIDs, \
                            ix == CHUNKRD-1 ? voidChunkIDs : chunks[ix+1][iy][iz].m_BlockIDs, \
                            ix == 0 ? voidChunkIDs : chunks[ix-1][iy][iz].m_BlockIDs, \
                            iz == CHUNKRD-1 ? voidChunkIDs : chunks[ix][iy][iz+1].m_BlockIDs, \
                            iz == 0 ? voidChunkIDs : chunks[ix][iy][iz-1].m_BlockIDs, \
                            ix, iy, iz));
                vaos[ix][iy].push_back(VertexArray());
                vaos[ix][iy][iz].genArray();
                vbos[ix][iy].push_back(VertexBuffer());
                vbos[ix][iy][iz].addData(chunkMeshes[ix][iy][iz].vertices.data(), \
                                                  chunkMeshes[ix][iy][iz].vertices.size() * sizeof(float));
                vaos[ix][iy][iz].addBuffer(vbos[ix][iy][iz], layout);
                ibos[ix][iy].push_back(IndexBuffer());
                ibos[ix][iy][iz].addData(chunkMeshes[ix][iy][iz].indices.data(), \
                                                  chunkMeshes[ix][iy][iz].indices.size());
            }
        }
    }
}
void World::drawChunks()
{
    renderer.clear();
    //for (int stresstest {0}; stresstest < 20; stresstest++)
    for (int ix {0}; ix < CHUNKRD; ix++)
        for (int iy {0}; iy < MAXHEIGHT; iy++)
            for (int iz {0}; iz < CHUNKRD; iz++)
                renderer.drawVA(vaos[ix][iy][iz], vbos[ix][iy][iz], ibos[ix][iy][iz]);
}

World::~World()
{
    #ifdef DEBUG
        ChunkMesh::printTimeStats();
    #endif // DEBUG
    printf("Saving chunks...\n");
}
