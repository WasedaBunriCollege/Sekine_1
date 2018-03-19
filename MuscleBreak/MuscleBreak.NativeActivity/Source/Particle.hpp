/************************/
/**      �֍� ����     **/
/** �p�[�e�B�N���N���X **/
/************************/

#pragma once

#include "MuscleBreak.hpp"

/// <summary>
/// �p�[�e�B�N��
/// </summary>
class Particle
{
private:

protected:

	/// <summary>
	/// ��ƂȂ���W
	/// </summary>
	Vector2 originalPos;

	/// <summary>
	/// �͈�
	/// </summary>
	int range;

	/// <summary>
	/// �傫��
	/// </summary>
	float size;
	/// <summary>
	/// �T�C�Y���ς�鑬�x
	/// </summary>
	float speed;
	/// <summary>
	/// ���W�����߂邽�߂̊p�x
	/// </summary>
	float angle;
	/// <summary>
	/// ����
	/// </summary>
	float time;

	/// <summary>
	/// ���������邩
	/// </summary>
	bool reverse = false;
	/// <summary>
	/// �~�܂��Ă��邩
	/// </summary>
	bool stop = true;

	/// <summary>
	/// �ʒu��ς���
	/// </summary>
	virtual void Move(void);

public:

	/// <summary>
	/// ���W
	/// </summary>
	Vector2 pos;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Particle()
	{
	}
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="originalPos">��ƂȂ���W</param>
	/// <param name="range">�͈�</param>
	/// <param name="time">�`�掞��</param>
	Particle(Vector2 originalPos, int range, float time);

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw(void);

	/// <summary>
	/// �T�C�Y��ύX
	/// </summary>
	virtual void ChangeSize(void);
};

/// <summary>
/// ���p�[�e�B�N��
/// </summary>
class SmokeParticle : public Particle
{
private:

	/// <summary>
	/// ��ƂȂ�p�x
	/// </summary>
	float centerAngle;
	/// <summary>
	/// �`�悷��p�x
	/// </summary>
	float rot;
	/// <summary>
	/// ��]���x
	/// </summary>
	float rotSpeed;

	/// <summary>
	/// �͈�
	/// </summary>
	float range;

	/// <summary>
	/// ����
	/// </summary>
	float time;

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move(void);

	/// <summary>
	/// �`��J�n��x�点��t���[����
	/// </summary>
	int delayCount;
	/// <summary>
	/// ��̍��W����̍ő勗��
	/// </summary>
	int length;

	/// <summary>
	/// ��̍��W����̋������擾
	/// </summary>
	/// <returns>��̍��W����̋���</returns>
	float Distance(void);

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset(void);

public:

	/// <summary>
	/// �~�܂��Ă��邩
	/// </summary>
	bool stop = false;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="originalPos">��ƂȂ���W</param>
	/// <param name="angle">��ƂȂ�p�x</param>
	/// <param name="range">�p�x�ł̕\���͈�</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="delayCount">�`��J�n��x�点��t���[����</param>
	/// <param name="time">�`�悷�鎞��</param>
	/// <param name="length">��̍��W����̍ő勗��</param>
	SmokeParticle(Vector2 originalPos, float angle, float range, float speed, int delayCount, float time, int length);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(void);

	/// <summary>
	/// �T�C�Y�̕ύX�ƈړ�
	/// </summary>
	void ChangeSize(void);
};

/// <summary>
/// �z�Ђ̃p�[�e�B�N��
/// </summary>
class ClothParticle : public Particle
{
private:

	/// <summary>
	/// �d�͉����x
	/// </summary>
	static const float g = 9.80665f;

	/// <summary>
	/// �`�悷��摜�̔ԍ�
	/// </summary>
	int imageNum;

	/// <summary>
	/// �p�[�e�B�N���������鑬�x
	/// </summary>
	float gravity;
	/// <summary>
	/// �`�悷��p�x
	/// </summary>
	float rot;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="originalPos">��ƂȂ���W</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="angle">���W�����߂邽�߂̊p�x</param>
	/// <param name="range">�͈�</param>
	ClothParticle(Vector2 originalPos, float speed, float angle, int range);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(void);

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move(void);

	/// <summary>
	/// �����J�n
	/// </summary>
	void Start(void);
};

/// <summary>
/// �W�����̃p�[�e�B�N��
/// </summary>
class LineParticle : public Particle
{
private:

	/// <summary>
	/// ��̍��W����̋���
	/// </summary>
	float length;

	/// <summary>
	/// ��̍��W����̊�̋���
	/// </summary>
	float lengthTmp;

	/// <summary>
	/// �F
	/// </summary>
	unsigned int color;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="originalPos">��ƂȂ���W</param>
	/// <param name="length">����W����̋���</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="color">�F</param>
	LineParticle(Vector2 pos, Vector2 originalPos, float length, float speed, unsigned int color);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(void);

	/// <summary>
	/// ����
	/// </summary>
	void Play(void);
};