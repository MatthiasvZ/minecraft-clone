#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall -std=c++20 -Iinclude -fexceptions -pipe -march=native
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = -lglfw -lGLEW -lX11 -lGLU -lGL libPetroleum.a

INC_DEBUG = $(INC) -Iinclude/game/ -Iinclude/optimisation
CFLAGS_DEBUG = $(CFLAGS) -Og -g -DDEBUG
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/minecraft-clone

INC_RELEASE = $(INC) -Iinclude/game/ -Iinclude/optimisation
CFLAGS_RELEASE = $(CFLAGS) -flto -Ofast
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -flto -s
OBJDIR_RELEASE = obj
DEP_RELEASE = 
OUT_RELEASE = bin/minecraft-clone

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/game/ChunkMesh.o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD.o $(OBJDIR_DEBUG)/src/game/World.o $(OBJDIR_DEBUG)/src/game/Player.o $(OBJDIR_DEBUG)/Main.o $(OBJDIR_DEBUG)/src/game/ChunkLoading.o $(OBJDIR_DEBUG)/src/game/Chunk.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/game/ChunkMesh.o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD.o $(OBJDIR_RELEASE)/src/game/World.o $(OBJDIR_RELEASE)/src/game/Player.o $(OBJDIR_RELEASE)/Main.o $(OBJDIR_RELEASE)/src/game/ChunkLoading.o $(OBJDIR_RELEASE)/src/game/Chunk.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src/game || mkdir -p $(OBJDIR_DEBUG)/src/game
	test -d $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD || mkdir -p $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/src/game/ChunkMesh.o: src/game/ChunkMesh.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/game/ChunkMesh.cpp -o $(OBJDIR_DEBUG)/src/game/ChunkMesh.o

$(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp -o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.o

$(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp -o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.o

$(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.cpp -o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.o

$(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp -o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.o

$(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp -o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.o

$(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD.cpp -o $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD/FastNoiseSIMD.o

$(OBJDIR_DEBUG)/src/game/World.o: src/game/World.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/game/World.cpp -o $(OBJDIR_DEBUG)/src/game/World.o

$(OBJDIR_DEBUG)/src/game/Player.o: src/game/Player.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/game/Player.cpp -o $(OBJDIR_DEBUG)/src/game/Player.o

$(OBJDIR_DEBUG)/Main.o: Main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Main.cpp -o $(OBJDIR_DEBUG)/Main.o

$(OBJDIR_DEBUG)/src/game/ChunkLoading.o: src/game/ChunkLoading.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/game/ChunkLoading.cpp -o $(OBJDIR_DEBUG)/src/game/ChunkLoading.o

$(OBJDIR_DEBUG)/src/game/Chunk.o: src/game/Chunk.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/game/Chunk.cpp -o $(OBJDIR_DEBUG)/src/game/Chunk.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src/game
	rm -rf $(OBJDIR_DEBUG)/src/vendor/FastNoiseSIMD
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin || mkdir -p bin
	test -d $(OBJDIR_RELEASE)/src/game || mkdir -p $(OBJDIR_RELEASE)/src/game
	test -d $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD || mkdir -p $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/src/game/ChunkMesh.o: src/game/ChunkMesh.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/game/ChunkMesh.cpp -o $(OBJDIR_RELEASE)/src/game/ChunkMesh.o

$(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp -o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse41.o

$(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp -o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_sse2.o

$(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.cpp -o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_internal.o

$(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp -o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx512.o

$(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp -o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD_avx2.o

$(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD.o: src/vendor/FastNoiseSIMD/FastNoiseSIMD.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/vendor/FastNoiseSIMD/FastNoiseSIMD.cpp -o $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD/FastNoiseSIMD.o

$(OBJDIR_RELEASE)/src/game/World.o: src/game/World.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/game/World.cpp -o $(OBJDIR_RELEASE)/src/game/World.o

$(OBJDIR_RELEASE)/src/game/Player.o: src/game/Player.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/game/Player.cpp -o $(OBJDIR_RELEASE)/src/game/Player.o

$(OBJDIR_RELEASE)/Main.o: Main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Main.cpp -o $(OBJDIR_RELEASE)/Main.o

$(OBJDIR_RELEASE)/src/game/ChunkLoading.o: src/game/ChunkLoading.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/game/ChunkLoading.cpp -o $(OBJDIR_RELEASE)/src/game/ChunkLoading.o

$(OBJDIR_RELEASE)/src/game/Chunk.o: src/game/Chunk.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/game/Chunk.cpp -o $(OBJDIR_RELEASE)/src/game/Chunk.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin
	rm -rf $(OBJDIR_RELEASE)/src/game
	rm -rf $(OBJDIR_RELEASE)/src/vendor/FastNoiseSIMD
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

