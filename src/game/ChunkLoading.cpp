#include "game/World.h"
#include <chrono>

void World::loadNewChunks()
{
    while(!stop)
    {
        /*
        fprintf(stderr, "x = %f\n", camera.getPosX());
        fprintf(stderr, "y = %f\n", camera.getPosY());
        fprintf(stderr, "z = %f\n\n", camera.getPosZ());
        */

        if (GLOsMissing)
            continue;

        for (size_t i {0}; i < chunks.size(); ++i)
        {
            if (chunks[i] == nullptr)
            continue;

            if (chunks[i]->meshGenerated == false)
            {
                lockRenderer = true;

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
                Chunk* cInFront = chunks.at(Positioni(cPos.x, cPos.y, cPos.z+1));
                cBall.blockIDsInFront = cInFront == nullptr ? &voidChunkIDs : &cInFront->blockIDs;
                Chunk* cBehind = chunks.at(Positioni(cPos.x, cPos.y, cPos.z - 1));
                cBall.blockIDsBehind  = cBehind  == nullptr ? &voidChunkIDs : &cBehind->blockIDs;

                chunkMeshes.add(new ChunkMesh(cBall, cPos.x, cPos.y, cPos.z, true));

                chunks[i]->meshGenerated = true;
                GLOsMissing  = true;
                lockRenderer = false;
            }
        }
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
