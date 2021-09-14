// 自作：Game インクルード
// 2021/08/29

#include "Game.h"

// コンストラクタ-------------------------------
Game::Game()
		:mWindow(nullptr)
		,mIsRunning(true)
{
}

// デストラクタ----------------------------------
Game:: ~Game()
{


}

// 初期化処理------------------------------------
bool Game:: Initialize()
{
	// ビデオサブシステムの初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	//初期化失敗時のエラー処理	
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

		return false;
	}

	//ウィンドウの作成 失敗時にはnullptrを返す
	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter1)",		// タイトル
		100,		// ウィンドウ左上端のx座標
		100,		// ウィンドウ左上端のy座標
		1024,		// ウィンドウ横幅
		768,		// ウィンドウ立幅
		0			// フラグ。設定することでフルスクリーンモードなどを使用可能

	);

	// ウィンドウ作成失敗時のエラー処理
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}


	// 正常終了した場合、trueを返す
	return true;
		
}

// 終了処理------------------------------------
void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}

// 終了処理------------------------------------
void Game::Shutdown()
{
	// ウィンドウを終了する
	SDL_DestroyWindow(mWindow);
	// SDLを終了する
	SDL_Quit();
}

// ***********************************************************
// ヘルパー関数群------------------------------------------
// ***********************************************************

// 入力処理
void Game::ProcessInput()
{
	SDL_Event event;

	// キューにイベントがあればtrueとなる
	while (SDL_PollEvent(&event) )
	{
		// イベントの種類によって処理を分岐
		switch (event.type)
		{
			// ウィンドウ[x]ボタンを押したとき、
			case SDL_QUIT:
				mIsRunning = false;		
				break;


		}
	}

	// キーボードの状態を取得（配列を取得）
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// [ESC]キーを押していた場合
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}



}
void Game::UpdateGame()
{
}
void Game::GenerateOutput() 
{

}
