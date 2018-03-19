/******************/
/**   関根 明良  **/
/** シーンクラス **/
/******************/

#include "Scene.hpp"

int Scene::nowScene = SceneList::Load;
int Scene::nextScene = -1;
int Scene::beforeScene = -1;
int Scene::alpha = 0;

bool Scene::isFading = false;

void Scene::Load(void)
{
	//表示するプレイヤーの番号
	int manNum = 0;
	//プレイヤーの表示を変更する時間
	float time = 0;

	//描画する文字列のカウンタ
	int dotCount = 0;
	//フレーム数のカウンタ
	int frameCount = 0;

	//読み込みをする数
	int loadMax;

	//背景色を変更
	SetBackgroundColor(10, 10, 10);

/*-----     画像ファイルの読み込み     -----*/

	//読み込み時に描画する画像の為先に読み込む
	for (int i = 0; i < 3; i++)
	{
		//読み込むファイル名
		char fileName[256];

		//ループの回数を使用してファイル名を取得
		sprintfDx(fileName, "./Images/body_rf%02d.png", i + 1);

		//画像を読み込む
		Images::man[i] = LoadGraph(fileName);
	}

	//非同期読み込みに設定
	SetUseASyncLoadFlag(true);

	Images::logo = LoadGraph("./Images/logo.png");
	Images::Tshirt = LoadGraph("./Images/Tshirt.png");
	Images::effect1 = LoadGraph("./Images/eff_glitter1.png");
	Images::smoke = LoadGraph("./Images/smoke.png");
	Images::circle = LoadGraph("./Images/eff_par2.png");
	Images::gas = LoadGraph("./Images/gas.png");
	Images::tapCircle = LoadGraph("./Images/TapCircle.png");
	Images::stage = LoadGraph("./Images/stage.png");
	Images::ranking = LoadGraph("./Images/Ranking.png");
	Images::guests[0] = LoadGraph("./Images/kankyaku01.png");
	Images::guests[1] = LoadGraph("./Images/kankyaku02.png");
	Images::description = LoadGraph("./Images/Description.png");
	Images::scoreBord = LoadGraph("./Images/Score.png");

	LoadDivGraph("./Images/ClothFragment.png", 5, 5, 1, 64, 64, Images::fragment);

/*-----     音声ファイルの読み込み     -----*/

	Sounds::big = LoadSoundMem(".\\Sounds\\Big.ogg");
	Sounds::ah = LoadSoundMem(".\\Sounds\\Ah.ogg");
	Sounds::judge[0] = LoadSoundMem(".\\Sounds\\Oh_1.ogg");
	Sounds::judge[1] = LoadSoundMem(".\\Sounds\\Oh_2.ogg");
	Sounds::judge[2] = LoadSoundMem(".\\Sounds\\Yes_1.ogg");
	Sounds::judge[3] = LoadSoundMem(".\\Sounds\\Yes_1.ogg");
	Sounds::judge[4] = LoadSoundMem(".\\Sounds\\Great_1.ogg");
	Sounds::judge[5] = LoadSoundMem(".\\Sounds\\Great_1.ogg");
	Sounds::fun[0] = LoadSoundMem(".\\Sounds\\Fun_1.ogg");
	Sounds::fun[1] = LoadSoundMem(".\\Sounds\\Fun_1.ogg");
	Sounds::tap = LoadSoundMem(".\\Sounds\\Tap.ogg");
	Sounds::breakS = LoadSoundMem(".\\Sounds\\break.ogg");
	Sounds::countDown = LoadSoundMem(".\\Sounds\\CountDown.ogg");
	Sounds::start = LoadSoundMem(".\\Sounds\\Start.ogg");
	Sounds::finish = LoadSoundMem(".\\Sounds\\Finish.ogg");

	Sounds::title = LoadSoundMem(".\\Sounds\\Title.ogg");
	Sounds::description = LoadSoundMem(".\\Sounds\\Description.ogg");
	Sounds::game = LoadSoundMem(".\\Sounds\\GameBgm.ogg");
	Sounds::result = LoadSoundMem(".\\Sounds\\Result.ogg");
	Sounds::ranking = LoadSoundMem(".\\Sounds\\Ranking.ogg");

	//ランキングの読み込み
	Ranking::LoadData();

	//同期読み込みに設定
	SetUseASyncLoadFlag(false);

	//読み込む数を取得
	loadMax = GetASyncLoadNum();

	//読み込みが終わるまでループ
	while (Loop() && GetASyncLoadNum() > 0)
	{
		//読み込んでる割合を取得
		float boxRight = (float)GetASyncLoadNum() / (float)loadMax;

		//タップ時のエフェクトの処理
		TapEffectPlay();

		//フレーム数をカウント
		frameCount++;

		//30フレーム以上経過していたら
		if(frameCount > 30)
		{
			//文字列の'.'を追加
			dotCount++;

			//'.'の数が3個を超えたら0個に戻す
			if (dotCount > 3)
				dotCount = 0;

			//フレーム数をリセット
			frameCount = 0;
		}

		//前フレームからの時間を加算
		time += Time::deltaTime;

		//0.25秒以上経過していたら
		if (time >= .25f)
		{
			//時間の計測をリセット
			time = 0.0f;

			//プレイヤーの番号が0なら2に変更
			if (manNum == 0)
				manNum = 2;
			//0以外なら0に変更
			else
				manNum = 0;
		}

		//描画している内容を削除
		ClearDrawScreen();

		//タップ時のエフェクトを描画
		for (int i = 0; i < 20; i++)
			tapEffect[i].Draw();

		//プレイヤーを描画
		DrawRotaGraph(1080 / 2, 1920 / 2 - 128, 0.5, 0.0f, Images::man[manNum], true);

		//文字列の描画
		DrawFormatString(1080 / 2 - GetDrawFormatStringWidth("Now Loading...") / 2, 1920 / 2 + 256, 0xffffff, "Now Loading");

		//文字列の最後に'.'を描画
		for (int i = 0; i < dotCount; i++)
			DrawString(1080 / 2 - GetDrawStringWidth("Now Loading...", strlenDx("Now Loading...")) / 2 + GetDrawStringWidth("Now Loading", strlenDx("Now Loading")) + i * 32, 1920 / 2 + 256, ".", 0xffffff);

		//読み込みのバーを描画
		DrawBox(100, 1770, 980, 1820, 0x888888, true);
		DrawBox(100, 1770, 100 + 880.f * (1.f-boxRight), 1820, 0xffffff, true);

		//全ての内容を画面に表示
		ScreenFlip();
	}

	//メインのBGMの音量を設定
	ChangeVolumeSoundMem(0.75 * 255, Sounds::game);

	//次のシーンをTitleに設定
	Scene::NextScene(SceneList::Title);

	//背景色を設定
	SetBackgroundColor(50, 50, 50);

	//フェード処理
	Fade();

	return;
}

void Scene::Title(void)
{
	//ボタンの生成
	Button button(Vector2(1080 / 2 - 150, 1920 / 2 - 50), Vector2(300, 100), "START");
	Button rank(Vector2(1080 / 2 - 150, 1920 / 2 + 100), Vector2(300, 100), "RANKING");

	//タイトルのアニメーションを生成
	static TitleAnimation TitleA;

	while (Loop() && GetNowScene() == SceneList::Title)
	{
		//タップ時のエフェクトの処理
		TapEffectPlay();

		//フェード処理が終わっていれば
		if (!isFading)
		{
			//ゲーム開始のボタンが押されていたら説明シーンに遷移
			if (button.CheckTap(Up))
				NextScene(SceneList::Description);

			//ランキングのボタンが押されていたらランキングシーンに遷移
			if (rank.CheckTap(Up))
				NextScene(SceneList::Ranking);
		}

		//描画している内容を削除
		ClearDrawScreen();

		//タイトルのアニメーションの描画とその描画が終わっていればボタンを描画
		if (TitleA.Draw())
		{
			button.Draw();

			rank.Draw();
		}

		//フェード処理
		if (isFading)
			Fade();

		//タップ時のエフェクトを描画
		for (int i = 0; i < 20; i++)
			tapEffect[i].Draw();

		//全ての内容を画面に表示
		ScreenFlip();
	}

	//タイトルのBGMを停止
	StopSoundMem(Sounds::title);

	//背景色を設定
	SetBackgroundColor(50, 50, 50);

	return;
}

void Scene::Description(void)
{
	//説明画面のBGMを再生
	PlaySoundMem(Sounds::description, DX_PLAYTYPE_LOOP);

	while (Loop() && GetNowScene() == SceneList::Description)
	{
		//タップ時のエフェクトの処理
		TapEffectPlay();

		//フェードが終わっていて画面がタップされていればゲームシーンに遷移
		if (!isFading && Input::GetTap(0, Down))
			NextScene(SceneList::Game);

		//描画している内容を削除
		ClearDrawScreen();

		//説明画像を描画
		DrawGraph(0, 0, Images::description, false);

		//文字列の描画
		DrawFormatString(1030 - GetDrawFormatStringWidth("Tap To Start"), 1920 - 75, 0xffffff, "Tap To Start");

		//フェード処理
		if (isFading)
			Fade();

		//タップ時のエフェクトを描画
		for (int i = 0; i < 20; i++)
			tapEffect[i].Draw();

		//全ての内容を画面に表示
		ScreenFlip();
	}

	//説明画面のBGMを停止
	StopSoundMem(Sounds::description);

	return;
}

void Scene::Game(void)
{
	//メーターの生成
	Meter meter(Vector2(110, 380), Vector2(50, 1000), 0, 100);

	//客の描画位置
	Vector2 guestsPos[15];

	//服を破いた時のポーズの時間計測用
	float enableTextTime = 2.f;

	//ゲームの時間計測用
	float time = 2.999f;

	//ゲーム終了時の処理の時間計測用
	float endTextTime = 3.f;

	//ボタンの生成
	Button pause(Vector2(1080 - 300, 100), Vector2(200, 100), "Pause");
	Button back(Vector2(1080 / 2 - 200, 1920 / 2 - 150), Vector2(400, 100), "CLOSE");
	Button title(Vector2(1080 / 2 - 225, 1920 / 2 + 50), Vector2(450, 100), "TITLE");

	//ポーズメニューが表示されているか
	bool isPause = false;
	//ゲームが始まっているか
	bool isPlay = false;
	//下半身をタップしているか
	bool isLowerBody = false;
	//ゲームが終わっているか
	bool isEnd = false;

	//描画するプレイヤーの番号
	int drawManNum = 0;
	//描画するプレイヤーの番号の一時保存用
	int drawManTmp = 0;

	//集中線の不透明度
	int lineAlpha = 0;

	//布片のエフェクトの生成
	ClothBreak clothBreak(Vector2(1080 / 2, 1920 / 2), 50, 5, 150);

	//煙のエフェクトの生成
	Smoke left(Vector2(270, 1536), 100, 290, 10, 10.f, 750, 1.5f);
	Smoke right(Vector2(810, 1536), 100, 250, 10, 10.f, 750, 1.5f);

	//集中線の生成
	LineEffect line(Vector2(1080 / 2, 1920 / 2), 100, 1101);

	//ジャストタップの生成
	JustTap justTap(Vector2(1080 / 2, 1920 / 2 - 300));

	//キラキラするエフェクトの生成
	Effect<Particle> effect(Vector2(1080 / 2, 1920 / 2 + 50), 0, 400, 1.f);

	//キラキラするエフェクトのパーティクルの数を0に設定
	effect.ChangeParticleCount(0);

	//客の位置をランダムで取得
	for (int i = 0; i < 15; i++)
		guestsPos[i] = Vector2((i % 5) * 1080 / 5 + (100 - GetRand(50)) - 250, 1400 + (i / 5) * 100 + (50 - GetRand(25)));

	//ゲームのBGMを再生
	PlaySoundMem(Sounds::game, DX_PLAYTYPE_LOOP);

	while (Loop() && GetNowScene() == SceneList::Game)
	{
		//描画するプレイヤーの番号を0に設定
		drawManNum = 0;

		//フェードが終わっていてゲームが終わっていなければ
		if (!isFading && !isEnd)
		{
			//煙パーティクルの処理が終わっていなくてゲームが始まっていなければ
			if ((!left.isStop || !right.isStop) && !isPlay)
			{
				//煙パーティクルの処理
				left.Play();
				right.Play();

				//煙パーティクルが終わっていればカウントダウンの音声を再生
				if (left.isStop && right.isStop)
					PlaySoundMem(Sounds::countDown, DX_PLAYTYPE_BACK);
			}
			//煙パーティクルの処理が終わっていてゲームが始まっていなければ
			else if (!isPlay)
			{
				//一定の時間から前フレームからの時間を減算
				time -= Time::deltaTime;

				//一定の時間経過したら
				if (time <= 0)
				{
					//ゲームを始める
					isPlay = true;
					//ゲーム時間を20秒に設定
					time = 20.f;
					//スタートの音声を再生
					PlaySoundMem(Sounds::start, DX_PLAYTYPE_BACK);
				}
			}

			//ポーズメニューが表示されていなくてゲームが始まっていて
			//ジャストタップが始まっていなければ
			if (!isPause && isPlay && !justTap.IsPlaying())
			{
				//タップした座標を格納する変数
				Vector2 tapPos;

				//ポーズボタンがタップされていたらポーズメニューを表示
				isPause = pause.CheckTap(Down);

				//残り時間から前フレームからの時間を減算
				time -= Time::deltaTime;

				//メーターの値を1ずつ減らす
				meter.AddValue(-1);

				//画面がタップされていたら
				if (Input::GetTap(0, Down, &tapPos))
				{
					//タップした位置がプレイヤーの位置なら
					if (tapPos.x >= 284 && tapPos.x <= 796 && tapPos.y >= 720 && tapPos.y <= 1303)
					{
						//メーターの値を20増やす
						meter.AddValue(20);

						//タップした座標のyの値が1072以上なら下半身のタップにする
						isLowerBody = tapPos.y > 1072;

						//下半身をタップしていなければ上半身用の音声を再生
						if (!isLowerBody)
							PlaySoundMem(Sounds::fun[GetRand(1)], DX_PLAYTYPE_BACK);
						//下半身をタップしていれば下半身用の音声を再生
						else
							PlaySoundMem(Sounds::ah, DX_PLAYTYPE_BACK);
					}
				}

				//メーターの値が最大値に達していればジャストタップを始める
				if (meter.isMax)
					justTap.Start();

				//残り時間が0以下になったら
				if (time <= .0f)
				{
					//時間を0に固定
					time = .0f;

					//ゲームが終わっている状態に設定
					isEnd = true;
					isPlay = false;

					//終了時の音声を再生
					PlaySoundMem(Sounds::finish, DX_PLAYTYPE_BACK);
				}
			}

			//ジャストタップが開始されていたら
			if (justTap.IsPlaying())
			{
				//ジャストタップの処理
				justTap.Play();

				//ジャストタップが終了していたら
				if (!justTap.IsPlaying())
				{
					//ジャストタップの結果によって残り時間に加算する値を変える
					time += .5f * justTap.judge;

					//ジャストタップの結果に合った音声を再生
					PlaySoundMem(Sounds::judge[2 * justTap.judge + GetRand(1)], DX_PLAYTYPE_BACK);

					//破いた服の枚数をカウント
					brokeCount++;

					//プレイヤーのポーズの時間を設定
					enableTextTime = 0;

					//次に描画するプレイヤーの番号をランダムで取得
					drawManTmp = GetRand(1) + 1;

					//集中線の不透明度を255に設定
					lineAlpha = 255;

					//メーターの値をリセット
					meter.SetValue(0);

					//布片のエフェクトを開始
					clothBreak.Start();

					//キラキラするエフェクトのパーティクルの数を設定
					effect.ChangeParticleCount(40 * justTap.judge);
					//キラキラするエフェクトを開始
					effect.Start();

					//服を破いた時の音声を再生
					PlaySoundMem(Sounds::breakS, DX_PLAYTYPE_BACK);
				}
			}

			//ポーズメニューが表示されていたら
			if (isPause)
			{
				//バックボタンがタップされていたらポーズメニューを非表示
				isPause = !back.CheckTap(Up);

				//タイトルボタンがタップされていたら
				if (title.CheckTap(Up))
				{
					//次のシーンをタイトルに設定
					NextScene(SceneList::Title);

					//破いた服の枚数を0にリセット
					brokeCount = 0;
				}
			}

			//ポーズをする時間を計測
			enableTextTime += Time::deltaTime;

			//ポーズをしている時間が0.5秒未満ならポーズをさせる
			if (enableTextTime < .5f)
				drawManNum = drawManTmp;
		}

		//ポーズメニューが表示されていなければ
		if (!isPause)
		{
			//布片のエフェクトを再生
			clothBreak.Play();

			//集中線の不透明度が1以上なら
			if (lineAlpha > 0)
			{
				//集中線を再生
				line.Play();
				//集中線の不透明度を下げる
				lineAlpha -= 4;
			}

			//キラキラするエフェクトの再生
			effect.Play();
		}

		//アプリが非アクティブになった時にInactive関数を呼ぶように設定
		SetAndroidLostFocusCallbackFunction(Inactive, &isPause);

		//描画している内容を削除
		ClearDrawScreen();

		//背景の描画
		DrawGraph(0, 0, Images::stage, true);

		//集中線の不透明度が1以上なら
		if (lineAlpha > 0)
		{
			//描画時のブレンドをアルファに設定
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, lineAlpha);

			//集中線の描画
			line.Draw();

			//描画時のブレンド設定を解除
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);
		}

		//プレイヤーの描画
		DrawGraph(1080 / 2 - 256, 1920 / 2 - 650, Images::man[drawManNum], true);

		//描画するプレイヤーの番号が0なら服を描画
		if (drawManNum == 0)
			DrawGraph(1080 / 2 - 256, 1920 / 2 - 285, Images::Tshirt, true);

		//煙パーティクルの描画
		left.Draw();
		right.Draw();

		//煙パーティクルの出現位置にスモークマシンを描画
		DrawRotaGraph3(252, 1582, 90, 250, .5, .5, 0, Images::gas, true, false);
		DrawRotaGraph3(827, 1582, 142, 250, .5, .5, 0, Images::gas, true, true);

		//布片のエフェクトの描画
		clothBreak.Draw();

		//キラキラするエフェクトの描画
		effect.Draw();

		//客の描画
		for (int i = 0; i < 15; i++)
			DrawGraph(guestsPos[i].x, guestsPos[i].y, Images::guests[i % 2], true);

		//ジャストタップの描画
		justTap.Draw();

		//ゲームが終わっていれば
		if (isEnd)
		{
			//終了の文字列を大きいフォントで描画
			DrawStringToHandle(1080 / 2 - GetDrawStringWidthToHandle("Finish!", 8, bigFont) / 2, 1920 / 2-200, "Finish!", 0xaaaaaa, bigFont);

			//一定の時間から前フレームからの時間を減算
			endTextTime -= Time::deltaTime;

			//一定の時間経過したら次のシーンをリザルト画面に設定
			if (endTextTime <= 0)
				NextScene(SceneList::Result);
		}

		//メーターの描画
		meter.Draw();

		//ポーズボタンの描画
		pause.Draw();

		//ゲームが始まっていなければカウントダウンの数字を描画
		if (!isPlay && left.isStop && !isEnd)
			DrawFormatStringToHandle(1080 / 2 - 64, 1920 / 2 - 128, 0xff0000, bigFont, "%d", (int)(time + 1));
		//ゲームが始まっていれば残り時間を描画
		else if (isPlay && !isEnd)
			DrawFormatString(100, 228, 0xffffff, "残り %2.1f 秒", time);

		//ポーズメニューが表示されていれば
		if (isPause)
		{
			//ポーズメニューの背景を描画
			DrawBox(1080 / 2 - 450, 1920 / 2 - 300, 1080 / 2 + 450, 1920 / 2 + 300, 0xeeeeee, true);

			//ポーズメニューのボタンを描画
			back.Draw();
			title.Draw();
		}

		//フェード処理
		if (isFading)
			Fade();

		//全ての内容を画面に表示
		ScreenFlip();
	}

	//ゲームのBGMを停止
	StopSoundMem(Sounds::game);

	//途中でやめたらタイトルのBGMを再生
	if(nowScene == SceneList::Title)
		PlaySoundMem(Sounds::title, DX_PLAYTYPE_LOOP);

	return;
}
void Scene::Result(void)
{
	//ボタンの生成
	Button replay(Vector2(1080 / 2 - 150, 1920 / 2 - 50), Vector2(300, 100), "RETRY");
	Button back(Vector2(1080 / 2 - 150, 1920 / 2 + 100), Vector2(300, 100), "TITLE");

	//現在の結果がランクインしていれば保存
	if (Ranking::AddRank(brokeCount))
		Ranking::SaveData();

	//リザルトのBGMを再生
	PlaySoundMem(Sounds::result, DX_PLAYTYPE_LOOP);

	while (Loop() && GetNowScene() == SceneList::Result)
	{
		//タップ時のエフェクトの処理
		TapEffectPlay();

		//フェードが終わっていれば
		if (!isFading)
		{
			//リプレイボタンがタップされていたら説明シーンに遷移
			if (replay.CheckTap(Up))
				NextScene(SceneList::Description);

			//戻るボタンがタップされていたらタイトルシーンに遷移
			if (back.CheckTap(Up))
				NextScene(SceneList::Title);
		}

		//描画している内容を削除
		ClearDrawScreen();

		//背景の描画
		DrawGraph(0, 0, Images::stage, false);

		//スコアの背景を描画
		DrawRotaGraph(1080 / 2, 1920 / 2 - 512, 1.0, 0.0, Images::scoreBord, true);

		//ボタンの描画
		replay.Draw();

		back.Draw();

		//結果の描画
		DrawFormatString(1080 / 2 - GetDrawFormatStringWidth("Oh! HADAKEの回数 %3d 回", brokeCount) / 2, 500, 0, "Oh! HADAKEの回数 %3d 回", brokeCount);
		DrawFormatString(1080 / 2 - GetDrawFormatStringWidth("今回の結果", brokeCount) / 2, 300, 0, "今回の結果", brokeCount);

		//フェード処理
		if (isFading)
			Fade();

		//タップエフェクトの描画
		for (int i = 0; i < 20; i++)
			tapEffect[i].Draw();

		//全ての内容を画面に表示
		ScreenFlip();
	}

	//リザルト画面のBGMを停止
	StopSoundMem(Sounds::result);

	//次のシーンがタイトルシーンならタイトル画面のBGMを再生
	if(nowScene==SceneList::Title)
		PlaySoundMem(Sounds::title, DX_PLAYTYPE_LOOP);
	//次のシーンが説明シーンなら説明画面のBGMを再生
	else
		PlaySoundMem(Sounds::description, DX_PLAYTYPE_LOOP);

	//破いた服の枚数をリセット
	brokeCount = 0;

	return;
}

void Scene::Ranking(void)
{
	//ボタンの生成
	Button button(Vector2(1080 / 2 - 100, 1920 / 2 +500), Vector2(200, 100), "BACK");

	//ランキングのBGMを再生
	PlaySoundMem(Sounds::ranking, DX_PLAYTYPE_LOOP);

	while (Loop() && GetNowScene() == SceneList::Ranking)
	{
		//タップ時のエフェクトの処理
		TapEffectPlay();

		//フェードが終わっていてボタンが押されていたら次のシーンをタイトルシーンに遷移
		if (!isFading && button.CheckTap(Up))
			NextScene(SceneList::Title);

		//描画している内容を削除
		ClearDrawScreen();

		//ランキングの背景を描画
		DrawGraph(0, 0, Images::ranking, false);

		//ボタンの描画
		button.Draw();

		//ランキングの内容を描画
		for (int i = 0; i < 10; i++)
			DrawFormatString(500, 290 + 92 * i, 0, "%3d 回", Ranking::GetSheets(i));

		//フェード処理
		if (isFading)
			Fade();

		//タップエフェクトの描画
		for (int i = 0; i < 20; i++)
			tapEffect[i].Draw();

		//内容を画面に表示
		ScreenFlip();
	}

	//ランキング画面のBGMを停止
	StopSoundMem(Sounds::ranking);

	//タイトル画面の音声を再生
	PlaySoundMem(Sounds::title, DX_PLAYTYPE_LOOP);

	return;
}

void Scene::NextScene(int next)
{
	//現在のシーンを前のシーンに変更
	beforeScene = nowScene;

	//次のシーンを設定
	nextScene = next;

	//フェード処理を行うように設定
	isFading = true;

	//現在のシーンがロードシーンなら集中線の不透明度を255に設定
	if (nowScene == SceneList::Load)
		alpha = 255;

	return;
}

void Scene::Fade(void)
{
	//不透明度を減らすか
	static bool subAlpha = false;

	//現在のシーンがロードシーンなら
	if (nowScene == SceneList::Load)
	{
		//不透明度を255に設定
		alpha = 255;
		//不透明度を減らすように設定
		subAlpha = true;
		//次のシーンを現在のシーンに設定
		nowScene = nextScene;
		//次のシーンを何もない状態に設定
		nextScene = -1;
	}

	//不透明度を上げる設定なら不透明度を上げる
	if (!subAlpha)
		alpha += 8;
	//不透明度を下げる設定なら不透明度を下げる
	else
		alpha -= 8;

	//不透明度を上げる設定で不透明度が255以上なら
	if (!subAlpha && alpha >= 255)
	{
		//不透明度を255に固定
		alpha = 255;

		//次のシーンを設定
		NextScene(nextScene);
		//現在のシーンに次のシーンを設定
		nowScene = nextScene;
		//次のシーンを何もない状態に設定
		nextScene = -1;

		//不透明度を下げるように設定
		subAlpha = true;
	}

	//不透明度を下げる設定で不透明度が0以下なら
	if (subAlpha && alpha <= 0)
	{
		//不透明度を0に固定
		alpha = 0;

		//フェード処理が終わっている状態に設定
		isFading = false;

		//不透明度を上げるように設定
		subAlpha = false;
	}

	//ブレンドをアルファに設定
	SetDrawBlendMode(DX_BLENDMODE_SUB, alpha);

	//フェード用の四角を描画
	DrawBox(0, 0, 1080, 1920, 0xffffff, true);

	//ブレンド設定を解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);

	return;
}
