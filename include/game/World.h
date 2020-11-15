#ifndef WORLD_H
#define WORLD_H

#define CHUNKRD 16     // 256 blocks render distance
#define MAXHEIGHT 8    // 128 block height max.

#include "game/Chunk.h"
#include "game/ChunkMesh.h"
#include "Petroleum.h"

inline std::vector<std::vector<std::vector<Chunk>>>* chunks;
inline std::vector<std::vector<std::vector<ChunkMesh>>>* chunkMeshes;
inline PT::Texture* atlas;

class World
{
    public:
        World();
        void drawChunks(float deltaTime, PT::Input* inputs);
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
};

#endif // WORLD_H
