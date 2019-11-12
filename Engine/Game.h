/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include <random>
#include "FrameTimer.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	GameSettings settings = "settings.txt";
	Board brd;
	Snake snek;
	Snake snek1;
	Location delta_loc = { 1,0 };
	Location delta_loc1 = { 1,0 };
	std::mt19937 rng;
	FrameTimer ft;
	FrameTimer ft1;
	// koniec gry jak zjedza 10;
	int snek1eaten = 0;
	int snekeaten = 0;
	//kolory lbow snekow
	static constexpr Color headColors[2] = { Colors::Yellow, Colors::Blue };
	static constexpr float snekMovePeriodMin = 0.040f;
	static constexpr float snekMovePeriodSpeedup = 0.15f;
	int nFood;
	float snekMovePeriod = 0.4f;
	float snekMoveCounter = 0.0f;
	float snekSpeedupFactor;


	//snek 2
	static constexpr float snekMovePeriodMin1 = 0.040f;
	static constexpr float snekMovePeriodSpeedup1 = 0.15f;
	float snekMovePeriod1 = 0.4f;
	float snekMoveCounter1 = 0.0f;
	float snekSpeedupFactor1;

	bool gameIsOver = false;
	bool snekWon = false;
	bool snek1Won = false;
	bool gameIsStarted = false;
	/********************************/
};