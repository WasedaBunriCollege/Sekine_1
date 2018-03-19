/*****************/
/**  島田 竜之介 **/
/*****************/
#include "Header.h"

/// <summary>
/// 
/// </summary>
JustTap::JustTap(Vector2 Pos)
{
	Postion = Pos;
}

/// <summary>
/// Tap判定
/// </summary>
void JustTap::Play(void)
{
	if (StartTap)
	{
		Vector2 tapPos;

		//リングの直径が0ならbad判定
		if (RingScale <= 0)
		{
			judge = 0;//bad
			ScaleChange = true;
		}

		//リングの直径が1以上なら縮小
		else if (RingScale > 0)
			RingScale -= 5 + RingCount / 2.5;//移動値の増加

		 //クリック時の判定処理
		if (Input::GetTap(0, Down,&tapPos) && Mouse == true && tapPos.Distance(Postion) < 150.f/2)
		{
			//just判定
			if (RingScale > 65 && RingScale < 85)
				judge = 2;//Just
			
			//good判定
			else if (RingScale > 35 && RingScale < 115)
				judge = 1;//Good
			
			//bad判定
			else 
				judge = 0;//bad

			ScaleChange = true;
			Mouse = false;
		
		}
		else if (Input::GetTap(0, Up)) Mouse = true;

		//判定処理終了後
		if (ScaleChange)
		{
			RingScale = 300;
			RingCount++;
			if (RingCount > 50)RingCount = 50;
			ScaleChange = false;
			StartTap = false;
			Playing = false;
		}
	}
	return;
}

/// <summary>
/// 判定線の描画
/// </summary>
void JustTap::Draw(void)
{
	if (StartTap && !ScaleChange)
	{
		DrawRotaGraph(Postion.x, Postion.y, 1.0, 0.0, Images::tapCircle, true);
		DrawCircleAA(Postion.x, Postion.y, RingScale, 50, 0xffff00, FALSE, 10.f);
		//DrawCircleAA(Postion.x, Postion.y, 50, 50, 0xff00, FALSE, 10.f);
	}
}