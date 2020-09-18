#include "Chip8.h"

using namespace std;

Chip8::Chip8() : randEngine{ chrono::system_clock::now().time_since_epoch().count() }
{
	programCounter = START_ADRESS;

	LoadFonts();

	randNumb = uniform_int_distribution<uint16_t>(0, 255U);
}

void Chip8::Cycle()
{
	opcode = (memory[programCounter] << 8u) | memory[programCounter + 1];
	programCounter += 2;

	(this->*opcodeRoutines[(opcode & 0xf000u) >> 12u])();

	if(delayTimer) delayTimer--;
	if (soundTimer) soundTimer--;
}

void Chip8::LoadROM(char const* inputFileName)
{
	ifstream inputFile{ inputFileName, ios::binary | ios::ate };

	if(inputFile.is_open())
	{
		streampos fileSize = inputFile.tellg();
		char* readBuffer = new char[fileSize];

		inputFile.seekg(0, ios_base::beg);
		inputFile.read(readBuffer, fileSize);

		inputFile.close();

		for (int i = 0; i < fileSize; i++)
			memory[START_ADRESS + i] = readBuffer[i];

		delete[] readBuffer;
	}
}

void Chip8::LoadFonts()
{
	for (unsigned int i = 0; i < FONTSET_SIZE; i++)
		memory[FONTSET_START_ADRESS + i] = fontset[i];
}

void Chip8::InitRoutines()
{
	opcodeRoutines[0x0] = routine0;

	opcodeRoutines[0x1] = op_1nnn;
	opcodeRoutines[0x2] = op_2nnn;
	opcodeRoutines[0x3] = op_3xnn;
	opcodeRoutines[0x4] = op_4xnn;
	opcodeRoutines[0x5] = op_5xy0;
	opcodeRoutines[0x6] = op_6xnn;
	opcodeRoutines[0x7] = op_7xnn;

	opcodeRoutines[0x8] = routine8;

	opcodeRoutines[0x9] = op_9xy0;
	opcodeRoutines[0xa] = op_annn;
	opcodeRoutines[0xb] = op_bnnn;
	opcodeRoutines[0xc] = op_cxnn;
	opcodeRoutines[0xd] = op_dxyn;

	opcodeRoutines[0xe] = routineE;
	opcodeRoutines[0xf] = routineF;


	opcodeRoutines0[0x0] = op_00e0;
	opcodeRoutines0[0xe] = op_00ee;


	opcodeRoutines8[0x0] = op_8xy0;
	opcodeRoutines8[0x1] = op_8xy1;
	opcodeRoutines8[0x2] = op_8xy2;
	opcodeRoutines8[0x3] = op_8xy3;
	opcodeRoutines8[0x4] = op_8xy4;
	opcodeRoutines8[0x5] = op_8xy5;
	opcodeRoutines8[0x0] = op_8xy6;
	opcodeRoutines8[0x7] = op_8xy7;
	opcodeRoutines8[0xe] = op_8xye;


	opcodeRoutinesE[0x1] = op_exa1;
	opcodeRoutinesE[0xe] = op_ex9e;


	opcodeRoutinesF[0x07] = op_fx07;
	opcodeRoutinesF[0x0a] = op_fx0a;
	opcodeRoutinesF[0x15] = op_fx15;
	opcodeRoutinesF[0x18] = op_fx18;
	opcodeRoutinesF[0x1E] = op_fx1E;
	opcodeRoutinesF[0x29] = op_fx29;
	opcodeRoutinesF[0x33] = op_fx33;
	opcodeRoutinesF[0x55] = op_fx55;
	opcodeRoutinesF[0x65] = op_fx65;
}

void Chip8::op_00e0()
{
	memset(display, 0, sizeof(display));
}

void Chip8::op_00ee()
{
	programCounter = stack[--stackPointer];
}

void Chip8::op_1nnn()
{
	programCounter = opcode & 0x0fffu;
}

void Chip8::op_2nnn()
{
	stack[stackPointer++] = programCounter;
	programCounter = opcode & 0x0fffu;
}


void Chip8::op_3xnn()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t nn_value = opcode & 0x00ffu;

	if(registers[x_register] == nn_value)
		programCounter += 2;
}

void Chip8::op_4xnn()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t nn_value = opcode & 0x00ffu;

	if(registers[x_register] != nn_value)
		programCounter += 2;
}

void Chip8::op_5xy0()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	if(x_register == y_register)
		programCounter += 2;
}

void Chip8::op_6xnn()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t nn_value = opcode & 0x00ffu;

	registers[x_register] = nn_value;
}

void Chip8::op_7xnn()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t nn_value = opcode & 0x00ffu;

	registers[x_register] += nn_value;
}

void Chip8::op_8xy0()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	registers[x_register] = registers[y_register];
}

void  Chip8::op_8xy1()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	registers[x_register] = registers[x_register] | registers[y_register];
}

void Chip8::op_8xy2()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	registers[x_register] = registers[x_register] & registers[y_register];
}

void  Chip8::op_8xy3()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	registers[x_register] = registers[x_register] ^ registers[y_register];
}

void  Chip8::op_8xy4()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	uint16_t register_sum = registers[x_register] + registers[y_register];

	registers[0xfu] = (register_sum > 0xffu) ? 1 : 0;
	registers[x_register] += register_sum & 0xffu;
}

void  Chip8::op_8xy5()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;
	
	registers[0xfu] = (registers[x_register] > registers[y_register]) ? 1 : 0;
	registers[x_register] -= registers[y_register];
}

void  Chip8::op_8xy6()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	registers[0xfu] = registers[x_register] & 0x1u;
	registers[x_register] >>= 1u;
}

void  Chip8::op_8xy7()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	registers[0xfu] = (registers[y_register] > registers[x_register]) ? 1 : 0;
	registers[x_register] = registers[y_register] - registers[x_register];
}

void  Chip8::op_8xye()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	registers[0xfu] = registers[x_register] & 0x80u;
	registers[x_register] <<= 1u;
}

void Chip8::op_9xy0()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;

	if (x_register != y_register)
		programCounter += 2;
}

void Chip8::op_annn()
{
	indexRegister = opcode & 0x0fffu;
}

void Chip8::op_bnnn()
{
	programCounter = registers[0] + (opcode & 0x0fffu);
}

void Chip8::op_cxnn()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t nn_anding = opcode & 0x00ffu;

	registers[x_register] = (static_cast<uint8_t>(randNumb(randEngine)) & nn_anding);
}

void Chip8::op_dxyn()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	uint8_t y_register = (opcode & 0x00f0u) >> 4u;
	uint8_t n_rows = opcode & 0x000fu;

	uint8_t xCoord = registers[x_register] % DISPLAY_WIDTH;
	uint8_t yCoord = registers[y_register] % DISPLAY_HEIGHT;

	registers[0xfu] = 0;

	for(unsigned int row = 0; row < n_rows; row++)
	{
		uint8_t spriteByte = memory[indexRegister + row];

		for(unsigned int column = 0; column < SPRITE_WIDTH; column++)
		{
			uint8_t spritePixel = spriteByte & (0x80u >> column);
			uint32_t* displayPixel = &display[(yCoord + row) * DISPLAY_WIDTH + xCoord + column];

			if(spritePixel)
			{
				if(*displayPixel == 0xffffffffu)
					registers[0xfu] = 1;

				*displayPixel ^= 0xffffffffu;
			}
		}
	}
}

void Chip8::op_ex9e()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;
	
	if(keypad[registers[x_register]])
		programCounter += 2;
}

void Chip8::op_exa1()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	if(!keypad[registers[x_register]])
		programCounter += 2;
}

void Chip8::op_fx07()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	registers[x_register] = delayTimer;
}

void Chip8::op_fx0a()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	for(unsigned int keyIndex = 0; keyIndex < INPUT_KEYS_AMOUNT; keyIndex++)
		if(keypad[keyIndex])
		{
			registers[x_register] = keyIndex;
			return;
		}

	programCounter -= 2;
}

void Chip8::op_fx15()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	delayTimer = registers[x_register];
}

void Chip8::op_fx18()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	soundTimer = registers[x_register];
}

void Chip8::op_fx1E()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	indexRegister += registers[x_register];
}

void Chip8::op_fx29()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	indexRegister += FONTSET_START_ADRESS + 5 * registers[x_register];
}

void Chip8::op_fx33()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	memory[indexRegister] = registers[x_register] / 100;
	memory[indexRegister + 1] = (registers[x_register] % 100) / 10;
	memory[indexRegister + 2] = registers[x_register] % 10;
}

void Chip8::op_fx55()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	for (uint8_t i_register = 0; i_register <= x_register; i_register++)
		memory[indexRegister + i_register] = registers[i_register];
}

void Chip8::op_fx65()
{
	uint8_t x_register = (opcode & 0x0f00u) >> 8u;

	for (uint8_t i_register = 0; i_register <= x_register; i_register++)
		registers[i_register] = memory[indexRegister + i_register];
}