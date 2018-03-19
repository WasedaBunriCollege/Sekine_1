/*****************/
/**  ���c ���V�� **/
/*****************/
#pragma once
#include "DxLib.h"
#include "MuscleBreak.hpp"

//extern int JustTap(void);
/// <summary>
/// �^�C�~���O�̔���
/// </summary>
class JustTap
{

public:
	JustTap(Vector2 Pos);

	void Play(void);
	void Draw(void);

	//inline��Class���ŏ������ł���
	/// <summary>
	/// �J�n
	/// </summary>
	inline void Start(void)
	{
		StartTap = true;
		Playing = true;
	}
	/// <summary>
	/// ���s��
	/// </summary>
	inline bool IsPlaying(void)
	{
		return Playing;
	}

	/// <summary>
	/// <para>�^�b�v����</para>
	/// <para>2:�听��</para>
	/// <para>1:����</para>
	/// <para>0:���s</para>
	/// </summary>
	int judge = 0;

private:
	/// <summary>
	/// Tap�����O�̑傫��
	/// </summary>
	float RingScale = 300;

	/// <summary>
	/// �����O���o����������
	/// </summary>
	float RingCount = 0;

	/// <summary>
	/// 
	/// </summary>
	bool StartTap = false;
	
	/// <summary>
	/// �}�E�X�̑���擾
	/// </summary>
	bool Mouse = true;
	
	/// <summary>
	/// �傫���̕ω��̉s�؂�ւ�
	/// </summary>
	bool ScaleChange = false;
	
	/// <summary>
	/// ���s���𔻒�
	/// </summary>
	bool Playing = false;


	Vector2 Postion;

};

class ClothBreak;

class TitleAnimation
{

public:
	bool Draw(void);


private:
	float Alpha=0;
	float time = 0;
	

	bool ManGrap = true;
	bool DrawB = true; 

	bool TimeF = false;
	bool EndF = false;

	static ClothBreak cloth;
};