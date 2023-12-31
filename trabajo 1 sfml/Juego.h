#pragma once
#include "SFML\Graphics.hpp"
#include "Afichmation.h"
#include "bloque.h"
#include "audioEngine.h"
#include <iostream>

using namespace sf;


class juego {

public:
	juego(int ancho, int alto, std::string titulo);
	void gameLoop();
	void dibujar();
	void procesarEventos();
	void procesarGravedad();//aca proceso la gravedad que se aplica en el mundo a mario
	void procesarColisiones();//procesamos las colisiones con las cajas
	void procesarTiempo();//procesamos el tiempo
	void bubbleSort(int arr[], int size);//algoritmo bubble sort
	void checkWin();//chequeamos si ganamos

private:

	RenderWindow * ventana1;
	int fps;
	Texture * background;
	Sprite * spriteBackground;

	//variables de mario
	Event * evento1;
	Texture * mario;
	Afichmation * spriteMario;
	float jumpVelocity = -10.f;
	bool en_piso = true;
	bool activar_idle = true;
	float aceleracion = 0.1f;
	float velocidadMaxima = 6.0f;
	float velocidadActual = 0.0f;

	

	//variables de juego (mundo)
	int floor = 400;
	const float gravity = 0.5f;
	int numeroBloque = 0;
	int bloquesGolpeados[10];
	bool win = false;//bandera de ganada
	audioEngine * audio;//desde esta variable accedemos a los sonidos

	//variables de juego(clock)
	Clock * reloj1;
	Time * tiempo1;
	float tiempoInicio;
	float tiempoFin;
	int TIEMPO_JUEGO;//en segundos
	bool gameOver;//bandera de fin de juego (fin de tiempo)

	//variable de HUD

	Font  * font;
	String stringTimer;
	Text * stringTimerText;
	String stringGameOver;
	Text * stringGameOverText;
	Text * stringGameWinText;

	//bloques

	bloque * arrayBloques[10];

	int arrayNumerosBloques[10];
	int numeroAnterior = 0;
	int arrayOrdenado[10];



};