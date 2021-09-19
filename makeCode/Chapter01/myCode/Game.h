// ����FGame �C���N���[�h
// 2021/08/28


// �d���C���N���[�h��h��
#pragma once

// SDL���C�u�������C���N���[�h
#include<SDL.h>

// �\���̐錾
struct Vector2
{
	float x;
	float y;
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

	// �{�[���̈ʒu
	Vector2 mBallPoss;



};
