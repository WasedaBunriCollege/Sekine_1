/********************/
/**    関根 明良   **/
/** メータークラス **/
/********************/

#include "Meter.hpp"

Meter::Meter(Vector2 position, Vector2 size, int initValue, int maxValue) :
	position(position), size(size), value(initValue), maxValue(maxValue)
{
	//塗りつぶされる長さの計算
	fillLength = (float)(value / maxValue * size.y);

	//初期値が最大値に達しているか
	if (initValue == maxValue)
		isMax = true;
	//初期値が最小値か
	else if (initValue == 0)
		isMin = true;
}

void Meter::AddValue(int add)
{
	//値を指定された値だけ加算する
	value += add;

	//isMaxとisMinをfalseに変更
	isMax = isMin = false;

	//値が最大値を超えたら
	if (value > maxValue)
	{
		//値を最大値に固定
		value = maxValue;

		//最大値になっている状態に変更
		isMax = true;
	}
	//値が最小値を下回っていたら
	else if (value < 0)
	{
		//値を0に固定
		value = 0;

		//最小値になっている状態に変更
		isMin = true;
	}

	//塗りつぶされる長さを再計算
	fillLength = (float)(value / maxValue * size.y);

	return;
}

void Meter::SetValue(int val)
{
	//値を変更
	value = val;

	//値が最大値に達しているか
	if (val == 0)
		isMin = true;
	//値が最小値か
	else if (val == maxValue)
		isMax = true;

	//塗りつぶされる長さを再計算
	fillLength = (float)(value / maxValue * size.y);

	return;
}

void Meter::Draw(void)
{
	//メーターの背景を描画
	DrawBox(position.x, position.y, position.x + size.x, position.y + size.y, 0xcccccc, true);
	//メーターの値の範囲を描画
	DrawBox(position.x + size.x, position.y + size.y, position.x, position.y + size.y - fillLength, 0xffffff, true);

	return;
}
