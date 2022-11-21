#include "FPS.h"

void FPS::Start()
{
	// ���C�����[�v�ɓ���O�ɐ��x���擾���Ă���
	if (QueryPerformanceFrequency(&timeFreq) == FALSE) { // ���̊֐���0(FALSE)���A�鎞�͖��Ή�
		// ��������QueryPerformanceFrequency���g���Ȃ��l��(�Â�)PC�ł͂ǂ����F�X�L�c�C���낤��
		return; // �{���͂���ȋA������Ă͍s���Ȃ�(�㑱�̉���������Ă΂�Ȃ�)
	}
	// 1�x�擾���Ă���(����v�Z�p)
	QueryPerformanceCounter(&timeStart);
}

void FPS::run()
{
	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&timeEnd);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FREAM_TIME) { // ���Ԃɗ]�T������
		// �~���b�ɕϊ�
		DWORD sleepTime = static_cast<DWORD>((MIN_FREAM_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // ����\���グ��(�������Ȃ���Sleep�̐��x�̓K�^�K�^)
		Sleep(sleepTime);   // �Q��
		timeEndPeriod(1);   // �߂�

		// ���T�Ɏ����z��(�������Ȃ���fps���ςɂȂ�?)
		return;
	}

	if (frameTime > 0.0) { // �o�ߎ��Ԃ�0���傫��(�������Ȃ��Ɖ��̌v�Z�Ń[�����Z�ɂȂ�Ǝv���)
		fps = (fps * 0.99f) + (0.01f / frameTime); // ����fps���v�Z
	}

	timeStart = timeEnd; // ����ւ�
}

FPS* FPS::Get()
{
	static FPS ins;

	return &ins;
}
