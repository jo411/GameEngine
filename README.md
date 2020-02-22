# u0936149
-----------------------------------------------Assignment 2.6 notes---------------------------------------------------------------

Monster_Chase.cpp is where all the main startup code is located for this assignment. 
 
There is a unused funtion called "CreateAndSaveGameObjects" that I used to generate the json at first from existing GameObjects.

Inside Monster_Chase.cpp the function "loadGameObjects" is what starts the json reading. Using a GameScene object it calls the new 
create game object function that takes a file path to json data and returns a weak pointer to the gameobject that was just added to 
the scene.

The function inside a GameScene calls the engine specific json parsing inside JsonHandler.h/cpp This class holds deserialization patterns
for engine built in components and types like the sprite renderer or the rigid body. It also takes a callback that the user can supply to 
define their own deserialization patterns for their own custom components. It also takes a smart pointer to the gameobject currently
being constructed.

"nonEngineJsonCallBack" inside Monster_Chase.cpp is my callback for Monster_chase specific components like the PlayerController or the Random-
Position components. 

The json asset files are located in ...Monster_Chase\Data\Json there are currently 2 files: player and enemy. 