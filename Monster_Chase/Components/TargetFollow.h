#pragma once
#include "Entity Component System/Component/Component.h"
#include "Entity Component System/GameObject/GameObject.h"
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

