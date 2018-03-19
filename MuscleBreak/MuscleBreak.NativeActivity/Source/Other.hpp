/********************/
/**   関根 明良    **/
/** その他のクラス **/
/********************/

#pragma once

#include"DxLib.h"

#include "MuscleBreakMath.hpp"

/// <summary>
/// 入力判定をする際のタイミングの列挙
/// </summary>
enum CheckType
{
	Down, Press, Up
};

/// <summary>
/// 時間取得クラス
/// </summary>
class Time
{
private:

	/// <summary>
	/// 元の時間
	/// </summary>
	static int64_t beforeTime;

	/// <summary>
	/// 今の時間
	/// </summary>
	static int64_t nowTime;

	/// <summary>
	/// 更新が必要か
	/// </summary>
	static bool needRefresh;

	/// <summary>
	/// 静的クラスにするためにコンストラクタはprivate
	/// </summary>
	Time();

public:

	/// <summary>
	/// 前フレームからの経過時間
	/// </summary>
	static double deltaTime;

	/// <summary>
	/// 毎フレーム呼ばなければならないメソッド
	/// Loop関数内で使用
	/// </summary>
	static void CallEveryFrame(void);

	/// <summary>
	/// 1秒あたりのフレーム数を取得
	/// </summary>
	/// <returns>1秒あたりのフレーム数</returns>
	static int GetFPS(void);
};

/// <summary>
/// 入力情報クラス
/// </summary>
class Input
{
private:

	/// <summary>
	/// Down,Press,Upそれぞれ更新が必要か
	/// </summary>
	static bool needRefrech[3];

	/// <summary>
	/// 1フレーム前の状態
	/// </summary>
	static bool before[3];

	/// <summary>
	/// フレーム毎の結果保存用
	/// </summary>
	static bool result[3];

	/// <summary>
	/// 静的クラスにするためにコンストラクタはprivate
	/// </summary>
	Input();

public:

	/// <summary>
	/// タップ情報を取得
	/// </summary>
	/// <param name="num">何番目のタップを取得するか</param>
	/// <param name="checkType">判定を行うタイミングの指定</param>
	/// <param name="position">タップした座標を格納するポインタ</param>
	/// <returns>checkTypeで指定したタイミングで入力されているか</returns>
	static bool GetTap(int num, int checkType, Vector2 * position = __null);

	/// <summary>
	/// 毎フレーム呼ばなければならないメソッド
	/// Loop関数内で使用
	/// </summary>
	static void CallEveryFrame(void);

};