#pragma region Windows
#include <iostream>
#include "conio.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <time.h>
#pragma endregion 

#pragma region ENGINE
#include "Synchronization/HighResolutionTimer.h"
#include "DataStructures/Pointer/SmartPointer.h"
#include "DataStructures/Pointer/WeakPointer.h"
#include "Rendering/SpriteSystem.h"
#include "Rendering/RenderingComponent/SpriteRenderer.h"
#include "Entity Component System/Game Scene/GameScene.h"
#include "Entity Component System/GameObject/GameObject.h"
#include "Physics/RigidBody2d/RigidBody2d.h"
#include "Physics/AABB/AABB.h"
#pragma endregion

#pragma region Components
#include "Components/PlayerController.h"
#include "Components/BallController.h"
#include "Components/GameManager.h"
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

void nonEngineJsonCallBack(SmartPointer<GameObject> obj, json j, std::map<std::string, Component*>& dependencies)
{
	if (j.contains("PlayerController"))
	{
		json j2 = j["PlayerController"];
		float forceMagnitude = j2["forceMagnitude"];
		float timeToApplyForce = j2["timeToApplyForce"];
		InputManager::Key downKey = j2["downKey"];
		InputManager::Key upKey = j2["upKey"];

		PlayerController* pc = new PlayerController(forceMagnitude,upKey,downKey);
		pc->timeToApplyForce = timeToApplyForce;
		pc->rb = dynamic_cast<RigidBody2d*>(dependencies.at("RigidBody2d"));
		obj->addComponent(pc);

		dependencies.emplace("PlayerController", pc);
	}

	if (j.contains("GameManager"))
	{
		json j2 = j["GameManager"];
		float timeToReset = j2["timeToReset"];
		float screenWidth = j2["screenWidth"];

		GameManager* GM = new GameManager(timeToReset, screenWidth);

		dependencies.emplace("GameManager", GM);

		obj->addComponent(GM);

	}
	if (j.contains("BallController"))
	{
		json j2 = j["BallController"];
		float speedX = j2["speedX"];
		float speedY = j2["speedY"];

		BallController* bc = new BallController(speedX,speedY);		

		dependencies.emplace("BallController", bc);
		bc->rb = dynamic_cast<RigidBody2d*>(dependencies.at("RigidBody2d"));

		obj->addComponent(bc);
	}
	
}

void loadGameObjects(GameScene& Scene, const char* jsonPath)
{	
	Scene.CreateGameObjectFromJsonAsync(jsonPath,nonEngineJsonCallBack);	
}

void loadPongSceneFromFile(GameScene& Scene)
{
	Engine::JobSystem::RunJob("LoadPlayer1", [&Scene]()
		{
			loadGameObjects(Scene, "Data/Json/Pong/p1.json");
		}
		, "Default");

	Engine::JobSystem::RunJob("LoadPlayer2", [&Scene]()
	{
		loadGameObjects(Scene, "Data/Json/Pong/p2.json");
	}
	, "Default");

	Engine::JobSystem::RunJob("LoadBall", [&Scene]()
	{
		loadGameObjects(Scene, "Data/Json/Pong/ball.json");
	}
	, "Default");

	Engine::JobSystem::RunJob("LoadBarrierTop", [&Scene]()
	{
		loadGameObjects(Scene, "Data/Json/Pong/bTop.json");
	}
	, "Default");

	Engine::JobSystem::RunJob("LoadBarrierBot", [&Scene]()
	{
		loadGameObjects(Scene, "Data/Json/Pong/bBot.json");
	}
	, "Default");

	Engine::JobSystem::RunJob("LoadGameManager", [&Scene]()
	{
		loadGameObjects(Scene, "Data/Json/Pong/GM.json");
	}
	, "Default");

}

//Not being called. This is only left in for reference on working with the ECS
void loadAndSavePongScene(GameScene& Scene)
{
	SmartPointer<GameObject> player1 = Scene.CreateGameObject();
	SmartPointer<GameObject> player2 = Scene.CreateGameObject();
	SmartPointer<GameObject> ball = Scene.CreateGameObject();

	SmartPointer<GameObject> barrierTop = Scene.CreateGameObject();
	SmartPointer<GameObject> barrierBottom = Scene.CreateGameObject();
	
	SmartPointer<GameObject> gameManager = Scene.CreateGameObject();

	gameManager->addComponent(new GameManager(2000,400));

	player1->name->fromCharArray("Player1");
	player1->addComponent(new SpriteRenderer("data\\bumperL.dds"));

	player2->name->fromCharArray("Player2");
	player2->addComponent(new SpriteRenderer("data\\bumperR.dds"));

	ball->name->fromCharArray("Ball");
	ball->addComponent(new SpriteRenderer("data\\ball.dds"));

	barrierTop->name->fromCharArray("TopWall");
	barrierTop->addComponent(new SpriteRenderer("data\\barrier.dds"));

	barrierBottom->name->fromCharArray("BottomWall");
	barrierBottom->addComponent(new SpriteRenderer("data\\barrier.dds"));


	Vector2 playerOffset(350, 0);
	Vector2 ballOffset(0, 0);

	player1->position = -playerOffset+ Vector2(0,-64);
	player2->position = playerOffset + Vector2(0, -64);
	ball->position = 0, 0;	
	barrierTop->position = Vector2(0, 268);
	barrierBottom->position = Vector2(0, -300);

	RigidBody2d* rbP1 = new RigidBody2d();
	RigidBody2d* rbP2 = new RigidBody2d();
	RigidBody2d* rbBall = new RigidBody2d();

	RigidBody2d* rbWallTop = new RigidBody2d();
	RigidBody2d* rbWallBottom = new RigidBody2d();

	rbP1->mass = 1.0f;
	rbP1->drag = .6f;
	rbP1->minGroundingSpeed = .01f;
	rbP1->canCollide = false;

	rbP2->mass = 1.0f;
	rbP2->drag = .6f;
	rbP2->minGroundingSpeed = .01f;
	rbP2->canCollide = false;

	rbBall->mass = 1.0f;
	rbBall->drag = .2f;
	rbBall->minGroundingSpeed = .01f;
	

	rbWallTop->mass = 1.0f;
	rbWallTop->drag = 1.0f;
	rbWallTop->minGroundingSpeed = 10.0f;
	rbWallTop->canCollide = false;
	
	rbWallBottom->mass = 1.0f;
	rbWallBottom->drag = 1.0f;
	rbWallBottom->minGroundingSpeed = 10.0f;
	rbWallBottom->canCollide = false;
	
	float moveforce = .01f;

	PlayerController* pc1 = new PlayerController(moveforce, InputManager::W, InputManager::S);
	PlayerController* pc2 = new PlayerController(moveforce, InputManager::I, InputManager::K);	
	BallController* bc = new BallController(.05f, .001f);



	AABB* ballBB = new AABB(0, 32, 32, 32);
	AABB* player1BB = new AABB(0, 64, 32, 64);
	AABB* player2BB = new AABB(0, 64, 32, 64);
	AABB* wallTopBB = new AABB(0, 16, 400, 16);
	AABB* wallBotBB = new AABB(0, 16, 400, 16);

	pc1->rb = rbP1;
	pc2->rb = rbP2;
	bc->rb = rbBall;

	rbBall->physicsType = 1;


	player1->addComponent(rbP1);
	player2->addComponent(rbP2);
	ball->addComponent(rbBall);

	barrierTop->addComponent(rbWallTop);
	barrierBottom->addComponent(rbWallBottom);

	player1->addComponent(pc1);
	player2->addComponent(pc2);
	ball->addComponent(bc);

	player1->addComponent(player1BB);
	player2->addComponent(player2BB);
	ball->addComponent(ballBB);
	barrierTop->addComponent(wallTopBB);
	barrierBottom->addComponent(wallBotBB);

	json j;
	std::ofstream myfile;

	player1->Serialize(j);	
	myfile.open("Data/Json/Pong/p1.json");
	myfile << j;
	myfile.close();	

	j.clear();
	player2->Serialize(j);
	myfile.open("Data/Json/Pong/p2.json");
	myfile << j;
	myfile.close();

	j.clear();
	ball->Serialize(j);
	myfile.open("Data/Json/Pong/ball.json");
	myfile << j;
	myfile.close();

	j.clear();
	barrierTop->Serialize(j);
	myfile.open("Data/Json/Pong/bTop.json");
	myfile << j;
	myfile.close();
	j.clear();

	barrierBottom->Serialize(j);
	myfile.open("Data/Json/Pong/bBot.json");
	myfile << j;
	myfile.close();

	j.clear();
	gameManager->Serialize(j);
	myfile.open("Data/Json/Pong/GM.json");
	myfile << j;
	myfile.close();
}

//do any setup the engine needs
void initEngine()
{
	Engine::JobSystem::CreateQueue("Default", 4);
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
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Pong Final", -1, 800, 600);

		srand((unsigned int)time(NULL));//seed the random function


		GameScene Scene;
		UpdateParams updateParams;
		HighResolutionTimer gameTimer;

		//loadAndSavePongScene(Scene);
		loadPongSceneFromFile(Scene);//load the scene file

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
					if (updateParams.deltaTime > 500) {updateParams.deltaTime = 1/60;}//Allow debugging with constant frametimes
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


