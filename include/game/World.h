#ifndef WORLD_H
#define WORLD_H

#define CHUNKRD 16     // 256 blocks render distance
#define MAXHEIGHT 8    // 128 block height max.

#include "game/Chunk.h"
#include "game/ChunkMesh.h"
#include "ChunkList.h"
#include "ChunkMeshList.h"
#include "game/Player.h"
#include "Petroleum.h"

#ifdef __unix__
#include <thread>
#elif defined _WIN32
#include "vendor/mingw.thread.h"
#else
#error Unsupported OS
#endif // __unix__


class World
{
    public:
        World();
        void drawChunks(float deltaTime, const PT::Window& window, bool mouseLocked);
        constexpr static unsigned int getSeed() {return seed;}
        ~World();
    protected:

    private:
        ChunkList<CHUNKRD * CHUNKRD * MAXHEIGHT> chunks;
        ChunkMeshList<CHUNKRD * CHUNKRD * MAXHEIGHT> chunkMeshes;

        static const unsigned int seed {1337};
        PT::SourcePackage srcpkg;
        PT::Shader shader;
        PT::Camera camera;

        void loadNewChunks();
        bool lockRenderer;
        bool stop;
        std::thread* chunkLoader;
        unsigned int GLOsMissing;
        void createBufferObjects();

        Player player;
        bool mouseHold;
        void breakBlock();

        PT::Texture* atlas;
};

#endif // WORLD_H
