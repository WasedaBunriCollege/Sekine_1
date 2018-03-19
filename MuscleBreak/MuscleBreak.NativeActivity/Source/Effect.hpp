/**********************/
/**     関根 明良    **/
/** エフェクトクラス **/
/**********************/

#pragma once

#include "DxLib.h"

#include "MuscleBreakMath.hpp"
#include "Particle.hpp"

/// <summary>
/// キラキラするエフェクト
/// </summary>
template <class T>
class Effect
{
private:

protected:

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 pos;

	/// <summary>
	/// パーティクル
	/// </summary>
	T ** particle;

	/// <summary>
	/// 範囲
	/// </summary>
	int range;

	/// <summary>
	/// パーティクルの数
	/// </summary>
	int particleCount;

	/// <summary>
	/// 時間
	/// </summary>
	float time;

public:

	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Effect(){ }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">描画する座標</param>
	/// <param name="particleCount">パーティクルの数</param>
	/// <param name="range">描画範囲(半径)</param>
	/// <param name="time">エフェクトを表示する時間</param>
	Effect(Vector2 pos, int particleCount, int range, float time) :
		pos(pos), particleCount(particleCount), range(range), time(time)
	{
		//指定されたパーティクルクラスを生成
		particle = new T *[particleCount];

		for (int i = 0; i < particleCount; i++)
		{
			particle[i] = new T(pos, range, time);
		}
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Effect()
	{
		//メモリの開放
		for (int i = 0; i < particleCount; i++)
			delete particle[i];

		delete[] particle;
	}

	/// <summary>
	/// エフェクトの実行
	/// </summary>
	inline virtual void Play(void)
	{
		//パーティクルのサイズを変更
		for (int i = 0; i < particleCount; i++)
			particle[i]->ChangeSize();
	}

	/// <summary>
	/// 描画
	/// </summary>
	inline virtual void Draw(void)
	{
		//パーティクルを描画
		for (int i = 0; i < particleCount; i++)
			particle[i]->Draw();
	}

	/// <summary>
	/// パーティクルの数の変更
	/// </summary>
	/// <param name="particleCount">パーティクルの数</param>
	inline void ChangeParticleCount(int particleCount)
	{
		//パーティクルのメモリを解放
		for (int i = 0; i < Effect::particleCount; i++)
			delete particle[i];

		delete[] particle;

		//新しいパーティクルの数に変更
		Effect::particleCount = particleCount;

		//パーティクルを指定された数で生成
		particle = new T*[particleCount];
	}

	/// <summary>
	/// 動作を開始
	/// </summary>
	inline void Start(void)
	{
		//パーティクルのインスタンスを生成
		for (int i = 0; i < particleCount; i++)
			particle[i] = new T(pos, range, time);
	}
};

class SmokeParticle;

/// <summary>
/// 煙エフェクト
/// </summary>
class Smoke : public Effect<SmokeParticle>
{
private:

	/// <summary>
	/// 長さ
	/// </summary>
	int length;
	/// <summary>
	/// 止まっているパーティクルの数
	/// </summary>
	int stopCount = 0;

public:

	/// <summary>
	/// エフェクトが止まっているか
	/// </summary>
	bool isStop = false;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">描画する座標</param>
	/// <param name="particleCount">パーティクルの数</param>
	/// <param name="angle">煙が進む角度</param>
	/// <param name="range">煙が進む方向の範囲</param>
	/// <param name="speed">煙が進む速度</param>
	/// <param name="length">煙が進む長さ</param>
	/// <param name="time">エフェクトを表示する時間</param>
	Smoke(Vector2 pos, int particleCount, float angle, float range, int speed, int length, float time);

	/// <summary>
	/// 実行
	/// </summary>
	void Play(void);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(void);
};

class ClothParticle;

/// <summary>
/// 布片のエフェクト
/// </summary>
class ClothBreak : public Effect<ClothParticle>
{
private:

	/// <summary>
	/// 実行しているか
	/// </summary>
	bool isPlay = false;

	/// <summary>
	/// 不透明度
	/// </summary>
	int alpha = 0;

	/// <summary>
	/// 時間
	/// </summary>
	float time;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">描画する座標</param>
	/// <param name="particleCount">パーティクルの数</param>
	/// <param name="speed">移動速度</param>
	/// <param name="range">範囲</param>
	ClothBreak(Vector2 pos, int particleCount, float speed, int range);

	/// <summary>
	/// 実行
	/// </summary>
	void Play(void);

	/// <summary>
	/// 開始
	/// </summary>
	void Start(void);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(void);
};

class LineParticle;

/// <summary>
/// 集中線のエフェクト
/// </summary>
class LineEffect : public Effect<LineParticle>
{
private:

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">描画する座標</param>
	/// <param name="particleCount">パーティクルの数</param>
	/// <param name="range">描画範囲</param>
	/// <param name="color">集中線の色</param>
	LineEffect(Vector2 pos, int particleCount, int range, unsigned int color = 0xffffff);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(void);

	/// <summary>
	/// 実行
	/// </summary>
	void Play(void);
};

/// <summary>
/// タップ時のエフェクト
/// </summary>
class TapEffect
{
private:

	/// <summary>
	/// 座標用の構造体
	/// </summary>
	struct Pos
	{
		float x, y;
	};

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 pos;
	/// <summary>
	/// パーティクルの座標
	/// </summary>
	Pos * particlePos;

	/// <summary>
	/// パーティクルの数
	/// </summary>
	int particleCount;
	/// <summary>
	/// 表示範囲
	/// </summary>
	int range;

	/// <summary>
	/// 不透明度
	/// </summary>
	int alpha = 0;
	/// <summary>
	/// 中心からの距離
	/// </summary>
	float radius = 0;

	/// <summary>
	/// 基準の角度
	/// </summary>
	float centerAngle = 0.f;

	/// <summary>
	/// 移動速度
	/// </summary>
	float speed;

	/// <summary>
	/// 実行しているか
	/// </summary>
	bool isPlaying = false;
	/// <summary>
	/// 処理が止まっているか
	/// </summary>
	bool isStopping = false;

public:

	/// <summary>
	/// 処理が終了していて使える状態か
	/// </summary>
	bool canUse = true;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TapEffect() { }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="particleCount">パーティクルの数</param>
	/// <param name="speed">速度</param>
	/// <param name="range">範囲</param>
	TapEffect(int particleCount, float speed, int range);

	/// <summary>
	/// 実行
	/// </summary>
	void Play(void);

	/// <summary>
	/// 開始
	/// </summary>
	/// <param name="pos">エフェクトの中心座標</param>
	void Start(Vector2 pos);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(void);
};