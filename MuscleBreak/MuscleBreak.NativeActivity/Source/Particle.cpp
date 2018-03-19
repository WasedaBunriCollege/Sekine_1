/************************/
/**      関根 明良     **/
/** パーティクルクラス **/
/************************/

#include "Particle.hpp"

void Particle::Move(void)
{
	//角度をランダムで取得
	float theta = GetRand(2 * PI * 100) / 100.f;
	//中心からの距離をランダムで取得
	int r = -range + GetRand(range * 2);

	//中心からの距離と角度から座標を計算
	pos = Vector2(r*cos(theta), r*sin(theta)) + originalPos;

	//サイズが変わる速度をランダムで取得
	speed = (float)(GetRand(100) / 2000.0f) + .075f;
}

void Particle::ChangeSize(void)
{
	//一定の時間から前フレームからの経過時間を減算
	time -= Time::deltaTime;

	//一定時間経過していたら処理を止める
	stop = time <= 0;

	//サイズの変更
	if (!reverse)
		size += speed;
	else
		size -= speed;

	//一定サイズ以上になっているか
	if (!reverse && size >= 1.f)
	{
		//サイズを1倍に固定
		size = 1.f;
		//サイズを小さくさせる処理に移行
		reverse = true;
	}
	//サイズが0以下になっているか
	else if (reverse && size <= 0.0f)
	{
		//サイズを0に固定
		size = 0.0f;
		//サイズを大きくさせる処理に移行
		reverse = false;

		//処理が止まっていなければ描画位置を変更
		if (!stop)
			Move();
	}
}

Particle::Particle(Vector2 originalPos, int range, float time) :
	originalPos(originalPos), range(range), time(time), size(0)
{
	//角度をランダムで取得
	float theta = GetRand(2 * PI * 100) / 100.f;
	//中心からの距離をランダムで取得
	int r = -range + GetRand(range * 2);

	//中心からの距離と角度から座標を計算
	pos = Vector2(r*cos(theta), r*sin(theta)) + originalPos;

	//サイズが変わる速度をランダムで取得
	speed = (float)(GetRand(100) / 2000.0f) + .075f;
}

void Particle::Draw(void)
{
	//処理が止まっていなければパーティクルを描画
	if (!stop)
		DrawRotaGraph2(pos.x, pos.y, 64, 64, size, 0.0f, Images::effect1, true);
}

void SmokeParticle::Move(void)
{
	//パーティクルの移動
	pos.x += speed*cos(angle);
	pos.y += speed*sin(angle);

	//指定された距離以上離れたらリセット
	if (Distance() >= length)
		Reset();
}

SmokeParticle::SmokeParticle(Vector2 originalPos, float angle, float range, float speed, int delayCount, float time, int length) :
	centerAngle(angle), range(range), rot(0.0f), rotSpeed(GetRand(PI / 16 * 100) / 100.0f), delayCount(delayCount), time(time), length(length)
{
	SmokeParticle::originalPos = originalPos;
	SmokeParticle::speed = speed;

	pos = originalPos;

	//進む方向を計算
	SmokeParticle::angle = centerAngle - range + GetRand(range * 2 * 100) / 100.0f;

	//サイズを0に設定
	size = 0;
}

void SmokeParticle::Draw(void)
{
	//指定されたフレーム数経過していたら描画
	if (delayCount <= 0 && !stop)
		DrawRotaGraph(pos.x, pos.y, size, rot, Images::smoke, true);
}

void SmokeParticle::ChangeSize(void)
{
	//一定の時間から前フレームからの経過時間を減算
	time -= Time::deltaTime;

	//指定されたフレーム数経過していたら
	if (--delayCount <= 0)
	{
		//回転させる
		rot += rotSpeed;
		//サイズを大きくさせる
		size += .01f;

		//止まっていなければ移動
		if (!stop)
			Move();
	}
}

float SmokeParticle::Distance(void)
{
	//基準の座標からの距離を返す
	return pos.Distance(originalPos);
}

void SmokeParticle::Reset(void)
{
	//サイズを0に設定
	size = 0;

	//回転速度をランダムで取得
	rotSpeed = GetRand(PI / 16 * 100) / 100.0f;

	//進む方向を再計算
	centerAngle = centerAngle - range + GetRand(range * 2 * 100) / 100.0f;

	//座標を元の位置に変更
	pos = originalPos;

	//指定された時間経過していたら止める
	stop = time <= 0;
}

void ClothParticle::Move(void)
{
	//移動
	pos += Vector2(speed*cos(angle), speed*sin(angle));

	//重力を計算
	gravity += g*Time::deltaTime;

	//重力を加算
	pos.y += gravity;
}
void ClothParticle::Start(void)
{
	//座標を中心座標からランダムの距離に設定
	pos = originalPos + Vector2(GetRand(range)*cos(angle), GetRand(range)*sin(angle));

	//重力をリセット
	gravity = 0;

	//角度をランダムで取得
	rot = GetRand(PI * 2 * 100) / 100.f;
}

ClothParticle::ClothParticle(Vector2 originalPos, float speed, float angle, int range)
{
	ClothParticle::speed = speed;
	ClothParticle::angle = angle;
	ClothParticle::originalPos = originalPos;
	ClothParticle::range = range;

	//描画する画像をランダムで設定
	imageNum = GetRand(4);
}

void ClothParticle::Draw(void)
{
	//描画
	DrawRotaGraph(pos.x, pos.y, 1.f, rot, Images::fragment[imageNum], true);
}

LineParticle::LineParticle(Vector2 pos, Vector2 originalPos, float length, float speed, unsigned int color) :
	length(length), color(color)
{
	LineParticle::pos = pos;
	LineParticle::originalPos = originalPos;
	LineParticle::speed = speed;

	lengthTmp = length;

	//角度を計算
	angle = pos.Angle(originalPos);
}

void LineParticle::Draw(void)
{
	//描画
	DrawTriangleAA(pos.x + 16 * cos(angle + PI / 2), pos.y + 16 * sin(angle + PI / 2), pos.x - 16 * cos(angle + PI / 2), pos.y - 16 * sin(angle + PI / 2), originalPos.x - length * cos(angle), originalPos.y - length * sin(angle), color, true);
}

void LineParticle::Play(void)
{
	//一定の速度で線の長さを変更
	length += speed;

	//一定の距離以上離れたら
	if (length > lengthTmp*1.5 || length < lengthTmp*0.5)
	{
		//進む方向を反転
		speed *= -1;
		//サイド線の長さを変更
		length += speed;
	}
}
