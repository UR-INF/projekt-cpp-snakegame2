/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(settings, gfx),
	rng(std::random_device()()),
	snek({ 2,2 }, headColors[0]),
	snek1({ 10,15 }, headColors[1]),
	nFood(settings.GetFoodAmount()),
	snekSpeedupFactor(settings.GetSpeedupRate()),
	snekSpeedupFactor1(settings.GetSpeedupRate())
{
	for (int i = 0; i < nFood; i++)
	{
		brd.SpawnContents(rng, snek, Board::CellContents::Food);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	const float dt1 = ft1.Mark();

	// jesli zjedza 10 to koniec gry;

	if (gameIsStarted)
	{
		if (!gameIsOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				const Location new_delta_loc = { 0,-1 };
				if (delta_loc != -new_delta_loc || snek.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				const Location new_delta_loc = { 0,1 };
				if (delta_loc != -new_delta_loc || snek.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				const Location new_delta_loc = { -1,0 };
				if (delta_loc != -new_delta_loc || snek.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				const Location new_delta_loc = { 1,0 };
				if (delta_loc != -new_delta_loc || snek.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}

			float snekModifiedMovePeriod = snekMovePeriod;
			if (wnd.kbd.KeyIsPressed(VK_NUMPAD0))
			{
				snekModifiedMovePeriod = std::min(snekMovePeriod, snekMovePeriodSpeedup);
			}

			snekMoveCounter += dt;
			if (snekMoveCounter >= snekModifiedMovePeriod)
			{
				snekMoveCounter -= snekModifiedMovePeriod;
				const Location next = snek.GetNextHeadLocation(delta_loc);
				const Board::CellContents contents = brd.IsInsideBoard(next) ? brd.GetContents(next)
					: Board::CellContents::Empty;
				if (!brd.IsInsideBoard(next) ||
					snek.IsInTileExceptEnd(next) ||
					contents == Board::CellContents::Obstacle
					)
				{
					gameIsOver = true;
					snek1Won = true;
					
				}
				else if (snekeaten == 10) {
					gameIsOver = true;
				}
				else if (contents == Board::CellContents::Food)
				{
					snek.GrowAndMoveBy(delta_loc);
					brd.ConsumeContents(next);
					++snekeaten;
					brd.SpawnContents(rng, snek, Board::CellContents::Obstacle);
					brd.SpawnContents(rng, snek, Board::CellContents::Food);
					snekMovePeriod = std::max(snekMovePeriod * snekSpeedupFactor, snekMovePeriodMin);
				}
				else
				{
					snek.MoveBy(delta_loc);
				}
			}


			//snek 2

			if (wnd.kbd.KeyIsPressed('W'))
			{
				const Location new_delta_loc = { 0,-1 };
				if (delta_loc1 != -new_delta_loc || snek1.GetLength() <= 2)
				{
					delta_loc1 = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed('S'))
			{
				const Location new_delta_loc = { 0,1 };
				if (delta_loc1 != -new_delta_loc || snek1.GetLength() <= 2)
				{
					delta_loc1 = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed('A'))
			{
				const Location new_delta_loc = { -1,0 };
				if (delta_loc1 != -new_delta_loc || snek1.GetLength() <= 2)
				{
					delta_loc1 = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed('D'))
			{
				const Location new_delta_loc = { 1,0 };
				if (delta_loc1 != -new_delta_loc || snek1.GetLength() <= 2)
				{
					delta_loc1 = new_delta_loc;
				}
			}

			float snekModifiedMovePeriod1 = snekMovePeriod1;
			if (wnd.kbd.KeyIsPressed(VK_CONTROL))
			{
				snekModifiedMovePeriod1 = std::min(snekMovePeriod1, snekMovePeriodSpeedup1);
			}

			snekMoveCounter1 += dt1;
			if (snekMoveCounter1 >= snekModifiedMovePeriod1)
			{
				snekMoveCounter1 -= snekModifiedMovePeriod1;
				const Location next = snek1.GetNextHeadLocation(delta_loc1);
				const Board::CellContents contents = brd.IsInsideBoard(next) ? brd.GetContents(next)
					: Board::CellContents::Empty;
				if (!brd.IsInsideBoard(next) ||
					snek1.IsInTileExceptEnd(next) ||
					contents == Board::CellContents::Obstacle)
				{
					gameIsOver = true;
					snekWon = true;

				}
				else if (snek1eaten == 10) {
					gameIsOver = true;
				}
				else if (contents == Board::CellContents::Food)
				{
					snek1.GrowAndMoveBy(delta_loc1);
					++snek1eaten;
					brd.ConsumeContents(next);
					brd.SpawnContents(rng, snek1, Board::CellContents::Obstacle);
					brd.SpawnContents(rng, snek1, Board::CellContents::Food);
					snekMovePeriod1 = std::max(snekMovePeriod1 * snekSpeedupFactor1, snekMovePeriodMin1);
				}
				else
				{
					snek1.MoveBy(delta_loc1);
				}
			}


		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameIsStarted = true;
		}
	}
}

void Game::ComposeFrame()
{
	if (gameIsStarted)
	{
		snek.Draw(brd);
		snek1.Draw(brd);
		brd.DrawCells();
		if (gameIsOver)
		{
			if (snekeaten == 10) {
				SpriteCodex::DrawPlayer1Win(275, 225, gfx);
			}
			else if (snek1eaten == 10) {
				SpriteCodex::DrawPlayer2Win(275, 225, gfx);
			}
			else if (snekWon) {
				SpriteCodex::DrawPlayer1Win(275, 225, gfx);
			}
			else if (snek1Won) {
				SpriteCodex::DrawPlayer2Win(275, 225, gfx);
			}

		}
		brd.DrawBorder();
	}
	else
	{
		SpriteCodex::DrawTitle(200, 150, gfx);
	}
}
