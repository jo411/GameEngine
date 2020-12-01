This repository holds the solution for a Game Engine I developed and a game made with it as part of a class in my Masters Degree.
Below is a readme from the project that may give some brief context. 

Josh Nelson Semester 2 Final Readme


-----THE GAME-----

The game is just pong with a couple tweaks to make it somewhat interesting. 
Player 1 uses W/D and Player 2 uses I/K to move up and down.
Players can only burst fire their rockets by tapping keys to move so they have to manage their accumulating velocity to slow and turn.
Additionally reflecting the energy ball drains your rocket bumper of energy momentarily stunning the player. 


---THE CODE---

All the systems we made this semester are being used. The code is pretty well organized so you shouldn't have an issue checking 
out anything you wanted to see specifically. 

The main projects are ENGINE and PONG 

The startup code is in Pong/pong.cpp

The game is set up to load the scene from json files in the data/json/pong folder. 

Memory leaks are forced to be printed if in debug mode using _CrtSetDbgFlag (pong.cpp)


--- WORTH CHECKING OUT --- 
(Sorry for the wall of text I wasn't sure how specific you wanted the descriptions so I went for a halfway point)

What I'm pretty proud of is my entity component system. I modeled it after unity in an attempt to allow me to develop with 
Unity design patterns in mind. I think it went pretty well. Once that was finished it was almost trivial to develop the pong game. 
I didn't have to touch any engine code and it brought everything together really cleanly.

The ECS touches essentially every system depending on how far you care to look. The biggest area to check out is:

-Engine/Entity Component System-

This holds the main classes of the ECS 
Game Scenes hold collections of Game Objects
Game Objects hold some basic data and a collection of Components
Components can modify behaviors of the GameObject they are attached to.
	Component defines virtual methods for building custom behaviors on derived classes.
	Many of the behaviors of the systems we made are implemented through components. See: Physics/Rigidbody2d or Physics/AABB for the collision examples.
Updates cascade down through all three classes from the main game loop.
Through the get component and find game object functions game objects can communicate with each other. 

Game objects can be added to or modified in the scene asynchronously through the job system. (this can be seen in the pong.cpp function loadPongSceneFromFile.

If you want to see a scripting example using the ECS check out loadAndSavePongScene which I used to create the json for the first time. 
Another good example of a few systems working together is in Pong.cpp: 
--nonEngineJsonCallBack()--
This is a a function being passed as a delegate to the json handler in the engine (Engine/Json) that lets a game set up their own hooks for json de-serialization totally separate from the engine code. It's a quick look at how easy the Async ECS makes it to create and modify behaviors on GameObjects.

A final good example of the ECS is pong/Components/GameManager
This is a managing class that handles game state and some ui. 
It shows cross Game Object communication, object creation at runtime, and enabling/disabling GameObjects in the middle of the game. 
It's also a good example of Unity like design patterns being enabled thanks to the ECS.
