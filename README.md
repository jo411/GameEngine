# u0936149
//---------------------------------------------- - Assignment 2.09 notes-------------------------------------------------------------- -

The main class is MonsterChase.cpp

Running the game will open a scene with two gameobjects coming at each other diagonally. When the collide they will print the details of the collision into the output console. 
The main classes added are both inside Engine/Physics. 
	AABB .h/cpp is the bounding box component than can be added to game objects. 
		(The Tag variable is part of my ECS that lets me call GetComponent on Game objects)
	CollisionHandler.h/cpp is a static engine class that has methods for determining if two gameobjects collided this frame. 
		I left my first function that only checks the current position without velocity interpolation. It is called "staticCollisionCheck"
		The Version being called in the running game is SweptAxisCollisionCheck which does all the fancy interpolation. 

There is a function in Engine/Gamescene that loops over all the Game Objects in the scene and calls the CollisionHandler::SweptAxisCollisionCheck on them. 
MonsterChase.cpp has a function called loadCollisionScene where I create the scene (gameobjects + components) if you need to see it for some reason. 