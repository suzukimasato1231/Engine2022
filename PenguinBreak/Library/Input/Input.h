#pragma once
#include"Controller.h"
#include "Keybord.h"
#include"Mouse.h"
#include"Singleton.h"
class Input :public Singleton<Input>
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	friend Singleton<Input>;
private://�����o�ϐ�
	//�L�[�{�[�h
	Keybord keybord;
	//�R���g���[���[
	Controller controller;
	//�}�E�X
	Mouse mouse;
public://�ÓI�����o�ϐ�
	//static Input *GetInstance();
public://�����o�֐�
	Input() = default;
	Input(const Input &) = delete;
	~Input() = default;
	Input &operator=(const Input &) = delete;
	//������
	void Initialize();
	//�X�V
	void Update();
public://�L�[�{�[�h
	//�����Ă鎞
	bool KeybordPush(BYTE keyNumber);
	//�������u��
	bool KeybordTrigger(BYTE keyNumber);
	//���L�[�̂����ꂩ�����������ǂ���
	bool KeybordInputArrow();
public://�Q�[���p�b�h

	//@brief �{�^����������Ă��邩�̔���֐�
	// @param[in] button ���肵�����{�^���̎��
	bool ControllerPush(ButtonKind button);

	// @brief �{�^���������ꂽ�u�Ԃ̔���֐�
	// @param[in] button ���肵�����{�^���̎��
	bool ControllerUp(ButtonKind button);

	// @brief �{�^���𗣂����u�Ԃ̔���֐�
	// @param[in] button ���肵�����{�^���̎��
	bool ControllerDown(ButtonKind button);
	//���X�e�B�b�N�p�x�擾
	float GetLeftAngle();

	float GetRightAngle();
	//�E�X�e�B�b�N���͂��Ă邩
	bool ConRightInput();

	//���X�e�B�b�N����͂��Ă邩
	bool ConLeftInput();
public://�}�E�X
	bool MousePushLeft();

	/// <summary>
	/// �L�[�̒��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool MousePushMiddle();

	/// <summary>
	/// �L�[�̍��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool MouseTriggerLeft();

	/// <summary>
	/// �L�[�̒��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool MouseTriggerMiddle();

	/// <summary>
	/// �}�E�X�ړ��ʂ��擾
	/// </summary>
	/// <returns>�}�E�X�ړ���</returns>
	Mouse::MouseMove GetMouseMove();
};