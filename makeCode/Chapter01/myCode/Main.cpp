// ����v���W�F�N�g
// 2021/08/28�F�쐬
// 2021/09/06�FSDL, SDL_image, openGL, RapidJson, EMOD����
// 2021/09/12�FChapter1.4.4�J�n
// 


#include "Game.h"

int main(int argc, char** argv)
{
	// �Q�[���̃C���X�^���X�쐬
	Game game;
	
	// ����������
	bool success = game.Initialize();

	// �������ɐ��������ꍇ�A�Q�[�����[�v�Ɉڍs
	if (success)
	{
		game.RunLoop();
	}

	// �Q�[���I������
	game.Shutdown();

	return 0;
}

