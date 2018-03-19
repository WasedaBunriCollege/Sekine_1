/******************/
/**   �֍� ����  **/
/** �{�^���N���X **/
/******************/

#include "Button.hpp"

Button::Button(Vector2 position, Vector2 size, char * text) :
	pos(position), size(size), text(text)
{
	//�{�^���̉E�����W�̌v�Z
	bottomRightPos = pos + size;
}

void Button::Draw()
{
	//������̍��W
	Vector2 textPos;

	//�{�^���̔w�i��`��
	DrawBox(pos.x, pos.y, bottomRightPos.x, bottomRightPos.y, 0xaaaaaa, true);

	//������̕`�悷����W���v�Z
	textPos.x = pos.x + size.x / 2 - GetDrawFormatStringWidth(text) / 2;
	textPos.y = pos.y + size.y / 2 - GetFontSize() / 2 - 10;

	//�������`��
	DrawFormatString(textPos.x, textPos.y, 0, "%s", text);

	return;
}

bool Button::CheckTap(int checkType)
{
	//�^�b�v�����ʒu
	Vector2 tapPos;

	//��ʂ��^�b�v���Ă��邩
	if (Input::GetTap(0, checkType, &tapPos))
	{
		//�^�b�v�����ʒu���{�^���͈̔͂ɓ����Ă��邩
		if (tapPos.x >= pos.x && tapPos.x <= bottomRightPos.x && tapPos.y >= pos.y && tapPos.y <= bottomRightPos.y)
			return true;
	}

	return false;
}
