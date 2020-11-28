#ifndef BIOME_H
#define BIOME_H

#define BIOME_GRASSLANDS 0
#define BIOME_FOREST 1
#define BIOME_DESERT 2

float biomeDirtHeight(unsigned char biome);
float biomeHeight(unsigned char biome);
float biomeBumpiness(unsigned char biome);
unsigned char biomePalTop(unsigned char biome);
unsigned char biomePalDirt(unsigned char biome);
bool biomePlaceTree(unsigned char biome, unsigned int srandSeed);

#endif // BIOME_H
