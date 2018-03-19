/****************/
/**  関根 明良 **/
/**   メイン   **/
/****************/

#include "MuscleBreak.hpp"

/*-----     グローバル変数,構造体の定義     -----*/

//画像に使用するハンドルの定義
int Images::logo;
int Images::man[3];
int Images::Tshirt;
int Images::effect1;
int Images::smoke;
int Images::circle;
int Images::fragment[5];
int Images::gas;
int Images::tapCircle;
int Images::stage;
int Images::ranking;
int Images::guests[2];
int Images::description;
int Images::scoreBord;

//SEに使用するハンドルの定義
int Sounds::big;
int Sounds::ah;
int Sounds::judge[6];
int Sounds::fun[2];
int Sounds::tap;
int Sounds::breakS;
int Sounds::countDown;
int Sounds::start;
int Sounds::finish;

//BGMに使用するハンドルの定義

int Sounds::title;
int Sounds::description;
int Sounds::game;
int Sounds::result;
int Sounds::ranking;

unsigned short brokeCount = 0;

TapEffect tapEffect[20];

int bigFont;

/*-----     ユーザ関数のプロトタイプ宣言     -----*/

/// <summary>
/// ゲームの初期化
/// </summary>
void MuscleBreakInit(void);
/// <summary>
/// ゲームの設定
/// </summary>
void MuscleBreakSetup(void);

/// <summary>
/// メイン関数
/// </summary>
int android_main(void)
{
	//ゲームを初期化
	MuscleBreakInit();

	while (!ProcessMessage())
	{
		//現在のシーンによって分岐
		switch (Scene::GetNowScene())
		{
		case SceneList::Load:

			Scene::Load();

			break;

		case SceneList::Title:

			Scene::Title();

			break;

		case SceneList::Description:

			Scene::Description();

			break;

		case SceneList::Game:

			Scene::Game();

			break;

		case SceneList::Result:

			Scene::Result();

			break;

		case SceneList::Ranking:

			Scene::Ranking();

			break;
		}
	}

	//Dxライブラリを終了
	DxLib_End();

	return 0;
}

void MuscleBreakInit(void)
{
	//画面サイズを設定
	SetGraphMode(1080, 1920, 32);

	//Dxライブラリを初期化
	if (DxLib_Init() == -1)
		exit(EXIT_FAILURE);

	//描画位置を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームを設定する
	MuscleBreakSetup();
}

void MuscleBreakSetup(void)
{
	//基本のフォントサイズを64に設定
	SetFontSize(64);

	//最初に実行するシーンを設定
	Scene::NextScene(SceneList::Load);

	//TapEffectのインスタンスを生成
	for (int i = 0; i < 20; i++)
		tapEffect[i] = TapEffect(12, .5f, 100);

	//大きいフォントを設定
	bigFont = CreateFontToHandle(NULL, 256, -1);
}

bool Loop(void)
{
	//時間を使うときに必要な関数
	Time::CallEveryFrame();

	//入力を使うときに必要な関数
	Input::CallEveryFrame();

	//アプリのメッセージを処理
	return !ProcessMessage();
}

void Inactive(void * isPause)
{
	//ポーズ画面を表示させる
	*(bool *)isPause = true;
}

void TapEffectPlay(void)
{
	//タップした座標を格納する変数
	Vector2 tapPoint;

	//タップしている数だけループする
	for (int i = 0; i < GetTouchInputNum(); i++)
	{
		//タップした瞬間をチェックする
		if (Input::GetTap(i, Down, &tapPoint))
		{
			for (int j = 0; j < 20; j++)
			{
				//使える状態になっているタップエフェクトを再生
				if (tapEffect[j].canUse)
				{
					tapEffect[j].Start(tapPoint);

					break;
				}
			}
		}
	}

	//タップエフェクトを実行
	for (int i = 0; i < 20; i++)
		tapEffect[i].Play();
}