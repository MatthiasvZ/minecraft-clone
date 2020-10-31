#ifndef WORLD_H
#define WORLD_H

#include "game/Chunk.h"
#include "game/ChunkMesh.h"
#include "Petroleum.h"

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
};

#endif // WORLD_H
