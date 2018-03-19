/*****************/
/**  ���c ���V�� **/
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
/// Tap����
/// </summary>
void JustTap::Play(void)
{
	if (StartTap)
	{
		Vector2 tapPos;

		//�����O�̒��a��0�Ȃ�bad����
		if (RingScale <= 0)
		{
			judge = 0;//bad
			ScaleChange = true;
		}

		//�����O�̒��a��1�ȏ�Ȃ�k��
		else if (RingScale > 0)
			RingScale -= 5 + RingCount / 2.5;//�ړ��l�̑���

		 //�N���b�N���̔��菈��
		if (Input::GetTap(0, Down,&tapPos) && Mouse == true && tapPos.Distance(Postion) < 150.f/2)
		{
			//just����
			if (RingScale > 65 && RingScale < 85)
				judge = 2;//Just
			
			//good����
			else if (RingScale > 35 && RingScale < 115)
				judge = 1;//Good
			
			//bad����
			else 
				judge = 0;//bad

			ScaleChange = true;
			Mouse = false;
		
		}
		else if (Input::GetTap(0, Up)) Mouse = true;

		//���菈���I����
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
/// ������̕`��
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