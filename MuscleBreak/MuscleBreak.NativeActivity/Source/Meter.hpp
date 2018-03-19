/********************/
/**    関根 明良   **/
/** メータークラス **/
/********************/

#pragma once

#include "DxLib.h"

#include "MuscleBreakMath.hpp"
#include "Other.hpp"

/// <summary>
/// メータークラス
/// </summary>
class Meter
{
private:

	/// <summary>
	/// サイズ
	/// </summary>
	Vector2 size;

	/// <summary>
	/// 塗りつぶされている長さ
	/// </summary>
	float fillLength;

	/// <summary>
	/// 最大値
	/// </summary>
	int maxValue;

	/// <summary>
	/// 現在の値
	/// </summary>
	float value;

public:

	/// <summary>
	/// 左上座標
	/// </summary>
	Vector2 position;

	/// <summary>
	/// 値が最大値に達しているか
	/// </summary>
	bool isMax = false;
	/// <summary>
	/// 値が最小値か
	/// </summary>
	bool isMin = false;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Meter(){ }

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="size">サイズ</param>
	/// <param name="initValue">初期値</param>
	/// <param name="maxValue">最大値</param>
	Meter(Vector2 position, Vector2 size, int initValue, int maxValue);

	/// <summary>
	/// 値を増やす
	/// </summary>
	/// <param name="add">増やす値</param>
	void AddValue(int add);

	/// <summary>
	/// 値を設定する
	/// </summary>
	/// <param name="val">設定する値</param>
	void SetValue(int val);

	/// <summary>
	/// 値を取得する
	/// </summary>
	inline int GetValue(void)
	{
		return (int)value;
	}

	/// <summary>
	/// メーターを描画する
	/// </summary>
	void Draw(void);
};