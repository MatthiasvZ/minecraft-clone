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
std::vector<Chunk> chunks;
std::vector<ChunkMesh> chunkMeshes;
std::vector<VertexArray> vaos;
std::vector<VertexBuffer> vbos;
std::vector<IndexBuffer> ibos;
VertexBufferLayout layout;

World::World()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    chunks.reserve(5);
    chunkMeshes.reserve(5);
    vaos.reserve(5);
    vbos.reserve(5);
    ibos.reserve(5);

    layout.push(GL_FLOAT, 3); // positions x,y,z
    layout.push(GL_FLOAT, 2); // tex coords u,v

    for (int ix {0}; ix < 5; ix++)
    {
        chunks.push_back(Chunk(ix, 0 , 0));
        chunkMeshes.push_back(ChunkMesh(chunks.at(ix).m_BlockIDs, ix, 0, 0));
        vaos.push_back(VertexArray());
        vaos.at(ix).genArray();
        vbos.push_back(VertexBuffer());
        vbos.at(ix).addData(chunkMeshes.at(ix).vertices.data(), chunkMeshes.at(ix).vertices.size() * sizeof(float));
        vaos.at(ix).addBuffer(vbos.at(ix), layout);
        ibos.push_back(IndexBuffer());
        ibos.at(ix).addData(chunkMeshes.at(ix).indices.data(), chunkMeshes.at(ix).indices.size());
    }
}
void World::drawChunks()
{
    renderer.clear();
    for (int ix {0}; ix < 5; ix++)
        renderer.drawVA(vaos.at(ix), vbos.at(ix), ibos.at(ix));
    renderer.countfps();
}

World::~World()
{
    //dtor
}
