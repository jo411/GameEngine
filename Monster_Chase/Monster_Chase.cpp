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

#pragma region JSON
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#pragma endregion

#pragma region JobSystem
#include "Job System/JobSystem.h"

#pragma endregion

#include <fstream>
#include <unordered_map>



#pragma comment(lib,"d3d11.lib")

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"


using namespace std::placeholders;


//Josh Nelson
//u0936149

//---------------------------------------------- - Assignment 2.7 notes-------------------------------------------------------------- -
//
//

//Only used to create initial json objects
void CreateAndSaveGameObjects(GameScene& Scene)
{
	////Create game objects for the scene
	//SmartPointer<GameObject> player = Scene.CreateGameObject();
	//player->name->fromCharArray("Player");
	//player->addComponent(new SpriteRenderer("data\\pikachu.dds"));

	//RigidBody2d* rb = new RigidBody2d();
	//rb->mass = 10;
	//rb->drag = .8f;
	//rb->minGroundingSpeed = .01f;

	//player->addComponent(rb);

	//PlayerController* pc = new PlayerController(.01f);
	//pc->timeToApplyForce = 1000.0f;
	//pc->rb = rb;//This is really bad but I couldnt get a template function for getComponent<type> working
	//player->addComponent(pc);

	//SmartPointer<GameObject> enemy = Scene.CreateGameObject();
	//enemy->name->fromCharArray("Enemy");
	//enemy->addComponent(new SpriteRenderer("data\\flygon.dds"));
	//enemy->addComponent(new randomPosition(50, 50));
	//enemy->addComponent(new Walker(1));

	//json j;
	//std::ofstream myfile;

	//enemy->Serialize(j);	
	//myfile.open("Data/Json/enemy.json");
	//myfile << j;
	//myfile.close();	

	//j.clear();
	//player->Serialize(j);
	//myfile.open("Data/Json/player.json");
	//myfile << j;
	//myfile.close();
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
		randomPosition* rp = new randomPosition(j2["xRange"], j2["yRange"]);
		obj->addComponent(rp);
	}

	if (j.contains("Walker"))
	{
		json j2 = j["Walker"];
		Walker* walkComp = new Walker(j2["speed"]);
		obj->addComponent(walkComp);
	}
}

void loadGameObjects(GameScene& Scene, const char* jsonPath)
{	
	Scene.CreateGameObjectFromJsonAsync(jsonPath,nonEngineJsonCallBack);	
}

//do any setup the engine needs
void initEngine()
{
	Engine::JobSystem::CreateQueue("Default", 2);
}

//do anything that the engine needs to do for shutdown before unloading
void shutdownEngine()
{
	Engine::JobSystem::RequestShutdown();
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{	
	//Force memory leak detection to run automatically at program termination
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);


	initEngine();
	
	{
		// IMPORTANT: first we need to initialize GLib		
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);

		srand((unsigned int)time(NULL));//seed the random function


		GameScene Scene;
		UpdateParams updateParams;
		HighResolutionTimer gameTimer;
		
		Engine::JobSystem::RunJob("LoadPlayer", [&Scene]() 
		{
			loadGameObjects(Scene, "Data/Json/player.json");
		}
		, "Default");


		Engine::JobSystem::RunJob("LoadEnemy", [&Scene]()
		{
			loadGameObjects(Scene, "Data/Json/enemy.json");
		}
		, "Default");		
		

		if (bSuccess)
		{
			// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
			//(updateParams.getInput())			
			GLib::SetKeyStateChangeCallback(InputManager::KeyCallback);

			
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

			shutdownEngine();
			//Tell the scene to release all resources
			Scene.Release();
					
			// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();
		}
	}
	return 0;
}


