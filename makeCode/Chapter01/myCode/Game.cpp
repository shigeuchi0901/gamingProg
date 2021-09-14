// ����FGame �C���N���[�h
// 2021/08/29

#include "Game.h"

// �R���X�g���N�^-------------------------------
Game::Game()
		:mWindow(nullptr)
		,mIsRunning(true)
{
}

// �f�X�g���N�^----------------------------------
Game:: ~Game()
{


}

// ����������------------------------------------
bool Game:: Initialize()
{
	// �r�f�I�T�u�V�X�e���̏�����
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	//���������s���̃G���[����	
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

		return false;
	}

	//�E�B���h�E�̍쐬 ���s���ɂ�nullptr��Ԃ�
	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter1)",		// �^�C�g��
		100,		// �E�B���h�E����[��x���W
		100,		// �E�B���h�E����[��y���W
		1024,		// �E�B���h�E����
		768,		// �E�B���h�E����
		0			// �t���O�B�ݒ肷�邱�ƂŃt���X�N���[�����[�h�Ȃǂ��g�p�\

	);

	// �E�B���h�E�쐬���s���̃G���[����
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}


	// ����I�������ꍇ�Atrue��Ԃ�
	return true;
		
}

// �I������------------------------------------
void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}

// �I������------------------------------------
void Game::Shutdown()
{
	// �E�B���h�E���I������
	SDL_DestroyWindow(mWindow);
	// SDL���I������
	SDL_Quit();
}

// ***********************************************************
// �w���p�[�֐��Q------------------------------------------
// ***********************************************************

// ���͏���
void Game::ProcessInput()
{
	SDL_Event event;

	// �L���[�ɃC�x���g�������true�ƂȂ�
	while (SDL_PollEvent(&event) )
	{
		// �C�x���g�̎�ނɂ���ď����𕪊�
		switch (event.type)
		{
			// �E�B���h�E[x]�{�^�����������Ƃ��A
			case SDL_QUIT:
				mIsRunning = false;		
				break;


		}
	}

	// �L�[�{�[�h�̏�Ԃ��擾�i�z����擾�j
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// [ESC]�L�[�������Ă����ꍇ
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
