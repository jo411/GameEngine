#include "CollisionHandler.h"
#include "../GLib/_Console/ConsolePrint.h"
#include "AABB.h"
#include "../RigidBody2d.h"

bool CollisionHandler::SweptSeparatingAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B, float deltaTime)
{
	std::array<float,4> AinBTimes = SweptAxisCollisionCheck(A, B, deltaTime);
	std::array<float, 4> BinATimes;
	if (AinBTimes[0] != FLT_MAX)//We don't have a guaranteed non collision
	{
		BinATimes = SweptAxisCollisionCheck(B, A, deltaTime);
	}
	else
	{
		return false;
	}
	if (BinATimes[0] == FLT_MAX)//We have guaranteed non collision
	{
		return false;
	}

	float latestCloseX = (AinBTimes[0]<BinATimes[0]? BinATimes[0]: AinBTimes[0]);
	float earliestOpenX = !(BinATimes[1] < AinBTimes[1]) ? AinBTimes[1] : BinATimes[1];
	
	float latestCloseY = (AinBTimes[2] < BinATimes[2] ? BinATimes[2] : AinBTimes[2]);
	float earliestOpenY = !(BinATimes[3] < AinBTimes[3]) ? AinBTimes[3] : BinATimes[3];
	
	float latestClose = (latestCloseX < latestCloseY) ? latestCloseY : latestCloseX;
	float earliestOpen = !(earliestOpenY < earliestOpenX) ? earliestOpenX : earliestOpenY;

	if (latestClose > earliestOpen)
	{
		return false;
	}
	else if(latestClose<earliestOpen)
	{
		DEBUG_PRINT("Object: \"%s\" just collided with Object: \"%s\" \n", A->name->getCharArray(), B->name->getCharArray());		
		return true;
	}

	return false;


	//No velocity interpolation version
	/*bool separationAinB = false;
bool separationBinA = false;

separationAinB = staticCollisionCheck(A, B);
if (!separationAinB)
{
	separationBinA = staticCollisionCheck(B, A);
}


if (!separationAinB && !separationBinA)
{
	DEBUG_PRINT("Object: \"%s\" just collided with Object: \"%s\" \n", A->name->getCharArray(), B->name->getCharArray());
}*/
}
//Check if A collides with B in B's coordinate system. No velocity interpolation
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


//Check if A collides or did collide with B in B's coordinate system in the last frame time. Returns open and close times for the
//separations in the form:[tCloseX,tOpenX, tCloseY,tOpenY]
std::array<float, 4> CollisionHandler::SweptAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B, float deltaTime)
{
	AABB* bbA = dynamic_cast<AABB*>(A->getComponent(AABB::tag).getRawPointer());
	AABB* bbB = dynamic_cast<AABB*>(B->getComponent(AABB::tag).getRawPointer());

	RigidBody2d* rbA = dynamic_cast<RigidBody2d*>(A->getComponent(RigidBody2d::tag).getRawPointer());
	RigidBody2d* rbB = dynamic_cast<RigidBody2d*>(B->getComponent(RigidBody2d::tag).getRawPointer());	
	

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

	Vector2 VelARelToB = rbA->getVelocity() - rbB->getVelocity();
	Vector4 VelAInB = WorldToB * Vector4(VelARelToB.x, VelARelToB.y, 0, 0);


	//-------------------------X AXIS--------------------------------
	float B_ExtentsX = bbB->getExtents().x + AProjectionOntoB_X;
	float B_LeftX = bbB->getCenter().x - B_ExtentsX;
	float B_RightX = bbB->getCenter().x + B_ExtentsX;

	float dCloseX = B_LeftX - AbbCenterInB.X();
	float dOpenX = B_RightX - AbbCenterInB.X();
	   
	float tCloseX = dCloseX / VelARelToB.x;
	float tOpenX = dOpenX / VelARelToB.x;


	//-------------------------Y AXIS--------------------------------
	float B_ExtentsY = bbB->getExtents().y + AProjectionOntoB_Y;
	float B_LeftY = bbB->getCenter().y - B_ExtentsY;
	float B_RightY = bbB->getCenter().y + B_ExtentsY;

	float dCloseY = B_LeftY - AbbCenterInB.Y();
	float dOpenY = B_RightY - AbbCenterInB.Y();

	float tCloseY = dCloseY / VelARelToB.y;
	float tOpenY = dOpenY / VelARelToB.y;

	float swap;	

	if (tOpenX < tCloseX)
	{		
		swap = tOpenX;
		tOpenX = tCloseX;
		tCloseX = swap;
	}
	if (tOpenY < tCloseY)
	{
		swap = tOpenY;
		tOpenY = tCloseY;
		tCloseY = swap;
	}

	if (tCloseX > deltaTime || tCloseY > deltaTime)
	{
		return { FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX };
	}
	if (tOpenX <0 || tOpenY <0)
	{
		return { FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX };
	}
	if ((VelARelToB.x == 0 && AbbCenterInB.X() < B_LeftX && AbbCenterInB.X() > B_RightX) || (VelARelToB.y == 0 && AbbCenterInB.Y() < B_LeftY && AbbCenterInB.Y() > B_RightY))
	{
		return { FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX };
	}

	return { tCloseX,tOpenX,tCloseY,tOpenY };
}

