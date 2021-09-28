#include <iostream>
#include "game.h"
#include "plane.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

void Plane() {
	game play(360, 630);
	mciSendString(L"open game_music.mp3", 0, 0, 0);
	mciSendString(L"play game_music.mp3", 0, 0, 0);
	play.start();
	return ;
}
