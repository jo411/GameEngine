#include "CollisionHandler.h"
#include "../GLib/_Console/ConsolePrint.h"
#include "AABB.h"

bool CollisionHandler::SweptSeparatingAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B, float deltaTime)
{
	bool separationAinB = false;
	bool separationBinA = false;

	separationAinB = staticCollisionCheck(A, B);
	if (!separationAinB)
	{
		separationBinA = staticCollisionCheck(B, A);
	}
		

	if (!separationAinB && !separationBinA)
	{
		DEBUG_PRINT("Object: \"%s\" just collided with Object: \"%s\" \n", A->name->getCharArray(), B->name->getCharArray());
	}

	return true;
}
//Check if A collides with B in B's coordinate system. 
bool CollisionHandler::staticCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B)
{	
	AABB* bbA = dynamic_cast<AABB*>(A->getComponent(AABB::tag).getRawPointer());
	AABB* bbB = dynamic_cast<AABB*>(B->getComponent(AABB::tag).getRawPointer());

	Vector2 A_Extents = bbA->getExtents();
	Vector2 A_Center = bbA->getCenter();
		
	Matrix4 AToWorld = A->ObjectToWorldTransform();
	Matrix4 WorldToB = B->ObjectToWorldTransform().getTranspose(true);
	Matrix4 AToB = WorldToB * AToWorld;

	Vector4 AbbCenterInB = AToB * Vector4(A_Center.x, A_Center.y, 0, 1);
	
	Vector4 AExtentsXInB = AToB * Vector4(A_Extents.x, 0, 0, 0);
	Vector4 AExtentsYInB = AToB * Vector4(0, A_Extents.y, 0, 0);

	float AProjectionOntoB_X = fabs(AExtentsXInB.X()) + fabs(AExtentsYInB.X());
	float AProjectionOntoB_Y = fabs(AExtentsXInB.Y()) + fabs(AExtentsYInB.Y());


	bool IsSeparatedX = fabs(AbbCenterInB.X() - bbB->getCenter().x) > bbB->getExtents().x + AProjectionOntoB_X;
	bool IsSeparatedY = fabs(AbbCenterInB.Y() - bbB->getCenter().y > bbB->getExtents().y + AProjectionOntoB_Y);

	return IsSeparatedX || IsSeparatedY;
}

