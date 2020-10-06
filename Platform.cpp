#include "Platform.h"

Platform::Platform(char const* windowTitle, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
	SDL_Init(SDL_INIT_VIDEO);

	emulatorWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	emulatorRenderer = SDL_CreateRenderer(emulatorWindow, -1, SDL_RENDERER_ACCELERATED);
	emulatorDisplayTexture = SDL_CreateTexture(emulatorRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}

Platform::~Platform()
{
	SDL_DestroyTexture(emulatorDisplayTexture);
	SDL_DestroyRenderer(emulatorRenderer);
	SDL_DestroyWindow(emulatorWindow);

	SDL_Quit();
}

void Platform::Update(const void* displayBuffer, int pitch)
{
	SDL_UpdateTexture(emulatorDisplayTexture, nullptr, displayBuffer, pitch);
	SDL_RenderClear(emulatorRenderer);
	SDL_RenderCopy(emulatorRenderer, emulatorDisplayTexture, nullptr, nullptr);
	SDL_RenderPresent(emulatorRenderer);
}

bool Platform::ProcessInput(uint8_t* keypad)
{
	SDL_Event event;
	bool quit = false;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true;	break;

			case SDL_KEYDOWN:
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = true;		break;

					case SDLK_x:
						keypad[0] = 1;		break;

					case SDLK_1:
						keypad[1] = 1;		break;

					case SDLK_2:
						keypad[2] = 1;		break;

					case SDLK_3:
						keypad[3] = 1;		break;

					case SDLK_q:
						keypad[4] = 1;		break;

					case SDLK_w:
						keypad[5] = 1;		break;

					case SDLK_e:
						keypad[6] = 1;		break;

					case SDLK_a:
						keypad[7] = 1;		break;

					case SDLK_s:
						keypad[8] = 1;		break;

					case SDLK_d:
						keypad[9] = 1;		break;

					case SDLK_z:
						keypad[0xa] = 1;	break;

					case SDLK_c:
						keypad[0xb] = 1;	break;

					case SDLK_4:
						keypad[0xc] = 1;	break;

					case SDLK_r:
						keypad[0xd] = 1;	break;

					case SDLK_f:
						keypad[0xe] = 1;	break;

					case SDLK_v:
						keypad[0xf] = 1;	break;
				}
			} break;

			case SDL_KEYUP:
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_x:
						keypad[0] = 0;		break;

					case SDLK_1:
						keypad[1] = 0;		break;

					case SDLK_2:
						keypad[2] = 0;		break;

					case SDLK_3:
						keypad[3] = 0;		break;

					case SDLK_q:
						keypad[4] = 0;		break;

					case SDLK_w:
						keypad[5] = 0;		break;

					case SDLK_e:
						keypad[6] = 0;		break;

					case SDLK_a:
						keypad[7] = 0;		break;

					case SDLK_s:
						keypad[8] = 0;		break;

					case SDLK_d:
						keypad[9] = 0;		break;

					case SDLK_z:
						keypad[0xa] = 0;	break;

					case SDLK_c:
						keypad[0xb] = 0;	break;

					case SDLK_4:
						keypad[0xc] = 0;	break;

					case SDLK_r:
						keypad[0xd] = 0;	break;

					case SDLK_f:
						keypad[0xe] = 0;	break;

					case SDLK_v:
						keypad[0xf] = 0;	break;
				}
			}break;
		}
	}

	return quit;
}