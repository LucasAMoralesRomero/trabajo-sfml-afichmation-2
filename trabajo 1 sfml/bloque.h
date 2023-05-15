#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>



using namespace sf;

class bloque
{

public:
	bloque(int numerotexto);
	Sprite getSprite();
	sf::FloatRect bloque::getPosition();
	Text getText();
	bool getGolpeado();
	void setPosition(int x, int y);
	void setColorGreen();
	void setColorRed();
	void setGolpeado();

private:
	//variables de las cajas
	Texture box;
	Sprite spriteBox;
	Text textBox;
	Font font;
	bool golpeado;
};