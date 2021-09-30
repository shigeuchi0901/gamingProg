// 自作：Game インクルード
// 2021/08/29

#include "Game.h"



// グローバル変数
	
const int thickness = 15;					//パドル、壁の厚さ
const float paddleH = 100.0f;				//パドルの大きさ	

const RGB paddleC = {50, 255, 50, 255};		//パドルの色
const RGB wallC = {255, 50, 50, 255 };		//壁の色
const RGB ballC = {255, 250, 250, 255 };	//ボールの色

const int windowW = 1024;					//ウィンドウ横幅
const int windowH = 768;					//ウィンドウ縦幅

const Vector2 ballV = { -200.0f, 235.0f };	//ボールの初期速度
const float paddleV = 300.0f;				//パドルの初期速度


// コンストラクタ-------------------------------
Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
	, mPaddleDir(0)
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
		20,			// ウィンドウ左上端のy座標
		windowW,		// ウィンドウ横幅
		windowH,		// ウィンドウ立幅
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

	//****************************
	// 各種メンバの初期化処理
	//****************************

	// パドルの色
	mPaddleColour.r = paddleC.r;
	mPaddleColour.g = paddleC.g;
	mPaddleColour.b = paddleC.b;
	mPaddleColour.a = paddleC.a;

	//壁の色
	mWallColour.r = wallC.r;
	mWallColour.g = wallC.g;
	mWallColour.b = wallC.b;
	mWallColour.a = wallC.a;

	// ボールの色
	mBallColour.r = ballC.r;
	mBallColour.g = ballC.g;
	mBallColour.b = ballC.b;
	mBallColour.a = ballC.a;

	// パドルの位置
	mPaddlePos.x = static_cast<float> (0);
	mPaddlePos.y = static_cast<float> (windowH / 2);

	//右側のパドルの位置
	mPaddlePos2.x = static_cast<float> (windowW - thickness);
	mPaddlePos2.y = static_cast<float> (windowH / 2);

	// ボールの位置
	mBallPoss.x = static_cast<float> (windowW / 2);
	mBallPoss.y = static_cast<float> (windowH / 2);

	//ボールの速度
	mBallVel = ballV;
	//パドルの速度
	mPaddleVel = paddleV;



	// 正常終了した場合、trueを返す
	return true;
		
}

// 終了処理------------------------------------
void Game::RunLoop()
{
	while (mIsRunning)
	{
		// 入力への対応処理
		ProcessInput();

		// ゲーム更新処理
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

// ***************************************************************************
// ヘルパー関数群-----------------------------------------------------------
// ***************************************************************************

// 入力処理-------------------------------------------------------------
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

	// パドルの位置変更処理（キーボードS,Wの入力に対する処理）
	mPaddleDir = 0;

	// Wが押されていた場合、フラグをパドルを上げる-1に
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir = -1;
	}
	// Sが押されていた場合、フラグをパドルを下げる1に
	else if(state[SDL_SCANCODE_S])
	{
		mPaddleDir = 1;
	}


	// 右側のパドルの位置変更処理（キーボードK,Iの入力に対する処理）
	mPaddleDir2 = 0;

	// Iが押されていた場合、フラグをパドルを上げる-1に
	if (state[SDL_SCANCODE_I])
	{
		mPaddleDir2 = -1;
	}
	// Kが押されていた場合、フラグをパドルを下げる1に
	else if (state[SDL_SCANCODE_K])
	{
		mPaddleDir2 = 1;
	}

	////上下キーでパドルとボールの速度を倍速化可能に
	//if (state[SDL_SCANCODE_UP])
	//{
	//	mPaddleVel += mPaddleVel * 0.5;
	//	mBallVel.x += mBallVel.x * 0.5;
	//	mBallVel.y += mBallVel.y * 0.5;
	//}
	//if (state[SDL_SCANCODE_DOWN])
	//{
	//	mPaddleVel -= mPaddleVel * 0.5;
	//	mBallVel.x -= mBallVel.x * 0.5;
	//	mBallVel.y -= mBallVel.y * 0.5;
	//}

}

// ゲームの更新処理
void Game::UpdateGame()
{
	// 直前のフレームから16ms経過するまではゲームを更新せずに待機
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// delttimeは直前のフレームとの時刻の差を秒に変換した値
	float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// deltatimeを最大値で制限する
	if (deltatime > 0.05f)
	{
		deltatime = 0.05f;
	}

	// 時刻を更新
	mTicksCount = SDL_GetTicks();		// 初期化から経過したミリ秒数を取得　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　 　　 　　 　　 　　 　　 　　 　　 　　 　　 　　 　　 　　 　　 　

	// ゲームワールドのオブジェクトをデルタタイムの関数として更新する----------------------

	// キーボード入力がある場合のパドルの移動処理
	if (mPaddleDir != 0)
	{

		//左側のパドルの処理
		mPaddlePos.y += mPaddleDir * mPaddleVel * deltatime;

		//パドルが画面外に出ないように補正する

		//下にオーバーする場合
		if (mPaddlePos.y  > (windowH - paddleH / 2.0f) )
		{
			mPaddlePos.y = windowH - paddleH / 2.0f;
		}
		// 上にオーバーする場合。
		else if(mPaddlePos.y < (paddleH / 2.0f  + thickness) )
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}

	}

	if (mPaddleDir2 != 0)
	{

		//右側のパドルの処理
		mPaddlePos2.y += mPaddleDir2 * mPaddleVel * deltatime;

		//パドルが画面外に出ないように補正する

		//下にオーバーする場合
		if (mPaddlePos2.y > (windowH - paddleH / 2.0f))
		{
			mPaddlePos2.y = windowH - paddleH / 2.0f;
		}
		// 上にオーバーする場合。
		else if (mPaddlePos2.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos2.y = paddleH / 2.0f + thickness;
		}
	}

	//ボールの反射動作---------------------------------
	
	// 上の壁に触れた場合
	if (mBallPoss.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}

	//下の壁
	if (mBallPoss.y >= windowH - thickness && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

	////右の壁→ばドルに変更
	//if(mBallPoss.x >= windowW - thickness && mBallVel.x > 0.0f)
	//{
	//	mBallVel.x *= -1;
	//}

	//パドルの中央とボールの中心のy座標の差分を取得
	float diff = mPaddlePos.y - mBallPoss.y;
	//絶対値を計算
	diff = (diff > 0.0f) ? diff : -diff;
	
	//パドルに触れた時
	if (
		//ボールがパドルの範囲内にあり、
		diff <= paddleH / 2.0f &&
		//パドルにボールが隣接し、
		mBallPoss.x - thickness / 2.0f <= mPaddlePos.x + thickness &&
		//ボールが左に進んでいる場合
		mBallVel.x < 0.0f )
	{
		mBallVel.x *= -1.0f;
	}


	//右側のパドルの中央とボールの中心のy座標の差分を取得
	 diff = mPaddlePos2.y - mBallPoss.y;
	//絶対値を計算
	diff = (diff > 0.0f) ? diff : -diff;

	//パドルに触れた時
	if (
		//ボールがパドルの範囲内にあり、
		diff <= paddleH / 2.0f &&
		//パドルにボールが隣接し、
		mBallPoss.x + thickness / 2.0f >= mPaddlePos2.x &&
		//ボールが左に進んでいる場合
		mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	// ボールの位置の更新
	mBallPoss.x += mBallVel.x * deltatime;
	mBallPoss.y += mBallVel.y * deltatime;


	// ボールが範囲外に出た場合、ゲームループを終了する
	if (mBallPoss.x < 0.0f || mBallPoss.x > windowW ||
		mBallPoss.y < 0.0f || mBallPoss.y > windowH)
	{
		mIsRunning = false;
	}

}
//********************************************************************************
// 出力作成ヘルパー関数----------------------------------------------------------
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


	// ゲームシーンの描画---------------------------------------------
	
	// 長方形を出力-----------------------------------------

	// レンダラーの設定(壁用)
	SDL_SetRenderDrawColor(
		mRenderer, 
		mWallColour.r, 
		mWallColour.g,
		mWallColour.b,
		mWallColour.a
	);
	
	// 上部の壁の設定
	SDL_Rect wall
	{
		0,			// 左上隅の x
		0,			// 左上隅の y
		windowW,		// 横幅
		thickness	// 高さ
	};

	// 描画
	SDL_RenderFillRect(mRenderer, &wall);

	// 下部の壁の設定
	wall.x = 0;
	wall.y = windowH - thickness;
	wall.w = windowW;
	wall.h = thickness;

	// 描画
	SDL_RenderFillRect(mRenderer, &wall);

	//// 右部の壁の設定　パドルに変更
	//wall.x = windowW - thickness;
	//wall.y =0;
	//wall.w = thickness;
	//wall.h = windowH;

	//// 描画
	//SDL_RenderFillRect(mRenderer, &wall);

	// 左部パドルの設定
	wall.x = mPaddlePos.x;
	wall.y = mPaddlePos.y - (paddleH / 2);
	wall.w = thickness;
	wall.h = paddleH;

	// 描画
	SDL_RenderFillRect(mRenderer, &wall);

	// 右側のパドルの設定
	wall.x = mPaddlePos2.x;
	wall.y = mPaddlePos2.y - (paddleH / 2);
	wall.w = thickness;
	wall.h = paddleH;

	// 描画
	SDL_RenderFillRect(mRenderer, &wall);

	// レンダラーの設定(ボール用)
	SDL_SetRenderDrawColor(
		mRenderer,
		mBallColour.r,
		mBallColour.g,
		mBallColour.b,
		mBallColour.a
	);
	// ボールの描画設定
	SDL_Rect ball
	{
		static_cast<int>(mBallPoss.x - thickness / 2),
		static_cast<int>(mBallPoss.y - thickness / 2),
		thickness,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	// フロントバッファとバックバッファの交換
	SDL_RenderPresent(mRenderer);

}
