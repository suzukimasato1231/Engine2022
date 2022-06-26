#include<Windows.h>
#include"SceneManagerh.h"
const int window_width = 1280;//横幅
const int window_height = 720;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SceneManagerh::Instance()->Initialize();
	while (true)  // ゲームループ
	{
		//メッセージ処理
		if (_Window::Instance()->ProcessMessage()) { break; }

		SceneManagerh::Instance()->Update();

		SceneManagerh::Instance()->Draw();

	}
#pragma region	//データ解放
	FbxLoader::GetInstance()->Finalize();
	//ゲームウィンドウの破棄
	_Window::Instance()->TerminateGameWindow();

	return 0;
}
