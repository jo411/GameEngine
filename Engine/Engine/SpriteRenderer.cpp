#define _USE_MATH_DEFINES
#include "SpriteRenderer.h"
#include "SpriteSystem.h"
#include "GameObject.h"
#include <cmath>
SpriteRenderer::SpriteRenderer(const char * i_pFilename)
{
	sprite = SpriteSystem::CreateSprite(i_pFilename);
	file = i_pFilename;
}

SpriteRenderer::~SpriteRenderer()
{
	if (sprite)
	{
		GLib::Sprites::Release(sprite);
	}
}


void SpriteRenderer::update(UpdateParams * params)
{
}

void SpriteRenderer::draw(UpdateParams * params)
{	
	GLib::Point2D	Offset = { gameObject->position.getX(), gameObject->position.getY() };
	GLib::Sprites::RenderSprite(*sprite, Offset, gameObject->rotation*(M_PI/180));
	
}

void SpriteRenderer::onAddToObject()
{	
}

void SpriteRenderer::Serialize(json & j)
{
	j["SpriteRenderer"] = { {"FileName",file } };
}
