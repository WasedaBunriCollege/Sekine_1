/******************/
/**   関根 明良  **/
/** ボタンクラス **/
/******************/

#pragma once

#include "DxLib.h"

#include "Other.hpp"

/// <summary>
/// ボタンクラス
/// </summary>
class Button
{
private:

	/// <summary>
	/// 左上座標
	/// </summary>
	Vector2 pos;
	/// <summary>
	/// サイズ
	/// </summary>
	Vector2 size;
	/// <summary>
	/// 右下座標
	/// </summary>
	Vector2 bottomRightPos;

	/// <summary>
	/// 表示する文字列
	/// </summary>
	char * text;

public:

	Button(){ }
	/// <summary>
	///	コンストラクタ
	/// </summary>
	/// <param name="position">ボタンを表示する左上の座標</param>
	/// <param name="size">ボタンのサイズ</param>
	/// <param name="text">ボタンに表示する文字列</param>
	Button(Vector2 position, Vector2 size, char * text);

	/// <summary>
	/// ボタンを描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ボタンがタップされているかの取得
	/// </summary>
	/// <param name="checkType">チェックのタイミングを指定</param>
	/// <returns>ボタンがタップされているか</returns>
	bool CheckTap(int checkType);
};