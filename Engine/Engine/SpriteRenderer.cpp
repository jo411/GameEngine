#include "SpriteRenderer.h"
#include "SpriteSystem.h"
#include "GameObject.h"
SpriteRenderer::SpriteRenderer(const char * i_pFilename)
{
	sprite = SpriteSystem::CreateSprite(i_pFilename);
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
	static GLib::Point2D	Offset = { gameObject->position.getX(), gameObject->position.getY() };
	GLib::Sprites::RenderSprite(*sprite, Offset, 0.0f);
}

void SpriteRenderer::onAddToObject()
{
}
