#include "CollisionHandler.h"
#include "../GLib/_Console/ConsolePrint.h"
#include "Physics/AABB/AABB.h"
#include "Physics/RigidBody2d/RigidBody2d.h"

struct CollisionTimesAndAxis
{
	std::array<float, 4> times;
	Vector2 axisX;
	Vector2 axisY;
};



CollisionData CollisionHandler::SweptSeparatingAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B, float deltaTime)
{
	CollisionData result;
	result.A = A;
	result.B = B;	
	result.didCollide = false;

	CollisionTimesAndAxis AinBTimes = SweptAxisCollisionCheck(A, B, deltaTime);
	CollisionTimesAndAxis BinATimes;	
	if (AinBTimes.times[0] != FLT_MAX)//We don't have a guaranteed non collision
	{
		BinATimes = SweptAxisCollisionCheck(B, A, deltaTime);
	}
	else
	{		
		return result;
	}
	if (BinATimes.times[0] == FLT_MAX)//We have guaranteed non collision
	{		
		return result;
	}

	float latestCloseX = (AinBTimes.times[0]<BinATimes.times[0]? BinATimes.times[0]: AinBTimes.times[0]);
	float earliestOpenX = !(BinATimes.times[1] < AinBTimes.times[1]) ? AinBTimes.times[1] : BinATimes.times[1];
	
	float latestCloseY = (AinBTimes.times[2] < BinATimes.times[2] ? BinATimes.times[2] : AinBTimes.times[2]);
	float earliestOpenY = !(BinATimes.times[3] < AinBTimes.times[3]) ? AinBTimes.times[3] : BinATimes.times[3];
	
	bool LatestCLoseWasAxisX = false;
	float latestClose;
	if (latestCloseX < latestCloseY)
	{
		latestClose = latestCloseY;
		LatestCLoseWasAxisX = true;
	}
	else
	{
		latestClose = latestCloseX;
		LatestCLoseWasAxisX = false;
	}

	float earliestOpen = !(earliestOpenY < earliestOpenX) ? earliestOpenX : earliestOpenY;

	if (latestClose > earliestOpen)
	{		
		return result;
	}
	else if(latestClose<earliestOpen)
	{			
		result.cTime = latestClose;
		result.didCollide = true;

		if (LatestCLoseWasAxisX)
		{
			result.CollisionAxis = Vector4(AinBTimes.axisX.x, AinBTimes.axisX.y, 0, 0);
		}
		else
		{
			result.CollisionAxis = Vector4(AinBTimes.axisY.x, AinBTimes.axisY.y, 0, 0);			
		}

		return result;
	}

	
	return result;


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
bool CollisionHandler::checkAllObjectsForCollision(const std::vector<SmartPointer<GameObject>>& collidables, const float& dt)
{
	//DEBUG_PRINT("DT: %f\n", dt);
	float totalDt = dt;
	float remainingDt = dt;
	while (remainingDt>0)
	{
		std::vector<CollisionData> results;

		for (int i = 0; i < collidables.size(); i++)
		{
			for (int j = i + 1; j < collidables.size(); j++)
			{
				CollisionData out = SweptSeparatingAxisCollisionCheck(collidables[i], collidables[j], remainingDt);
				if (out.didCollide && out.cTime>0)
				{
					results.push_back(out);
				}
			}

		}
		CollisionData firstCollision;

		if (results.size() > 0)
		{
			firstCollision = results[0];
			for (int i = 0; i < results.size(); i++)
			{
				if (results[i].cTime < firstCollision.cTime)
				{
					firstCollision = results[i];
				}
			}

		

			//handle collision
			RigidBody2d* rbA = dynamic_cast<RigidBody2d*>(firstCollision.A->getComponent(RigidBody2d::tag).getRawPointer());
			RigidBody2d* rbB = dynamic_cast<RigidBody2d*>(firstCollision.B->getComponent(RigidBody2d::tag).getRawPointer());

			rbA->onCollision(firstCollision);
			rbB->onCollision(firstCollision);
			rbA->refresh();
			rbB->refresh();

			//step simulation
			for (int i = 0; i < collidables.size(); i++)
			{
				resolveCollisionPosition(collidables[i], firstCollision.cTime);
			}

			remainingDt -= firstCollision.cTime;

			DEBUG_PRINT("Object: \"%s\" just collided with Object: \"%s\" \n", firstCollision.A->name->getCharArray(), firstCollision.B->name->getCharArray());
		}
		else
		{
			for (int i = 0; i < collidables.size(); i++)
			{
				resolveCollisionPosition(collidables[i], remainingDt);
			}
			remainingDt = 0;
		}

	}	
	
	return false;
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
CollisionTimesAndAxis CollisionHandler::SweptAxisCollisionCheck(SmartPointer<GameObject> A, SmartPointer<GameObject> B, float deltaTime)
{
	CollisionTimesAndAxis result;

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
	bool swappedX = false;
	bool swappedY = false;

	if (tOpenX < tCloseX)
	{		
		swap = tOpenX;
		tOpenX = tCloseX;
		tCloseX = swap;
		swappedX = true;
	}
	if (tOpenY < tCloseY)
	{
		swap = tOpenY;
		tOpenY = tCloseY;
		tCloseY = swap;
		swappedY = true;
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

	result.times = { tCloseX,tOpenX,tCloseY,tOpenY };

	Vector4 axisX;
	Vector4 axisY;

	Matrix4 BToWorld = B->ObjectToWorldTransform();
	Vector2 BXAxis(B_ExtentsX, 0);
	Vector2 BYAxis(0, B_ExtentsY);

	Vector4 BExtentsX4(B_ExtentsX,0,0,0);
	Vector4 BExtentsY4(0, B_ExtentsY, 0, 0);

	
	axisX = BToWorld* BExtentsX4;
	axisY = BToWorld * BExtentsY4;
	float lenX = sqrt(axisX.X()*axisX.X());
	float lenY = sqrt(axisY.Y()*axisY.Y());

	Vector4 BXAxisInWorldNorm(axisX.X() / lenX,0,0,0);
	Vector4 BYAxisInWorldNorm(0, axisY.Y() / lenY, 0, 0);

	result.axisX = Vector2(BXAxisInWorldNorm.X(),0);
	result.axisY = Vector2(0, BYAxisInWorldNorm.Y());

	if (swappedX)
	{
		result.axisX.x = -result.axisX.x;
	}
	if (swappedY)
	{
		result.axisY.y = -result.axisY.y;
	}


	return result;

}

void CollisionHandler::resolveCollisionPosition(SmartPointer<GameObject> A, const float cTime)
{
	RigidBody2d* rbA = dynamic_cast<RigidBody2d*>(A->getComponent(RigidBody2d::tag).getRawPointer());

	//A->position += rbA->getVelocity()*cTime;
	UpdateParams dummy;
	dummy.deltaTime = cTime;
	rbA->physicsUpdate(&dummy);
}

