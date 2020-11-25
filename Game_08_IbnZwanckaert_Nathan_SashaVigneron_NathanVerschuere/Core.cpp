#pragma once
#include "pch.h"
#include "Core.h"
#include <iostream>

#include <chrono>

// Variables
SDL_Window* g_pWindow; // The window we'll be rendering to
SDL_GLContext g_pContext; // OpenGL context
Uint32 g_MilliSeconds{};
const Uint32 g_MaxElapsedTime{ 100 }; // limit in case of breakpoint

#pragma region windowInformation
extern float g_WindowWidth;
extern float g_WindowHeight;
extern std::string g_WindowTitle;
bool g_IsVSyncOn{ true };
extern InputS Input;

#pragma endregion windowInformation

#pragma region UIElements
UIRect g_UiRect{};
UIElip g_UiElip{};
UITria g_UiTria{};
UItext g_UiText{};

std::vector<AllData> g_UIData{};
#pragma endregion UIElements


#pragma region coreImplementations


void Initzialize()
{
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		QuitOnSDLError();
	}

	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create window
	g_pWindow = SDL_CreateWindow(
		g_WindowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(g_WindowWidth),
		int(g_WindowHeight),
		SDL_WINDOW_OPENGL);

	if (g_pWindow == nullptr)
	{
		QuitOnSDLError();
	}

	// Create an opengl context and attach it to the window 
	g_pContext = SDL_GL_CreateContext(g_pWindow);
	if (g_pContext == nullptr)
	{
		QuitOnSDLError();
	}

	if (g_IsVSyncOn)
	{
		// Synchronize buffer swap with the monitor's vertical refresh
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			QuitOnSDLError();
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}

	// Initialize Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the clipping (viewing) area's left, right, bottom and top
	gluOrtho2D(0, g_WindowWidth, 0, g_WindowHeight);// y from bottom to top

	// The viewport is the rectangular region of the window where the image is drawn.
	// Set it to the entire client area of the created window
	glViewport(0, 0, int(g_WindowWidth), int(g_WindowHeight));

	//Initialize Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		QuitOnImageError();
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		QuitOnTtfError();
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}
}

extern void Start();
extern void Update(float elapsedSec);
extern void Draw();
extern void End();
void DrawUI();

void Run()
{
	//Main loop flag
	bool quit{ false };

	// Set start time
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	Start();

	//The event loop
	SDL_Event e{};
	while (!quit)
	{
		// reworked Input 
		// Poll next event from queue
		while (SDL_PollEvent(&e) != 0)
		{
			// Handle the polled event
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				Input.keyDown = e.key.keysym.sym;
				break;
			case SDL_KEYUP:
				Input.keyUp = e.key.keysym.sym;
				break;
			case SDL_MOUSEMOTION:
				Input.mousePos.x = (float)e.motion.x;
				Input.mousePos.y = g_WindowHeight - e.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == 1)Input.ClickDown = Input.ClickState::MB1;
				else if (e.button.button == 2)Input.ClickDown = Input.ClickState::MB2;
				else if (e.button.button == 3)Input.ClickDown = Input.ClickState::MB3;
				else Input.ClickDown = Input.ClickState::NA;
				break;
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == 1)Input.ClickUp = Input.ClickState::MB1;
				else if (e.button.button == 2)Input.ClickUp = Input.ClickState::MB2;
				else if (e.button.button == 3)Input.ClickUp = Input.ClickState::MB3;
				else Input.ClickUp = Input.ClickState::NA;

				break;
			default:
				//std::cout << "\n Warning: This event is not captured. \n";
				break;
			}
		}

		if (!quit)
		{
			// Get current time
			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

			// Calculate elapsed time
			float elapsedSeconds = std::chrono::duration<float>(t2 - t1).count();

			// Update current time
			t1 = t2;

			// Prevent jumps in time caused by break points
			if (elapsedSeconds > g_MaxElapsedTime)
			{
				elapsedSeconds = g_MaxElapsedTime;
			}

			// Call update function, using time in seconds (!)
			Update(elapsedSeconds);

			// Draw in the back buffer
			Draw();
			DrawUI();

			//input reset
			{
				if (Input.keyDown != 0)Input.keyDownTime += elapsedSeconds;
				if (Input.keyUp != 0) {
					Input.keyDown = 0;
					Input.keyDownTime = 0;
				}
				Input.keyUp = 0;
				if(Input.ClickUp != 0)Input.ClickDown = Input.ClickState::NA;
				Input.ClickUp = Input.ClickState::NA;
			}

			// Update the window: swap back and front buffer
			SDL_GL_SwapWindow(g_pWindow);
		}
	}
	End();
}


void DrawUI() {
	for (size_t i = 0; i < g_UIData.size(); i++)
	{
		g_UIData[i].p->c = g_UIData[i].c;
		g_UIData[i].p->Size = g_UIData[i].Size;
		g_UIData[i].p->Pos = g_UIData[i].Pos;
		g_UIData[i].p->Pos2 = g_UIData[i].Pos2;
		g_UIData[i].p->Pos3 = g_UIData[i].Pos3;
		g_UIData[i].p->t = g_UIData[i].t;
		g_UIData[i].p->r = g_UIData[i].r;
		g_UIData[i].p->Draw();
	}
	g_UIData.clear();
}

void Cleanup()
{
	SDL_GL_DeleteContext(g_pContext);

	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

void QuitOnSDLError()
{
	std::cout << "Problem during SDL initialization: ";
	std::cout << SDL_GetError();
	std::cout << std::endl;
	Cleanup();
	exit(-1);
}

void QuitOnOpenGlError()
{
	std::cout << "Problem during OpenGL initialization: ";
	std::cout << SDL_GetError();
	std::cout << std::endl;
	Cleanup();
	exit(-1);
}

void QuitOnImageError()
{
	std::cout << "Problem during SDL_image initialization: ";
	std::cout << IMG_GetError();
	std::cout << std::endl;
	Cleanup();
	exit(-1);
}

void QuitOnTtfError()
{
	std::cout << "Problem during SDL_ttf initialization: ";
	std::cout << TTF_GetError();
	std::cout << std::endl;
	Cleanup();
	exit(-1);
}
#pragma endregion coreImplementations