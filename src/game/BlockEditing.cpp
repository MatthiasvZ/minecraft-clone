#include "World.h"
#include "Ray.h"

#define INT(x) static_cast<int>(x)

void World::breakBlock()
{

    Ray ray(camera.getPitch(), camera.getYaw(), camera.getPosX(), camera.getPosY(), camera.getPosZ());
    for (int i {0}; i < 600; ++i)
    {
        if (INT(ray.getX()) > 16 * chunks.at(Positioni(CHUNKRD - 1, MAXHEIGHT - 1, CHUNKRD - 1))->getPos().x + 15 ||
            INT(ray.getX()) < 16 * chunks.at(Positioni(0, 0, 0))->getPos().x ||
            INT(ray.getY()) > 16 * chunks.at(Positioni(CHUNKRD - 1, MAXHEIGHT - 1, CHUNKRD - 1))->getPos().y + 15 ||
            INT(ray.getY()) < 16 * chunks.at(Positioni(0, 0, 0))->getPos().y ||
            INT(ray.getZ()) > 16 * chunks.at(Positioni(CHUNKRD - 1, MAXHEIGHT - 1, CHUNKRD - 1))->getPos().z + 15 ||
            INT(ray.getZ()) < 16 * chunks.at(Positioni(0, 0, 0))->getPos().z)
            break;

        if (chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))
            ->blockIDs[INT(ray.getX()) % 16][INT(ray.getY()) % 16][INT(ray.getZ()) % 16] != BLOCK_AIR)
        {
            #ifdef DEBUG
            fprintf(stderr, "Hit block of type %d!\n", chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))
                    ->blockIDs[INT(ray.getX()) % 16][INT(ray.getY()) % 16][INT(ray.getZ()) % 16]);
            #endif // DEBUG

            // Replace the block with air
            chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))
                     ->blockIDs[INT(ray.getX()) % 16][INT(ray.getY()) % 16][INT(ray.getZ()) % 16] = BLOCK_AIR;

            for (int ix {0}; ix < 16; ix++)
                for (int iy {0}; iy < 16; iy++)
                    for (int iz {0}; iz < 16; iz++)
                        voidChunkIDs[ix][iy][iz] = 0;


            // Update the chunk
            (*chunkMeshes)[INT(ray.getX() / 16) - offsetX][INT(ray.getY() / 16)][INT(ray.getZ() / 16) - offsetZ]
                            .updateChunkMesh(chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                            INT(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16)+1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                            INT(ray.getY() / 16) == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16)-1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                            INT(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX+1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                            INT(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX-1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                            INT(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ+1))->blockIDs,
                            INT(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ-1))->blockIDs, false);


            // Update neighbouring chunks if necessairy
            if (INT(ray.getY() / 16) < MAXHEIGHT - 1) // above
            {
                if (INT(ray.getY()) % 16 == 15 &&
                    chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) + 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs
                    [INT(ray.getX()) % 16][0][INT(ray.getZ()) % 16] != BLOCK_AIR)
                {
                    (*chunkMeshes)[INT(ray.getX() / 16) - offsetX][INT(ray.getY() / 16) + 1][INT(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh(chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) + 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) + 1 == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) + 1+1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) + 1 == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) + 1-1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX+1, INT(ray.getY() / 16) + 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX-1, INT(ray.getY() / 16) + 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) + 1, INT(ray.getZ() / 16) - offsetZ+1))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) + 1, INT(ray.getZ() / 16) - offsetZ-1))->blockIDs, false);
                }
            }
            if (INT(ray.getY() / 16) > 0) // below
            {
                if (INT(ray.getY()) % 16 == 0 &&
                    chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) - 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs
                    [INT(ray.getX()) % 16][15][INT(ray.getZ()) % 16] != BLOCK_AIR)
                {
                    (*chunkMeshes)[INT(ray.getX() / 16) - offsetX][INT(ray.getY() / 16) - 1][INT(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh(chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) - 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) - 1 == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) - 1+1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) - 1 == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) - 1-1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX+1, INT(ray.getY() / 16) - 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX-1, INT(ray.getY() / 16) - 1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) - 1, INT(ray.getZ() / 16) - offsetZ+1))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16) - 1, INT(ray.getZ() / 16) - offsetZ-1))->blockIDs, false);
                }
            }
            if (INT(ray.getX() / 16) < CHUNKRD - 1) // to the right
            {
                if (INT(ray.getX()) % 16 == 15 &&
                    chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs
                    [0][INT(ray.getY()) % 16][INT(ray.getZ()) % 16] != BLOCK_AIR)
                {
                    (*chunkMeshes)[INT(ray.getX() / 16) + 1 - offsetX][INT(ray.getY() / 16)][INT(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh(chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX, INT(ray.getY() / 16)+1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX, INT(ray.getY() / 16)-1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) + 1 - offsetX == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX+1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) + 1 - offsetX == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX-1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ+1))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) + 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ-1))->blockIDs, false);
                }
            }
            if (INT(ray.getX() / 16) > 0) // to the left
            {
                if (INT(ray.getX()) % 16 == 0 &&
                    chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs
                    [15][INT(ray.getY()) % 16][INT(ray.getZ()) % 16] != BLOCK_AIR)
                {
                    (*chunkMeshes)[INT(ray.getX() / 16) - 1 - offsetX][INT(ray.getY() / 16)][INT(ray.getZ() / 16) - offsetZ]
                                    .updateChunkMesh(chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX, INT(ray.getY() / 16)+1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX, INT(ray.getY() / 16)-1, INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - 1 - offsetX == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX+1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - 1 - offsetX == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX-1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ+1))->blockIDs,
                                    INT(ray.getZ() / 16) - offsetZ == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - 1 - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - offsetZ-1))->blockIDs, false);
                }
            }
            if (INT(ray.getZ() / 16) < CHUNKRD - 1) // to the front
            {
                if (INT(ray.getZ()) % 16 == 15 &&
                    chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) + 1 - offsetZ))->blockIDs
                    [INT(ray.getX()) % 16][INT(ray.getY()) % 16][0] != BLOCK_AIR)
                {
                    (*chunkMeshes)[INT(ray.getX() / 16) - offsetX][INT(ray.getY() / 16)][INT(ray.getZ() / 16) + 1 - offsetZ]
                                    .updateChunkMesh(chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) + 1 - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16)+1, INT(ray.getZ() / 16) + 1 - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16)-1, INT(ray.getZ() / 16) + 1 - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX+1, INT(ray.getY() / 16), INT(ray.getZ() / 16) + 1 - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX-1, INT(ray.getY() / 16), INT(ray.getZ() / 16) + 1 - offsetZ))->blockIDs,
                                    INT(ray.getZ() / 16) + 1 - offsetZ == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) + 1 - offsetZ+1))->blockIDs,
                                    INT(ray.getZ() / 16) + 1 - offsetZ == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) + 1 - offsetZ-1))->blockIDs, false);
                }
            }
            if (INT(ray.getZ() / 16) > 0) // to the back
            {
                if (INT(ray.getZ()) % 16 == 0 &&
                    chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - 1 - offsetZ))->blockIDs
                    [INT(ray.getX()) % 16][INT(ray.getY()) % 16][15] != BLOCK_AIR)
                {
                    (*chunkMeshes)[INT(ray.getX() / 16) - offsetX][INT(ray.getY() / 16)][INT(ray.getZ() / 16) - 1 - offsetZ]
                                    .updateChunkMesh(chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - 1 - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16)+1, INT(ray.getZ() / 16) - 1 - offsetZ))->blockIDs,
                                    INT(ray.getY() / 16) == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16)-1, INT(ray.getZ() / 16) - 1 - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX+1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - 1 - offsetZ))->blockIDs,
                                    INT(ray.getX() / 16) - offsetX == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX-1, INT(ray.getY() / 16), INT(ray.getZ() / 16) - 1 - offsetZ))->blockIDs,
                                    INT(ray.getZ() / 16) - 1 - offsetZ == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - 1 - offsetZ+1))->blockIDs,
                                    INT(ray.getZ() / 16) - 1 - offsetZ == 0 ? voidChunkIDs : chunks.at(Positioni(INT(ray.getX() / 16) - offsetX, INT(ray.getY() / 16), INT(ray.getZ() / 16) - 1 - offsetZ-1))->blockIDs, false);
                }
            }
            return;
        }
        ray.step(0.01f);
    }
}
