#pragma once
#include "GLib.h"
class SpriteSystem
{
public:
	static GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

private:
	static void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);	
};

