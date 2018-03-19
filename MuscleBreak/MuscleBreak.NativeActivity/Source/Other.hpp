/********************/
/**   �֍� ����    **/
/** ���̑��̃N���X **/
/********************/

#pragma once

#include"DxLib.h"

#include "MuscleBreakMath.hpp"

/// <summary>
/// ���͔��������ۂ̃^�C�~���O�̗�
/// </summary>
enum CheckType
{
	Down, Press, Up
};

/// <summary>
/// ���Ԏ擾�N���X
/// </summary>
class Time
{
private:

	/// <summary>
	/// ���̎���
	/// </summary>
	static int64_t beforeTime;

	/// <summary>
	/// ���̎���
	/// </summary>
	static int64_t nowTime;

	/// <summary>
	/// �X�V���K�v��
	/// </summary>
	static bool needRefresh;

	/// <summary>
	/// �ÓI�N���X�ɂ��邽�߂ɃR���X�g���N�^��private
	/// </summary>
	Time();

public:

	/// <summary>
	/// �O�t���[������̌o�ߎ���
	/// </summary>
	static double deltaTime;

	/// <summary>
	/// ���t���[���Ă΂Ȃ���΂Ȃ�Ȃ����\�b�h
	/// Loop�֐����Ŏg�p
	/// </summary>
	static void CallEveryFrame(void);

	/// <summary>
	/// 1�b������̃t���[�������擾
	/// </summary>
	/// <returns>1�b������̃t���[����</returns>
	static int GetFPS(void);
};

/// <summary>
/// ���͏��N���X
/// </summary>
class Input
{
private:

	/// <summary>
	/// Down,Press,Up���ꂼ��X�V���K�v��
	/// </summary>
	static bool needRefrech[3];

	/// <summary>
	/// 1�t���[���O�̏��
	/// </summary>
	static bool before[3];

	/// <summary>
	/// �t���[�����̌��ʕۑ��p
	/// </summary>
	static bool result[3];

	/// <summary>
	/// �ÓI�N���X�ɂ��邽�߂ɃR���X�g���N�^��private
	/// </summary>
	Input();

public:

	/// <summary>
	/// �^�b�v�����擾
	/// </summary>
	/// <param name="num">���Ԗڂ̃^�b�v���擾���邩</param>
	/// <param name="checkType">������s���^�C�~���O�̎w��</param>
	/// <param name="position">�^�b�v�������W���i�[����|�C���^</param>
	/// <returns>checkType�Ŏw�肵���^�C�~���O�œ��͂���Ă��邩</returns>
	static bool GetTap(int num, int checkType, Vector2 * position = __null);

	/// <summary>
	/// ���t���[���Ă΂Ȃ���΂Ȃ�Ȃ����\�b�h
	/// Loop�֐����Ŏg�p
	/// </summary>
	static void CallEveryFrame(void);

};