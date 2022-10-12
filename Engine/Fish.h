#include"Object.h"
#include<vector>

class Fish
{
public:
	//コンストラクタ
	Fish();
	//デスコンストラクタ
	~Fish();
	//作成
	void Create(int stageNum);
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
private:
	ObjectData fishOBJ;

	std::vector<Vec3*>position;
};