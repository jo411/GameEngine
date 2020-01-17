#include <iostream>
#include "conio.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include "SpriteSystem.h"
#include "GameScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

#pragma region Components
#include "Components/randomPosition.h"
#pragma endregion


#pragma comment(lib,"d3d11.lib")

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"
//Josh Nelson
//u0936149
//

//Main Game logic

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{		
	
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	{
		// IMPORTANT: first we need to initialize GLib
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
		GameScene Scene;

		GameObject* player = Scene.CreateGameObject();
		player->name->fromCharArray("Player");
		player->addComponent(new SpriteRenderer("data\\GoodGuy.dds"));
		//player->addComponent(new randomPosition(100, 100));

		if (bSuccess)
		{
			// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
			GLib::SetKeyStateChangeCallback(TestKeyCallback);

			// Create a couple of sprites using our own helper routine CreateSprite		

			bool bQuit = false;

			do
			{
				// IMPORTANT: We need to let GLib do it's thing. 
				GLib::Service(bQuit);

				if (!bQuit)
				{
					Scene.update(NULL);//update the scene
					GLib::BeginRendering();
					GLib::Sprites::BeginRendering();
					//Scene.draw(NULL);//draw the scene
					GLib::Sprites::EndRendering();
					GLib::EndRendering();
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


