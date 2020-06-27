#include "World.h"

#include "Chunk.h"
#include "ChunkMesh.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Renderer.h"


Renderer renderer;
Chunk testChunk(0, 0, 0);
ChunkMesh testChunkMesh(testChunk.m_BlockIDs, 0, 0, 0);
VertexArray vao;
VertexBuffer vbo;
IndexBuffer ibo;
VertexBufferLayout layout;


World::World()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    vao.genArray();
    vbo.addData(testChunkMesh.vertices.data(), testChunkMesh.vertices.size() * sizeof(float));
    layout.push(GL_FLOAT, 3); // positions x,y,z
    layout.push(GL_FLOAT, 2); // tex coords u,v
    ibo.addData(testChunkMesh.indices.data(), testChunkMesh.indices.size());
    vao.addBuffer(vbo, layout);
}
void World::drawChunks(const Shader& shader)
{

    renderer.clear();
    renderer.drawVA(vao, vbo, ibo, shader);
    renderer.countfps();
}

World::~World()
{
    //dtor
}
