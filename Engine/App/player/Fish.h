#include"Object.h"
#include<vector>

class Fish
{
public:
	//�R���X�g���N�^
	Fish();
	//�f�X�R���X�g���N�^
	~Fish();
	//�쐬
	void Create(int stageNum);
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
private:
	ObjectData fishOBJ;

	std::vector<Vec3*>position;
};