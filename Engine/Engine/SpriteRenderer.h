#pragma once
#include "Component.h"
#include "GLib.h"
class SpriteRenderer: public Component
{
	public:
	SpriteRenderer(const char * i_pFilename);
	~SpriteRenderer();	
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	void Serialize(json& j);
private:	
	GLib::Sprites::Sprite* sprite;
	const char* file;
};

