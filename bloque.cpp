#include "bloque.h"

bloque::bloque(int numerotexto) 
{

	//inicializamos el box
	box.loadFromFile("assets/bloque_pared.png");
	spriteBox.setTexture(box);
	//inicializamos la fuente
	font.loadFromFile("assets/fontnes.otf");
	//inicializamo el texto del bloque
	textBox.setFont(font);
	textBox.setCharacterSize(20);
	textBox.setString((std::to_string(numerotexto)));
	golpeado = false;//por defecto no esta golpeado, recien fue creado

}

Sprite bloque::getSprite() {
	return spriteBox;
}



Text bloque::getText() {//retornamos el text
	return textBox;
}

String bloque::getTextString() {//retornamos el numero de bloque como string
	String txt = textBox.getString();
	return txt;

}

bool bloque::getGolpeado() {
	return golpeado;
}

void bloque::setText(int numero) {
	textBox.setString((std::to_string(numero)));
}

void bloque::setPosition(int x, int y) {
	spriteBox.setPosition(x, y);
	textBox.setPosition(x, y);
}

void bloque::setGolpeado() {//indicamos si el bloque fue golpeado
	golpeado = true;
}

sf::FloatRect bloque::getPosition() {
	sf::FloatRect posicion = spriteBox.getGlobalBounds();
	return posicion;
}

void bloque::setColorGreen() {
	textBox.setFillColor(sf::Color::Green);
}

void bloque::setColorRed() {
	textBox.setFillColor(sf::Color::Red);
}