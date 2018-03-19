/******************/
/**   �֍� ����  **/
/** �{�^���N���X **/
/******************/

#pragma once

#include "DxLib.h"

#include "Other.hpp"

/// <summary>
/// �{�^���N���X
/// </summary>
class Button
{
private:

	/// <summary>
	/// ������W
	/// </summary>
	Vector2 pos;
	/// <summary>
	/// �T�C�Y
	/// </summary>
	Vector2 size;
	/// <summary>
	/// �E�����W
	/// </summary>
	Vector2 bottomRightPos;

	/// <summary>
	/// �\�����镶����
	/// </summary>
	char * text;

public:

	Button(){ }
	/// <summary>
	///	�R���X�g���N�^
	/// </summary>
	/// <param name="position">�{�^����\�����鍶��̍��W</param>
	/// <param name="size">�{�^���̃T�C�Y</param>
	/// <param name="text">�{�^���ɕ\�����镶����</param>
	Button(Vector2 position, Vector2 size, char * text);

	/// <summary>
	/// �{�^����`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �{�^�����^�b�v����Ă��邩�̎擾
	/// </summary>
	/// <param name="checkType">�`�F�b�N�̃^�C�~���O���w��</param>
	/// <returns>�{�^�����^�b�v����Ă��邩</returns>
	bool CheckTap(int checkType);
};