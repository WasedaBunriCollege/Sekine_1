/**********************/
/**     �֍� ����    **/
/** �G�t�F�N�g�N���X **/
/**********************/

#include "Effect.hpp"

Smoke::Smoke(Vector2 pos, int particleCount, float angle, float range, int speed, int length, float time) :
	length(length)
{
	Smoke::pos = pos;
	Smoke::particleCount = particleCount;

	//�p�[�e�B�N����SmokeParticle���w��
	particle = new SmokeParticle *[particleCount];

	//SmokeParticle�̃C���X�^���X�𐶐�
	for (int i = 0; i < particleCount; i++)
		particle[i] = new SmokeParticle(pos, angle*PI / 180, range * PI / 180, speed, GetRand(70), time, length);
}

void Smoke::Play(void)
{
	//�~�܂��Ă��鐔�����Z�b�g
	stopCount = 0;

	for (int i = 0; i < particleCount; i++)
	{
		//�p�[�e�B�N���̃T�C�Y�̕ύX�ƈړ�
		particle[i]->ChangeSize();

		//�p�[�e�B�N�����~�܂��Ă��鐔���J�E���g
		if (particle[i]->stop)
			stopCount++;
	}

	//�S�Ẵp�[�e�B�N�����~�܂��Ă�����isStop��true�ɂ���
	isStop = stopCount == particleCount;
}

void Smoke::Draw(void)
{
	//�`�掞�̃u�����h�����Z�ɐݒ�
	SetDrawBlendMode(DX_BLENDMODE_ADD, 95);

	//�p�[�e�B�N����`��
	for (int i = 0; i < particleCount; i++)
		particle[i]->Draw();

	//�`�掞�̃u�����h�ݒ������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}

void ClothBreak::Play(void)
{
	if (isPlay)
	{
		//�p�[�e�B�N�����ړ�
		for (int i = 0; i < particleCount; i++)
			particle[i]->Move();

		//�O�t���[������̎��Ԃ����Z
		time += Time::deltaTime;

		//0.25�b�o�߂��Ă�����
		if (time >= 0.25f)
		{
			//�s�����x�����炷
			alpha -= 8;

			//�s�����x��0�ȉ��Ȃ���s���Ȃ��悤�ɂ���
			isPlay = !alpha <= 0;
		}
	}
}

ClothBreak::ClothBreak(Vector2 pos, int particleCount, float speed, int range)
{
	ClothBreak::particleCount = particleCount;
	ClothBreak::pos = pos;
	
	//�p�[�e�B�N����ClothParticle���w��
	particle = new ClothParticle * [particleCount];

	//ClothParticle�̃C���X�^���X�𐶐�
	for (int i = 0; i < particleCount; i++)
		particle[i] = new ClothParticle(pos, GetRand(speed * 100) / 100.f, (2 * PI / particleCount)*i,range);
}

void ClothBreak::Start(void)
{
	//���s����悤�ɐݒ�
	isPlay = true;
	//�s�����x���ő�ɐݒ�
	alpha = 255;

	//���Ԃ�������
	time = 0;

	//�p�[�e�B�N���̏������J�n
	for (int i = 0; i < particleCount; i++)
		particle[i]->Start();
}

void ClothBreak::Draw(void)
{
	//�`�掞�̃u�����h���A���t�@�u�����h�ɐݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	//�p�[�e�B�N����`��
	for (int i = 0; i < particleCount; i++)
		particle[i]->Draw();

	//�`�掞�̃u�����h�ݒ������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}

LineEffect::LineEffect(Vector2 pos, int particleCount, int range, unsigned int color)
{
	LineEffect::pos = pos;
	LineEffect::particleCount = particleCount;
	LineEffect::range = range;

	//�p�[�e�B�N����LineParticle���w��
	particle = new LineParticle*[particleCount];

	for (int i = 0; i < particleCount; i++)
	{
		//�p�[�e�B�N���̕`��ʒu���v�Z
		Vector2 tmp(range * cos(PI * 2 / particleCount*i), range * sin(PI * 2 / particleCount*i));
		//LineParticle�̃C���X�^���X�𐶐�
		particle[i] = new LineParticle(pos + tmp, pos, 550 - GetRand(100), GetRand(10) - 5, color);
	}
}

void LineEffect::Draw(void)
{
	//�p�[�e�B�N����`��
	for (int i = 0; i < particleCount; i++)
		particle[i]->Draw();
}

void LineEffect::Play(void)
{
	//�p�[�e�B�N���̏��������s
	for (int i = 0; i < particleCount; i++)
		particle[i]->Play();
}

TapEffect::TapEffect(int particleCount, float speed, int range) :
	particleCount(particleCount), speed(speed), range(range)
{
	//�p�[�e�B�N���̍��W���w�肳�ꂽ����������
	particlePos = new Pos[particleCount];
}

void TapEffect::Play(void)
{
	//��̊p�x��ύX���ĉ�]������
	centerAngle += PI / 24;

	if (isPlaying  && !isStopping)
	{
		//���S����̋����𒷂�����
		radius += speed;

		//�p�[�e�B�N�����ړ�
		for (int i = 0; i < particleCount; i++)
		{
			particlePos[i].x += cos(centerAngle+(PI * 2 / particleCount)*i)*radius;
			particlePos[i].y += sin(centerAngle+(PI * 2 / particleCount)*i)*radius;
		}

		//���S����p�[�e�B�N���̋������w�肳�ꂽ�͈͈ȏ㗣�ꂽ�瓮����~�߂�
		isStopping = pos.Distance(particlePos[0].x, particlePos[0].y) >= range;
	}
	else if (isStopping)
	{
		//�s�����x�����炷
		alpha -= 8;

		//�s�����x���}�C�i�X�ɂȂ�����
		if (alpha < 0)
		{
			//���s���Ă��邩�Ǝ~�܂��Ă��邩�̃t���O��false�ɂ���
			isPlaying = false;
			isStopping = false;

			//�G�t�F�N�g���g����悤�ɐݒ�
			canUse = true;

			//�s�����x��0�ɐݒ�
			alpha = 0;

			//���S����̋�����0�ɐݒ�
			radius = 0.0f;
		}
	}
}

void TapEffect::Start(Vector2 pos)
{
	if (!isPlaying && !isStopping)
	{
		//�V�����g���Ȃ��悤�ɐݒ�
		canUse = false;
		//���s����悤�ɐݒ�
		isPlaying = true;

		//�s�����x�𔼕��ɐݒ�
		alpha = 127;

		//�w�肳�ꂽ�ʒu�ɐݒ�
		TapEffect::pos = pos;

		//�p�[�e�B�N�����w�肳�ꂽ�ʒu�ɐݒ�
		for (int i = 0; i < particleCount; i++)
		{
			particlePos[i].x = pos.x;
			particlePos[i].y = pos.y;
		}

		//�^�b�v���������Đ�
		PlaySoundMem(Sounds::tap, DX_PLAYTYPE_BACK);
	}
}

void TapEffect::Draw(void)
{
	//�`�掞�̃u�����h���A���t�@�ɐݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	//�p�[�e�B�N���̕`��
	for (int i = 0; i < particleCount; i++)
		DrawRotaGraph(particlePos[i].x, particlePos[i].y, .5, 0.0, Images::circle, true);

	//�`�掞�̃u�����h�ݒ������
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
}
