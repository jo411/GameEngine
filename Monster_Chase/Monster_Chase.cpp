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
int main()
{
	srand((unsigned int)time(NULL));
	GameScene Scene;

	std::cout << "What is your name?\n";	
	SimpleString playerName;
	char in = ' ';
	while ((in=_getche()) != '\r')
	{
		playerName.append(in);		
	}

	std::cout << "How many monsters to start?\n";
	SimpleString number;
	while ((in = _getche()) != '\r')
	{
		if (isdigit(in))
		{
			number.append(in);
		}
	}

	GameObject* player = Scene.CreateGameObject();
	(*player->name) = playerName;
	player->addComponent(new Talker());
	player->addComponent(new PlayerController());

	int numMonster = atoi(number.getCharArray());
	

	for (int i = 0; i < numMonster;i++)
	{
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

	GameObject* hive = Scene.CreateGameObject();
	hive->name->fromCharArray("Hive");
	hive->addComponent(new randomPosition(8,8));
	hive->addComponent(new Spawner(3));
	hive->addComponent(new Talker());
		
	UpdateParams params;
	params.keyPressed = '\0';
	std::cout << "Use WASD keys to move. At any time press 'q' to quit.\n";
	do
	{		
		std::cout << "-------------------------------\n";
		Scene.update(&params);
		Scene.draw(&params);
		std::cout << "-------------------------------\n";
		
	} while ((params.keyPressed = _getch()) != 'q');
}

