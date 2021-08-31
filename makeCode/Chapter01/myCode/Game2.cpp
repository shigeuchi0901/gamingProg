// 自作：Game インクルード
// 2021/08/29

#include "Game2.h"

// コンストラクタ-------------------------------
Game::Game()
{
	mWindow = null;
	mIsRunning = true;

}

// デストラクタ----------------------------------
Game:: ~Game()
{


}

// 初期化処理------------------------------------
Game::Initialize()
{
	// ビデオサブシステムの初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	//初期化失敗時のエラー処理	
	if (sdlResult != 0)
	{
		SDL_log("SDLの初期化に失敗しました: %s", SDL_GetError());
		return false;
	}

	//ウィンドウの作成 失敗時にはnullptrを返す
	mWindow = SDL_CreateWindow(
		"Game Programming in C++(第一章)",		// タイトル
		100,		// ウィンドウ左上端のx座標
		100,		// ウィンドウ左上端のy座標
		1024,		// ウィンドウ横幅
		768,		// ウィンドウ立幅
		0			// フラグ。設定することでフルスクリーンモードなどを使用可能

	);

	// ウィンドウさくせい失敗時のエラー処理
	if (!mWindow)
	{
		SDL_Log("ウィンドウの作成に失敗しました: %s", SDL_GetError);
		return false;
	}


	// 正常終了した場合、trueを返す
	return true;
		
}

// 終了処理------------------------------------
Game::RunLoop()
{
	if (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}

// 終了処理------------------------------------
Game::Shutdown()
{
	// ウィンドウを終了する
	SDL_DestroyWindow(mWindow);
	// SDLを終了する
	SDL_Quit();
}