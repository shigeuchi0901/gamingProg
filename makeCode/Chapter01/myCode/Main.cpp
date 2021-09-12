// 自作プロジェクト
// 2021/08/28：作成
// 2021/09/06：SDL, SDL_image, openGL, RapidJson, EMOD導入
// 2021/09/12：Chapter1.4.4開始
// 


#include "Game.h"

int main(int argc, char** argv)
{
	// ゲームのインスタンス作成
	Game game;
	
	// 初期化処理
	bool success = game.Initialize();

	// 初期化に成功した場合、ゲームループに移行
	if (success)
	{
		game.RunLoop();
	}

	// ゲーム終了処理
	game.Shutdown();

	return 0;
}

