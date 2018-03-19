/********************/
/**    �֍� ����   **/
/** ���[�^�[�N���X **/
/********************/

#include "Meter.hpp"

Meter::Meter(Vector2 position, Vector2 size, int initValue, int maxValue) :
	position(position), size(size), value(initValue), maxValue(maxValue)
{
	//�h��Ԃ���钷���̌v�Z
	fillLength = (float)(value / maxValue * size.y);

	//�����l���ő�l�ɒB���Ă��邩
	if (initValue == maxValue)
		isMax = true;
	//�����l���ŏ��l��
	else if (initValue == 0)
		isMin = true;
}

void Meter::AddValue(int add)
{
	//�l���w�肳�ꂽ�l�������Z����
	value += add;

	//isMax��isMin��false�ɕύX
	isMax = isMin = false;

	//�l���ő�l�𒴂�����
	if (value > maxValue)
	{
		//�l���ő�l�ɌŒ�
		value = maxValue;

		//�ő�l�ɂȂ��Ă����ԂɕύX
		isMax = true;
	}
	//�l���ŏ��l��������Ă�����
	else if (value < 0)
	{
		//�l��0�ɌŒ�
		value = 0;

		//�ŏ��l�ɂȂ��Ă����ԂɕύX
		isMin = true;
	}

	//�h��Ԃ���钷�����Čv�Z
	fillLength = (float)(value / maxValue * size.y);

	return;
}

void Meter::SetValue(int val)
{
	//�l��ύX
	value = val;

	//�l���ő�l�ɒB���Ă��邩
	if (val == 0)
		isMin = true;
	//�l���ŏ��l��
	else if (val == maxValue)
		isMax = true;

	//�h��Ԃ���钷�����Čv�Z
	fillLength = (float)(value / maxValue * size.y);

	return;
}

void Meter::Draw(void)
{
	//���[�^�[�̔w�i��`��
	DrawBox(position.x, position.y, position.x + size.x, position.y + size.y, 0xcccccc, true);
	//���[�^�[�̒l�͈̔͂�`��
	DrawBox(position.x + size.x, position.y + size.y, position.x, position.y + size.y - fillLength, 0xffffff, true);

	return;
}
