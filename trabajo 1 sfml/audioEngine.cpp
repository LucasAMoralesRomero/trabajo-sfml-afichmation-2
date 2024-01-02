#include "audioEngine.h"

audioEngine::audioEngine()
{
	//cargamos el sonido ambiente en el buffer
	bufferSound.loadFromFile("gameMusic.ogg");
	//cargamos en Music todos los sonidos FX
	errorMusic.openFromFile("ohNo.ogg");
	winMusic.openFromFile("gameWin.ogg");
	gameOverMusic.openFromFile("gameOver.ogg");
	hurryUpMusic.openFromFile("hurryUp.ogg");
	//definimos que el sonido ambiente puede loopear
	worldSound.setLoop(true);
}

void audioEngine::playBackgroundSound()
{
	worldSound.setPitch(1.0f);//seteamos la velocidad en 1 para la reproduccion
	worldSound.setBuffer(bufferSound);//seteamos el buffer
	worldSound.play();//reproducimos
}

void audioEngine::playBackgroundSoundFaster()
{
	worldSound.setPitch(1.5f);//seteamos la velocidad de reproduccion en 1.5
	worldSound.play();//reproducimos
}

void audioEngine::stopBackgroundSound()
{
	worldSound.stop();//detenemos la reproduccion de la musica ambiente
}

void audioEngine::playMusicError()
{
	errorMusic.play();//reproducimos el sonido al errar el bloque
}

void audioEngine::playMusicWin()
{
	winMusic.play();//reproducimos el sonido de ganar
}

void audioEngine::playMusicdGameOver()
{
	gameOverMusic.play();//reproducimos el sonido de perder
}

void audioEngine::playMusicHurryUp()
{
	hurryUpMusic.play();//reproducimos el sonido de apurarse
}
