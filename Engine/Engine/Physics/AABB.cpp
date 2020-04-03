#include "AABB.h"
const std::string AABB::tag = "AABB";
AABB::AABB(float cX, float cY, float eX, float eY)
{
	Extents.x = eX;
	Extents.y = eY;

	Center.x = cX;
	Center.y = cY;
}

const Vector2 & AABB::getExtents()
{
	return Extents;
}

const Vector2 & AABB::getCenter()
{
	return Center;
}

void AABB::update(UpdateParams * params)
{
}

void AABB::draw(UpdateParams * params)
{
}

void AABB::onAddToObject()
{
}
