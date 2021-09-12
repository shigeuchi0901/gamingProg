#include <SDL.h>

int main(int argc, char** argv) {
	// 初期化
	if (SDL_Init(SDL_INIT_VIDEO) != NULL) {
		// error
		SDL_Quit();
		return 1;
	}

	// Windowを生成する
	SDL_Window* window = SDL_CreateWindow(
		u8"ハローワールド",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, 0
	);

	if (window == NULL) {
		// error
		SDL_Quit();
		return 1;
	}

	// 3秒ウェイトする
	SDL_Delay(3000);

	// 後処理
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}