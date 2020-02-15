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


#pragma comment(lib,"d3d11.lib")

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"
//Josh Nelson
//u0936149

//-----------------------------------------------Assignment notes---------------------------------------------------------------
// Here is where all the code is located for this assignment. 
//SmartPointer.h and WeakPointer.h inside the engine hold exactly what their names suggest 
//RefCounter.h in the engine holds the reference counter
//This file holds the tests I created. I turned off the display for this assignment. 
//Person.h is a simple class I use in my tests. A person holds a name and age and can speak it to the output buffer.




void testSmartPointersOnly()
{
	SmartPointer<Person> p(new Person("Josh", 23));
	p->Display();
	{
		SmartPointer<Person> q = p;
		q->Display();
	

		SmartPointer<Person> r;
		r = p;
		r->Display();
		// Destructor of r will be called here..
			// Destructor of q will be called here..
	}
	p->Display();
	// Destructor of p will be called here 
	// and person pointer will be deleted
}
void testSmartPointerComparison()
{
	for (int i = 0; i < 10; i++)
	{
		SmartPointer<Person> p(new Person("Josh", 23));
		SmartPointer<Person> q(new Person("Josh2", 46));
		if (p < q)
		{
			assert(p < q);
		}
		else
		{
			assert(p > q);
		}

		if (p == p)
		{
			assert(p == p);
		}
		else
		{
			assert(p != p);
		}
		if (p <= p)
		{
			assert(p <= p);
		}
		else
		{
			assert(p >= p);
		}
		if ((q < p))
		{
			assert((q < p));
		}
		else
		{
			assert((q > p));
		}
	}
	
}

bool testSmartNull()
{
	SmartPointer<Person> p;	
	{
		SmartPointer<Person> q = p;
		if (q)
		{
			return false;
		}
		// Destructor of q will be called here..

		SmartPointer<Person> r;
		SmartPointer<Person> s;
		r = p;
		r = SmartPointer<Person>(new Person("Josh", 23));
		if (!r)
		{
			return false;
		}
		r->Display();
		// Destructor of r will be called here..
	}
	if (p)
	{
		return false;
	}
	return true;
}

bool TestWeakGet()
{
	SmartPointer<Person> p(new Person("Promoted pointer", 23));
	WeakPointer<Person> observer(p);

	assert(p);

	assert(observer.Aquire());

	SmartPointer<Person> promoted = observer.Aquire();

	promoted->Display();
	return true;
}

bool TestWeakDoesntDelete()
{
	SmartPointer<Person> p(new Person("Promoted pointer", 23));

	{
		WeakPointer<Person> observer(p);
		if (!observer.Aquire())
		{
			return false;
		}
	}
	if (!p)
	{
		return false;
	}
	return true;
}

bool TestSmartAndWeakNull()
{
	WeakPointer<Person> wp1;
	{
		SmartPointer<Person> p(new Person("Good pointer", 23));
		WeakPointer<Person> wp2(p);
		wp1 = wp2;
	}
	
	if (wp1.IsAlive())
	{
		return false;
	}	
	return(true);
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	{
		testSmartPointersOnly();
		testSmartPointerComparison();
		assert(testSmartNull());
		assert(TestWeakGet());
		assert(TestWeakDoesntDelete());
		assert(TestSmartAndWeakNull());
	}	
	_CrtDumpMemoryLeaks();
	return 1;
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
		rb->mass = 10;
		rb->drag = .8f;	
		rb->minGroundingSpeed = .01f;

		player->addComponent(rb);

		PlayerController* pc = new PlayerController(.01f);	
		pc->timeToApplyForce = 1000.0f;
		pc->rb = rb;//This is really bad but I couldnt get a template function for getComponent<type> working
		player->addComponent(pc);

		GameObject* enemy = Scene.CreateGameObject();
		enemy->name->fromCharArray("Enemy");
		enemy->addComponent(new SpriteRenderer("data\\flygon.dds"));
		enemy->addComponent(new randomPosition(50, 50));
		enemy->addComponent(new Walker(1));

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


