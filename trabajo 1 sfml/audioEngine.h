#pragma once
# include "SFML\Audio.hpp"
#include <iostream>
#include <string>


using namespace sf;

class audioEngine {

public:
	audioEngine();
	void playBackgroundSound();//reproduce el sonido ambiente
	void playBackgroundSoundFaster();//reproducimos el sonido ambiente mas rapido
	void stopBackgroundSound();//detiene el sonido ambiente
	void playMusicError();//reproduce sonido al errar el bloque
	void playMusicWin();//reproduce sonido si ganamos
	void playMusicdGameOver();//reproduce un sonido si perdemos
	void playMusicHurryUp();//reproduce el sonido de apurarse
private:
	SoundBuffer bufferSound; //buffer del sonido ambiente
	Sound worldSound;//sonido de ambiente
	Music errorMusic;//carga el sonido de errar el bloque
	Music winMusic;//carga el sonido de ganar
	Music gameOverMusic;//carga el sonido de perder (Game Over)
	Music hurryUpMusic;//carga el sonido de apurarse

};