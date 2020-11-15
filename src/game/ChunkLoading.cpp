#include "game/World.h"

void World::loadNewChunks()
{
    while(!stop)
    {
        /*fprintf(stderr, "x = %f\n", camera.getPosX());
        fprintf(stderr, "y = %f\n", camera.getPosY());
        fprintf(stderr, "z = %f\n\n", camera.getPosZ());*/

        if (camera.getPosX() / 16 > (*chunks)[0][0][0].getPosition().x + CHUNKRD)
        {
            fprintf(stderr, "starting load\n");
            lock = true;
            constexpr unsigned int x = CHUNKRD - 1;

            chunks->erase(chunks->begin());
            chunks->shrink_to_fit();

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
            for (int jy {0}; jy < MAXHEIGHT; ++jy)
                for (int jz {0}; jz < CHUNKRD; ++jz)
                    (*chunkMeshes)[0][jy][jz].freeMemory();

            chunkMeshes->erase(chunkMeshes->begin());
            chunkMeshes->shrink_to_fit();

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
                                x == CHUNKRD-1 ? voidChunkIDs : (*chunks)[x+1][iy][iz].m_BlockIDs, \
                                x == 0 ? voidChunkIDs : (*chunks)[x-1][iy][iz].m_BlockIDs, \
                                iz == CHUNKRD-1 ? voidChunkIDs : (*chunks)[x][iy][iz+1].m_BlockIDs, \
                                iz == 0 ? voidChunkIDs : (*chunks)[x][iy][iz-1].m_BlockIDs, \
                                (*chunks)[x - 1][iy][iz].getPosition().x + 1, iy, iz, true));

                    (*chunkMeshes)[x - 1][iy][iz].updateChunkMesh((*chunks)[x - 1][iy][iz].m_BlockIDs, \
                                iy == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[x - 1][iy+1][iz].m_BlockIDs, \
                                iy == 0 ? voidChunkIDs : (*chunks)[x - 1][iy-1][iz].m_BlockIDs, \
                                x - 1 == CHUNKRD-1 ? voidChunkIDs : (*chunks)[x - 1+1][iy][iz].m_BlockIDs, \
                                x - 1 == 0 ? voidChunkIDs : (*chunks)[x - 1-1][iy][iz].m_BlockIDs, \
                                iz == CHUNKRD-1 ? voidChunkIDs : (*chunks)[x - 1][iy][iz+1].m_BlockIDs, \
                                iz == 0 ? voidChunkIDs : (*chunks)[x - 1][iy][iz-1].m_BlockIDs, true);

                    (*chunkMeshes)[0][iy][iz].updateChunkMesh((*chunks)[0][iy][iz].m_BlockIDs, \
                                iy == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[0][iy+1][iz].m_BlockIDs, \
                                iy == 0 ? voidChunkIDs : (*chunks)[0][iy-1][iz].m_BlockIDs, \
                                0 == CHUNKRD-1 ? voidChunkIDs : (*chunks)[0+1][iy][iz].m_BlockIDs, \
                                0 == 0 ? voidChunkIDs : (*chunks)[0-1][iy][iz].m_BlockIDs, \
                                iz == CHUNKRD-1 ? voidChunkIDs : (*chunks)[0][iy][iz+1].m_BlockIDs, \
                                iz == 0 ? voidChunkIDs : (*chunks)[0][iy][iz-1].m_BlockIDs, true);
                }
            }
            GLOsMissing = PLUS_X;
            lock = false;
            fprintf(stderr, "finished load");
        }
    }
}

void World::createBufferObjects()
{
    if (GLOsMissing == PLUS_X)
    {
        for (int iy {0}; iy < MAXHEIGHT; iy++)
            for (int iz {0}; iz < CHUNKRD; iz++)
                {
                    (*chunkMeshes)[CHUNKRD - 1][iy][iz].createGLOs();
                    (*chunkMeshes)[CHUNKRD - 2][iy][iz].createGLOs();
                    (*chunkMeshes)[0][iy][iz].createGLOs();
                }
        GLOsMissing = false;
        fprintf(stderr, "tst\n");
    }
}
