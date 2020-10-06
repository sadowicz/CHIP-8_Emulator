#include "Emulator.h"

using namespace std;

Emulator::~Emulator()
{
	delete Chip8Logic;
	delete PlatformLayer;
}

void Emulator::GetInput()
{
	cout << "Enter Settings\n";

	cout << "Display scale: ";
	cin >> DisplayScale;

	cout << "Cycle delay: ";
	cin >> CycleDelay;

	cout << "ROM name: ";
	cin >> NameOfROM;
}

void Emulator::SetUp()
{
	PlatformLayer = new Platform{ "CHIP-8 EMULATOR by Filip", static_cast<int>(Chip8::DISPLAY_WIDTH) * DisplayScale, static_cast<int>(Chip8::DISPLAY_HEIGHT) * DisplayScale, static_cast<int>(Chip8::DISPLAY_WIDTH), static_cast<int>(Chip8::DISPLAY_HEIGHT) };

	Chip8Logic = new Chip8{};
	Chip8Logic->LoadROM(NameOfROM);
}

void Emulator::Emulate()
{
	int displayPitch = sizeof(Chip8Logic->display[0]) * Chip8::DISPLAY_WIDTH;

	auto lastCycleTime = chrono::high_resolution_clock::now();
	bool quitEmulating = false;

	while(!quitEmulating)
	{
		quitEmulating = PlatformLayer->ProcessInput(Chip8Logic->keypad);

		auto currentTime = chrono::high_resolution_clock::now();
		float timeDifference = chrono::duration<float, chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if(timeDifference > CycleDelay)
		{
			lastCycleTime = currentTime;
			Chip8Logic->Cycle();
			PlatformLayer->Update(Chip8Logic->display, displayPitch);
		}
	}
}