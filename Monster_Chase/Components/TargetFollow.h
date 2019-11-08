#pragma once
#include "Component.h"
#include "GameObject.h"
class TargetFollow : public Component
{
public:
	TargetFollow(int moveSpeed, GameObject* target);
	~TargetFollow();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	void setTarget(GameObject* target);
private:
	GameObject* target;
	int speed;//how fast it can move
};

