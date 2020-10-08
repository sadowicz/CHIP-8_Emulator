#include <iostream>
#include <string>
#include <chrono>
#include "Emulator.h"

using namespace std;

int main(int argc, char* argv[])
{
	Emulator* chip8Emultor = new Emulator{};

	chip8Emultor->GetInput();
	chip8Emultor->SetUp();
	chip8Emultor->Emulate();

	delete chip8Emultor;

	return 0;
}