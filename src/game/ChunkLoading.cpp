#include "game/World.h"

void World::loadNewChunks()
{
    /*fprintf(stderr, "x = %f\n", camera.getPosX());
    fprintf(stderr, "y = %f\n", camera.getPosY());
    fprintf(stderr, "z = %f\n\n", camera.getPosZ());*/

    if (camera.getPosX() / 16 > (*chunks)[0][0][0].getPosition().x + CHUNKRD)
    {
        constexpr unsigned int x = CHUNKRD - 1;

        std::vector<std::vector<std::vector<Chunk>>>* tempChunks = new std::vector<std::vector<std::vector<Chunk>>>(CHUNKRD);
        tempChunks->assign(chunks->begin() + 1, chunks->end());

        tempChunks->push_back(std::vector<std::vector<Chunk>>());
        (*tempChunks)[x].reserve(MAXHEIGHT);
        for (int iy {0}; iy < MAXHEIGHT; iy++)
        {
            (*tempChunks)[x].push_back(std::vector<Chunk>());
            (*tempChunks)[x][iy].reserve(CHUNKRD);
            for (int iz {0}; iz < CHUNKRD; iz++)
                (*tempChunks)[x][iy].push_back(Chunk((*tempChunks)[x - 1][iy][iz].getPosition().x + 1, iy, iz));
        }


        std::vector<std::vector<std::vector<ChunkMesh>>>* tempChunkMeshes = new std::vector<std::vector<std::vector<ChunkMesh>>>(CHUNKRD);
        tempChunkMeshes->assign(chunkMeshes->begin() + 1, chunkMeshes->end());
        tempChunkMeshes->push_back(std::vector<std::vector<ChunkMesh>>());

        for (int iy {0}; iy < MAXHEIGHT; iy++)
        {
            (*tempChunkMeshes)[x].push_back(std::vector<ChunkMesh>());
            (*tempChunkMeshes)[x][iy].reserve(CHUNKRD);

            for (int iz {0}; iz < CHUNKRD; iz++)
            {
                (*tempChunkMeshes)[x][iy].push_back(ChunkMesh((*tempChunks)[x][iy][iz].m_BlockIDs, \
                            iy == MAXHEIGHT-1 ? voidChunkIDs : (*tempChunks)[x][iy+1][iz].m_BlockIDs, \
                            iy == 0 ? voidChunkIDs : (*tempChunks)[x][iy-1][iz].m_BlockIDs, \
                            x == CHUNKRD-1 ? voidChunkIDs : (*tempChunks)[x+1][iy][iz].m_BlockIDs, \
                            x == 0 ? voidChunkIDs : (*tempChunks)[x-1][iy][iz].m_BlockIDs, \
                            iz == CHUNKRD-1 ? voidChunkIDs : (*tempChunks)[x][iy][iz+1].m_BlockIDs, \
                            iz == 0 ? voidChunkIDs : (*tempChunks)[x][iy][iz-1].m_BlockIDs, \
                            (*tempChunks)[x - 1][iy][iz].getPosition().x + 1, iy, iz));

                (*tempChunkMeshes)[x - 1][iy][iz].updateChunkMesh((*tempChunks)[x - 1][iy][iz].m_BlockIDs, \
                            iy == MAXHEIGHT-1 ? voidChunkIDs : (*tempChunks)[x - 1][iy+1][iz].m_BlockIDs, \
                            iy == 0 ? voidChunkIDs : (*tempChunks)[x - 1][iy-1][iz].m_BlockIDs, \
                            x - 1 == CHUNKRD-1 ? voidChunkIDs : (*tempChunks)[x - 1+1][iy][iz].m_BlockIDs, \
                            x - 1 == 0 ? voidChunkIDs : (*tempChunks)[x - 1-1][iy][iz].m_BlockIDs, \
                            iz == CHUNKRD-1 ? voidChunkIDs : (*tempChunks)[x - 1][iy][iz+1].m_BlockIDs, \
                            iz == 0 ? voidChunkIDs : (*tempChunks)[x - 1][iy][iz-1].m_BlockIDs);

                (*tempChunkMeshes)[0][iy][iz].updateChunkMesh((*tempChunks)[0][iy][iz].m_BlockIDs, \
                            iy == MAXHEIGHT-1 ? voidChunkIDs : (*tempChunks)[0][iy+1][iz].m_BlockIDs, \
                            iy == 0 ? voidChunkIDs : (*tempChunks)[0][iy-1][iz].m_BlockIDs, \
                            0 == CHUNKRD-1 ? voidChunkIDs : (*tempChunks)[0+1][iy][iz].m_BlockIDs, \
                            0 == 0 ? voidChunkIDs : (*tempChunks)[0-1][iy][iz].m_BlockIDs, \
                            iz == CHUNKRD-1 ? voidChunkIDs : (*tempChunks)[0][iy][iz+1].m_BlockIDs, \
                            iz == 0 ? voidChunkIDs : (*tempChunks)[0][iy][iz-1].m_BlockIDs);
            }
        }

        lock = true;
        for (int jx {0}; jx < CHUNKRD; ++jx)
            for (int jy {0}; jy < MAXHEIGHT; ++jy)
                for (int jz {0}; jz < CHUNKRD; ++jz)
                {
                    //(*chunkMeshes)[jx][jy][jz].freeMemory();
                    fprintf(stderr, "cm %d, %d, %d successfully freed\n", jx, jy, jz);
                }
        delete chunks;
        chunks = tempChunks;
        delete chunkMeshes;
        chunkMeshes = tempChunkMeshes;
        lock = false;
        fprintf(stderr, "New chunk row loaded!\n");
    }
}
