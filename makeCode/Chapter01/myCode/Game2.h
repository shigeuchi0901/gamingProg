// 自作：Game インクルード
// 2021/08/28


// 重複インクルードを防ぐ
#pragma once

// SDLライブラリをインクルード
#include "SDL/SDL.h"

class Game
{
public:
	//インストラクタ、デストラクタ
	Game();
	~Game();
	
	// 初期化
	bool Initialize();

	// ゲームループ
	void RunLoop();

	// 終了処理
	void Shutdown();

private:
	
	// SDLが作るウィンドウ
	SDL_Window* mWindow;

	// ゲームの継続フラグ
	bool mIsRunning;

};

Game::Game()
{
}

Game::~Game()
{
}


