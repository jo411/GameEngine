#pragma once
#include "../Component.h"
#include "../Vector2.h"


class AABB :public Component
{
public:
	AABB(float cX, float cY, float eX, float eY);

	const Vector2& getExtents();
	const Vector2& getCenter();

	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();

	
	static const std::string tag;
	virtual const std::string& getTag() { return tag; }

private:
	Vector2 Extents;
	Vector2 Center;
};
