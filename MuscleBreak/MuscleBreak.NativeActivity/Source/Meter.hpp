/********************/
/**    �֍� ����   **/
/** ���[�^�[�N���X **/
/********************/

#pragma once

#include "DxLib.h"

#include "MuscleBreakMath.hpp"
#include "Other.hpp"

/// <summary>
/// ���[�^�[�N���X
/// </summary>
class Meter
{
private:

	/// <summary>
	/// �T�C�Y
	/// </summary>
	Vector2 size;

	/// <summary>
	/// �h��Ԃ���Ă��钷��
	/// </summary>
	float fillLength;

	/// <summary>
	/// �ő�l
	/// </summary>
	int maxValue;

	/// <summary>
	/// ���݂̒l
	/// </summary>
	float value;

public:

	/// <summary>
	/// ������W
	/// </summary>
	Vector2 position;

	/// <summary>
	/// �l���ő�l�ɒB���Ă��邩
	/// </summary>
	bool isMax = false;
	/// <summary>
	/// �l���ŏ��l��
	/// </summary>
	bool isMin = false;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Meter(){ }

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="size">�T�C�Y</param>
	/// <param name="initValue">�����l</param>
	/// <param name="maxValue">�ő�l</param>
	Meter(Vector2 position, Vector2 size, int initValue, int maxValue);

	/// <summary>
	/// �l�𑝂₷
	/// </summary>
	/// <param name="add">���₷�l</param>
	void AddValue(int add);

	/// <summary>
	/// �l��ݒ肷��
	/// </summary>
	/// <param name="val">�ݒ肷��l</param>
	void SetValue(int val);

	/// <summary>
	/// �l���擾����
	/// </summary>
	inline int GetValue(void)
	{
		return (int)value;
	}

	/// <summary>
	/// ���[�^�[��`�悷��
	/// </summary>
	void Draw(void);
};