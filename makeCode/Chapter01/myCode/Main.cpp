// 自作：メイン
// 2021/08/28


#include "Game2.h"

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

