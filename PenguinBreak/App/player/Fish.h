#pragma once
class FishClass
{
public: 
	/// <summary>
	/// �R���X�g���N�g
	/// </summary>
	FishClass();
	/// <summary>
	/// �f�X�R���X�g���N�g
	/// </summary>
	~FishClass();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// ���̍X�V
	/// </summary>
	void Update(bool& m_changeBreakFlag, int& m_remainLives);

	int GetFishNum()const { return m_fishNum; }
private:
	bool m_fishFlag = false;			//�����l��������
	int m_fishNum = 0;					//���l����
	const int c_fishMax = 100;			//�ő�l����
	const int c_fishPlas = 5;			//���̊l����
};

