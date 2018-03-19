/********************/
/**   �֍� ����    **/
/** ���̑��̃N���X **/
/********************/

#include "Other.hpp"

int64_t Time::beforeTime = 0;

int64_t Time::nowTime = 0;

bool Time::needRefresh = false;

double Time::deltaTime = 0.0;

void Time::CallEveryFrame(void)
{
	//Android���N�����Ă���̎��Ԃ��擾
	nowTime = GetNowHiPerformanceCount();

	//�O�t���[������̎��Ԃ��擾
	deltaTime = (double)(nowTime - beforeTime) / 1000000.0;

	//���̎��Ԃ�ۑ�
	beforeTime = nowTime;

	//�X�V���s�v�ȏ�ԂɕύX
	needRefresh = false;

	return;
}

int Time::GetFPS(void)
{
	//1�b�Ԃ̃t���[����
	static int fps = 0;

	//���s���Ă����
	static int frameCount = 0;

	//���Ԃ̌v���p
	static double sum = 0.0;

	//�X�V���s�v�Ȃ�
	if (!needRefresh)
	{
		//�O�񂩂�̌o�ߎ��Ԃ����Z
		sum += deltaTime;

		//���s�񐔂��J�E���g
		frameCount++;

		//1�b�o�߂�����
		if (sum >= 1.0)
		{
			//���s�񐔂�1�b�Ԃ̃t���[�����ɐݒ�
			fps = frameCount;

			//���s�񐔂����Z�b�g
			frameCount = 0;
			//�o�ߎ��Ԃ����Z�b�g
			sum = 0;
		}

		//�X�V���K�v��ԂɕύX
		needRefresh = true;
	}

	//1�b������̃t���[������Ԃ�
	return fps;
}

bool Input::needRefrech[3] = { false,false,false };

bool Input::before[3] = { false,false,false };

bool Input::result[3] = { false,false,false };

bool Input::GetTap(int num, int checkType, Vector2 * position)
{
	//�O�t���[���̓��͏��
	static bool beforeBuf[3][16];

	//���������K�v��
	static bool first = true;

	//���͍��W�̕ۑ��p
	static Vector2 positionBuf;

	//�������Ă��邩
	bool isProcess = false;

	//�Ԃ��l
	bool returnValue = false;

	//�^�b�v��ID
	int ID;

	if (first)
	{
		//�O�t���[���̓��͏�Ԃ�������
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 16; j++)
				beforeBuf[i][j] = false;
		}

		//����ȍ~���������Ȃ��悤�ɂ���
		first = false;
	}

	//�^�b�v���Ă��鐔�������[�v����
	for (int i = 0; i < GetTouchInputNum(); i++)
	{
		//position�Ƀ��������n����Ă�����
		if (position != __null)
		{
			int x, y;

			//�^�b�v���͂��擾
			GetTouchInput(i, &x, &y, &ID);

			//�^�b�v���W���i�[
			positionBuf = Vector2(x, y);
		}
		else
			//�^�b�v���͂��擾
			GetTouchInput(i, __null, __null, &ID);

		//num��ID�������Ȃ烋�[�v�𔲂���
		if (num == ID)
			break;
	}

	//checkType�̍X�V���s�v�Ȃ�
	if (!needRefrech[checkType])
	{
		//�^�b�v���Ă��鐔�������[�v����
		for (int i = 0; i < GetTouchInputNum(); i++)
		{
			//num��ID��������烋�[�v�̐擪�ɖ߂�
			if (num != ID)
				continue;

			//���������s���Ă����ԂɕύX
			isProcess = true;

			//checkType�̒l�ŕ���
			switch (checkType)
			{
			//�^�b�v�����u��
			case Down:

				//�O�t���[����false�Ȃ�
				if (!beforeBuf[Down][num])
				{
					//Down�̍X�V���K�v�ȏ�Ԃɂ���
					needRefrech[Down] = true;
					//���t���[����Down�̌��ʂ�true�ɂ���
					result[Down] = true;
					//�Ԃ�l��true��ݒ�
					returnValue = true;

					//���t���[���̏�Ԃ�ۑ�
					beforeBuf[Down][num] = true;

					//position�Ƀ|�C���^���n����Ă�������͍��W��Ԃ�
					if (position != __null)
						*position = positionBuf;
				}

				break;

			//�^�b�v���Ă����
			case Press:

				//Press�̍X�V���K�v�ȏ�Ԃɂ���
				needRefrech[Press] = true;
				//���t���[����Press�̌��ʂ�true�ɂ���
				result[Press] = true;
				//�Ԃ�l��true��ݒ�
				returnValue = true;

				//���t���[���̏�Ԃ�ۑ�
				beforeBuf[Press][num] = true;

				//position�Ƀ|�C���^���n����Ă�������͍��W��Ԃ�
				if (position != __null)
					*position = positionBuf;

				break;

			//�^�b�v���I������u��
			case Up:

				//���t���[���̏�Ԃ�ۑ�
				beforeBuf[Up][num] = true;

				break;
			}

			break;
		}

		//���������Ȃ���ԂȂ�
		if (!isProcess)
		{
			//checkType��Up�őO�t���[���ɓ��͂���Ă�����
			if (checkType == Up && beforeBuf[Up][num])
			{
				//Up�̍X�V���K�v�ȏ��
				needRefrech[Up] = true;
				//���t���[����Up�̌��ʂ�true�ɂ���
				result[Up] = true;
				//�Ԃ�l��true��ݒ�
				returnValue = true;

				//���t���[���̌��ʂ�ۑ�
				beforeBuf[Up][num] = false;

				//position�Ƀ|�C���^���n����Ă�������͍��W��Ԃ�
				if (position != __null)
					*position = positionBuf;
			}

			//Down��Press�̑O�t���[���̌��ʂ�false�ɐݒ�
			for (int i = 0; i < 2; i++)
				beforeBuf[i][num] = false;
		}
	}
	else
	{
		//���t���[���̌��ʂ�Ԃ�l�ɐݒ�
		returnValue = result[checkType];

		//position�Ƀ|�C���^���n����Ă�������͍��W��Ԃ�
		if (position != __null)
			*position = positionBuf;
	}

	return returnValue;
}

void Input::CallEveryFrame(void)
{
	for (int i = 0; i < 3; i++)
	{
		//�X�V���s�v�ȏ�Ԃɐݒ�
		needRefrech[i] = false;
		//���ʂ�false�ɐݒ�
		result[i] = false;
	}

	return;
}
