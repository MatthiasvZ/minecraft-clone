#ifndef WORLD_H
#define WORLD_H

#define MAX_CHUNKS_V 8
#define RENDERDISTANCE 16
#define UNLOAD_DISTANCE 17
#define CHUNK_LOADING_INTERVAL 1 // load new chunks after n slots are freed

#include "game/Chunk.h"
#include "game/ChunkMesh.h"
#include "ChunkList.h"
#include "ChunkMeshList.h"
#include "game/Player.h"
#include "Petroleum.h"

#include <mutex>

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
        ChunkList<2 * UNLOAD_DISTANCE * std::min(2 * UNLOAD_DISTANCE, MAX_CHUNKS_V) * 2 * UNLOAD_DISTANCE> chunks;
        ChunkMeshList<2 * UNLOAD_DISTANCE * std::min(2 * UNLOAD_DISTANCE, MAX_CHUNKS_V) * 2 * UNLOAD_DISTANCE> chunkMeshes;

        static const unsigned int seed {1337};
        PT::SourcePackage srcpkg;
        PT::Shader shader;
        PT::Camera camera;

        void unloadChunks();
        void loadChunks();
        void generateMeshes();
        void updateChunks();
        std::mutex me_ChunkAccess;
        std::mutex me_GLDataAccess;
        bool glCleanUpRequired;
        bool stop;
        std::thread* chunkLoader;
        unsigned int GLOsMissing;
        void createBufferObjects();

        Player player;
        bool mouseHeld;
        void breakBlock();

        PT::Texture* atlas;
};

#endif // WORLD_H
