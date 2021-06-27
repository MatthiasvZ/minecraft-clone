#include "game/World.h"

#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>
#include <unistd.h>
#ifdef _WIN32
    #include <libloaderapi.h>
#endif // _WIN32

std::string getDir()
{
    char result[ PATH_MAX ];
    #if __unix__
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    #elif _WIN32
        ssize_t count = GetModuleFileName(NULL, result, PATH_MAX);
    #else
    #error Unsupported OS
    #endif // __unix__

    std::string sresult(result, (count > 0) ? count : 0);
    sresult = std::filesystem::path(sresult).parent_path().parent_path().parent_path().string();
    return sresult;
}

World::World()
    : shader(PT::Shader(PT_SHADER_XYZBUV_M)), glCleanUpRequired(false), stop(false), GLOsMissing(false), mouseHeld(0)
{
    atlas = new PT::Texture(getDir() + "/assets/texAtlas.bmp", 0, GL_NEAREST, GL_NEAREST);

    camera.setClippingDistance(1000.0f);
    camera.setPosX(CHUNKRD * 8);
    camera.setPosY(80);
    camera.setPosZ(CHUNKRD * 8);

    struct stat buffer;
    if (stat ("saves", &buffer) != 0)
        std::filesystem::create_directory("saves");

    // TODO: This is stupid
    for (int ix {0}; ix < 16; ix++)
        for (int iy {0}; iy < 16; iy++)
            for (int iz {0}; iz < 16; iz++)
                voidChunkIDs[ix][iy][iz] = 0;

    chunkLoader = new std::thread(&World::updateChunks, this);
}

void World::drawChunks(float deltaTime, const PT::Window& window, bool mouseLocked)
{
    shader.setMat(camera.update(deltaTime, window));
    shader.setTexSlot(0);
    shader.bindShader();
    if (!mouseLocked)
        camera.setMouseSpeed(0.0f);
    else
        camera.setMouseSpeed(0.35f);

    camera.setSpeedH(100.0f);

    if (!window.getMouseButton(GLFW_MOUSE_BUTTON_1))
        mouseHeld = false;
    if (window.getMouseButton(GLFW_MOUSE_BUTTON_1) && !mouseHeld)
    {
        breakBlock();
        mouseHeld = true;
    }

    me_GLDataAccess.lock();
    if (GLOsMissing)
        createBufferObjects();

    // for (int stresstest {0}; stresstest < 20; stresstest++)
    for (size_t i {0}; i < chunkMeshes.size(); ++i)
    {
        if (chunkMeshes[i] == nullptr)
            continue;
        if (chunkMeshes[i]->isEmpty())
            continue;

        PT::drawVA(*chunkMeshes[i]->getVA(), *chunkMeshes[i]->getIBO());
    }



    if (glCleanUpRequired == true)
    {
        me_ChunkAccess.lock();
        glCleanUpRequired = false;
        for (size_t i {0}; i < chunkMeshes.size(); ++i)
        {
            if (chunkMeshes[i] != nullptr)
                if (chunkMeshes[i]->flaggedForDeletion)
                {
                    Chunk* chunk = chunks.at(chunkMeshes[i]->getPos());
                    if (chunk != nullptr)
                        chunk->meshGenerated = false;
                    chunkMeshes.remove(i);
                }
        }
        me_ChunkAccess.unlock();
    }
    me_GLDataAccess.unlock();
}

World::~World()
{
    stop = true;
    chunkLoader->join();
    delete chunkLoader;
    delete atlas;
    #ifdef DEBUG
        ChunkMesh::printTimeStats();
    #endif // DEBUG
    printf("Saving chunks...\n");
}
