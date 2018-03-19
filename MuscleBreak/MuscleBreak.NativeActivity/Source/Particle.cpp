/************************/
/**      �֍� ����     **/
/** �p�[�e�B�N���N���X **/
/************************/

#include "Particle.hpp"

void Particle::Move(void)
{
	//�p�x�������_���Ŏ擾
	float theta = GetRand(2 * PI * 100) / 100.f;
	//���S����̋����������_���Ŏ擾
	int r = -range + GetRand(range * 2);

	//���S����̋����Ɗp�x������W���v�Z
	pos = Vector2(r*cos(theta), r*sin(theta)) + originalPos;

	//�T�C�Y���ς�鑬�x�������_���Ŏ擾
	speed = (float)(GetRand(100) / 2000.0f) + .075f;
}

void Particle::ChangeSize(void)
{
	//���̎��Ԃ���O�t���[������̌o�ߎ��Ԃ����Z
	time -= Time::deltaTime;

	//��莞�Ԍo�߂��Ă����珈�����~�߂�
	stop = time <= 0;

	//�T�C�Y�̕ύX
	if (!reverse)
		size += speed;
	else
		size -= speed;

	//���T�C�Y�ȏ�ɂȂ��Ă��邩
	if (!reverse && size >= 1.f)
	{
		//�T�C�Y��1�{�ɌŒ�
		size = 1.f;
		//�T�C�Y�������������鏈���Ɉڍs
		reverse = true;
	}
	//�T�C�Y��0�ȉ��ɂȂ��Ă��邩
	else if (reverse && size <= 0.0f)
	{
		//�T�C�Y��0�ɌŒ�
		size = 0.0f;
		//�T�C�Y��傫�������鏈���Ɉڍs
		reverse = false;

		//�������~�܂��Ă��Ȃ���Ε`��ʒu��ύX
		if (!stop)
			Move();
	}
}

Particle::Particle(Vector2 originalPos, int range, float time) :
	originalPos(originalPos), range(range), time(time), size(0)
{
	//�p�x�������_���Ŏ擾
	float theta = GetRand(2 * PI * 100) / 100.f;
	//���S����̋����������_���Ŏ擾
	int r = -range + GetRand(range * 2);

	//���S����̋����Ɗp�x������W���v�Z
	pos = Vector2(r*cos(theta), r*sin(theta)) + originalPos;

	//�T�C�Y���ς�鑬�x�������_���Ŏ擾
	speed = (float)(GetRand(100) / 2000.0f) + .075f;
}

void Particle::Draw(void)
{
	//�������~�܂��Ă��Ȃ���΃p�[�e�B�N����`��
	if (!stop)
		DrawRotaGraph2(pos.x, pos.y, 64, 64, size, 0.0f, Images::effect1, true);
}

void SmokeParticle::Move(void)
{
	//�p�[�e�B�N���̈ړ�
	pos.x += speed*cos(angle);
	pos.y += speed*sin(angle);

	//�w�肳�ꂽ�����ȏ㗣�ꂽ�烊�Z�b�g
	if (Distance() >= length)
		Reset();
}

SmokeParticle::SmokeParticle(Vector2 originalPos, float angle, float range, float speed, int delayCount, float time, int length) :
	centerAngle(angle), range(range), rot(0.0f), rotSpeed(GetRand(PI / 16 * 100) / 100.0f), delayCount(delayCount), time(time), length(length)
{
	SmokeParticle::originalPos = originalPos;
	SmokeParticle::speed = speed;

	pos = originalPos;

	//�i�ޕ������v�Z
	SmokeParticle::angle = centerAngle - range + GetRand(range * 2 * 100) / 100.0f;

	//�T�C�Y��0�ɐݒ�
	size = 0;
}

void SmokeParticle::Draw(void)
{
	//�w�肳�ꂽ�t���[�����o�߂��Ă�����`��
	if (delayCount <= 0 && !stop)
		DrawRotaGraph(pos.x, pos.y, size, rot, Images::smoke, true);
}

void SmokeParticle::ChangeSize(void)
{
	//���̎��Ԃ���O�t���[������̌o�ߎ��Ԃ����Z
	time -= Time::deltaTime;

	//�w�肳�ꂽ�t���[�����o�߂��Ă�����
	if (--delayCount <= 0)
	{
		//��]������
		rot += rotSpeed;
		//�T�C�Y��傫��������
		size += .01f;

		//�~�܂��Ă��Ȃ���Έړ�
		if (!stop)
			Move();
	}
}

float SmokeParticle::Distance(void)
{
	//��̍��W����̋�����Ԃ�
	return pos.Distance(originalPos);
}

void SmokeParticle::Reset(void)
{
	//�T�C�Y��0�ɐݒ�
	size = 0;

	//��]���x�������_���Ŏ擾
	rotSpeed = GetRand(PI / 16 * 100) / 100.0f;

	//�i�ޕ������Čv�Z
	centerAngle = centerAngle - range + GetRand(range * 2 * 100) / 100.0f;

	//���W�����̈ʒu�ɕύX
	pos = originalPos;

	//�w�肳�ꂽ���Ԍo�߂��Ă�����~�߂�
	stop = time <= 0;
}

void ClothParticle::Move(void)
{
	//�ړ�
	pos += Vector2(speed*cos(angle), speed*sin(angle));

	//�d�͂��v�Z
	gravity += g*Time::deltaTime;

	//�d�͂����Z
	pos.y += gravity;
}
void ClothParticle::Start(void)
{
	//���W�𒆐S���W���烉���_���̋����ɐݒ�
	pos = originalPos + Vector2(GetRand(range)*cos(angle), GetRand(range)*sin(angle));

	//�d�͂����Z�b�g
	gravity = 0;

	//�p�x�������_���Ŏ擾
	rot = GetRand(PI * 2 * 100) / 100.f;
}

ClothParticle::ClothParticle(Vector2 originalPos, float speed, float angle, int range)
{
	ClothParticle::speed = speed;
	ClothParticle::angle = angle;
	ClothParticle::originalPos = originalPos;
	ClothParticle::range = range;

	//�`�悷��摜�������_���Őݒ�
	imageNum = GetRand(4);
}

void ClothParticle::Draw(void)
{
	//�`��
	DrawRotaGraph(pos.x, pos.y, 1.f, rot, Images::fragment[imageNum], true);
}

LineParticle::LineParticle(Vector2 pos, Vector2 originalPos, float length, float speed, unsigned int color) :
	length(length), color(color)
{
	LineParticle::pos = pos;
	LineParticle::originalPos = originalPos;
	LineParticle::speed = speed;

	lengthTmp = length;

	//�p�x���v�Z
	angle = pos.Angle(originalPos);
}

void LineParticle::Draw(void)
{
	//�`��
	DrawTriangleAA(pos.x + 16 * cos(angle + PI / 2), pos.y + 16 * sin(angle + PI / 2), pos.x - 16 * cos(angle + PI / 2), pos.y - 16 * sin(angle + PI / 2), originalPos.x - length * cos(angle), originalPos.y - length * sin(angle), color, true);
}

void LineParticle::Play(void)
{
	//���̑��x�Ő��̒�����ύX
	length += speed;

	//���̋����ȏ㗣�ꂽ��
	if (length > lengthTmp*1.5 || length < lengthTmp*0.5)
	{
		//�i�ޕ����𔽓]
		speed *= -1;
		//�T�C�h���̒�����ύX
		length += speed;
	}
}
