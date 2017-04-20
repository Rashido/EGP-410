/*main.cpp
 *	Adapted from: Example program for the Allegro library, by Shawn Hargreaves.
 *	Sets up all systems and runs the main game loop until it is time to quit.
 *
 *	Dean Lawson
 *	Champlain College
 *	2011
 *
 */
#define ALLEGRO_USE_CONSOLE

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "KinematicUnit.h"
#include "InputManager.h"
#include "Timer.h"
#include "PerformanceTracker.h"
#include "MemoryTracker.h"

using namespace std;

PerformanceTracker* gpPerformanceTracker = NULL;

//computer science gross test stuff
float totalTime = 0;
float average;
float amount = 0;

float maxTime = 10000;
bool timerOn = false;
std::string fileName = "asm40BoidsTest3.txt";

int main(int argc, char **argv)
{
	gpPerformanceTracker = new PerformanceTracker();

	gpPerformanceTracker->startTracking("init");

	//create the global game object
	gpGame = new Game;
	//init the game
	bool goodGame = gpGame->init();
	if(!goodGame) 
	{
		fprintf(stderr, "failed to initialize Game object!\n");
		return -1;
	}

	gpPerformanceTracker->stopTracking("init");
	cout << "initialization took:" << gpPerformanceTracker->getElapsedTime("init") << "ms\n";

	bool shouldExit = false;

	//game loop
	while( !shouldExit )
	{
		gpPerformanceTracker->clearTracker("loop");
		gpPerformanceTracker->startTracking("loop");

		gpGame->beginLoop();

		gpPerformanceTracker->clearTracker("draw");
		gpPerformanceTracker->startTracking("draw");

		gpGame->processLoop();

		gpPerformanceTracker->stopTracking("draw");

		shouldExit = gpGame->endLoop();

		gpPerformanceTracker->stopTracking("loop");
		cout << "loop took:" << gpPerformanceTracker->getElapsedTime("loop") << "ms";
		cout << "draw took:" << gpPerformanceTracker->getElapsedTime("draw") << "ms\n";

		//test stuff I know its gross sorry :(
		if (!timerOn && gpGame->getInputManager()->gPressed)
			timerOn = true;

		if (timerOn)
		{
			totalTime += gpPerformanceTracker->getElapsedTime("loop");
			amount++;
			
			if (totalTime >= maxTime)
			{
				average = totalTime / amount;
				std::ofstream fout(fileName);
				fout << "The average frame rate for 10 seconds is " << average << std::endl;
				fout.close();

				timerOn = false;
			}
		}

	}

	gpGame->cleanup();
	delete gpGame;
	gpGame = NULL;

	delete gpPerformanceTracker;
	gMemoryTracker.reportAllocations( cout );
	system("pause");

	return 0;
}