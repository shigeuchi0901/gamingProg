// ����F���C��
// 2021/08/28


#include "Game2.h"

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

