/*****************/
/**  ���c ���V�� **/
/*****************/
#include "Header.h"

ClothBreak TitleAnimation::cloth(Vector2(535, 960+110), 50, 5, 150);

/// <summary>
/// ���[�h�I���ォ��^�C�g���`��܂ł̃A�j���[�V����
/// </summary>
bool TitleAnimation::Draw(void)
{
	//�t���[�����Ƃ̌o�߂̎��Ԏ擾
	time += Time::deltaTime;

	if (time > 2 && !TimeF)
		TimeF = true;

	//�eImage�̃��[�h
	DrawRotaGraph(540, 960, 1.0, 0.0, Images::stage, true);

	DrawRotaGraph3(252, 1582, 90, 250, .5, .5, 0, Images::gas, true, false);
	DrawRotaGraph3(827, 1582, 142, 250, .5, .5, 0, Images::gas, true, true);

	DrawGraph(1080 / 2 - 512, 250, Images::logo, true);

	//�A�j���[�V�����̏I������������Ă��Ȃ��̂Ȃ�
	if (!EndF)
	{
		//�t���O��True�Ȃ獕�w�i���^�C�g������O�ɕ`��
		if (DrawB)
			DrawBox(0, 0, 1080, 1920, 0, true);

		//�t���O��False��������^�C�g����ʂ�\��
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
			DrawBox(0, 0, 1080, 1920, 0xFFFFFF, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			Alpha -= 2;
			if (Alpha == 0)
			{
				EndF = true;
				PlaySoundMem(Sounds::title, DX_PLAYTYPE_LOOP);
			}
		}

		if (TimeF&&ManGrap)
		{

			//�L������Alpha��255(�ő�)�����̏ꍇ�AAlpha���㏸������
			if (Alpha < 255)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
				DrawRotaGraph(540, 960, 1.0, 0.0, Images::man[0], true);
				DrawRotaGraph(540, 960 + 110, 1.0, 0.0, Images::Tshirt, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				Alpha += 4;
				time = 0;
			}

			//�L������Alpha���ő�ɂȂ��Ă���2�b���o�߂���܂ł̃L�����̓���
			else if (time < 2)
			{
				int rand = GetRand(10);
				DrawRotaGraph(535 + rand, 960, 1.0, 0.0, Images::man[0], true);
				DrawRotaGraph(535 + rand, 960 + 110, 1.0, 0.0, Images::Tshirt, true);

				cloth.Start();
			}

			//2�b���o�߂�2.5�b�o�߂���܂ł̃L������T�V���c�̓���
			else if (time < 2.5)
			{
				DrawRotaGraph(540, 960, 1.0, 0.0, Images::man[1], true);
				cloth.Draw();
			}

			//2.5�b�o�ߌ�^�C�g����`��
			else
			{
				DrawB = false;
				ManGrap = false;
				cloth.Draw();
			}
		}

		//�^�b�v������A�j���[�V�����̏I�����A�^�C�g����`�悷��
		if (Input::GetTap(0, Down))
		{
			EndF = true;
			PlaySoundMem(Sounds::title, DX_PLAYTYPE_LOOP);
		}

		cloth.Play();
	}

	return EndF;
}