#include "juego.h"
#include "bloque.h"
#include "audioEngine.h"
#include <stdlib.h>

juego::juego(int ancho, int alto, std::string titulo)
{
	fps = 60;
	TIEMPO_JUEGO = 60;
	ventana1 = new RenderWindow(VideoMode(ancho, alto), titulo);

	ventana1->setFramerateLimit(fps);

	//generamos el audioEngine
	audio = new audioEngine();
	
	//inicializamos el rejor
	reloj1 = new Clock();
	tiempo1 = new Time();
	tiempoInicio = reloj1->getElapsedTime().asSeconds() + TIEMPO_JUEGO;
	gameOver = false;
	for (int i = 0; i < 10; i++) {
		bloquesGolpeados[i] = 0;
	}



	//sprite y textura de fondo
	background = new Texture;
	spriteBackground = new Sprite;
	//inicializamos fondo
	background->loadFromFile("assets/mundo_fondo.jpg");
	spriteBackground->setTexture(*background);
	//ajustamos al tamaño de ventana
	spriteBackground->setScale((float)(ventana1->getSize().x) / background->getSize().x, (float)(ventana1->getSize().y) / background->getSize().y); //escalamos el fondo
	//empezamos a reproducir el audio
	audio->playBackgroundSound();


	//ajustes de HUD
	font = new Font;
	font->loadFromFile("assets/fontnes.otf");
	stringTimerText = new Text();
	stringTimerText->setFont(*font);
	stringTimerText->setPosition(400, 1);

	stringGameOverText = new Text();
	stringGameOverText->setFont(*font);
	stringGameOverText->setString("Time's up, GAME OVER!");
	stringGameOverText->setFillColor(sf::Color::Red);
	stringGameOverText->setPosition((float)(ventana1->getSize().x / 3), (float)(ventana1->getSize().y / 2));

	stringGameWinText = new Text();
	stringGameWinText->setFont(*font);
	stringGameWinText->setString("Ganaste!");
	stringGameWinText->setFillColor(sf::Color::Green);
	stringGameWinText->setPosition((float)(ventana1->getSize().x / 3), (float)(ventana1->getSize().y / 2));

	//////////////

	//sprite y textura de mario
	mario = new Texture;
	//inicializamos mario
	mario->loadFromFile("assets/spritesheet.png");
	spriteMario = new Afichmation(*mario, true, 104, 125);

	//añadimos las animaciones que se van a usar
	spriteMario->Add("idle", { 0, 1, 2, 1, 0 }, 8, true);
	spriteMario->Add("run", { 3, 4, 5, 6, 7, 8, 9, 10, 11, 10, 9, 8, 7 }, 8, true);
	spriteMario->Add("jump", { 12, 13, 14, 13, 12 }, 8, false);
	//reproduzco la animacion idle
	spriteMario->Play("idle");
	//seteo la escala del sprite con setScale
	spriteMario->setScale(Vector2f(0.5f, 0.5f));
	//ubicamos al personaje
	spriteMario->move(500, 400);


	//generar los numeros random

	//creamos aleatoriamente el numero para el bloque, si se repite lo volvemos a sacar
	for (int h = 0; h <= 9; h++) {
		int num = 1 + rand() % (1000 - 1);
		arrayNumerosBloques[h] = num;
		numeroAnterior = num;
		}
	for (int k = 0; k < 10; k++) {
		arrayOrdenado[k] = arrayNumerosBloques[k];
	}
		//ordenamos el array
		int minimo=0, auxiliar=0;
		for (int i = 0; i < 10; i++) {
			minimo = i;
			for (int j = i + 1; j < 10; j++) {
				if (arrayOrdenado[j] < arrayOrdenado[minimo]) {
					minimo = j;
				}
			}
			auxiliar = arrayOrdenado[i];
			arrayOrdenado[i] = arrayOrdenado[minimo];
			arrayOrdenado[minimo] = auxiliar;
		}

	//generamos los objetos bloques y le pasamos el numero aleatorio y posicionamos
	for (int i = 0; i <= 9; i++)
	{
		arrayBloques[i] = new bloque(arrayNumerosBloques[i]);
		arrayBloques[i]->setPosition((65 * i), 200);
	}

	evento1 = new Event;
	gameLoop();
}

void juego::gameLoop() {

	while (ventana1->isOpen()){  
		*tiempo1 = reloj1->getElapsedTime();
		if (tiempo1->asSeconds() > 1 / fps && !gameOver && !win)
		{
			procesarColisiones();
			procesarEventos();
			procesarGravedad();
			spriteMario->Update();
			dibujar();
			procesarTiempo();
			checkWin();
		}
		if (gameOver) {
			//ventana1->clear();
			ventana1->clear();
			for (int i = 0; i <= 9; i++)
			{
				arrayBloques[i]->setText(arrayOrdenado[i]);
			}
			ventana1->draw(*spriteBackground);
			ventana1->draw(*spriteMario);
			//ventana1->draw(arrayBloques[3]->getSprite());
			for (int i = 0; i <= 9; i++)
			{
				ventana1->draw(arrayBloques[i]->getSprite());
				ventana1->draw(arrayBloques[i]->getText());
			}

			ventana1->draw(*stringTimerText);
			if (!win) {
				ventana1->draw(*stringGameOverText);
				ventana1->display();
			}
			
		}
		if (win) {
			ventana1->clear();
			ventana1->draw(*spriteBackground);
			ventana1->draw(*spriteMario);
			for (int i = 0; i <= 9; i++)
			{
				arrayBloques[i]->setText(arrayOrdenado[i]);
			}
			//ventana1->draw(arrayBloques[3]->getSprite());
			for (int i = 0; i <= 9; i++)
			{
				ventana1->draw(arrayBloques[i]->getSprite());
				ventana1->draw(arrayBloques[i]->getText());
			}

			ventana1->draw(*stringTimerText);
			ventana1->draw(*stringGameWinText);
			ventana1->display();
		}
	}
}

void juego::dibujar() {
	
	ventana1->clear();
	ventana1->draw(*spriteBackground);
	ventana1->draw(*spriteMario);
	//ventana1->draw(arrayBloques[3]->getSprite());
	for (int i = 0; i <= 9; i++)
	{
		ventana1->draw(arrayBloques[i]->getSprite());
		ventana1->draw(arrayBloques[i]->getText());
	}

	ventana1->draw(*stringTimerText);
	ventana1->display();
	cout << "-------------------" << endl;
	for (int i = 0; i <= 9; i++)
	{
		cout << arrayNumerosBloques[i];
		cout << "-";
	}
	cout << "-------------------" << endl;

	cout << "-------------------" << endl;
	for (int i = 0; i <= 9; i++)
	{
		cout << arrayOrdenado[i];
		cout << "-";
	}
	cout << "-------------------" << endl;


}
void juego::procesarEventos() {
	while (ventana1->pollEvent(*evento1))
	{
		switch (evento1->type)
		{
		case Event::Closed:
			ventana1->close();
			exit(1);
			break;

		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::Left)) //corre a la izquierda
			{
				velocidadActual = velocidadActual + aceleracion;//aceleramos el movimiento del personaje
				if (velocidadActual > velocidadMaxima)//si la aceleracion es mayor a la maxima, la seteamos nuevamente
				{
					velocidadActual = velocidadMaxima;
				}
				spriteMario->Play("run");
				spriteMario->FlipX(false);
				spriteMario->setPosition(spriteMario->getPosition().x - velocidadActual, spriteMario->getPosition().y);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right))//corre a la derecha
			{
				velocidadActual = velocidadActual + aceleracion;//aceleramos el movimiento del personaje
				if (velocidadActual > velocidadMaxima)//si la aceleracion es mayor a la maxima, la seteamos nuevamente
				{
					velocidadActual = velocidadMaxima;
				}
				spriteMario->Play("run");
				spriteMario->FlipX(true);
				spriteMario->setPosition(spriteMario->getPosition().x + velocidadActual, spriteMario->getPosition().y);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space) && spriteMario->getPosition().y == floor)//salto de mario
			{
				if (en_piso)
				{
					spriteMario->Play("jump");
					spriteMario->setPosition(spriteMario->getPosition().x, spriteMario->getPosition().y - 90);
					jumpVelocity += gravity;
					jumpVelocity = -10.f; // reiniciar la velocidad de salto
					en_piso = false;//desactivamos bandera del piso
					activar_idle = false;//desactivamos bandera de idle
				}
			}
				break;
		default://en default, ajustamos la aceleracion y seteamos si se reproduce la animacion de idle
			if (activar_idle)
			{
				spriteMario->Play("idle");
				velocidadActual = 0;//ajustamos a cero la velocidad de mario
			}

		}

	}
}

void juego::procesarGravedad() {//aca procesamos la gravedad para mario
	spriteMario->move(0.f, jumpVelocity);//aplicamos la gravedad y la velocidad de salto
	jumpVelocity += 0.5f;//ajustamos el valor de gravedad para controlar la altura de salto
	if (!en_piso)
	{
		en_piso = true;
		activar_idle = true;
	}
	if (spriteMario->getPosition().y < floor)
	{
		spriteMario->setPosition(spriteMario->getPosition().x, spriteMario->getPosition().y +4);
	}
	if (spriteMario->getPosition().y > floor)
	{
		spriteMario->setPosition(spriteMario->getPosition().x, (float)floor);
	}
}

void juego::procesarColisiones() {//aca vamos a procesar la colision de mario con las cajas
	for (int i = 0; i < 10; i++) {

		if (spriteMario->getGlobalBounds().intersects(arrayBloques[i]->getPosition()) && arrayBloques[i]->getGolpeado() == false)
		{
			if ((arrayBloques[i]->getTextString()) == (to_string)(arrayOrdenado[numeroBloque])) {
				arrayBloques[i]->setColorGreen();
				arrayBloques[i]->setGolpeado();
				numeroBloque = numeroBloque + 1;
				bloquesGolpeados[i] = 1;
			}
			else {
				arrayBloques[i]->setColorRed();
				arrayBloques[i]->setGolpeado();
				tiempoInicio = tiempoInicio - 10.f;
				numeroBloque = numeroBloque + 1;
				//reproducimos audio de errar
				audio->playMusicError();
			}




		}
	}
}


void juego::procesarTiempo()
{
	tiempoFin = reloj1->getElapsedTime().asSeconds();
	int seconds = ((int)(tiempoInicio - tiempoFin));
	stringTimerText->setString("Tiempo: " + (std::to_string(seconds)));
	if (seconds == -1 || seconds < -2)//si el tiempo es cero es game over (si le digo == a cero el reloj se detiene en 1)
	{
		gameOver = true;
	}
	//cout << seconds << endl;
}

void juego::bubbleSort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// Intercambiar los elementos si están en el orden incorrecto
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void juego::checkWin() {
	if (bloquesGolpeados[0]==1 && bloquesGolpeados[1] == 1 && bloquesGolpeados[2] == 1 && bloquesGolpeados[3] == 1 && bloquesGolpeados[4] == 1 && bloquesGolpeados[5] == 1 && bloquesGolpeados[6] == 1 && bloquesGolpeados[7] == 1 && bloquesGolpeados[8] == 1 && bloquesGolpeados[9] == 1) {
		win = true;
	}
}
