#include"Game.h"
#include<iostream>

void main(int argc, char ** argv[])
{
	Game Game;
	while (Game.GetWindow()->isDone() == false)
	{
		Game.HandleInput();
		Game.Update();
		Game.Render();
		Game.RestartClock();
	}
}