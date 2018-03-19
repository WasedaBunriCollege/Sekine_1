/*****************/
/**  島田 竜之介 **/
/*****************/
#include "Header.h"

ClothBreak TitleAnimation::cloth(Vector2(535, 960+110), 50, 5, 150);

/// <summary>
/// ロード終了後からタイトル描画までのアニメーション
/// </summary>
bool TitleAnimation::Draw(void)
{
	//フレームごとの経過の時間取得
	time += Time::deltaTime;

	if (time > 2 && !TimeF)
		TimeF = true;

	//各Imageのロード
	DrawRotaGraph(540, 960, 1.0, 0.0, Images::stage, true);

	DrawRotaGraph3(252, 1582, 90, 250, .5, .5, 0, Images::gas, true, false);
	DrawRotaGraph3(827, 1582, 142, 250, .5, .5, 0, Images::gas, true, true);

	DrawGraph(1080 / 2 - 512, 250, Images::logo, true);

	//アニメーションの終了処理がされていないのなら
	if (!EndF)
	{
		//フラグがTrueなら黒背景をタイトルより手前に描画
		if (DrawB)
			DrawBox(0, 0, 1080, 1920, 0, true);

		//フラグがFalseだったらタイトル画面を表示
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

			//キャラのAlphaが255(最大)未満の場合、Alphaを上昇させる
			if (Alpha < 255)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
				DrawRotaGraph(540, 960, 1.0, 0.0, Images::man[0], true);
				DrawRotaGraph(540, 960 + 110, 1.0, 0.0, Images::Tshirt, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				Alpha += 4;
				time = 0;
			}

			//キャラのAlphaが最大になってから2秒が経過するまでのキャラの動き
			else if (time < 2)
			{
				int rand = GetRand(10);
				DrawRotaGraph(535 + rand, 960, 1.0, 0.0, Images::man[0], true);
				DrawRotaGraph(535 + rand, 960 + 110, 1.0, 0.0, Images::Tshirt, true);

				cloth.Start();
			}

			//2秒が経過し2.5秒経過するまでのキャラとTシャツの動き
			else if (time < 2.5)
			{
				DrawRotaGraph(540, 960, 1.0, 0.0, Images::man[1], true);
				cloth.Draw();
			}

			//2.5秒経過後タイトルを描画
			else
			{
				DrawB = false;
				ManGrap = false;
				cloth.Draw();
			}
		}

		//タップしたらアニメーションの終了し、タイトルを描画する
		if (Input::GetTap(0, Down))
		{
			EndF = true;
			PlaySoundMem(Sounds::title, DX_PLAYTYPE_LOOP);
		}

		cloth.Play();
	}

	return EndF;
}