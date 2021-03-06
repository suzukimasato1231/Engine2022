#include<Windows.h>
#include"SceneManagerh.h"
const int window_width = 1280;//横幅
const int window_height = 720;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SceneManagerh::Get()->Initialize();
	while (true)  // ゲームループ
	{
		//メッセージ処理
		if (_Window::Get()->ProcessMessage()) { break; }

		SceneManagerh::Get()->Update();

		SceneManagerh::Get()->Draw();

	}
#pragma region	//データ解放
	FbxLoader::GetInstance()->Finalize();
	//ゲームウィンドウの破棄
	_Window::Get()->TerminateGameWindow();

	return 0;
}
