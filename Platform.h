#pragma once
#include <iostream>
#include <SDL.h>

class Platform
{
public:
	Platform(char const* windowTitle, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
	~Platform();

	void Update(const void* displayBuffer, int pitch);
	bool ProcessInput(uint8_t* keypad);

private:
	SDL_Window* emulatorWindow{};
	SDL_Renderer* emulatorRenderer{};
	SDL_Texture* emulatorDisplayTexture{};

};

