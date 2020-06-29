#include "game/World.h"

#include "game/Chunk.h"
#include "game/ChunkMesh.h"
#include "gl/VertexArray.h"
#include "gl/VertexBuffer.h"
#include "gl/VertexBufferLayout.h"
#include "gl/IndexBuffer.h"
#include "gl/Renderer.h"

#include <vector>
#include <iostream>


Renderer renderer;
std::vector<std::vector<std::vector<Chunk> > > chunks;
std::vector<std::vector<std::vector<ChunkMesh> > > chunkMeshes;
std::vector<std::vector<std::vector<VertexArray> > > vaos;
std::vector<std::vector<std::vector<VertexBuffer> > > vbos;
std::vector<std::vector<std::vector<IndexBuffer> > > ibos;
VertexBufferLayout layout;

World::World()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    chunks.reserve(10);
    chunkMeshes.reserve(10);
    vaos.reserve(10);
    vbos.reserve(10);
    ibos.reserve(10);

    layout.push(GL_FLOAT, 3); // positions x,y,z
    layout.push(GL_FLOAT, 2); // tex coords u,v

    for (int ix {0}; ix < 10; ix++)
    {
        chunks.push_back(std::vector<std::vector<Chunk> >());
        chunkMeshes.push_back(std::vector<std::vector<ChunkMesh> >());
        vaos.push_back(std::vector<std::vector<VertexArray> >());
        vbos.push_back(std::vector<std::vector<VertexBuffer> >());
        ibos.push_back(std::vector<std::vector<IndexBuffer> >());

        chunks.at(ix).reserve(10);
        chunkMeshes.at(ix).reserve(10);
        vaos.at(ix).reserve(10);
        vbos.at(ix).reserve(10);
        ibos.at(ix).reserve(10);

        for (int iy {0}; iy < 10; iy++)
        {
            chunks.at(ix).push_back(std::vector<Chunk>());
            chunkMeshes.at(ix).push_back(std::vector<ChunkMesh>());
            vaos.at(ix).push_back(std::vector<VertexArray>());
            vbos.at(ix).push_back(std::vector<VertexBuffer>());
            ibos.at(ix).push_back(std::vector<IndexBuffer>());

            chunks.at(ix).at(iy).reserve(10);
            chunkMeshes.at(ix).at(iy).reserve(10);
            vaos.at(ix).at(iy).reserve(10);
            vbos.at(ix).at(iy).reserve(10);
            ibos.at(ix).at(iy).reserve(10);

            for (int iz {0}; iz < 10; iz++)
            {
                chunks.at(ix).at(iy).push_back(Chunk(ix, iy, iz));
                chunkMeshes.at(ix).at(iy).push_back(ChunkMesh(chunks.at(ix).at(iy).at(iz).m_BlockIDs, ix, iy, iz));
                vaos.at(ix).at(iy).push_back(VertexArray());
                vaos.at(ix).at(iy).at(iz).genArray();
                vbos.at(ix).at(iy).push_back(VertexBuffer());
                vbos.at(ix).at(iy).at(iz).addData(chunkMeshes.at(ix).at(iy).at(iz).vertices.data(), chunkMeshes.at(ix).at(iy).at(iz).vertices.size() * sizeof(float));
                vaos.at(ix).at(iy).at(iz).addBuffer(vbos.at(ix).at(iy).at(iz), layout);
                ibos.at(ix).at(iy).push_back(IndexBuffer());
                ibos.at(ix).at(iy).at(iz).addData(chunkMeshes.at(ix).at(iy).at(iz).indices.data(), chunkMeshes.at(ix).at(iy).at(iz).indices.size());
            }
        }
    }
}
void World::drawChunks()
{
    renderer.clear();
    //for (int stresstest {0}; stresstest < 20; stresstest++)
    for (int ix {0}; ix < 10; ix++)
        for (int iy {0}; iy < 10; iy++)
            for (int iz {0}; iz < 10; iz++)
            renderer.drawVA(vaos.at(ix).at(iy).at(iz), vbos.at(ix).at(iy).at(iz), ibos.at(ix).at(iy).at(iz));
}

World::~World()
{
    //dtor
}
