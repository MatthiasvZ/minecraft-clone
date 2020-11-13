#include "game/World.h"

#define CHUNKRD 16     // 256 blocks render distance
#define MAXHEIGHT 8    // 128 block height max.

#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>
#include <unistd.h>

std::vector<std::vector<std::vector<Chunk>>>* chunks;
std::vector<std::vector<std::vector<ChunkMesh>>>* chunkMeshes;
PT::Texture* atlas;

std::string getDir()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    std::string sresult( result, (count > 0) ? count : 0 );
    #ifdef DEBUG
        sresult = (std::string)std::filesystem::path(sresult).parent_path().parent_path().parent_path();
    #else
        sresult = (std::string)std::filesystem::path(sresult).parent_path().parent_path();
    #endif //DEBUG
    return sresult;
}

World::World()
    : shader(PT::Shader(PT_SHADER_XYZBUV_M))
{
    atlas = new PT::Texture(getDir() + "/assets/texAtlas.bmp", 0, GL_NEAREST, GL_NEAREST);
    camera.setDrawDistance(1000.0f);

    struct stat buffer;
    if (stat ("saves", &buffer) != 0)
        mkdir("saves", 0755);

    chunks = new std::vector<std::vector<std::vector<Chunk>>>();
    chunkMeshes = new std::vector<std::vector<std::vector<ChunkMesh>>>();
    chunks->reserve(CHUNKRD);
    chunkMeshes->reserve(CHUNKRD);

    unsigned char voidChunkIDs[16][16][16];
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
                (*chunks)[ix][iy].push_back(Chunk(ix, iy, iz));
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
                            ix, iy, iz));
            }
        }
    }
}

void World::drawChunks(float deltaTime, PT::Input* inputs)
{
    shader.setUniformMat4f("u_MVP", camera.update(deltaTime, *inputs));
    shader.bindShader();

    // for (int stresstest {0}; stresstest < 20; stresstest++)
    for (int ix {0}; ix < CHUNKRD; ix++)
        for (int iy {0}; iy < MAXHEIGHT; iy++)
            for (int iz {0}; iz < CHUNKRD; iz++)
            {
                if ((*chunkMeshes)[ix][iy][iz].isEmpty())
                    continue;
                PT::drawVA(*(*chunkMeshes)[ix][iy][iz].getVA(), *(*chunkMeshes)[ix][iy][iz].getIBO());
            }
}

World::~World()
{
    delete atlas;
    delete chunks;
    for (int ix {0}; ix < CHUNKRD; ix++)
        for (int iy {0}; iy < MAXHEIGHT; iy++)
            for (int iz {0}; iz < CHUNKRD; iz++)
                (*chunkMeshes)[ix][iy][iz].freeMemory();
    delete chunkMeshes;
    #ifdef DEBUG
        ChunkMesh::printTimeStats();
    #endif // DEBUG
    printf("Saving chunks...\n");
}
