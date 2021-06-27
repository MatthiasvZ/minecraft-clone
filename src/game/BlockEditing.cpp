#include "World.h"
#include "Ray.h"

#define INT(x) static_cast<int>(x)

void World::breakBlock()
{
    Ray ray(camera.getPitch(), camera.getYaw(), camera.getPosX(), camera.getPosY(), camera.getPosZ());
    for (int i {0}; i < 600; ++i)
    {
        Chunk* chunk = chunks.at(Positioni(INT(ray.getX() / 16), INT(ray.getY() / 16), INT(ray.getZ() / 16)));
        if (chunk == nullptr)
            continue;

        if (chunk->blockIDs[INT(ray.getX()) % 16][INT(ray.getY()) % 16][INT(ray.getZ()) % 16] != BLOCK_AIR)
        {
            #ifdef DEBUG
            fprintf(stderr, "Hit block of type %d!\n", chunk->blockIDs[INT(ray.getX()) % 16][INT(ray.getY()) % 16][INT(ray.getZ()) % 16]);
            #endif // DEBUG

            // Replace the block with air
            chunk->blockIDs[INT(ray.getX()) % 16][INT(ray.getY()) % 16][INT(ray.getZ()) % 16] = BLOCK_AIR;

            Positioni cPos = chunk->getPos();

            // Flag all affected meshes for recreation
            ChunkMesh* cmCentre = chunkMeshes.at(cPos);
            if (cmCentre != nullptr)
                cmCentre->flaggedForDeletion = true;
            ChunkMesh* cmAbove = chunkMeshes.at(Positioni(cPos.x, cPos.y + 1, cPos.z));
            if (cmAbove != nullptr)
                cmAbove->flaggedForDeletion = true;
            ChunkMesh* cmBelow = chunkMeshes.at(Positioni(cPos.x, cPos.y - 1, cPos.z));
            if (cmBelow != nullptr)
                cmBelow->flaggedForDeletion = true;
            ChunkMesh* cmLeft = chunkMeshes.at(Positioni(cPos.x + 1, cPos.y, cPos.z));
            if (cmLeft != nullptr)
                cmLeft->flaggedForDeletion = true;
            ChunkMesh* cmRight = chunkMeshes.at(Positioni(cPos.x - 1, cPos.y, cPos.z));
            if (cmRight != nullptr)
                cmRight->flaggedForDeletion = true;
            ChunkMesh* cmInFront = chunkMeshes.at(Positioni(cPos.x, cPos.y, cPos.z + 1));
            if (cmInFront != nullptr)
                cmInFront->flaggedForDeletion = true;
            ChunkMesh* cmBehind = chunkMeshes.at(Positioni(cPos.x, cPos.y, cPos.z - 1));
            if (cmBehind != nullptr)
                cmBehind->flaggedForDeletion = true;
            glCleanUpRequired = true;

            return;
        }
        ray.step(0.01f);
    }
}
