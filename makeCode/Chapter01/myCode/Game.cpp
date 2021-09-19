// ����FGame �C���N���[�h
// 2021/08/29

#include "Game.h"



// �O���[�o���ϐ�

const int thinkness = 15;
const float paddle = 100.0f;

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

	// SDL�����_���[���쐬����B�@�쐬���s���ɂ� false, �������ɂ�true��Ԃ�
	mRenderer = SDL_CreateRenderer(
		mWindow,												// �쐬���郌���_���[�̕`��ΏۂƂȂ�E�B���h�E(�̃|�C���^)
		-1,														// �ʏ�� -1�@�O���t�B�b�N�X�h���C�o���w�肷��B�i�����̃f�B�X�v���C�ɕ`�悷��ۂɂ� -1�ȊO��ݒ肷��K�v������B-1 �ł�SDL���C�ӂŐݒ肷��B
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	// �������t���O�@
	);

	//SDL�쐬���s���̃G���[����	
	if (!mRenderer)
	{
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
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

		// �o�͍쐬�w���p�[�֐�
		GenerateOutput();
	}

}

// �I������------------------------------------
void Game::Shutdown()
{
	// �E�B���h�E���I������
	SDL_DestroyWindow(mWindow);

	// �����_���[���I������
	SDL_DestroyRenderer(mRenderer);

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

// �o�͍쐬�w���p�[�֐�
void Game::GenerateOutput() 
{

	// �Q�[���o�b�t�@��P�F�ŃN���A����
	SDL_SetRenderDrawColor(
		mRenderer,	// �����_���[�̃|�C���^
		0,			// R
		0,			// G
		255,		// B
		255			// A �i�A���t�@�l�A�����x�j
	);

	// �o�b�N�o�b�t�@�����݂̕`��F�ŃN���A����
	SDL_RenderClear(mRenderer);


	// �Q�[���V�[���̕`��
	
	// �����`���o��

	// �����_���[�̐ݒ�
	SDL_SetRenderDrawColor(
		mRenderer, 
		255, 
		255, 
		255, 
		255
	);
	
	//�����`�̕`��w��
	SDL_Rect wall
	{
		0,			// ������� x
		0,			// ������� y
		1024,		// ��
		thinkness	// ����
	};

	// �����`��`��
	SDL_RenderFillRect(mRenderer, &wall);

	// �{�[���̈ʒu���v�Z
	mBallPoss.x = 500.0f;
	mBallPoss.y = 100.0f;

	// �{�[���̕`��ݒ�
	SDL_Rect ball
	{
		static_cast<int>(mBallPoss.x - thinkness / 2),
		static_cast<int>(mBallPoss.y - thinkness / 2),
		thinkness,
		thinkness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̌���
	SDL_RenderPresent(mRenderer);

}
