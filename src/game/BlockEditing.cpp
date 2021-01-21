#include "World.h"
#include "Ray.h"

void World::breakBlock()
{
    Ray ray(camera.getPitch(), camera.getYaw(), camera.getPosX(), camera.getPosY(), camera.getPosZ());
    for (int i {0}; i < 600; ++i)
    {
        if (static_cast<int>(ray.getX()) > 16 * (*chunks)[CHUNKRD - 1][MAXHEIGHT - 1][CHUNKRD - 1].getPosition().x + 15 ||
            static_cast<int>(ray.getX()) < 16 * (*chunks)[0][0][0].getPosition().x ||
            static_cast<int>(ray.getY()) > 16 * (*chunks)[CHUNKRD - 1][MAXHEIGHT - 1][CHUNKRD - 1].getPosition().y + 15 ||
            static_cast<int>(ray.getY()) < 16 * (*chunks)[0][0][0].getPosition().y ||
            static_cast<int>(ray.getZ()) > 16 * (*chunks)[CHUNKRD - 1][MAXHEIGHT - 1][CHUNKRD - 1].getPosition().z + 15 ||
            static_cast<int>(ray.getZ()) < 16 * (*chunks)[0][0][0].getPosition().z)
            break;

        if ((*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ] \
            .m_BlockIDs[static_cast<int>(ray.getX()) % 16][static_cast<int>(ray.getY()) % 16][static_cast<int>(ray.getZ()) % 16] != BLOCK_AIR)
        {
            #ifdef DEBUG
            fprintf(stderr, "Hit block of type %d!\n", (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ] \
                    .m_BlockIDs[static_cast<int>(ray.getX()) % 16][static_cast<int>(ray.getY()) % 16][static_cast<int>(ray.getZ()) % 16]);
            #endif // DEBUG

            // Replace the block with air
            (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ] \
                     .m_BlockIDs[static_cast<int>(ray.getX()) % 16][static_cast<int>(ray.getY()) % 16][static_cast<int>(ray.getZ()) % 16] = BLOCK_AIR;

            for (int ix {0}; ix < 16; ix++)
                for (int iy {0}; iy < 16; iy++)
                    for (int iz {0}; iz < 16; iz++)
                        voidChunkIDs[ix][iy][iz] = 0;

            // Update the chunk
            (*chunkMeshes)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ]
                            .updateChunkMesh((*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                            static_cast<int>(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)+1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                            static_cast<int>(ray.getY() / 16) == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)-1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                            static_cast<int>(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX+1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                            static_cast<int>(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX-1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                            static_cast<int>(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ+1].m_BlockIDs, \
                            static_cast<int>(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ-1].m_BlockIDs, false);


            // Update neighbouring chunks if necessairy
            if (static_cast<int>(ray.getY() / 16) < MAXHEIGHT - 1) // above
            {
                if (static_cast<int>(ray.getY()) % 16 == 15 &&
                    (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) + 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs \
                    [static_cast<int>(ray.getX()) % 16][0][static_cast<int>(ray.getZ()) % 16] != BLOCK_AIR)
                    (*chunkMeshes)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) + 1][static_cast<int>(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh((*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) + 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) + 1 == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) + 1+1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) + 1 == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) + 1-1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX+1][static_cast<int>(ray.getY() / 16) + 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX-1][static_cast<int>(ray.getY() / 16) + 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) + 1][static_cast<int>(ray.getZ() / 16) - offsetZ+1].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) + 1][static_cast<int>(ray.getZ() / 16) - offsetZ-1].m_BlockIDs, false);

            }
            if (static_cast<int>(ray.getY() / 16) > 0) // below
            {
                if (static_cast<int>(ray.getY()) % 16 == 0 &&
                    (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) - 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs \
                    [static_cast<int>(ray.getX()) % 16][15][static_cast<int>(ray.getZ()) % 16] != BLOCK_AIR)
                    (*chunkMeshes)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) - 1][static_cast<int>(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh((*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) - 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) - 1 == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) - 1+1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) - 1 == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) - 1-1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX+1][static_cast<int>(ray.getY() / 16) - 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX-1][static_cast<int>(ray.getY() / 16) - 1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) - 1][static_cast<int>(ray.getZ() / 16) - offsetZ+1].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16) - 1][static_cast<int>(ray.getZ() / 16) - offsetZ-1].m_BlockIDs, false);
            }
            if (static_cast<int>(ray.getX() / 16) < CHUNKRD - 1) // to the right
            {
                if (static_cast<int>(ray.getX()) % 16 == 15 &&
                    (*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs \
                    [static_cast<int>(ray.getX()) % 16][0][static_cast<int>(ray.getZ()) % 16] != BLOCK_AIR)
                    (*chunkMeshes)[static_cast<int>(ray.getX() / 16) + 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh((*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX][static_cast<int>(ray.getY() / 16)+1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX][static_cast<int>(ray.getY() / 16)-1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) + 1 - offsetX == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX+1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) + 1 - offsetX == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX-1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ+1].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) + 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ-1].m_BlockIDs, false);

            }
            if (static_cast<int>(ray.getX() / 16) > 0) // to the left
            {
                if (static_cast<int>(ray.getX()) % 16 == 0 &&
                    (*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs \
                    [static_cast<int>(ray.getX()) % 16][0][static_cast<int>(ray.getZ()) % 16] != BLOCK_AIR)
                    (*chunkMeshes)[static_cast<int>(ray.getX() / 16) - 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh((*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX][static_cast<int>(ray.getY() / 16)+1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX][static_cast<int>(ray.getY() / 16)-1][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - 1 - offsetX == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX+1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - 1 - offsetX == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX-1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ+1].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - 1 - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - offsetZ-1].m_BlockIDs, false);

            }
            if (static_cast<int>(ray.getZ() / 16) < CHUNKRD - 1) // to the front
            {
                if (static_cast<int>(ray.getZ()) % 16 == 15 &&
                    (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ].m_BlockIDs \
                    [static_cast<int>(ray.getX()) % 16][0][static_cast<int>(ray.getZ()) % 16] != BLOCK_AIR)
                    (*chunkMeshes)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ]
                                    .updateChunkMesh((*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)+1][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)-1][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX+1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX-1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) + 1 - offsetZ == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ+1].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) + 1 - offsetZ == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) + 1 - offsetZ-1].m_BlockIDs, false);

            }
            if (static_cast<int>(ray.getZ() / 16) > 0) // to the back
            {
                if (static_cast<int>(ray.getZ()) % 16 == 0 &&
                    (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ].m_BlockIDs \
                    [static_cast<int>(ray.getX()) % 16][0][static_cast<int>(ray.getZ()) % 16] != BLOCK_AIR)
                    (*chunkMeshes)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ]
                                    .updateChunkMesh((*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)+1][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getY() / 16) == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)-1][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX+1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX-1][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - 1 - offsetZ == CHUNKRD-1 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ+1].m_BlockIDs, \
                                    static_cast<int>(ray.getZ() / 16) - 1 - offsetZ == 0 ? voidChunkIDs : (*chunks)[static_cast<int>(ray.getX() / 16) - offsetX][static_cast<int>(ray.getY() / 16)][static_cast<int>(ray.getZ() / 16) - 1 - offsetZ-1].m_BlockIDs, false);

            }
            return;
        }
        ray.step(0.01f);
    }
}
