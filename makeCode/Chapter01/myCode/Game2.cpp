// ����FGame �C���N���[�h
// 2021/08/29

#include "Game2.h"

// �R���X�g���N�^-------------------------------
Game::Game()
{
	mWindow = null;
	mIsRunning = true;

}

// �f�X�g���N�^----------------------------------
Game:: ~Game()
{


}

// ����������------------------------------------
Game::Initialize()
{
	// �r�f�I�T�u�V�X�e���̏�����
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	//���������s���̃G���[����	
	if (sdlResult != 0)
	{
		SDL_log("SDL�̏������Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}

	//�E�B���h�E�̍쐬 ���s���ɂ�nullptr��Ԃ�
	mWindow = SDL_CreateWindow(
		"Game Programming in C++(����)",		// �^�C�g��
		100,		// �E�B���h�E����[��x���W
		100,		// �E�B���h�E����[��y���W
		1024,		// �E�B���h�E����
		768,		// �E�B���h�E����
		0			// �t���O�B�ݒ肷�邱�ƂŃt���X�N���[�����[�h�Ȃǂ��g�p�\

	);

	// �E�B���h�E�����������s���̃G���[����
	if (!mWindow)
	{
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s���܂���: %s", SDL_GetError);
		return false;
	}


	// ����I�������ꍇ�Atrue��Ԃ�
	return true;
		
}

// �I������------------------------------------
Game::RunLoop()
{
	if (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}

// �I������------------------------------------
Game::Shutdown()
{
	// �E�B���h�E���I������
	SDL_DestroyWindow(mWindow);
	// SDL���I������
	SDL_Quit();
}