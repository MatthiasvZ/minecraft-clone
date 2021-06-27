#include "game/World.h"
#include <unistd.h>

void World::unloadChunks()
{
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

            glCleanUpRequired = true;
            chunks.remove(i);
        }
    }
}

void World::loadChunks()
{
    size_t freeChunkSlots {0};
    for (size_t i {0}; i < chunks.size(); ++i)
        if (chunks[i] == nullptr)
            ++freeChunkSlots;

    if (freeChunkSlots < CHUNK_LOADING_INTERVAL)
        return;
    // std::cerr << "free slots = " << freeChunkSlots << std::endl;

    const int pCX = camera.getPosX() / 16.0f;
    const int pCY = camera.getPosY() / 16.0f;
    const int pCZ = camera.getPosZ() / 16.0f;
    const Positioni playerPos {Positioni(pCX, pCY, pCZ)};

    std::vector<Positioni> chunkPositions;
    chunkPositions.reserve(chunks.size());

    for (int x {-CHUNKRD / 2}; x < CHUNKRD / 2; ++x)
        for (int y {0}; y < MAXHEIGHT; ++y)
            for (int z {-CHUNKRD / 2}; z < CHUNKRD / 2; ++z)
                if (chunks.at(Positioni(pCX + x, y, pCZ + z)) == nullptr)
                    chunkPositions.push_back(Positioni(pCX + x, y, pCZ + z));

    if (chunkPositions.size() == 0)
        return;
    // std::cerr << "loadable chunks = " << chunkPositions.size() << std::endl;

    // Sort
    float* distances = new float[chunkPositions.size()];
    for (size_t i {0}; i < chunkPositions.size(); ++i)
        distances[i] = chunkPositions[i].distanceTo(playerPos);

    bool unchanged {false};
    while (!unchanged)
    {
        unchanged = true;
        for (size_t i {0}; i < chunkPositions.size() - 1; ++i)
        {
            if (distances[i] > distances[i + 1] + 0.01f)
            {
                unchanged = false;
                Positioni tempPos  = chunkPositions[i];
                float tempDistance = distances[i];
                chunkPositions[i] = chunkPositions[i + 1];
                distances[i]      = distances[i + 1];
                chunkPositions[i + 1] = tempPos;
                distances[i + 1]      = tempDistance;
            }
        }
    }
    delete distances;

    #pragma omp parallel for num_threads(2)
    for (size_t i = 0; i < freeChunkSlots; ++i)
        chunks.add(new Chunk(chunkPositions[i]));
}

void World::generateMeshes()
{
    int totalMeshesToGenerate {0};
    for (size_t i {0}; i < chunks.size(); ++i)
        if (chunks[i] != nullptr)
            totalMeshesToGenerate += chunks[i]->meshGenerated == false;
    #pragma omp parallel for if (totalMeshesToGenerate > 128)
    for (size_t i = 0; i < chunks.size(); ++i)
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

            me_GLDataAccess.lock();
            chunkMeshes.add(new ChunkMesh(cBall, cPos.x, cPos.y, cPos.z));
            GLOsMissing  = true;
            me_GLDataAccess.unlock();

            me_ChunkAccess.lock();
            chunks[i]->meshGenerated = true;
            me_ChunkAccess.unlock();
        }
    }
}

void World::updateChunks()
{
    while(!stop)
    {
        // Unload distant chunks
        me_ChunkAccess.lock();
        unloadChunks();
        me_ChunkAccess.unlock();

        // Generate chunk meshes
        // Expects chunks to be read-only, might become a problem
        generateMeshes();

        // Load new chunks, if there's space
        me_ChunkAccess.lock();
        loadChunks();
        me_ChunkAccess.unlock();
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
