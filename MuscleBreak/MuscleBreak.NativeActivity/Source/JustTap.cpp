/*****************/
/**  c ³Vî **/
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
/// Tap»è
/// </summary>
void JustTap::Play(void)
{
	if (StartTap)
	{
		Vector2 tapPos;

		//OÌ¼aª0Èçbad»è
		if (RingScale <= 0)
		{
			judge = 0;//bad
			ScaleChange = true;
		}

		//OÌ¼aª1ÈãÈçk¬
		else if (RingScale > 0)
			RingScale -= 5 + RingCount / 2.5;//Ú®lÌÁ

		 //NbNÌ»è
		if (Input::GetTap(0, Down,&tapPos) && Mouse == true && tapPos.Distance(Postion) < 150.f/2)
		{
			//just»è
			if (RingScale > 65 && RingScale < 85)
				judge = 2;//Just
			
			//good»è
			else if (RingScale > 35 && RingScale < 115)
				judge = 1;//Good
			
			//bad»è
			else 
				judge = 0;//bad

			ScaleChange = true;
			Mouse = false;
		
		}
		else if (Input::GetTap(0, Up)) Mouse = true;

		//»èI¹ã
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
/// »èüÌ`æ
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