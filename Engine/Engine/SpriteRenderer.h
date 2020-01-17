#pragma once
#include "Component.h"
#include "GLib.h"
class SpriteRenderer: public Component
{
	public:
	SpriteRenderer(const char * i_pFilename);
	~SpriteRenderer();
	void Destroy();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
private:
	GLib::Sprites::Sprite* sprite;
};

