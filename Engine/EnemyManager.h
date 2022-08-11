#pragma once

class EnemyManager
{
protected:
	int hp;
	int graph=0;
	bool flag = true;
private:
	
public:
	EnemyManager();

	~EnemyManager();

	void update();

	void draw();
private:



};

