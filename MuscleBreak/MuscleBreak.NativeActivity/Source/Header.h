/*****************/
/**  島田 竜之介 **/
/*****************/
#pragma once
#include "DxLib.h"
#include "MuscleBreak.hpp"

//extern int JustTap(void);
/// <summary>
/// タイミングの判定
/// </summary>
class JustTap
{

public:
	JustTap(Vector2 Pos);

	void Play(void);
	void Draw(void);

	//inlineはClass内で処理ができる
	/// <summary>
	/// 開始
	/// </summary>
	inline void Start(void)
	{
		StartTap = true;
		Playing = true;
	}
	/// <summary>
	/// 実行中
	/// </summary>
	inline bool IsPlaying(void)
	{
		return Playing;
	}

	/// <summary>
	/// <para>タップ判定</para>
	/// <para>2:大成功</para>
	/// <para>1:成功</para>
	/// <para>0:失敗</para>
	/// </summary>
	int judge = 0;

private:
	/// <summary>
	/// Tapリングの大きさ
	/// </summary>
	float RingScale = 300;

	/// <summary>
	/// リングを出現させた回数
	/// </summary>
	float RingCount = 0;

	/// <summary>
	/// 
	/// </summary>
	bool StartTap = false;
	
	/// <summary>
	/// マウスの操作取得
	/// </summary>
	bool Mouse = true;
	
	/// <summary>
	/// 大きさの変化の可不可切り替え
	/// </summary>
	bool ScaleChange = false;
	
	/// <summary>
	/// 実行中を判定
	/// </summary>
	bool Playing = false;


	Vector2 Postion;

};

class ClothBreak;

class TitleAnimation
{

public:
	bool Draw(void);


private:
	float Alpha=0;
	float time = 0;
	

	bool ManGrap = true;
	bool DrawB = true; 

	bool TimeF = false;
	bool EndF = false;

	static ClothBreak cloth;
};