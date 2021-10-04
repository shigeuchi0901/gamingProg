// 自作：Game インクルード
// 2021/08/28


// 重複インクルードを防ぐ
#pragma once

// SDLライブラリをインクルード
#include<SDL.h>
#include<vector>

// ******************************************
// 構造体宣言
// ******************************************

// ベクトル
struct Vector2
{
	float x;
	float y;
};

// 色彩情報
struct RGB
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

struct Ball
{
	Vector2 position;
	Vector2 velocity;
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

	// ゲームの更新処理
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

	//// ボールの位置
	//Vector2 mBallPoss;

	// 直前の時間記録用バッファ
	Uint32 mTicksCount;

	// パドルの位置更新用変数
	int mPaddleDir;

	//パドルの色
	RGB mPaddleColour;

	//壁の色
	RGB mWallColour;

	//ボールの色
	RGB mBallColour;



	////ボールの速度
	//Vector2 mBallVel;

	//パドルの速度
	float mPaddleVel;

	//***********************************************
	// 2プレイヤー用メンバ
	//***********************************************

	// 右側のパドル位置
	Vector2 mPaddlePos2;

	//右側のパドル位置変更用メンバ
	int mPaddleDir2;

	//**********************************************
	// ボール用動的配列
	std::vector<Ball> mBalls;


};
