// 自作：Game インクルード
// 2021/08/28


// 重複インクルードを防ぐ
#pragma once

// SDLライブラリをインクルード
#include<SDL.h>

// 構造体宣言
struct Vector2
{
	float x;
	float y;
};

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

	//// ゲームループのためのヘルパー関数群ーーーーーーーーーー
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	

	//// メンバ変数ーーーーーーーーーーーーーーーーーーーーーー
	// 
	// SDLが作るウィンドウ
	SDL_Window* mWindow;

	// ゲームの継続フラグ
	bool mIsRunning;

	// レンダラー
	SDL_Renderer* mRenderer;

	// パドルの位置
	Vector2 mPaddlePos;

	// ボールの位置
	Vector2 mBallPoss;



};
