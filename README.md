# u0936149
//---------------------------------------------- - Assignment 2.7 notes-------------------------------------------------------------- -

I based my job system off of the lambda sample with some changes to how it handles the condition variables that made integrating with my engine a little easier.

Engine/HashedString  Engine/JobSystem and Engine/Synchronization hold all the code. 

Engine/GameScene has a new function for loading a gameobject as a job routine.

The game scene also has a threadsafe buffer which is locked and added to the main scene every frame. 

The calling and setup of the job system happen inside Monster_Chase.cpp.

initEngine() creates the job queues and shutdownEngine() shutsdown the system inside Monster_Chase.cpp.

loadGameObjects(...) is passed as a lambda to the job::run() calls on line 176-190 of monster_chase.cpp which in turn calls the game scene create async function which loads 
the json. 
