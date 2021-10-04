// ����FGame �C���N���[�h
// 2021/08/28


// �d���C���N���[�h��h��
#pragma once

// SDL���C�u�������C���N���[�h
#include<SDL.h>
#include<vector>

// ******************************************
// �\���̐錾
// ******************************************

// �x�N�g��
struct Vector2
{
	float x;
	float y;
};

// �F�ʏ��
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
	//�C���X�g���N�^�A�f�X�g���N�^
	Game();
	~Game();
	
	// ������
	bool Initialize();

	// �Q�[�����[�v
	void RunLoop();

	// �I������
	void Shutdown();

private:

	//// �Q�[�����[�v�̂��߂̃w���p�[�֐��Q�[�[�[�[�[�[�[�[�[�[
	void ProcessInput();

	// �Q�[���̍X�V����
	void UpdateGame();
	void GenerateOutput();
	

	//// �����o�ϐ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	// 
	// SDL�����E�B���h�E
	SDL_Window* mWindow;

	// �Q�[���̌p���t���O
	bool mIsRunning;

	// �����_���[
	SDL_Renderer* mRenderer;

	// �p�h���̈ʒu
	Vector2 mPaddlePos;

	//// �{�[���̈ʒu
	//Vector2 mBallPoss;

	// ���O�̎��ԋL�^�p�o�b�t�@
	Uint32 mTicksCount;

	// �p�h���̈ʒu�X�V�p�ϐ�
	int mPaddleDir;

	//�p�h���̐F
	RGB mPaddleColour;

	//�ǂ̐F
	RGB mWallColour;

	//�{�[���̐F
	RGB mBallColour;



	////�{�[���̑��x
	//Vector2 mBallVel;

	//�p�h���̑��x
	float mPaddleVel;

	//***********************************************
	// 2�v���C���[�p�����o
	//***********************************************

	// �E���̃p�h���ʒu
	Vector2 mPaddlePos2;

	//�E���̃p�h���ʒu�ύX�p�����o
	int mPaddleDir2;

	//**********************************************
	// �{�[���p���I�z��
	std::vector<Ball> mBalls;


};
