/**********************/
/**     関根 明良    **/
/** エフェクトクラス **/
/**********************/

#include "Effect.hpp"

Smoke::Smoke(Vector2 pos, int particleCount, float angle, float range, int speed, int length, float time) :
	length(length)
{
	Smoke::pos = pos;
	Smoke::particleCount = particleCount;

	//パーティクルにSmokeParticleを指定
	particle = new SmokeParticle *[particleCount];

	//SmokeParticleのインスタンスを生成
	for (int i = 0; i < particleCount; i++)
		particle[i] = new SmokeParticle(pos, angle*PI / 180, range * PI / 180, speed, GetRand(70), time, length);
}

void Smoke::Play(void)
{
	//止まっている数をリセット
	stopCount = 0;

	for (int i = 0; i < particleCount; i++)
	{
		//パーティクルのサイズの変更と移動
		particle[i]->ChangeSize();

		//パーティクルが止まっている数をカウント
		if (particle[i]->stop)
			stopCount++;
	}

	//全てのパーティクルが止まっていたらisStopをtrueにする
	isStop = stopCount == particleCount;
}

void Smoke::Draw(void)
{
	//描画時のブレンドを加算に設定
	SetDrawBlendMode(DX_BLENDMODE_ADD, 95);

	//パーティクルを描画
	for (int i = 0; i < particleCount; i++)
		particle[i]->Draw();

	//描画時のブレンド設定を解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}

void ClothBreak::Play(void)
{
	if (isPlay)
	{
		//パーティクルを移動
		for (int i = 0; i < particleCount; i++)
			particle[i]->Move();

		//前フレームからの時間を加算
		time += Time::deltaTime;

		//0.25秒経過していたら
		if (time >= 0.25f)
		{
			//不透明度を減らす
			alpha -= 8;

			//不透明度が0以下なら実行しないようにする
			isPlay = !alpha <= 0;
		}
	}
}

ClothBreak::ClothBreak(Vector2 pos, int particleCount, float speed, int range)
{
	ClothBreak::particleCount = particleCount;
	ClothBreak::pos = pos;
	
	//パーティクルにClothParticleを指定
	particle = new ClothParticle * [particleCount];

	//ClothParticleのインスタンスを生成
	for (int i = 0; i < particleCount; i++)
		particle[i] = new ClothParticle(pos, GetRand(speed * 100) / 100.f, (2 * PI / particleCount)*i,range);
}

void ClothBreak::Start(void)
{
	//実行するように設定
	isPlay = true;
	//不透明度を最大に設定
	alpha = 255;

	//時間を初期化
	time = 0;

	//パーティクルの処理を開始
	for (int i = 0; i < particleCount; i++)
		particle[i]->Start();
}

void ClothBreak::Draw(void)
{
	//描画時のブレンドをアルファブレンドに設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	//パーティクルを描画
	for (int i = 0; i < particleCount; i++)
		particle[i]->Draw();

	//描画時のブレンド設定を解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}

LineEffect::LineEffect(Vector2 pos, int particleCount, int range, unsigned int color)
{
	LineEffect::pos = pos;
	LineEffect::particleCount = particleCount;
	LineEffect::range = range;

	//パーティクルにLineParticleを指定
	particle = new LineParticle*[particleCount];

	for (int i = 0; i < particleCount; i++)
	{
		//パーティクルの描画位置を計算
		Vector2 tmp(range * cos(PI * 2 / particleCount*i), range * sin(PI * 2 / particleCount*i));
		//LineParticleのインスタンスを生成
		particle[i] = new LineParticle(pos + tmp, pos, 550 - GetRand(100), GetRand(10) - 5, color);
	}
}

void LineEffect::Draw(void)
{
	//パーティクルを描画
	for (int i = 0; i < particleCount; i++)
		particle[i]->Draw();
}

void LineEffect::Play(void)
{
	//パーティクルの処理を実行
	for (int i = 0; i < particleCount; i++)
		particle[i]->Play();
}

TapEffect::TapEffect(int particleCount, float speed, int range) :
	particleCount(particleCount), speed(speed), range(range)
{
	//パーティクルの座標を指定された数だけ生成
	particlePos = new Pos[particleCount];
}

void TapEffect::Play(void)
{
	//基準の角度を変更して回転させる
	centerAngle += PI / 24;

	if (isPlaying  && !isStopping)
	{
		//中心からの距離を長くする
		radius += speed;

		//パーティクルを移動
		for (int i = 0; i < particleCount; i++)
		{
			particlePos[i].x += cos(centerAngle+(PI * 2 / particleCount)*i)*radius;
			particlePos[i].y += sin(centerAngle+(PI * 2 / particleCount)*i)*radius;
		}

		//中心からパーティクルの距離が指定された範囲以上離れたら動作を止める
		isStopping = pos.Distance(particlePos[0].x, particlePos[0].y) >= range;
	}
	else if (isStopping)
	{
		//不透明度を減らす
		alpha -= 8;

		//不透明度がマイナスになったら
		if (alpha < 0)
		{
			//実行しているかと止まっているかのフラグをfalseにする
			isPlaying = false;
			isStopping = false;

			//エフェクトが使えるように設定
			canUse = true;

			//不透明度を0に設定
			alpha = 0;

			//中心からの距離を0に設定
			radius = 0.0f;
		}
	}
}

void TapEffect::Start(Vector2 pos)
{
	if (!isPlaying && !isStopping)
	{
		//新しく使えないように設定
		canUse = false;
		//実行するように設定
		isPlaying = true;

		//不透明度を半分に設定
		alpha = 127;

		//指定された位置に設定
		TapEffect::pos = pos;

		//パーティクルを指定された位置に設定
		for (int i = 0; i < particleCount; i++)
		{
			particlePos[i].x = pos.x;
			particlePos[i].y = pos.y;
		}

		//タップした音を再生
		PlaySoundMem(Sounds::tap, DX_PLAYTYPE_BACK);
	}
}

void TapEffect::Draw(void)
{
	//描画時のブレンドをアルファに設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	//パーティクルの描画
	for (int i = 0; i < particleCount; i++)
		DrawRotaGraph(particlePos[i].x, particlePos[i].y, .5, 0.0, Images::circle, true);

	//描画時のブレンド設定を解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}
