#include"Object.h"
#include<vector>

class Fish
{
public:
	Fish();

	~Fish();

	void Create(int stageNum);

	void Init();

	void Update();

	void Draw();
private:
	ObjectData fishOBJ;

	std::vector<Vec3*>position;
};