/****************/
/**  関根 明良 **/
/**   メイン   **/
/****************/

#pragma once

#include <cstdlib>
#include <cmath>

#include "DxLib.h"

#include "MuscleBreakMath.hpp"
#include "Scene.hpp"
#include "Meter.hpp"
#include "Other.hpp"
#include "Button.hpp"
#include "Ranking.hpp"
#include "Effect.hpp"
#include "Particle.hpp"

#include "Header.h"

using namespace std;

class TapEffect;

/// <summary>
/// ゲーム内で使用する画像のハンドル
/// </summary>
struct Images
{
	static int logo;
	static int man[3];
	static int Tshirt;
	static int effect1;
	static int smoke;
	static int circle;
	static int fragment[5];
	static int gas;
	static int tapCircle;
	static int stage;
	static int ranking;
	static int guests[2];
	static int description;
	static int scoreBord;
};

/// <summary>
/// ゲーム内で使用する音声のハンドル
/// </summary>
struct Sounds
{
	static int big;
	static int ah;
	static int judge[6];
	static int fun[2];
	static int tap;
	static int breakS;
	static int countDown;
	static int start;
	static int finish;

	static int title;
	static int description;
	static int game;
	static int result;
	static int ranking;
};

/*-----     グローバル変数宣言     -----*/


// 破いた服の枚数
extern unsigned short brokeCount;


// タップ時のエフェクト
extern TapEffect tapEffect[20];


// 大きいフォントを使う時に使用するハンドル
extern int bigFont;

/*-----     グローバル関数宣言     -----*/

/// <summary>
/// ループ毎に呼び出す
/// </summary>
extern bool Loop(void);

/// <summary>
/// アプリが非アクティブになった時に呼ばれる関数
/// </summary>
/// <param name="isPause">ポーズメニューが表示されているかを格納する変数のポインタ</param>
extern void Inactive(void * isPause);

/// <summary>
/// タップ入力があった時にタップエフェクトを描画する
/// </summary>
extern void TapEffectPlay(void);