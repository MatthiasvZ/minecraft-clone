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

    chunks = new std::vector<std::vector<std::vector<Chunk>>>();
    chunkMeshes = new std::vector<std::vector<std::vector<ChunkMesh>>>();
    chunks->reserve(CHUNKRD + 1);
    chunkMeshes->reserve(CHUNKRD + 1);

    for (int ix {0}; ix < 16; ix++)
        for (int iy {0}; iy < 16; iy++)
            for (int iz {0}; iz < 16; iz++)
                voidChunkIDs[ix][iy][iz] = 0;

    // Generate/load the chunks.
    for (int ix {0}; ix < CHUNKRD; ix++)
    {
        chunks->push_back(std::vector<std::vector<Chunk>>());
        (*chunks)[ix].reserve(MAXHEIGHT);
        for (int iy {0}; iy < MAXHEIGHT; iy++)
        {
            (*chunks)[ix].push_back(std::vector<Chunk>());
            (*chunks)[ix][iy].reserve(CHUNKRD);
            for (int iz {0}; iz < CHUNKRD; iz++)
                (*chunks)[ix][iy].push_back(Chunk(ix + INIT_X_OFFSET / 16, iy, iz));
        }
    }

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
                (*chunkMeshes)[ix][iy].push_back(ChunkMesh((*chunks)[ix][iy][iz].m_BlockIDs, \
                            iy == MAXHEIGHT-1 ? voidChunkIDs : (*chunks)[ix][iy+1][iz].m_BlockIDs, \
                            iy == 0 ? voidChunkIDs : (*chunks)[ix][iy-1][iz].m_BlockIDs, \
                            ix == CHUNKRD-1 ? voidChunkIDs : (*chunks)[ix+1][iy][iz].m_BlockIDs, \
                            ix == 0 ? voidChunkIDs : (*chunks)[ix-1][iy][iz].m_BlockIDs, \
                            iz == CHUNKRD-1 ? voidChunkIDs : (*chunks)[ix][iy][iz+1].m_BlockIDs, \
                            iz == 0 ? voidChunkIDs : (*chunks)[ix][iy][iz-1].m_BlockIDs, \
                            ix + INIT_X_OFFSET / 16, iy, iz));
            }
        }
    }

    chunkLoader = new std::thread(&World::loadNewChunks, this);
}

void World::drawChunks(float deltaTime, PT::Input* inputs, bool mouseLocked)
{
    shader.setUniformMat4f("u_MVP", camera.update(deltaTime, *inputs));
    shader.bindShader();
    if (!mouseLocked)
        camera.setMouseSpeed(0.0f);
    else
        camera.setMouseSpeed(0.35f);

    if (!inputs->mouse1)
        mouseHold = false;
    if (inputs->mouse1 && !mouseHold)
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

                // very expensive
                //fprintf(stderr, "attempting draw. lock = %d, missing = %d, c = %d, %d, %d\n", lock, GLOsMissing, (*chunks)[ix][iy][iz].getPosition().x
                //         , (*chunks)[ix][iy][iz].getPosition().y, (*chunks)[ix][iy][iz].getPosition().z);

                PT::drawVA(*(*chunkMeshes)[ix][iy][iz].getVA(), *(*chunkMeshes)[ix][iy][iz].getIBO());
            }
}

World::~World()
{
    stop = true;
    chunkLoader->join();
    delete chunkLoader;
    delete atlas;
    delete chunks;
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
