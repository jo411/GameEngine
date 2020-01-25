#include <iostream>
#include "conio.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <time.h>

#include "HighResolutionTimer.h"

#include "SpriteSystem.h"
#include "GameScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"


#pragma region Components
#include "Components/randomPosition.h"
#include "Components/Walker.h"
#include "Components/PlayerController.h"
#include "RigidBody2d.h"
#pragma endregion


#pragma comment(lib,"d3d11.lib")

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"
//Josh Nelson
//u0936149

//-----------------------------------------------CLASS SETUP---------------------------------------------------------------
// Below I've used my old ECS setup from semester 1
// Engine/SpriteSystem is a wrapper for the load file and create sprite methods that makes them static functions
// Engine/SpriteRenderer is a component that creates and renders a sprite. 

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	{
		// IMPORTANT: first we need to initialize GLib		
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);

		srand((unsigned int)time(NULL));//seed the random function


		GameScene Scene;
		UpdateParams updateParams;
		HighResolutionTimer gameTimer;
		//Create game objects for the scene
		GameObject* player = Scene.CreateGameObject();
		player->name->fromCharArray("Player");
		player->addComponent(new SpriteRenderer("data\\pikachu.dds"));

		RigidBody2d* rb = new RigidBody2d();
		rb->mass = 1000;
		rb->drag = .99f;
		Vector2 testForce;
		testForce.x = .05;
		testForce.y = .1;
		//rb->addForce(testForce);

		player->addComponent(rb);

		PlayerController* pc = new PlayerController(.1f);
		pc->rb = rb;//This is really bad but I couldnt get a template function for getComponent<type> working
		player->addComponent(pc);

		/*GameObject* enemy = Scene.CreateGameObject();
		enemy->name->fromCharArray("Enemy");
		enemy->addComponent(new SpriteRenderer("data\\flygon.dds"));
		enemy->addComponent(new randomPosition(50, 50));*/
		//enemy->addComponent(new Walker(1));

		if (bSuccess)
		{
			// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
			//(updateParams.getInput())			
			GLib::SetKeyStateChangeCallback(InputManager::KeyCallback);

			// Create a couple of sprites using our own helper routine CreateSprite		

			bool bQuit = false;

			updateParams.deltaTime = 16.68;//60fps in miliseconds default
				
			do
			{
				gameTimer.StartCounter();//reset timer	

				// IMPORTANT: We need to let GLib do it's thing. 
				GLib::Service(bQuit);				

				if (!bQuit)
				{		

					Scene.update(&updateParams);//update the scene

					GLib::BeginRendering();
					GLib::Sprites::BeginRendering();

					Scene.draw(&updateParams);//draw the scene

					GLib::Sprites::EndRendering();
					GLib::EndRendering();

					updateParams.deltaTime = gameTimer.GetCounter();//get last frame time					
				}
			} while (bQuit == false);



			//Tell the scene to release all resources
			Scene.Release();
			// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();
		}
	}
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}


