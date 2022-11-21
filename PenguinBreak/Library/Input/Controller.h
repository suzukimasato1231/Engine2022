#pragma once
#include <dinput.h>
#include <DirectXMath.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
enum ButtonKind
{
	LButtonUp,
	LButtonDown,
	LButtonLeft,
	LButtonRight,
	RButtonUp,
	RButtonDown,
	RButtonLeft,
	RButtonRight,
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	ButtonRB,
	ButtonLB,
	ButtonRT,
	ButtonLT,
	ButtonKindMax,
};

enum ButtonState
{
	ButtonStateNone,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
};

class Controller
{
private:
	// �Q�[���p�b�h�̓��͏��擾
	DIJOYSTATE pad_data = {};
	DIJOYSTATE oldpad_data={};
	LPDIRECTINPUTDEVICE8 g_GamePadDevice = nullptr;
	LPDIRECTINPUT8 g_InputInterface = nullptr;
public://�Q�[���p�b�h
	/// <summary>
	/// �f�o�C�X���͂̏�����
	/// </summary>
	/// <returns></returns>
	bool InitController();

	/// <summary>
	/// Input�I���֐�
	/// </summary>
	void ReleaseInput();

	/// <summary>
	/// �f�o�C�X�̍X�V
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// �{�^����������Ă��邩�ǂ���
	/// </summary>
	/// <param name="button">�{�^���̎��</param>
	/// <returns></returns>
	bool IsButtonPush(ButtonKind button);

	/// <summary>
	/// �{�^���������ꂽ�u�Ԃ��ǂ���
	/// </summary>
	/// <param name="button">�{�^���̎��</param>
	/// <returns></returns>
	bool IsButtonUp(ButtonKind button);

	/// <summary>
	/// �{�^�������ꂽ�u��
	/// </summary>
	/// <param name="button">�{�^���̎��</param>
	/// <returns></returns>
	bool IsButtonDown(ButtonKind button);

	/// <summary>
	/// ���p�b�h�p�x�擾
	/// </summary>
	/// <returns></returns>
	float GetLeftAngle();
	/// <summary>
	/// �E�X�e�B�b�N�p�x�擾
	/// </summary>
	/// <returns></returns>
	float GetRightAngle();

};