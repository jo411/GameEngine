#include <iostream>
#include "conio.h"
#include "time.h"
#include "SimpleString.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Components\Talker.h"
#include "Components\PlayerController.h"
#include "Components\randomPosition.h"
#include "Components\Walker.h"
#include "Components\Spawner.h"
//Josh Nelson
//u0936149
//There are a lot of classes especially for components but they aren't large
//The basic structure I used to organize this assignment looks like this


//       +-------------------+    +-----------------+
//       | GameScene         |    |GameObject       |
//       |  List<GameObject> +--->+ Vector2         |
//       |                   |    | SimpleString    |
//       +-------------------+    | List<Component> |
//                                |                 |
//                                +-----------------+


//Main Game logic

int main()
{
	srand((unsigned int)time(NULL));//seed the random function

	GameScene Scene;//Create the main scene.

	//Get the player's name
	std::cout << "What is your name?\n";	
	SimpleString playerName;
	char in = ' ';
	while ((in=_getche()) != '\r')
	{
		playerName.append(in);		
	}

	//Ask how many monsters they want
	std::cout << "How many monsters to start?\n";
	SimpleString number;
	while ((in = _getche()) != '\r')
	{
		if (isdigit(in))
		{
			number.append(in);
		}
	}

	//atoi the input
	int numMonster = atoi(number.getCharArray());

	//Create the player Gameobject and add it to the scene 
	//with the components for drawing to the screen and keyboard motion

	GameObject* player = Scene.CreateGameObject();
	(*player->name) = playerName;
	player->addComponent(new Talker());
	player->addComponent(new PlayerController());

	
	
	//Create the correct number of monster game objects 
	//Give them components for drawing, random starting positions, and random movement
	for (int i = 0; i < numMonster;i++)
	{
		//Dumb hack for concating strings since i wasn't sure if string.h was allowed 
		char numberString[(((sizeof i) * CHAR_BIT) + 2) / 3 + 2];//No buffer overflows here ;P
		sprintf_s(numberString, "%d", i);

		GameObject* monster = Scene.CreateGameObject();		
		const char* finalName="_Monster ";
		strcat_s( numberString,finalName);
		monster->name->fromCharArray(numberString);
		monster->addComponent(new Talker());
		monster->addComponent(new randomPosition(10, 10));
		monster->addComponent(new Walker(1));		
	}

	//Create a GameObject with a spawner component that adds monsters to the scene that will be removed over time
	GameObject* hive = Scene.CreateGameObject();
	hive->name->fromCharArray("Hive");
	hive->addComponent(new randomPosition(8,8));
	hive->addComponent(new Spawner(3));
	hive->addComponent(new Talker());
		
	//initialize the object to pass things into the scene
	UpdateParams params;
	params.keyPressed = '\0';
	std::cout << "Use WASD keys to move. At any time press 'q' to quit.\n";

	do
	{		
		std::cout << "-------------------------------\n";
		Scene.update(&params);//update the scene
		Scene.draw(&params);//draw the scene
		std::cout << "-------------------------------\n";
		
	} while ((params.keyPressed = _getch()) != 'q');//Use 'q' to quit
}

