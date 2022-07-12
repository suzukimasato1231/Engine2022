#include"Singleton.h"

class ResultScene :public Singleton<ResultScene>
{
private:
	friend Singleton<ResultScene>;
public:
	void Init();

	void Update();

	void Draw();

private:




};