#ifndef WORLD_H
#define WORLD_H

#define CHUNKRD 16     // 256 blocks render distance
#define MAXHEIGHT 8    // 128 block height max.

#include "game/Chunk.h"
#include "game/ChunkMesh.h"
#include "game/Player.h"
#include "Petroleum.h"

#if __unix__
#include <thread>
#elif _WIN32
#include "vendor/mingw.thread.h"
#else
#error Unsupported OS
#endif // __unix__

#define PLUS_X 1
#define MINUS_X 2
#define PLUS_Z 3
#define MINUS_Z 4

inline std::vector<std::vector<std::vector<Chunk>>>* chunks;
inline std::vector<std::vector<std::vector<ChunkMesh>>>* chunkMeshes;
inline PT::Texture* atlas;

class World
{
    public:
        World();
        void drawChunks(float deltaTime, PT::Input* inputs, bool mouseLocked);
        constexpr static unsigned int getSeed() {return m_Seed;}
        ~World();
    protected:

    private:
        static const unsigned int m_Seed {1337};
        PT::SourcePackage srcpkg;
        PT::Shader shader;
        PT::Camera camera;
        unsigned char voidChunkIDs[16][16][16];

        void loadNewChunks();
        bool lock;
        bool stop;
        std::thread* chunkLoader;
        unsigned int GLOsMissing;
        void createBufferObjects();
        int offsetX;
        int offsetZ;

        Player player;
        bool mouseHold;
        void breakBlock();
};

#endif // WORLD_H
