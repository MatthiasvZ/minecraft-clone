#include "Biome.h"
#include "Chunk.h"


float biomeDirtHeight(unsigned char biome)
{
    switch (biome)
    {
    case BIOME_GRASSLANDS:
        return 4.0f;
        break;
    case BIOME_FOREST:
        return 4.5f;
        break;
    case BIOME_DESERT:
        return 4.0f;
        break;
    }
    return 4.0f;
}

float biomeHeight(unsigned char biome)
{
    switch (biome)
    {
    case BIOME_GRASSLANDS:
        return 4.0f;
        break;
    case BIOME_FOREST:
        return 3.5f;
        break;
    case BIOME_DESERT:
        return 3.0f;
        break;
    }
    return 4.0f;
}

float biomeBumpiness(unsigned char biome)
{
    switch (biome)
    {
    case BIOME_GRASSLANDS:
        return 15.0f;
        break;
    case BIOME_FOREST:
        return 10.0f;
        break;
    case BIOME_DESERT:
        return 20.0f;
        break;
    }
    return 20.0f;
}

unsigned char biomePalTop(unsigned char biome)
{
    switch (biome)
    {
    case BIOME_GRASSLANDS:
        return BLOCK_GRASS;
        break;
    case BIOME_FOREST:
        return BLOCK_GRASS;
        break;
    case BIOME_DESERT:
        return BLOCK_SAND;
        break;
    }
    return BLOCK_AIR;
}

unsigned char biomePalDirt(unsigned char biome)
{
    switch (biome)
    {
    case BIOME_GRASSLANDS:
        return BLOCK_DIRT;
        break;
    case BIOME_FOREST:
        return BLOCK_DIRT;
        break;
    case BIOME_DESERT:
        return BLOCK_SAND;
        break;
    }
    return BLOCK_AIR;
}

bool biomePlaceTree(unsigned char biome, unsigned int srandSeed)
{
    srand(srandSeed);
    switch (biome)
    {
    case BIOME_GRASSLANDS:
        return rand() % 100 < 3;
        break;
    case BIOME_FOREST:
        return rand() % 100 < 12;
        break;
    case BIOME_DESERT:
        return rand() % 100 < 2;
        break;
    }
    return false;
}
