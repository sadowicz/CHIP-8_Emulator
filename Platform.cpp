#include "Platform.h"

using namespace std;
using namespace sf;

Platform::Platform(string windowTitle, Vector2u windowSize, Vector2u textureSize)
{
	window = new RenderWindow{ VideoMode{windowSize.x, windowSize.y}, windowTitle, Style::Titlebar | Style::Close };

	displayTexture = InitTexture(textureSize);

	displaySprite = InitSprite(displayTexture, Vector2u{windowSize.x / textureSize.x, windowSize.y / textureSize.y });
}

Platform::~Platform()
{
	delete displaySprite;
	delete displayTexture;
	delete window;
}

void Platform::Update(uint8_t* displayBuffer)
{
	displayTexture->update(displayBuffer);

	window->clear();

	window->draw(*displaySprite);

	window->display();
}

bool Platform::ProcessInput(uint8_t* keypad)
{
	Event event;
	bool quit = false;

	while(window->pollEvent(event))
	{
		switch(event.type)
		{
			case Event::Closed:
				quit = true;
				break;

			case Event::KeyPressed:
			{
				switch(event.key.code)
				{
					case Keyboard::Escape:
						quit = true;
						break;

					case Keyboard::X:
						keypad[0] = 1;
						break;

					case Keyboard::Num1:
						keypad[1] = 1;
						break;

					case Keyboard::Num2:
						keypad[2] = 1;
						break;

					case Keyboard::Num3:
						keypad[3] = 1;
						break;

					case Keyboard::Q:
						keypad[4] = 1;
						break;

					case Keyboard::W:
						keypad[5] = 1;
						break;

					case Keyboard::E:
						keypad[6] = 1;
						break;

					case Keyboard::A:
						keypad[7] = 1;
						break;

					case Keyboard::S:
						keypad[8] = 1;
						break;

					case Keyboard::D:
						keypad[9] = 1;
						break;

					case Keyboard::Z:
						keypad[0xa] = 1;
						break;

					case Keyboard::C:
						keypad[0xb] = 1;
						break;

					case Keyboard::Num4:
						keypad[0xc] = 1;
						break;

					case Keyboard::R:
						keypad[0xd] = 1;
						break;

					case Keyboard::F:
						keypad[0xe] = 1;
						break;

					case Keyboard::V:
						keypad[0xf] = 1;
						break;
				}
				break;
			}

			case Event::KeyReleased:
			{
				switch(event.key.code)
				{
					case Keyboard::Escape:
						quit = true;
						break;

					case Keyboard::X:
						keypad[0] = 0;
						break;

					case Keyboard::Num1:
						keypad[1] = 0;
						break;

					case Keyboard::Num2:
						keypad[2] = 0;
						break;

					case Keyboard::Num3:
						keypad[3] = 0;
						break;

					case Keyboard::Q:
						keypad[4] = 0;
						break;

					case Keyboard::W:
						keypad[5] = 0;
						break;

					case Keyboard::E:
						keypad[6] = 0;
						break;

					case Keyboard::A:
						keypad[7] = 0;
						break;

					case Keyboard::S:
						keypad[8] = 0;
						break;

					case Keyboard::D:
						keypad[9] = 0;
						break;

					case Keyboard::Z:
						keypad[0xa] = 0;
						break;

					case Keyboard::C:
						keypad[0xb] = 0;
						break;

					case Keyboard::Num4:
						keypad[0xc] = 0;
						break;

					case Keyboard::R:
						keypad[0xd] = 0;
						break;

					case Keyboard::F:
						keypad[0xe] = 0;
						break;

					case Keyboard::V:
						keypad[0xf] = 0;
						break;
				}
				break;
			}
		}
	}

	return quit;
}

Texture* Platform::InitTexture(Vector2u size)
{
	Texture* texture = new Texture{};
	texture->create(size.x, size.y);

	return texture;
}

Sprite* Platform::InitSprite(Texture* baseTexture, Vector2u scale)
{
	Sprite* sprite = new Sprite{ *baseTexture };
	sprite->scale(scale.x, scale.y);

	return sprite;
}