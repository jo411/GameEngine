#include <iostream>
#include "conio.h"
#include "SimpleString.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Components\Talker.h"
#include "Components\PlayerController.h"
int main()
{
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
		
	}
		
	UpdateParams params;
	params.keyPressed = '\0';
	do
	{
		std::cout << "Use WASD keys to move. At any time press 'q' to quit.\n";
		Scene.update(&params);
		Scene.draw(&params);
	} while ((params.keyPressed = _getch()) != 'q');
}
 
//Look at component update order.