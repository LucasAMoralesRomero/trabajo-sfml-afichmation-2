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
	bool backgroundSoundStatus();//retorna el status de la reproduccion true reproduciendo false pausado
private:
	SoundBuffer errorBuffer; //buffer del sonido errar bloque
	SoundBuffer winBuffer;//buffer del sonido de ganar
	SoundBuffer gameOverBuffer;//buffer del sonido de perder
	SoundBuffer hurryUpBuffer;//buffer de sonido de apurarse
	Music worldSound;//sonido de ambiente
	Sound errorMusic;//carga el sonido de errar el bloque
	Sound winMusic;//carga el sonido de ganar
	Sound gameOverMusic;//carga el sonido de perder (Game Over)
	Sound hurryUpMusic;//carga el sonido de apurarse

};