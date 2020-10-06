#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono>
#include "Platform.h"
#include "Chip8.h"

class Emulator
{
public:
	Emulator() : PlatformLayer{ nullptr }, Chip8Logic{ nullptr }, DisplayScale{}, CycleDelay{}, NameOfROM{ "" } {}
	~Emulator();

	void GetInput();
	void SetUp();
	void Emulate();

private:
	Platform* PlatformLayer;
	Chip8* Chip8Logic;

	int DisplayScale;
	int CycleDelay;
	std::string NameOfROM;
	
};

