#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

int DISPLAY_WIDTH = 640;
int DISPLAY_HEIGHT = 360;
int DISPLAY_SCALE = 1;
int score = 0;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CreateGameObject(1, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, 60, "yellowghost");
	Play::CreateGameObject(2, { DISPLAY_WIDTH / 8, DISPLAY_HEIGHT / 8 }, 60, "coin");
	Play::CentreAllSpriteOrigins();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cOrange );
	GameObject& player = Play::GetGameObject(1);
	GameObject& coin = Play::GetGameObject(2);

	
	Play::UpdateGameObject(coin);
	Play::DrawObject(coin);
	
	
	Play::UpdateGameObject(player);
	Play::DrawObject(player);

	if (Play::IsColliding(player, coin))
	{
		coin.pos = { Play::RandomRollRange(1,DISPLAY_WIDTH) , Play::RandomRollRange(1,DISPLAY_HEIGHT) };
	}
	if (Play::KeyDown(KEY_UP))
	{
		player.velocity = { 0,4 };
	}
	else if (Play::KeyDown(KEY_DOWN))
	{
		player.velocity = { 0,-4 };
	}
	else if (Play::KeyDown(KEY_LEFT))
	{
		player.velocity = { -4,0 };
	}
	else if (Play::KeyDown(KEY_RIGHT))
	{
		player.velocity = { 4,0 };
	}

	Play::PresentDrawingBuffer();

	return Play::KeyDown(KEY_ESCAPE);
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

