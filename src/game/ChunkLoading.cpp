#include "game/World.h"
#include <unistd.h>

void World::loadNewChunks()
{
    while(!stop)
    {
        /*
        fprintf(stderr, "x = %f\n", camera.getPosX());
        fprintf(stderr, "y = %f\n", camera.getPosY());
        fprintf(stderr, "z = %f\n\n", camera.getPosZ());
        */

        me_ChunkAccess.lock();

        // Unload distant chunks
        for (size_t i {0}; i < chunks.size(); ++i)
        {
            if (chunks[i] == nullptr)
                continue;

            const Positioni& cPos = chunks[i]->getPos();
            const float x = static_cast<float>(cPos.x) * 16.0f;
            const float z = static_cast<float>(cPos.z) * 16.0f;
            const float d = sqrt((x - camera.getPosX()) * (x - camera.getPosX()) + (z - camera.getPosZ()) * (z - camera.getPosZ()));

            if (d > RENDERDISTANCE)
            {
                // Flag affected meshes
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
                lockMeshGen = true;

                chunks.remove(i);
            }
        }

        // Load new chunks, if there's space
        for (size_t i {0}; i < chunks.size(); ++i)
        {

        }

        me_ChunkAccess.unlock();
        me_GLDataAccess.lock();
        me_ChunkAccess.lock();

        for (size_t i {0}; i < chunks.size(); ++i)
        {
            if (chunks[i] == nullptr)
            continue;

            if (chunks[i]->meshGenerated == false)
            {
                ChunkBall cBall;
                cBall.blockIDs = &chunks[i]->blockIDs;
                Positioni cPos = chunks[i]->getPos();

                Chunk* cAbove = chunks.at(Positioni(cPos.x, cPos.y + 1, cPos.z));
                cBall.blockIDsAbove   = cAbove   == nullptr ? &voidChunkIDs : &cAbove->blockIDs;
                Chunk* cBelow = chunks.at(Positioni(cPos.x, cPos.y - 1, cPos.z));
                cBall.blockIDsBelow   = cBelow   == nullptr ? &voidChunkIDs : &cBelow->blockIDs;
                Chunk* cLeft = chunks.at(Positioni(cPos.x + 1, cPos.y, cPos.z));
                cBall.blockIDsLeft    = cLeft    == nullptr ? &voidChunkIDs : &cLeft->blockIDs;
                Chunk* cRight = chunks.at(Positioni(cPos.x - 1, cPos.y, cPos.z));
                cBall.blockIDsRight   = cRight   == nullptr ? &voidChunkIDs : &cRight->blockIDs;
                Chunk* cInFront = chunks.at(Positioni(cPos.x, cPos.y, cPos.z + 1));
                cBall.blockIDsInFront = cInFront == nullptr ? &voidChunkIDs : &cInFront->blockIDs;
                Chunk* cBehind = chunks.at(Positioni(cPos.x, cPos.y, cPos.z - 1));
                cBall.blockIDsBehind  = cBehind  == nullptr ? &voidChunkIDs : &cBehind->blockIDs;

                chunkMeshes.add(new ChunkMesh(cBall, cPos.x, cPos.y, cPos.z));

                chunks[i]->meshGenerated = true;
                GLOsMissing  = true;
            }
        }
        me_ChunkAccess.unlock();
        me_GLDataAccess.unlock();
    }
}


void World::createBufferObjects()
{
    for (size_t i {0}; i < chunkMeshes.size(); ++i)
    {
        if (chunkMeshes[i] == nullptr)
            continue;

        if (chunkMeshes[i]->getGLOsMissing())
            chunkMeshes[i]->createGLOs();
    }
    GLOsMissing = false;
}
