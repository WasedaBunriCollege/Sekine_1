/****************/
/**  �֍� ���� **/
/**   ���C��   **/
/****************/

#include "MuscleBreak.hpp"

/*-----     �O���[�o���ϐ�,�\���̂̒�`     -----*/

//�摜�Ɏg�p����n���h���̒�`
int Images::logo;
int Images::man[3];
int Images::Tshirt;
int Images::effect1;
int Images::smoke;
int Images::circle;
int Images::fragment[5];
int Images::gas;
int Images::tapCircle;
int Images::stage;
int Images::ranking;
int Images::guests[2];
int Images::description;
int Images::scoreBord;

//SE�Ɏg�p����n���h���̒�`
int Sounds::big;
int Sounds::ah;
int Sounds::judge[6];
int Sounds::fun[2];
int Sounds::tap;
int Sounds::breakS;
int Sounds::countDown;
int Sounds::start;
int Sounds::finish;

//BGM�Ɏg�p����n���h���̒�`

int Sounds::title;
int Sounds::description;
int Sounds::game;
int Sounds::result;
int Sounds::ranking;

unsigned short brokeCount = 0;

TapEffect tapEffect[20];

int bigFont;

/*-----     ���[�U�֐��̃v���g�^�C�v�錾     -----*/

/// <summary>
/// �Q�[���̏�����
/// </summary>
void MuscleBreakInit(void);
/// <summary>
/// �Q�[���̐ݒ�
/// </summary>
void MuscleBreakSetup(void);

/// <summary>
/// ���C���֐�
/// </summary>
int android_main(void)
{
	//�Q�[����������
	MuscleBreakInit();

	while (!ProcessMessage())
	{
		//���݂̃V�[���ɂ���ĕ���
		switch (Scene::GetNowScene())
		{
		case SceneList::Load:

			Scene::Load();

			break;

		case SceneList::Title:

			Scene::Title();

			break;

		case SceneList::Description:

			Scene::Description();

			break;

		case SceneList::Game:

			Scene::Game();

			break;

		case SceneList::Result:

			Scene::Result();

			break;

		case SceneList::Ranking:

			Scene::Ranking();

			break;
		}
	}

	//Dx���C�u�������I��
	DxLib_End();

	return 0;
}

void MuscleBreakInit(void)
{
	//��ʃT�C�Y��ݒ�
	SetGraphMode(1080, 1920, 32);

	//Dx���C�u������������
	if (DxLib_Init() == -1)
		exit(EXIT_FAILURE);

	//�`��ʒu�𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[����ݒ肷��
	MuscleBreakSetup();
}

void MuscleBreakSetup(void)
{
	//��{�̃t�H���g�T�C�Y��64�ɐݒ�
	SetFontSize(64);

	//�ŏ��Ɏ��s����V�[����ݒ�
	Scene::NextScene(SceneList::Load);

	//TapEffect�̃C���X�^���X�𐶐�
	for (int i = 0; i < 20; i++)
		tapEffect[i] = TapEffect(12, .5f, 100);

	//�傫���t�H���g��ݒ�
	bigFont = CreateFontToHandle(NULL, 256, -1);
}

bool Loop(void)
{
	//���Ԃ��g���Ƃ��ɕK�v�Ȋ֐�
	Time::CallEveryFrame();

	//���͂��g���Ƃ��ɕK�v�Ȋ֐�
	Input::CallEveryFrame();

	//�A�v���̃��b�Z�[�W������
	return !ProcessMessage();
}

void Inactive(void * isPause)
{
	//�|�[�Y��ʂ�\��������
	*(bool *)isPause = true;
}

void TapEffectPlay(void)
{
	//�^�b�v�������W���i�[����ϐ�
	Vector2 tapPoint;

	//�^�b�v���Ă��鐔�������[�v����
	for (int i = 0; i < GetTouchInputNum(); i++)
	{
		//�^�b�v�����u�Ԃ��`�F�b�N����
		if (Input::GetTap(i, Down, &tapPoint))
		{
			for (int j = 0; j < 20; j++)
			{
				//�g�����ԂɂȂ��Ă���^�b�v�G�t�F�N�g���Đ�
				if (tapEffect[j].canUse)
				{
					tapEffect[j].Start(tapPoint);

					break;
				}
			}
		}
	}

	//�^�b�v�G�t�F�N�g�����s
	for (int i = 0; i < 20; i++)
		tapEffect[i].Play();
}