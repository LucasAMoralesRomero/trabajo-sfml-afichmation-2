#include "audioEngine.h"

audioEngine::audioEngine()
{
	//cargamos el sonido ambiente
	worldSound.openFromFile("gameMusic.ogg");
	//cargamos todos los sonidos FX en sus buffers
	errorBuffer.loadFromFile("ohNo.ogg");
	winBuffer.loadFromFile("gameWin.ogg");
	gameOverBuffer.loadFromFile("gameOver.ogg");
	hurryUpBuffer.loadFromFile("hurryUp.ogg");
	//asignamos los buffers
	errorMusic.setBuffer(errorBuffer);
	winMusic.setBuffer(winBuffer);
	gameOverMusic.setBuffer(gameOverBuffer);
	hurryUpMusic.setBuffer(hurryUpBuffer);
	//definimos que el sonido ambiente puede loopear
	worldSound.setLoop(true);
}

void audioEngine::playBackgroundSound()
{
	worldSound.setPitch(1.0f);//seteamos la velocidad en 1 para la reproduccion
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
