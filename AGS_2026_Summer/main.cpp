#include <DxLib.h>
#include "SceneManager.h"
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
	//シーンマネージャーのオブジェクトを作成
	SceneManager sceneMana;

	//初期化処理
	sceneMana.SystemInit();
	//ゲーム起動
	sceneMana.Run();
	//開放処理
	sceneMana.Release();






}