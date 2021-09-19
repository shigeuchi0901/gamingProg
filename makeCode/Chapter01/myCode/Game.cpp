// 自作：Game インクルード
// 2021/08/29

#include "Game.h"



// グローバル変数

const int thinkness = 15;
const float paddle = 100.0f;

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

	// SDLレンダラーを作成する。　作成失敗時には false, 成功時にはtrueを返す
	mRenderer = SDL_CreateRenderer(
		mWindow,												// 作成するレンダラーの描画対象となるウィンドウ(のポインタ)
		-1,														// 通常は -1　グラフィックスドライバを指定する。（複数のディスプレイに描画する際には -1以外を設定する必要がある。-1 ではSDLが任意で設定する。
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	// 初期化フラグ　
	);

	//SDL作成失敗時のエラー処理	
	if (!mRenderer)
	{
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
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

		// 出力作成ヘルパー関数
		GenerateOutput();
	}

}

// 終了処理------------------------------------
void Game::Shutdown()
{
	// ウィンドウを終了する
	SDL_DestroyWindow(mWindow);

	// レンダラーを終了する
	SDL_DestroyRenderer(mRenderer);

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

// 出力作成ヘルパー関数
void Game::GenerateOutput() 
{

	// ゲームバッファを単色でクリアする
	SDL_SetRenderDrawColor(
		mRenderer,	// レンダラーのポインタ
		0,			// R
		0,			// G
		255,		// B
		255			// A （アルファ値、透明度）
	);

	// バックバッファを現在の描画色でクリアする
	SDL_RenderClear(mRenderer);


	// ゲームシーンの描画
	
	// 長方形を出力

	// レンダラーの設定
	SDL_SetRenderDrawColor(
		mRenderer, 
		255, 
		255, 
		255, 
		255
	);
	
	//長方形の描画指定
	SDL_Rect wall
	{
		0,			// 左上隅の x
		0,			// 左上隅の y
		1024,		// 幅
		thinkness	// 高さ
	};

	// 長方形を描画
	SDL_RenderFillRect(mRenderer, &wall);

	// ボールの位置を計算
	mBallPoss.x = 500.0f;
	mBallPoss.y = 100.0f;

	// ボールの描画設定
	SDL_Rect ball
	{
		static_cast<int>(mBallPoss.x - thinkness / 2),
		static_cast<int>(mBallPoss.y - thinkness / 2),
		thinkness,
		thinkness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	// フロントバッファとバックバッファの交換
	SDL_RenderPresent(mRenderer);

}
