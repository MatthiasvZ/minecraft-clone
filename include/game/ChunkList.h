#ifndef CHUNKLIST_H
#define CHUNKLIST_H

#include <array>
#include <cassert>
#include <iostream>
#include "Chunk.h"

template<size_t S>
class ChunkList
{
    public:
        ChunkList()
        {
            for (size_t i {0}; i < S; ++i)
                chunkPointers[i] = nullptr;
        }

        void add(Chunk* chunk)
        {
            for (size_t i {0}; i < S; ++i)
                if (chunkPointers[i] == nullptr)
                {
                    chunkPointers[i] = chunk;
                    return;
                }
            assert(0);
        }

        void remove(size_t n)
        {
            delete chunkPointers[n];
            chunkPointers[n] = nullptr;
        }

        void remove(Positioni pos)
        {
            for (size_t i {0}; i < S; ++i)
            {
                if (chunkPointers[i] == nullptr)
                    continue;
                if (chunkPointers[i]->getPos() == pos)
                {
                    delete chunkPointers[i];
                    chunkPointers[i] = nullptr;
                    return;
                }
            }
            assert(0);
        }

        Chunk* at(Positioni pos)
        {
            for (size_t i {0}; i < S; ++i)
            {
                if (chunkPointers[i] == nullptr)
                    continue;
                if (chunkPointers[i]->getPos() == pos)
                {
                    return chunkPointers[i];
                }
            }
            return nullptr;
        }

        Chunk* operator[](size_t n) { return chunkPointers[n]; }

        constexpr size_t size() { return S; }

        virtual ~ChunkList()
        {
            for (size_t i {0}; i < S; ++i)
                if (chunkPointers[i] != nullptr)
                    delete chunkPointers[i];
        }

    protected:

    private:
        std::array<Chunk*, S> chunkPointers;
};

#endif // CHUNKLIST_H
