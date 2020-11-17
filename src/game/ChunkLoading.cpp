#include "game/World.h"
#include <chrono>

void World::loadNewChunks()
{
    while(!stop)
    {
        /*fprintf(stderr, "x = %f\n", camera.getPosX());
        fprintf(stderr, "y = %f\n", camera.getPosY());
        fprintf(stderr, "z = %f\n\n", camera.getPosZ());*/

        if (GLOsMissing)
            continue;

        if (camera.getPosX() / 16 > (*chunks)[0][0][0].getPosition().x + CHUNKRD)
        {
            fprintf(stderr, "starting load, ");
            constexpr unsigned int x = CHUNKRD;
            //constexpr unsigned int nX = CHUNKRD - 1;

            chunks->push_back(std::vector<std::vector<Chunk>>());
            (*chunks)[x].reserve(MAXHEIGHT);
            for (int iy {0}; iy < MAXHEIGHT; iy++)
            {
                (*chunks)[x].push_back(std::vector<Chunk>());
                (*chunks)[x][iy].reserve(CHUNKRD);
                for (int iz {0}; iz < CHUNKRD; iz++)
                    (*chunks)[x][iy].push_back(Chunk((*chunks)[x - 1][iy][iz].getPosition().x + 1, iy, iz));
            }

            lock = true;

            fprintf(stderr, "finished c1, ");
            chunkMeshes->push_back(std::vector<std::vector<ChunkMesh>>());
            for (int iy {0}; iy < MAXHEIGHT; iy++)
            {
                (*chunkMeshes)[x].push_back(std::vector<ChunkMesh>());
                (*chunkMeshes)[x][iy].reserve(CHUNKRD);

                for (int iz {0}; iz < CHUNKRD; iz++)
                {
                    (*chunkMeshes)[x][iy].push_back(ChunkMesh((*chunks)[x][iy][iz].m_BlockIDs, \
                                iy == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[x][iy+1][iz].m_BlockIDs, \
                                iy == 0 ? voidChunkIDs : (*chunks)[x][iy-1][iz].m_BlockIDs, \
                                voidChunkIDs, \
                                x == 0 ? voidChunkIDs : (*chunks)[x-1][iy][iz].m_BlockIDs, \
                                iz == CHUNKRD-1 ? voidChunkIDs : (*chunks)[x][iy][iz+1].m_BlockIDs, \
                                iz == 0 ? voidChunkIDs : (*chunks)[x][iy][iz-1].m_BlockIDs, \
                                (*chunks)[x - 1][iy][iz].getPosition().x + 1, iy, iz, true));

                    (*chunkMeshes)[x - 1][iy][iz].updateChunkMesh((*chunks)[x - 1][iy][iz].m_BlockIDs, \
                                iy == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[x - 1][iy+1][iz].m_BlockIDs, \
                                iy == 0 ? voidChunkIDs : (*chunks)[x - 1][iy-1][iz].m_BlockIDs, \
                                (*chunks)[x - 1+1][iy][iz].m_BlockIDs, \
                                x - 1 == 0 ? voidChunkIDs : (*chunks)[x - 1-1][iy][iz].m_BlockIDs, \
                                iz == CHUNKRD-1 ? voidChunkIDs : (*chunks)[x - 1][iy][iz+1].m_BlockIDs, \
                                iz == 0 ? voidChunkIDs : (*chunks)[x - 1][iy][iz-1].m_BlockIDs, true);

                    (*chunkMeshes)[1][iy][iz].updateChunkMesh((*chunks)[1][iy][iz].m_BlockIDs, \
                                iy == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[1][iy+1][iz].m_BlockIDs, \
                                iy == 0 ? voidChunkIDs : (*chunks)[1][iy-1][iz].m_BlockIDs, \
                                1 == CHUNKRD-1 ? voidChunkIDs : (*chunks)[1+1][iy][iz].m_BlockIDs, \
                                voidChunkIDs, \
                                iz == CHUNKRD-1 ? voidChunkIDs : (*chunks)[1][iy][iz+1].m_BlockIDs, \
                                iz == 0 ? voidChunkIDs : (*chunks)[1][iy][iz-1].m_BlockIDs, true);
                }
            }
            fprintf(stderr, "finished c2, ");


            GLOsMissing = PLUS_X;
            fprintf(stderr, "finished load, ");
        }
    }
}

void World::createBufferObjects()
{
    if (GLOsMissing == PLUS_X)
    {
        for (int jy {0}; jy < MAXHEIGHT; ++jy)
            for (int jz {0}; jz < CHUNKRD; ++jz)
                (*chunkMeshes)[0][jy][jz].freeMemory();

        chunks->erase(chunks->begin());
        chunks->shrink_to_fit();

        chunkMeshes->erase(chunkMeshes->begin());
        chunkMeshes->shrink_to_fit();

        for (int iy {0}; iy < MAXHEIGHT; iy++)
            for (int iz {0}; iz < CHUNKRD; iz++)
                {
                    (*chunkMeshes)[CHUNKRD - 1][iy][iz].createGLOs();
                    (*chunkMeshes)[CHUNKRD - 2][iy][iz].createGLOs();
                    (*chunkMeshes)[0][iy][iz].createGLOs();
                }

        fprintf(stderr, "updated buffers\n");
        GLOsMissing = false;
        lock = false;
    }
}
