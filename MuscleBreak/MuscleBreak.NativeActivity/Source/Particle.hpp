/************************/
/**      関根 明良     **/
/** パーティクルクラス **/
/************************/

#pragma once

#include "MuscleBreak.hpp"

/// <summary>
/// パーティクル
/// </summary>
class Particle
{
private:

protected:

	/// <summary>
	/// 基準となる座標
	/// </summary>
	Vector2 originalPos;

	/// <summary>
	/// 範囲
	/// </summary>
	int range;

	/// <summary>
	/// 大きさ
	/// </summary>
	float size;
	/// <summary>
	/// サイズが変わる速度
	/// </summary>
	float speed;
	/// <summary>
	/// 座標を求めるための角度
	/// </summary>
	float angle;
	/// <summary>
	/// 時間
	/// </summary>
	float time;

	/// <summary>
	/// 小さくするか
	/// </summary>
	bool reverse = false;
	/// <summary>
	/// 止まっているか
	/// </summary>
	bool stop = true;

	/// <summary>
	/// 位置を変える
	/// </summary>
	virtual void Move(void);

public:

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 pos;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Particle()
	{
	}
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="originalPos">基準となる座標</param>
	/// <param name="range">範囲</param>
	/// <param name="time">描画時間</param>
	Particle(Vector2 originalPos, int range, float time);

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(void);

	/// <summary>
	/// サイズを変更
	/// </summary>
	virtual void ChangeSize(void);
};

/// <summary>
/// 煙パーティクル
/// </summary>
class SmokeParticle : public Particle
{
private:

	/// <summary>
	/// 基準となる角度
	/// </summary>
	float centerAngle;
	/// <summary>
	/// 描画する角度
	/// </summary>
	float rot;
	/// <summary>
	/// 回転速度
	/// </summary>
	float rotSpeed;

	/// <summary>
	/// 範囲
	/// </summary>
	float range;

	/// <summary>
	/// 時間
	/// </summary>
	float time;

	/// <summary>
	/// 移動
	/// </summary>
	void Move(void);

	/// <summary>
	/// 描画開始を遅らせるフレーム数
	/// </summary>
	int delayCount;
	/// <summary>
	/// 基準の座標からの最大距離
	/// </summary>
	int length;

	/// <summary>
	/// 基準の座標からの距離を取得
	/// </summary>
	/// <returns>基準の座標からの距離</returns>
	float Distance(void);

	/// <summary>
	/// リセット
	/// </summary>
	void Reset(void);

public:

	/// <summary>
	/// 止まっているか
	/// </summary>
	bool stop = false;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="originalPos">基準となる座標</param>
	/// <param name="angle">基準となる角度</param>
	/// <param name="range">角度での表示範囲</param>
	/// <param name="speed">移動速度</param>
	/// <param name="delayCount">描画開始を遅らせるフレーム数</param>
	/// <param name="time">描画する時間</param>
	/// <param name="length">基準の座標からの最大距離</param>
	SmokeParticle(Vector2 originalPos, float angle, float range, float speed, int delayCount, float time, int length);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(void);

	/// <summary>
	/// サイズの変更と移動
	/// </summary>
	void ChangeSize(void);
};

/// <summary>
/// 布片のパーティクル
/// </summary>
class ClothParticle : public Particle
{
private:

	/// <summary>
	/// 重力加速度
	/// </summary>
	static const float g = 9.80665f;

	/// <summary>
	/// 描画する画像の番号
	/// </summary>
	int imageNum;

	/// <summary>
	/// パーティクルが落ちる速度
	/// </summary>
	float gravity;
	/// <summary>
	/// 描画する角度
	/// </summary>
	float rot;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="originalPos">基準となる座標</param>
	/// <param name="speed">移動速度</param>
	/// <param name="angle">座標を求めるための角度</param>
	/// <param name="range">範囲</param>
	ClothParticle(Vector2 originalPos, float speed, float angle, int range);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(void);

	/// <summary>
	/// 移動
	/// </summary>
	void Move(void);

	/// <summary>
	/// 処理開始
	/// </summary>
	void Start(void);
};

/// <summary>
/// 集中線のパーティクル
/// </summary>
class LineParticle : public Particle
{
private:

	/// <summary>
	/// 基準の座標からの距離
	/// </summary>
	float length;

	/// <summary>
	/// 基準の座標からの基準の距離
	/// </summary>
	float lengthTmp;

	/// <summary>
	/// 色
	/// </summary>
	unsigned int color;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="originalPos">基準となる座標</param>
	/// <param name="length">基準座標からの距離</param>
	/// <param name="speed">移動速度</param>
	/// <param name="color">色</param>
	LineParticle(Vector2 pos, Vector2 originalPos, float length, float speed, unsigned int color);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(void);

	/// <summary>
	/// 処理
	/// </summary>
	void Play(void);
};