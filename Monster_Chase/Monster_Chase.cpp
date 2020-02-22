#include <iostream>
#include "conio.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <time.h>

#include "HighResolutionTimer.h"
#include "SmartPointer.h"
#include "WeakPointer.h"

#include "SpriteSystem.h"
#include "GameScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Person.h"

#pragma region Components
#include "Components/randomPosition.h"
#include "Components/Walker.h"
#include "Components/PlayerController.h"
#include "RigidBody2d.h"
#pragma endregion

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <fstream>
#include <unordered_map>



#pragma comment(lib,"d3d11.lib")

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"
//Josh Nelson
//u0936149

//-----------------------------------------------Assignment notes---------------------------------------------------------------
//
//
//
//
//

void CreateAndSaveGameObjects(GameScene& Scene)
{
	//Create game objects for the scene
	SmartPointer<GameObject> player = Scene.CreateGameObject();
	player->name->fromCharArray("Player");
	player->addComponent(new SpriteRenderer("data\\pikachu.dds"));

	RigidBody2d* rb = new RigidBody2d();
	rb->mass = 10;
	rb->drag = .8f;
	rb->minGroundingSpeed = .01f;

	player->addComponent(rb);

	PlayerController* pc = new PlayerController(.01f);
	pc->timeToApplyForce = 1000.0f;
	pc->rb = rb;//This is really bad but I couldnt get a template function for getComponent<type> working
	player->addComponent(pc);

	SmartPointer<GameObject> enemy = Scene.CreateGameObject();
	enemy->name->fromCharArray("Enemy");
	enemy->addComponent(new SpriteRenderer("data\\flygon.dds"));
	enemy->addComponent(new randomPosition(50, 50));
	enemy->addComponent(new Walker(1));

	json j;
	std::ofstream myfile;

	enemy->Serialize(j);	
	myfile.open("Data/Json/enemy.json");
	myfile << j;
	myfile.close();	

	j.clear();
	player->Serialize(j);
	myfile.open("Data/Json/player.json");
	myfile << j;
	myfile.close();
}

void nonEngineJsonCallBack(SmartPointer<GameObject> obj, json j, std::map<std::string, Component*>& dependencies)
{
	if (j.contains("PlayerController"))
	{
		json j2 = j["PlayerController"];
		float forceMagnitude = j2["forceMagnitude"];
		float timeToApplyForce = j2["timeToApplyForce"];
		PlayerController* pc = new PlayerController(forceMagnitude);
		pc->timeToApplyForce = timeToApplyForce;
		pc->rb = dynamic_cast<RigidBody2d*>(dependencies.at("RigidBody2d"));
		obj->addComponent(pc);

		dependencies.emplace("PlayerController", pc);
	}

	if (j.contains("RandomPosition"))
	{
		json j2 = j["RandomPosition"];
		randomPosition* rp = new randomPosition(j["xRange"], j["yRange"]);
		obj->addComponent(rp);
	}

	if (j.contains("Walker"))
	{
		json j2 = j["Walker"];
		Walker* = new Walker(j2["speed"]);
	}
}

void loadGameObjects(GameScene& Scene)
{	
	Scene.CreateGameObject("Data/Json/player.json",nonEngineJsonCallBack);
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{	
	{
		// IMPORTANT: first we need to initialize GLib		
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);

		srand((unsigned int)time(NULL));//seed the random function


		GameScene Scene;
		UpdateParams updateParams;
		HighResolutionTimer gameTimer;
		
		loadGameObjects(Scene);
		
		return 0;

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
	return 0;
}


