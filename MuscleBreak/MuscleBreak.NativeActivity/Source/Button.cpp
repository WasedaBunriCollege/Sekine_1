/******************/
/**   関根 明良  **/
/** ボタンクラス **/
/******************/

#include "Button.hpp"

Button::Button(Vector2 position, Vector2 size, char * text) :
	pos(position), size(size), text(text)
{
	//ボタンの右下座標の計算
	bottomRightPos = pos + size;
}

void Button::Draw()
{
	//文字列の座標
	Vector2 textPos;

	//ボタンの背景を描画
	DrawBox(pos.x, pos.y, bottomRightPos.x, bottomRightPos.y, 0xaaaaaa, true);

	//文字列の描画する座標を計算
	textPos.x = pos.x + size.x / 2 - GetDrawFormatStringWidth(text) / 2;
	textPos.y = pos.y + size.y / 2 - GetFontSize() / 2 - 10;

	//文字列を描画
	DrawFormatString(textPos.x, textPos.y, 0, "%s", text);

	return;
}

bool Button::CheckTap(int checkType)
{
	//タップした位置
	Vector2 tapPos;

	//画面をタップしているか
	if (Input::GetTap(0, checkType, &tapPos))
	{
		//タップした位置がボタンの範囲に入っているか
		if (tapPos.x >= pos.x && tapPos.x <= bottomRightPos.x && tapPos.y >= pos.y && tapPos.y <= bottomRightPos.y)
			return true;
	}

	return false;
}
