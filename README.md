# u0936149
//---------------------------------------------- - Assignment 2.10 notes-------------------------------------------------------------- -

The main class is MonsterChase.cpp

Running the game will open a scene with 3 gameobjects coming at each other. When the collide they rebound using conservation of momentum and reflection formulas. 

No new classes have been added 

	CollisionHandler.h/cpp has been restructured to take in a list of gameobjects and step them all through the frames delta time. 
	Once collisions are found the oncollision function is called on the two rigid bodies. The default action is for a rigid body to apply a force on itself from it's movement vector reflection about the collision normal with a strength determined by conservation of momentum formulas. 
	
	Rigid bodies also have a callback pointer that can be used to override the default collision handler with custom behavior. 
	
	The physics has been thoroughly tested with several different kinds of collision involving various speeds,masses, angles, and combinations of moving and non moving objects. 