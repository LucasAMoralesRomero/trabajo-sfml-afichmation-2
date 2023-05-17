#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>


using namespace sf;

class bloque
{

public:
	bloque(int numerotexto);
	Sprite getSprite();
	sf::FloatRect bloque::getPosition();
	Text getText();
	String getTextString();
	bool getGolpeado();
	void setPosition(int x, int y);
	void setColorGreen();
	void setColorRed();
	void setGolpeado();
	void setText(int numero);

private:
	//variables de las cajas
	Texture box;
	Sprite spriteBox;
	Text textBox;
	Font font;
	bool golpeado;
};