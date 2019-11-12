#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	static void DrawGameOver( int x,int y,Graphics& gfx );
	static void DrawTitle( int x,int y,Graphics& gfx );
	static void DrawPlayer2Win(int x, int y, Graphics& gfx);
	static void DrawPlayer1Win(int x, int y, Graphics& gfx);
};