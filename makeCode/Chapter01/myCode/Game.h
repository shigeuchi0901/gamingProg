// ����FGame �C���N���[�h
// 2021/08/28


// �d���C���N���[�h��h��
#pragma once

// SDL���C�u�������C���N���[�h
#include<SDL.h>

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

	//// �Q�[�����[�v�̂��߂̃w���p�[�֐��Q
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	
	// SDL�����E�B���h�E
	SDL_Window* mWindow;

	// �Q�[���̌p���t���O
	bool mIsRunning;



};
