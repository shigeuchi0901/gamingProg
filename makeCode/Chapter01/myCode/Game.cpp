// ����FGame �C���N���[�h
// 2021/08/29

#include "Game.h"



// �O���[�o���ϐ�
	
const int thickness = 15;					//�p�h���A�ǂ̌���
const float paddleH = 100.0f;				//�p�h���̑傫��	

const RGB paddleC = {50, 255, 50, 255};		//�p�h���̐F
const RGB wallC = {255, 50, 50, 255 };		//�ǂ̐F
const RGB ballC = {255, 250, 250, 255 };	//�{�[���̐F

const int windowW = 1024;					//�E�B���h�E����
const int windowH = 768;					//�E�B���h�E�c��

const Vector2 ballV = { -200.0f, 235.0f };	//�{�[���̏������x
const float paddleV = 300.0f;				//�p�h���̏������x


// �R���X�g���N�^-------------------------------
Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
	, mPaddleDir(0)
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
		20,			// �E�B���h�E����[��y���W
		windowW,		// �E�B���h�E����
		windowH,		// �E�B���h�E����
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

	//****************************
	// �e�탁���o�̏���������
	//****************************

	// �p�h���̐F
	mPaddleColour.r = paddleC.r;
	mPaddleColour.g = paddleC.g;
	mPaddleColour.b = paddleC.b;
	mPaddleColour.a = paddleC.a;

	//�ǂ̐F
	mWallColour.r = wallC.r;
	mWallColour.g = wallC.g;
	mWallColour.b = wallC.b;
	mWallColour.a = wallC.a;

	// �{�[���̐F
	mBallColour.r = ballC.r;
	mBallColour.g = ballC.g;
	mBallColour.b = ballC.b;
	mBallColour.a = ballC.a;

	// �p�h���̈ʒu
	mPaddlePos.x = static_cast<float> (0);
	mPaddlePos.y = static_cast<float> (windowH / 2);

	//�E���̃p�h���̈ʒu
	mPaddlePos2.x = static_cast<float> (windowW - thickness);
	mPaddlePos2.y = static_cast<float> (windowH / 2);

	// �{�[���̈ʒu
	mBallPoss.x = static_cast<float> (windowW / 2);
	mBallPoss.y = static_cast<float> (windowH / 2);

	//�{�[���̑��x
	mBallVel = ballV;
	//�p�h���̑��x
	mPaddleVel = paddleV;



	// ����I�������ꍇ�Atrue��Ԃ�
	return true;
		
}

// �I������------------------------------------
void Game::RunLoop()
{
	while (mIsRunning)
	{
		// ���͂ւ̑Ή�����
		ProcessInput();

		// �Q�[���X�V����
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

// ***************************************************************************
// �w���p�[�֐��Q-----------------------------------------------------------
// ***************************************************************************

// ���͏���-------------------------------------------------------------
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

	// �p�h���̈ʒu�ύX�����i�L�[�{�[�hS,W�̓��͂ɑ΂��鏈���j
	mPaddleDir = 0;

	// W��������Ă����ꍇ�A�t���O���p�h�����グ��-1��
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir = -1;
	}
	// S��������Ă����ꍇ�A�t���O���p�h����������1��
	else if(state[SDL_SCANCODE_S])
	{
		mPaddleDir = 1;
	}


	// �E���̃p�h���̈ʒu�ύX�����i�L�[�{�[�hK,I�̓��͂ɑ΂��鏈���j
	mPaddleDir2 = 0;

	// I��������Ă����ꍇ�A�t���O���p�h�����グ��-1��
	if (state[SDL_SCANCODE_I])
	{
		mPaddleDir2 = -1;
	}
	// K��������Ă����ꍇ�A�t���O���p�h����������1��
	else if (state[SDL_SCANCODE_K])
	{
		mPaddleDir2 = 1;
	}

	////�㉺�L�[�Ńp�h���ƃ{�[���̑��x��{�����\��
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

// �Q�[���̍X�V����
void Game::UpdateGame()
{
	// ���O�̃t���[������16ms�o�߂���܂ł̓Q�[�����X�V�����ɑҋ@
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// delttime�͒��O�̃t���[���Ƃ̎����̍���b�ɕϊ������l
	float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// deltatime���ő�l�Ő�������
	if (deltatime > 0.05f)
	{
		deltatime = 0.05f;
	}

	// �������X�V
	mTicksCount = SDL_GetTicks();		// ����������o�߂����~���b�����擾�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@�@ �@

	// �Q�[�����[���h�̃I�u�W�F�N�g���f���^�^�C���̊֐��Ƃ��čX�V����----------------------

	// �L�[�{�[�h���͂�����ꍇ�̃p�h���̈ړ�����
	if (mPaddleDir != 0)
	{

		//�����̃p�h���̏���
		mPaddlePos.y += mPaddleDir * mPaddleVel * deltatime;

		//�p�h������ʊO�ɏo�Ȃ��悤�ɕ␳����

		//���ɃI�[�o�[����ꍇ
		if (mPaddlePos.y  > (windowH - paddleH / 2.0f) )
		{
			mPaddlePos.y = windowH - paddleH / 2.0f;
		}
		// ��ɃI�[�o�[����ꍇ�B
		else if(mPaddlePos.y < (paddleH / 2.0f  + thickness) )
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}

	}

	if (mPaddleDir2 != 0)
	{

		//�E���̃p�h���̏���
		mPaddlePos2.y += mPaddleDir2 * mPaddleVel * deltatime;

		//�p�h������ʊO�ɏo�Ȃ��悤�ɕ␳����

		//���ɃI�[�o�[����ꍇ
		if (mPaddlePos2.y > (windowH - paddleH / 2.0f))
		{
			mPaddlePos2.y = windowH - paddleH / 2.0f;
		}
		// ��ɃI�[�o�[����ꍇ�B
		else if (mPaddlePos2.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos2.y = paddleH / 2.0f + thickness;
		}
	}

	//�{�[���̔��˓���---------------------------------
	
	// ��̕ǂɐG�ꂽ�ꍇ
	if (mBallPoss.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}

	//���̕�
	if (mBallPoss.y >= windowH - thickness && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

	////�E�̕ǁ��΃h���ɕύX
	//if(mBallPoss.x >= windowW - thickness && mBallVel.x > 0.0f)
	//{
	//	mBallVel.x *= -1;
	//}

	//�p�h���̒����ƃ{�[���̒��S��y���W�̍������擾
	float diff = mPaddlePos.y - mBallPoss.y;
	//��Βl���v�Z
	diff = (diff > 0.0f) ? diff : -diff;
	
	//�p�h���ɐG�ꂽ��
	if (
		//�{�[�����p�h���͈͓̔��ɂ���A
		diff <= paddleH / 2.0f &&
		//�p�h���Ƀ{�[�����אڂ��A
		mBallPoss.x - thickness / 2.0f <= mPaddlePos.x + thickness &&
		//�{�[�������ɐi��ł���ꍇ
		mBallVel.x < 0.0f )
	{
		mBallVel.x *= -1.0f;
	}


	//�E���̃p�h���̒����ƃ{�[���̒��S��y���W�̍������擾
	 diff = mPaddlePos2.y - mBallPoss.y;
	//��Βl���v�Z
	diff = (diff > 0.0f) ? diff : -diff;

	//�p�h���ɐG�ꂽ��
	if (
		//�{�[�����p�h���͈͓̔��ɂ���A
		diff <= paddleH / 2.0f &&
		//�p�h���Ƀ{�[�����אڂ��A
		mBallPoss.x + thickness / 2.0f >= mPaddlePos2.x &&
		//�{�[�������ɐi��ł���ꍇ
		mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	// �{�[���̈ʒu�̍X�V
	mBallPoss.x += mBallVel.x * deltatime;
	mBallPoss.y += mBallVel.y * deltatime;


	// �{�[�����͈͊O�ɏo���ꍇ�A�Q�[�����[�v���I������
	if (mBallPoss.x < 0.0f || mBallPoss.x > windowW ||
		mBallPoss.y < 0.0f || mBallPoss.y > windowH)
	{
		mIsRunning = false;
	}

}
//********************************************************************************
// �o�͍쐬�w���p�[�֐�----------------------------------------------------------
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


	// �Q�[���V�[���̕`��---------------------------------------------
	
	// �����`���o��-----------------------------------------

	// �����_���[�̐ݒ�(�Ǘp)
	SDL_SetRenderDrawColor(
		mRenderer, 
		mWallColour.r, 
		mWallColour.g,
		mWallColour.b,
		mWallColour.a
	);
	
	// �㕔�̕ǂ̐ݒ�
	SDL_Rect wall
	{
		0,			// ������� x
		0,			// ������� y
		windowW,		// ����
		thickness	// ����
	};

	// �`��
	SDL_RenderFillRect(mRenderer, &wall);

	// �����̕ǂ̐ݒ�
	wall.x = 0;
	wall.y = windowH - thickness;
	wall.w = windowW;
	wall.h = thickness;

	// �`��
	SDL_RenderFillRect(mRenderer, &wall);

	//// �E���̕ǂ̐ݒ�@�p�h���ɕύX
	//wall.x = windowW - thickness;
	//wall.y =0;
	//wall.w = thickness;
	//wall.h = windowH;

	//// �`��
	//SDL_RenderFillRect(mRenderer, &wall);

	// �����p�h���̐ݒ�
	wall.x = mPaddlePos.x;
	wall.y = mPaddlePos.y - (paddleH / 2);
	wall.w = thickness;
	wall.h = paddleH;

	// �`��
	SDL_RenderFillRect(mRenderer, &wall);

	// �E���̃p�h���̐ݒ�
	wall.x = mPaddlePos2.x;
	wall.y = mPaddlePos2.y - (paddleH / 2);
	wall.w = thickness;
	wall.h = paddleH;

	// �`��
	SDL_RenderFillRect(mRenderer, &wall);

	// �����_���[�̐ݒ�(�{�[���p)
	SDL_SetRenderDrawColor(
		mRenderer,
		mBallColour.r,
		mBallColour.g,
		mBallColour.b,
		mBallColour.a
	);
	// �{�[���̕`��ݒ�
	SDL_Rect ball
	{
		static_cast<int>(mBallPoss.x - thickness / 2),
		static_cast<int>(mBallPoss.y - thickness / 2),
		thickness,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̌���
	SDL_RenderPresent(mRenderer);

}
