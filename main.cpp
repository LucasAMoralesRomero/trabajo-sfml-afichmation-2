#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Juego.h"

using namespace sf;

int main(int argc, char * args[])
{
	srand(time(NULL));
	juego * partida1;
	while (true) {
		partida1 = new juego(640, 480, "Juego de mario");
	}

	return 0;
}