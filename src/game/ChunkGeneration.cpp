#include "game/Chunk.h"
#include "game/World.h"

#include "vendor/FastNoiseLite.h"
#include "Biome.h"

void Chunk::generate()
{
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed(World::getSeed());
    noise.SetFrequency(0.01f);
    float pnoise[16][16];
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iz {0}; iz < 16; iz++)
        {
            pnoise[ix][iz] = (noise.GetNoise(static_cast<float>(pos.x*16 + ix), static_cast<float>(pos.z*16 + iz)) +
                             noise.GetNoise(static_cast<float>(pos.x*16 + ix + 42), static_cast<float>(pos.z*16 + iz)) * 2 +
                             noise.GetNoise(static_cast<float>(pos.x*16 + ix + 420), static_cast<float>(pos.z*16 + iz)) * 4) / 7;
        }
    }

    noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    noise.SetFrequency(0.002f);
    noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
    noise.SetCellularJitter(1.0f);
    noise.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
    noise.SetDomainWarpAmp(100.0f);
    noise.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
    noise.SetFractalOctaves(3);
    noise.SetFractalLacunarity(2.00f);
    noise.SetFractalGain(0.50f);

    float bnoise[16][16];
    for (int ix {0}; ix < 16; ix++)
    {
        for (int iz {0}; iz < 16; iz++)
        {
            float wPosX = static_cast<float>(pos.x*16 + ix);
            float wPosZ = static_cast<float>(pos.z*16 + iz);
            noise.DomainWarp(wPosX, wPosZ);
            bnoise[ix][iz] = noise.GetNoise(wPosX, wPosZ);
        }
    }


    for (int ix {0}; ix < 16; ++ix)
    {
        for (int iz {0}; iz < 16; ++iz)
        {
            if (bnoise[ix][iz] > 0.0f)
                biomeIDs[ix][iz] = BIOME_GRASSLANDS;
            else if (bnoise[ix][iz] > -0.5f)
                biomeIDs[ix][iz] = BIOME_FOREST;
            else
                biomeIDs[ix][iz] = BIOME_DESERT;
        }
    }

    for (int ix {0}; ix < 16; ix++)
    {
        for (int iy {0}; iy < 16; iy++)
        {
            for (int iz {0}; iz < 16; iz++)
            {
                if (pnoise[ix][iz] > static_cast<float>(pos.y*16 + iy) / biomeBumpiness(biomeIDs[ix][iz]) - biomeHeight(biomeIDs[ix][iz]))
                {

                    if (pnoise[ix][iz] < static_cast<float>(pos.y*16 + iy + 1) / biomeBumpiness(biomeIDs[ix][iz]) - biomeHeight(biomeIDs[ix][iz]))
                    {
                        blockIDs[ix][iy][iz] = biomePalTop(biomeIDs[ix][iz]);
                        if (biomePlaceTree(biomeIDs[ix][iz], static_cast<unsigned int>(pnoise[ix][iz] * 100'000'000)) && iy != 15)
                            blockIDs[ix][iy + 1][iz] = BLOCK_OAK_LOG;
                    }
                    else if (pnoise[ix][iz] < static_cast<float>(pos.y*16 + iy + biomeDirtHeight(biomeIDs[ix][iz])) / biomeBumpiness(biomeIDs[ix][iz]) - biomeHeight(biomeIDs[ix][iz]))
                        blockIDs[ix][iy][iz] = biomePalDirt(biomeIDs[ix][iz]);
                    else
                        blockIDs[ix][iy][iz] = BLOCK_STONE;
                }
                else
                    blockIDs[ix][iy][iz] = BLOCK_AIR;
            }
        }
    }
}
