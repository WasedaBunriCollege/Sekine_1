/**********************/
/**    �֍� ����     **/
/** �����L���O�N���X **/
/**********************/

#pragma once

#include "DxLib.h"

/// <summary>
/// �����L���O
/// </summary>
class Ranking
{
private:

	/// <summary>
	/// �ۑ��t�@�C���̃p�X
	/// </summary>
	static char dataPath[256];

	/// <summary>
	/// �����L���O�̒l
	/// </summary>
	static int sheet[10];

	/// <summary>
	/// �ÓI�N���X�ɂ��邽�߂ɃR���X�g���N�^��private
	/// </summary>
	Ranking();

public:

	/// <summary>
	/// �f�[�^�̓ǂݍ���
	/// </summary>
	static void LoadData(void);

	/// <summary>
	/// �f�[�^�̏�������
	/// </summary>
	static void SaveData(void);

	/// <summary>
	/// �����L���O�̒ǉ�
	/// </summary>
	/// <param name="_sheet">�ǉ�����l</param>
	/// <returns>�ǉ������l�������N�ɓ����Ă��邩</returns>
	static bool AddRank(int _sheet);

	/// <summary>
	/// �f�[�^�̍폜
	/// </summary>
	static void Reset(void);

	/// <summary>
	/// �ۑ��t�@�C���̃p�X
	/// </summary>
	/// <returns>�p�X�̕�����</returns>
	inline static char * GetPath(void)
	{
		return dataPath;
	}
	
	/// <summary>
	/// �l�̎擾
	/// </summary>
	/// <param name="num">�擾����������</param>
	/// <returns>�擾�����l</returns>
	inline static int GetSheets(int num)
	{
		return sheet[num];
	}
};