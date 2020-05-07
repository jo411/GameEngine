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
#include "Physics/AABB.h"
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

void loadPongScene(GameScene& Scene)
{
	SmartPointer<GameObject> player1 = Scene.CreateGameObject();
	SmartPointer<GameObject> player2 = Scene.CreateGameObject();
	SmartPointer<GameObject> ball = Scene.CreateGameObject();

	player1->name->fromCharArray("Player1");
	player1->addComponent(new SpriteRenderer("data\\bumper.dds"));

	player2->name->fromCharArray("Player1");
	player2->addComponent(new SpriteRenderer("data\\bumper.dds"));

	ball->name->fromCharArray("Ball");
	ball->addComponent(new SpriteRenderer("data\\ball.dds"));

	Vector2 playerOffset(350, 0);
	Vector2 ballOffset(0, 0);

	player1->position = -playerOffset+ Vector2(0,-64);
	player2->position = playerOffset + Vector2(0, 64);
	ball->position = 0, 0;

	player2->rotation = 180;
}

void loadCollisionScene(GameScene& Scene)
{
	////Create game objects for the scene
	SmartPointer<GameObject> player = Scene.CreateGameObject();
	player->name->fromCharArray("Player");
	player->addComponent(new SpriteRenderer("data\\pikachu.dds"));

	SmartPointer<GameObject> player2 = Scene.CreateGameObject();
	player2->name->fromCharArray("Player2");
	player2->addComponent(new SpriteRenderer("data\\pikachu.dds"));


	
	Vector2 CollisionForce;
	CollisionForce.x = .05;
	CollisionForce.y = .01;

	RigidBody2d* rb = new RigidBody2d();
	rb->mass = 10;
	rb->drag = .6f;
	rb->minGroundingSpeed = .01f;
	

	RigidBody2d* rb2 = new RigidBody2d();
	rb2->mass = 10;
	rb2->drag = .6f;
	rb2->minGroundingSpeed = .01f;

	RigidBody2d* rb3 = new RigidBody2d();
	rb3->mass = 10;
	rb3->drag = .6f;
	rb3->minGroundingSpeed = .01f;

	rb2->addForce(-CollisionForce);
	rb->addForce(CollisionForce);
	rb3->addForce(Vector2(0,.1));

	player->addComponent(rb);	
	player2->addComponent(rb3);

	SmartPointer<GameObject> enemy = Scene.CreateGameObject();
	enemy->name->fromCharArray("Enemy");
	enemy->addComponent(new SpriteRenderer("data\\flygon.dds"));	

	enemy->addComponent(rb2);

	Vector2 startPosEnemy(200,0);	

	Vector2 startPosPlayer(-200,0);
	Vector2 startPosPlayer2(120, -250);

	player2->position = startPosPlayer2;
	player->position = startPosPlayer;
	enemy->position = startPosEnemy;

	player->rotation = 0;	
	enemy->rotation = 0;
	player2->rotation = 0;
	
	Vector2 enemyCenter(0, 94);
	Vector2 enemyExtents(82, 94);

	AABB* enemyBB = new AABB(enemyCenter.x, enemyCenter.y, enemyExtents.x, enemyExtents.y);
	AABB* playerBB = new AABB(0, 58, 50, 58);
	AABB* player2BB = new AABB(0, 58, 50, 58);

	player->addComponent(playerBB);
	enemy->addComponent(enemyBB);
	player2->addComponent(player2BB);

	//Draw debug bounding boxes
	/*Matrix4 enemyToWorld = enemy->ObjectToWorldTransform();

	SmartPointer<GameObject> marker1 = Scene.CreateGameObject();
	marker1->name->fromCharArray("Marker1");
	marker1->addComponent(new SpriteRenderer("data\\marker.dds"));
	

	Vector4 LocalPos(enemyCenter.x - enemyExtents.x, enemyCenter.y + enemyExtents.y, 0, 1);
	Vector4 transformed = enemyToWorld *LocalPos;
	marker1->position.x = transformed.X();
	marker1->position.y = transformed.Y();

	SmartPointer<GameObject> marker2 = Scene.CreateGameObject();
	marker2->name->fromCharArray("Marker2");
	marker2->addComponent(new SpriteRenderer("data\\marker.dds"));

	Vector4 LocalPos2(enemyCenter.x + enemyExtents.x, enemyCenter.y + enemyExtents.y, 0, 1);
	Vector4 transformed2 = enemyToWorld *LocalPos2;
	marker2->position.x = transformed2.X();
	marker2->position.y = transformed2.Y();

	SmartPointer<GameObject> marker3 = Scene.CreateGameObject();
	marker3->name->fromCharArray("Marker3");
	marker3->addComponent(new SpriteRenderer("data\\marker.dds"));

	Vector4 LocalPos3(enemyCenter.x - enemyExtents.x, enemyCenter.y - enemyExtents.y, 0, 1);
	Vector4 transformed3 = enemyToWorld *LocalPos3;
	marker3->position.x = transformed3.X();
	marker3->position.y = transformed3.Y();

	SmartPointer<GameObject> marker4 = Scene.CreateGameObject();
	marker4->name->fromCharArray("Marker4");
	marker4->addComponent(new SpriteRenderer("data\\marker.dds"));

	Vector4 LocalPos4(enemyCenter.x + enemyExtents.x, enemyCenter.y - enemyExtents.y, 0, 1);
	Vector4 transformed4 = enemyToWorld *LocalPos4;
	marker4->position.x = transformed4.X();
	marker4->position.y = transformed4.Y();
	
	marker1->rotation = enemy->rotation;
	marker2->rotation = enemy->rotation;
	marker3->rotation = enemy->rotation;
	marker4->rotation = enemy->rotation;*/
	
}
//do anything that the engine needs to do for shutdown before unloading
void shutdownEngine()
{
	Engine::JobSystem::RequestShutdown();
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
#ifdef _DEBUG
	//Force memory leak detection to run automatically at program termination
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);
#endif

	initEngine();
	
	{
		// IMPORTANT: first we need to initialize GLib		
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);

		srand((unsigned int)time(NULL));//seed the random function


		GameScene Scene;
		UpdateParams updateParams;
		HighResolutionTimer gameTimer;
		
		/*Engine::JobSystem::RunJob("LoadPlayer", [&Scene]() 
		{
			loadGameObjects(Scene, "Data/Json/player.json");
		}
		, "Default");


		Engine::JobSystem::RunJob("LoadEnemy", [&Scene]()
		{
			loadGameObjects(Scene, "Data/Json/enemy.json");
		}
		, "Default");	*/	
		
		loadPongScene(Scene);

		if (bSuccess)
		{
			// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
			//(updateParams.getInput())			
			GLib::SetKeyStateChangeCallback(InputManager::KeyCallback);

			
			bool bQuit = false;

			updateParams.deltaTime = 1 / 60;//60fps in miliseconds default
				
			do
			{
				gameTimer.StartCounter();//reset timer	

				// IMPORTANT: We need to let GLib do it's thing. 
				GLib::Service(bQuit);				

				if (!bQuit)
				{
					Scene.checkCollision(&updateParams);

					Scene.update(&updateParams);//update the scene

					GLib::BeginRendering();
					GLib::Sprites::BeginRendering();

					Scene.draw(&updateParams);//draw the scene

					GLib::Sprites::EndRendering();
					GLib::EndRendering();
					

					updateParams.deltaTime = gameTimer.GetCounter();//get last frame time	
					
#ifdef _DEBUG
					if (updateParams.deltaTime > 500) {updateParams.deltaTime = 1/60;}
#endif // DEBUG

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


