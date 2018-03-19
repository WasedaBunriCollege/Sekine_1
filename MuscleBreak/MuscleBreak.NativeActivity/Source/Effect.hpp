/**********************/
/**     �֍� ����    **/
/** �G�t�F�N�g�N���X **/
/**********************/

#pragma once

#include "DxLib.h"

#include "MuscleBreakMath.hpp"
#include "Particle.hpp"

/// <summary>
/// �L���L������G�t�F�N�g
/// </summary>
template <class T>
class Effect
{
private:

protected:

	/// <summary>
	/// ���W
	/// </summary>
	Vector2 pos;

	/// <summary>
	/// �p�[�e�B�N��
	/// </summary>
	T ** particle;

	/// <summary>
	/// �͈�
	/// </summary>
	int range;

	/// <summary>
	/// �p�[�e�B�N���̐�
	/// </summary>
	int particleCount;

	/// <summary>
	/// ����
	/// </summary>
	float time;

public:

	/// <summary>
	/// �f�t�H���g�R���X�g���N�^
	/// </summary>
	Effect(){ }
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�`�悷����W</param>
	/// <param name="particleCount">�p�[�e�B�N���̐�</param>
	/// <param name="range">�`��͈�(���a)</param>
	/// <param name="time">�G�t�F�N�g��\�����鎞��</param>
	Effect(Vector2 pos, int particleCount, int range, float time) :
		pos(pos), particleCount(particleCount), range(range), time(time)
	{
		//�w�肳�ꂽ�p�[�e�B�N���N���X�𐶐�
		particle = new T *[particleCount];

		for (int i = 0; i < particleCount; i++)
		{
			particle[i] = new T(pos, range, time);
		}
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Effect()
	{
		//�������̊J��
		for (int i = 0; i < particleCount; i++)
			delete particle[i];

		delete[] particle;
	}

	/// <summary>
	/// �G�t�F�N�g�̎��s
	/// </summary>
	inline virtual void Play(void)
	{
		//�p�[�e�B�N���̃T�C�Y��ύX
		for (int i = 0; i < particleCount; i++)
			particle[i]->ChangeSize();
	}

	/// <summary>
	/// �`��
	/// </summary>
	inline virtual void Draw(void)
	{
		//�p�[�e�B�N����`��
		for (int i = 0; i < particleCount; i++)
			particle[i]->Draw();
	}

	/// <summary>
	/// �p�[�e�B�N���̐��̕ύX
	/// </summary>
	/// <param name="particleCount">�p�[�e�B�N���̐�</param>
	inline void ChangeParticleCount(int particleCount)
	{
		//�p�[�e�B�N���̃����������
		for (int i = 0; i < Effect::particleCount; i++)
			delete particle[i];

		delete[] particle;

		//�V�����p�[�e�B�N���̐��ɕύX
		Effect::particleCount = particleCount;

		//�p�[�e�B�N�����w�肳�ꂽ���Ő���
		particle = new T*[particleCount];
	}

	/// <summary>
	/// ������J�n
	/// </summary>
	inline void Start(void)
	{
		//�p�[�e�B�N���̃C���X�^���X�𐶐�
		for (int i = 0; i < particleCount; i++)
			particle[i] = new T(pos, range, time);
	}
};

class SmokeParticle;

/// <summary>
/// ���G�t�F�N�g
/// </summary>
class Smoke : public Effect<SmokeParticle>
{
private:

	/// <summary>
	/// ����
	/// </summary>
	int length;
	/// <summary>
	/// �~�܂��Ă���p�[�e�B�N���̐�
	/// </summary>
	int stopCount = 0;

public:

	/// <summary>
	/// �G�t�F�N�g���~�܂��Ă��邩
	/// </summary>
	bool isStop = false;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�`�悷����W</param>
	/// <param name="particleCount">�p�[�e�B�N���̐�</param>
	/// <param name="angle">�����i�ފp�x</param>
	/// <param name="range">�����i�ޕ����͈̔�</param>
	/// <param name="speed">�����i�ޑ��x</param>
	/// <param name="length">�����i�ޒ���</param>
	/// <param name="time">�G�t�F�N�g��\�����鎞��</param>
	Smoke(Vector2 pos, int particleCount, float angle, float range, int speed, int length, float time);

	/// <summary>
	/// ���s
	/// </summary>
	void Play(void);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(void);
};

class ClothParticle;

/// <summary>
/// �z�Ђ̃G�t�F�N�g
/// </summary>
class ClothBreak : public Effect<ClothParticle>
{
private:

	/// <summary>
	/// ���s���Ă��邩
	/// </summary>
	bool isPlay = false;

	/// <summary>
	/// �s�����x
	/// </summary>
	int alpha = 0;

	/// <summary>
	/// ����
	/// </summary>
	float time;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�`�悷����W</param>
	/// <param name="particleCount">�p�[�e�B�N���̐�</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="range">�͈�</param>
	ClothBreak(Vector2 pos, int particleCount, float speed, int range);

	/// <summary>
	/// ���s
	/// </summary>
	void Play(void);

	/// <summary>
	/// �J�n
	/// </summary>
	void Start(void);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(void);
};

class LineParticle;

/// <summary>
/// �W�����̃G�t�F�N�g
/// </summary>
class LineEffect : public Effect<LineParticle>
{
private:

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�`�悷����W</param>
	/// <param name="particleCount">�p�[�e�B�N���̐�</param>
	/// <param name="range">�`��͈�</param>
	/// <param name="color">�W�����̐F</param>
	LineEffect(Vector2 pos, int particleCount, int range, unsigned int color = 0xffffff);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(void);

	/// <summary>
	/// ���s
	/// </summary>
	void Play(void);
};

/// <summary>
/// �^�b�v���̃G�t�F�N�g
/// </summary>
class TapEffect
{
private:

	/// <summary>
	/// ���W�p�̍\����
	/// </summary>
	struct Pos
	{
		float x, y;
	};

	/// <summary>
	/// ���W
	/// </summary>
	Vector2 pos;
	/// <summary>
	/// �p�[�e�B�N���̍��W
	/// </summary>
	Pos * particlePos;

	/// <summary>
	/// �p�[�e�B�N���̐�
	/// </summary>
	int particleCount;
	/// <summary>
	/// �\���͈�
	/// </summary>
	int range;

	/// <summary>
	/// �s�����x
	/// </summary>
	int alpha = 0;
	/// <summary>
	/// ���S����̋���
	/// </summary>
	float radius = 0;

	/// <summary>
	/// ��̊p�x
	/// </summary>
	float centerAngle = 0.f;

	/// <summary>
	/// �ړ����x
	/// </summary>
	float speed;

	/// <summary>
	/// ���s���Ă��邩
	/// </summary>
	bool isPlaying = false;
	/// <summary>
	/// �������~�܂��Ă��邩
	/// </summary>
	bool isStopping = false;

public:

	/// <summary>
	/// �������I�����Ă��Ďg�����Ԃ�
	/// </summary>
	bool canUse = true;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TapEffect() { }
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="particleCount">�p�[�e�B�N���̐�</param>
	/// <param name="speed">���x</param>
	/// <param name="range">�͈�</param>
	TapEffect(int particleCount, float speed, int range);

	/// <summary>
	/// ���s
	/// </summary>
	void Play(void);

	/// <summary>
	/// �J�n
	/// </summary>
	/// <param name="pos">�G�t�F�N�g�̒��S���W</param>
	void Start(Vector2 pos);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(void);
};