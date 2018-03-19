/**********************/
/**    �֍� ����     **/
/** �����L���O�N���X **/
/**********************/

#include "Ranking.hpp"

char Ranking::dataPath[256];

int Ranking::sheet[10];

void Ranking::LoadData(void)
{
	//�t�@�C���\���̂̃|�C���^
	FILE * fp;

	//�f�[�^�ۑ��p�̃f�B���N�g�����擾
	GetInternalDataPath(dataPath, sizeof dataPath);

	//�t�@�C�������w�肵�ăt�@�C���̃p�X��ݒ�
	strcatDx(dataPath, "/RankingData.dat");

	//�t�@�C����ǂݍ��ݐ�p�ŊJ��
	fp = fopen(dataPath, "r");

	//�t�@�C��������������ǂݏ����ݒ�ŊJ���t�@�C�����쐬
	if (fp == __null)
		fp = fopen(dataPath, "w+");

	for (int i = 0; i < 10; i++)
	{
		//�t�@�C���̏I���ʒu�܂�1�s���ǂݍ���
		if (fscanf(fp, "%d\n", &sheet[i]) == EOF)
			break;
	}

	//�t�@�C�������
	fclose(fp);

	return;
}

void Ranking::SaveData(void)
{
	//�t�@�C���\���̂̃|�C���^
	FILE * fp;

	//�t�@�C�����������ݐ�p�ŊJ��
	fp = fopen(dataPath, "w");

	//�f�[�^����������
	for (int i = 0; i < 10; i++)
		fprintf(fp, "%d\n", sheet[i]);

	//�t�@�C�������
	fclose(fp);

	return;
}

bool Ranking::AddRank(int _sheet)
{
	for (int i = 0; i < 10; i++)
	{
		//�V�����f�[�^��i�Ԗڈȏ�Ȃ�
		if (_sheet >= sheet[i])
		{
			//i�Ԗڈȍ~��1�����炷
			for (int j = 9; j > i; j--)
				sheet[j] = sheet[j - 1];

			//i�ԖڂɐV�����f�[�^��}��
			sheet[i] = _sheet;

			//�����N�C���������Ƃ�Ԃ�
			return true;
		}
	}

	//�����N�C�����Ȃ��������Ƃ�Ԃ�
	return false;
}

void Ranking::Reset(void)
{
	//�l��S�ă��Z�b�g
	for (int i = 0; i < 10; i++)
		sheet[i] = 0;

	//�f�[�^��ۑ�
	SaveData();
}
