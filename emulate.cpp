#include <iostream>
#include <string>
#include <chrono>
#include "Emulator.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*
	if(argc != 4)
	{
		cerr << "USAGE: " << argv[0] << " <SCALE> <DELAY> <ROM>\n";
		exit(EXIT_FAILURE);
	}

	int displayScale = stoi(argv[1]);
	int cycleDelay = stoi(argv[2]);
	char const* romFileName = argv[3];

	Platform* emulatorPlatformLayer = new Platform{ "CHIP-8 EMULATOR by Filip", static_cast<int>(Chip8::DISPLAY_WIDTH) * displayScale, static_cast<int>(Chip8::DISPLAY_HEIGHT) * displayScale, static_cast<int>(Chip8::DISPLAY_WIDTH), static_cast<int>(Chip8::DISPLAY_HEIGHT) };

	Chip8* emulatorChip8Logic = new Chip8{};
	emulatorChip8Logic->LoadROM(romFileName);

	//int displayPitch = sizeof(emulatorChip8Logic->display[0]) * Chip8::DISPLAY_WIDTH;

	auto lastCycleTime = chrono::high_resolution_clock::now();
	bool quitEmulating = false;

	while(!quitEmulating)
	{
		quitEmulating = emulatorPlatformLayer->ProcessInput(emulatorChip8Logic->keypad);

		auto currentTime = chrono::high_resolution_clock::now();
		float timeDifference = chrono::duration<float, chrono::nanoseconds::period>(currentTime - lastCycleTime).count();

		if(timeDifference > cycleDelay)
		{
			lastCycleTime = currentTime;
			emulatorChip8Logic->Cycle();
			emulatorPlatformLayer->Update(emulatorChip8Logic->display, displayPitch);
		}
	}

	delete emulatorChip8Logic;
	delete emulatorPlatformLayer;

	return 0;
	*/

	Emulator* chip8Emultor = new Emulator{};

	chip8Emultor->GetInput();
	chip8Emultor->SetUp();
	chip8Emultor->Emulate();

	delete chip8Emultor;

	return 0;
}