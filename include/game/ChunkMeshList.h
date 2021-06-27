#ifndef CHUNKMESHLIST_H
#define CHUNKMESHLIST_H

#include <array>
#include <cassert>
#include <iostream>
#include "ChunkMesh.h"

template<size_t S>
class ChunkMeshList
{
    public:
        ChunkMeshList()
        {
            for (size_t i {0}; i < S; ++i)
                chunkMeshPointers[i] = nullptr;
        }

        void add(ChunkMesh* chunkMesh)
        {
            for (size_t i {0}; i < S; ++i)
                if (chunkMeshPointers[i] == nullptr)
                {
                    chunkMeshPointers[i] = chunkMesh;
                    return;
                }
            assert(0);
        }

        void remove(size_t n)
        {
            delete chunkMeshPointers[n];
            chunkMeshPointers[n] = nullptr;
        }

        void remove(Positioni pos)
        {
            for (size_t i {0}; i < S; ++i)
            {
                if (chunkMeshPointers[i] == nullptr)
                    continue;
                if (chunkMeshPointers[i]->getPos() == pos)
                {
                    delete chunkMeshPointers[i];
                    chunkMeshPointers[i] = nullptr;
                    return;
                }
            }
            assert(0);
        }

        ChunkMesh* at(Positioni pos)
        {
            for (size_t i {0}; i < S; ++i)
            {
                if (chunkMeshPointers[i] == nullptr)
                    continue;
                if (chunkMeshPointers[i]->getPos() == pos)
                {
                    return chunkMeshPointers[i];
                }
            }
            return nullptr;
        }

        ChunkMesh*& operator[](size_t n) { return chunkMeshPointers[n]; }

        constexpr size_t size() { return S; }

        virtual ~ChunkMeshList()
        {
            for (size_t i {0}; i < S; ++i)
                if (chunkMeshPointers[i] != nullptr)
                    delete chunkMeshPointers[i];
        }

    protected:

    private:
        std::array<ChunkMesh*, S> chunkMeshPointers;
};

#endif // CHUNKMESHLIST_H
