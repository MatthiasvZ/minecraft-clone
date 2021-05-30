#include "game/World.h"

#define INIT_X_OFFSET 0
//#define INIT_X_OFFSET 10'000
//#define INIT_X_OFFSET 100'000
//#define INIT_X_OFFSET 500'000
//#define INIT_X_OFFSET 1'000'000
//#define INIT_X_OFFSET 5'000'000
//#define INIT_X_OFFSET 10'000'000
//#define INIT_X_OFFSET 50'000'000
//#define INIT_X_OFFSET 100'000'000
//#define INIT_X_OFFSET 250'000'000
//#define INIT_X_OFFSET 500'000'000
//#define INIT_X_OFFSET 1'000'000'000


#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>
#include <unistd.h>
#if _WIN32
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
    : shader(PT::Shader(PT_SHADER_XYZBUV_M)), lock(0), stop(0), GLOsMissing(0), offsetX(INIT_X_OFFSET / 16), offsetZ(0), mouseHold(0)
{
    atlas = new PT::Texture(getDir() + "/assets/texAtlas.bmp", 0, GL_NEAREST, GL_NEAREST);

    camera.setClippingDistance(1000.0f);
    camera.setPosX(CHUNKRD * 8 + INIT_X_OFFSET);
    camera.setPosY(80);
    camera.setPosZ(CHUNKRD * 8);

    struct stat buffer;
    if (stat ("saves", &buffer) != 0)
        std::filesystem::create_directory("saves");

    chunkMeshes = new std::vector<std::vector<std::vector<ChunkMesh>>>();
    chunkMeshes->reserve(CHUNKRD + 1);

    for (int ix {0}; ix < 16; ix++)
        for (int iy {0}; iy < 16; iy++)
            for (int iz {0}; iz < 16; iz++)
                voidChunkIDs[ix][iy][iz] = 0;

    // Generate/load the chunks.
    for (int ix {0}; ix < CHUNKRD; ++ix)
        for (int iy {0}; iy < MAXHEIGHT; ++iy)
            for (int iz {0}; iz < CHUNKRD; ++iz)
                chunks.add(new Chunk(ix + INIT_X_OFFSET / 16, iy, iz));

    // Now that that's done, generate the chunk meshes.
    for (int ix {0}; ix < CHUNKRD; ix++)
    {
        chunkMeshes->push_back(std::vector<std::vector<ChunkMesh>>());
        (*chunkMeshes)[ix].reserve(MAXHEIGHT);

        for (int iy {0}; iy < MAXHEIGHT; iy++)
        {
            (*chunkMeshes)[ix].push_back(std::vector<ChunkMesh>());
            (*chunkMeshes)[ix][iy].reserve(CHUNKRD);

            for (int iz {0}; iz < CHUNKRD; iz++)
            {
                (*chunkMeshes)[ix][iy].push_back(ChunkMesh(chunks.at(Positioni(ix, iy, iz))->blockIDs,
                            iy == MAXHEIGHT-1 ? voidChunkIDs : chunks.at(Positioni(ix, iy + 1, iz))->blockIDs,
                            iy == 0 ? voidChunkIDs : chunks.at(Positioni(ix, iy - 1, iz))->blockIDs,
                            ix == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(ix + 1, iy, iz))->blockIDs,
                            ix == 0 ? voidChunkIDs : chunks.at(Positioni(ix - 1, iy, iz))->blockIDs,
                            iz == CHUNKRD-1 ? voidChunkIDs : chunks.at(Positioni(ix, iy, iz+1))->blockIDs,
                            iz == 0 ? voidChunkIDs : chunks.at(Positioni(ix, iy, iz - 1))->blockIDs,
                            ix + INIT_X_OFFSET / 16, iy, iz));
            }
        }
    }

    chunkLoader = new std::thread(&World::loadNewChunks, this);
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

    if (!window.getMouseButton(GLFW_MOUSE_BUTTON_1))
        mouseHold = false;
    if (window.getMouseButton(GLFW_MOUSE_BUTTON_1) && !mouseHold)
    {
        breakBlock();
        mouseHold = true;
    }

    // for (int stresstest {0}; stresstest < 20; stresstest++)
    for (long unsigned int ix {0}; ix < CHUNKRD; ix++)
        for (long unsigned int iy {0}; iy < MAXHEIGHT; iy++)
            for (long unsigned int iz {0}; iz < CHUNKRD; iz++)
            {
                if ((*chunkMeshes)[ix][iy][iz].isEmpty())
                    continue;
                while (lock || GLOsMissing)
                    if (GLOsMissing)
                        createBufferObjects();

                PT::drawVA(*(*chunkMeshes)[ix][iy][iz].getVA(), *(*chunkMeshes)[ix][iy][iz].getIBO());
            }
}

World::~World()
{
    stop = true;
    chunkLoader->join();
    delete chunkLoader;
    delete atlas;
    for (long unsigned int ix {0}; ix < chunkMeshes->size(); ix++)
        for (long unsigned int iy {0}; iy < (*chunkMeshes)[ix].size(); iy++)
            for (long unsigned int iz {0}; iz < (*chunkMeshes)[ix][iy].size(); iz++)
                (*chunkMeshes)[ix][iy][iz].freeMemory();
    delete chunkMeshes;
    #ifdef DEBUG
        ChunkMesh::printTimeStats();
    #endif // DEBUG
    printf("Saving chunks...\n");
}
