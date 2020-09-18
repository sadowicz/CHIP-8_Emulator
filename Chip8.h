#pragma once

//#define REGISTERS_AMOUNT 16
//#define MEMORY_SIZE 4096
//#define STACK_LEVELS 16
//#define DISPLAY_SIZE 64 * 32 // width * height
//#define INPUT_KEYS_AMOUNT 16


#include <cstdint>
#include <fstream>
#include <random>
#include <chrono>

class Chip8
{
public:
	Chip8();

	void LoadROM(char const* inputFileName);
	void LoadFonts();

	void op_00e0();
	void op_00ee();
	void op_1nnn();
	void op_2nnn();
	void op_3xnn();
	void op_4xnn();
	void op_5xy0();
	void op_6xnn();
	void op_7xnn();
	void op_8xy0();
	void op_8xy1();
	void op_8xy2();
	void op_8xy3();
	void op_8xy4();
	void op_8xy5();
	void op_8xy6();
	void op_8xy7();
	void op_8xye();
	void op_9xy0();
	void op_annn();
	void op_bnnn();
	void op_cxnn();
	void op_dxyn();
	void op_ex9e();
	void op_exa1();
	void op_fx07();
	void op_fx0a();
	void op_fx15();
	void op_fx18();
	void op_fx1E();
	void op_fx29();
	void op_fx33();
	void op_fx55();
	void op_fx65();


	static const unsigned int REGISTERS_AMOUNT = 16;
	static const unsigned int MEMORY_SIZE = 4096;
	static const unsigned int STACK_LEVELS = 16;
	static const unsigned int DISPLAY_WIDTH = 64; // width * height
	static const unsigned int DISPLAY_HEIGHT = 32; // width * height
	static const unsigned int INPUT_KEYS_AMOUNT = 16;
	static const unsigned int FONTSET_SIZE = 80;

	const unsigned int START_ADRESS = 0x200u;
	const unsigned int FONTSET_START_ADRESS = 0x50u;
	const unsigned int SPRITE_WIDTH =8;

	uint8_t registers[REGISTERS_AMOUNT]{};
	uint8_t memory[MEMORY_SIZE]{};
	uint16_t indexRegister{};
	uint16_t programCounter{};
	uint16_t stack[STACK_LEVELS]{};
	uint8_t stackPointer{};
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint8_t keypad[INPUT_KEYS_AMOUNT]{};
	uint32_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT]{};
	uint8_t fontset[FONTSET_SIZE] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
	std::default_random_engine randEngine;
	std::uniform_int_distribution<uint16_t> randNumb;


	uint16_t opcode;

};

