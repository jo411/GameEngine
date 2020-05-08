#pragma once
#include "GLib.h"
#include "Synchronization/Mutex.h"
class SpriteSystem
{
public:
	static GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
	static Engine::Mutex spriteSystemMutex;

private:
	static void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);	
};

