#include <iostream>
#include "conio.h"
#include "SimpleString.h"
#include "GameScene.h"
#include "GameObject.h"
int main()
{
	GameScene Scene;
	while (_getch() != 'q')
	{
		Scene.update();
	}
}
 
