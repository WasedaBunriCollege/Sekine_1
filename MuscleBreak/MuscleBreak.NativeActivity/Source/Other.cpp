/********************/
/**   関根 明良    **/
/** その他のクラス **/
/********************/

#include "Other.hpp"

int64_t Time::beforeTime = 0;

int64_t Time::nowTime = 0;

bool Time::needRefresh = false;

double Time::deltaTime = 0.0;

void Time::CallEveryFrame(void)
{
	//Androidが起動してからの時間を取得
	nowTime = GetNowHiPerformanceCount();

	//前フレームからの時間を取得
	deltaTime = (double)(nowTime - beforeTime) / 1000000.0;

	//今の時間を保存
	beforeTime = nowTime;

	//更新が不要な状態に変更
	needRefresh = false;

	return;
}

int Time::GetFPS(void)
{
	//1秒間のフレーム数
	static int fps = 0;

	//実行している回数
	static int frameCount = 0;

	//時間の計測用
	static double sum = 0.0;

	//更新が不要なら
	if (!needRefresh)
	{
		//前回からの経過時間を加算
		sum += deltaTime;

		//実行回数をカウント
		frameCount++;

		//1秒経過したら
		if (sum >= 1.0)
		{
			//実行回数を1秒間のフレーム数に設定
			fps = frameCount;

			//実行回数をリセット
			frameCount = 0;
			//経過時間をリセット
			sum = 0;
		}

		//更新が必要状態に変更
		needRefresh = true;
	}

	//1秒あたりのフレーム数を返す
	return fps;
}

bool Input::needRefrech[3] = { false,false,false };

bool Input::before[3] = { false,false,false };

bool Input::result[3] = { false,false,false };

bool Input::GetTap(int num, int checkType, Vector2 * position)
{
	//前フレームの入力状態
	static bool beforeBuf[3][16];

	//初期化が必要か
	static bool first = true;

	//入力座標の保存用
	static Vector2 positionBuf;

	//処理しているか
	bool isProcess = false;

	//返す値
	bool returnValue = false;

	//タップのID
	int ID;

	if (first)
	{
		//前フレームの入力状態を初期化
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 16; j++)
				beforeBuf[i][j] = false;
		}

		//次回以降初期化しないようにする
		first = false;
	}

	//タップしている数だけループする
	for (int i = 0; i < GetTouchInputNum(); i++)
	{
		//positionにメモリが渡されていたら
		if (position != __null)
		{
			int x, y;

			//タップ入力を取得
			GetTouchInput(i, &x, &y, &ID);

			//タップ座標を格納
			positionBuf = Vector2(x, y);
		}
		else
			//タップ入力を取得
			GetTouchInput(i, __null, __null, &ID);

		//numとIDが同じならループを抜ける
		if (num == ID)
			break;
	}

	//checkTypeの更新が不要なら
	if (!needRefrech[checkType])
	{
		//タップしている数だけループする
		for (int i = 0; i < GetTouchInputNum(); i++)
		{
			//numとIDが違ったらループの先頭に戻る
			if (num != ID)
				continue;

			//処理を実行している状態に変更
			isProcess = true;

			//checkTypeの値で分岐
			switch (checkType)
			{
			//タップした瞬間
			case Down:

				//前フレームでfalseなら
				if (!beforeBuf[Down][num])
				{
					//Downの更新が必要な状態にする
					needRefrech[Down] = true;
					//今フレームのDownの結果をtrueにする
					result[Down] = true;
					//返り値にtrueを設定
					returnValue = true;

					//今フレームの状態を保存
					beforeBuf[Down][num] = true;

					//positionにポインタが渡されていたら入力座標を返す
					if (position != __null)
						*position = positionBuf;
				}

				break;

			//タップしている間
			case Press:

				//Pressの更新が必要な状態にする
				needRefrech[Press] = true;
				//今フレームのPressの結果をtrueにする
				result[Press] = true;
				//返り値にtrueを設定
				returnValue = true;

				//今フレームの状態を保存
				beforeBuf[Press][num] = true;

				//positionにポインタが渡されていたら入力座標を返す
				if (position != __null)
					*position = positionBuf;

				break;

			//タップが終わった瞬間
			case Up:

				//今フレームの状態を保存
				beforeBuf[Up][num] = true;

				break;
			}

			break;
		}

		//処理をしない状態なら
		if (!isProcess)
		{
			//checkTypeがUpで前フレームに入力されていたら
			if (checkType == Up && beforeBuf[Up][num])
			{
				//Upの更新が必要な状態
				needRefrech[Up] = true;
				//今フレームのUpの結果をtrueにする
				result[Up] = true;
				//返り値にtrueを設定
				returnValue = true;

				//今フレームの結果を保存
				beforeBuf[Up][num] = false;

				//positionにポインタが渡されていたら入力座標を返す
				if (position != __null)
					*position = positionBuf;
			}

			//DownとPressの前フレームの結果をfalseに設定
			for (int i = 0; i < 2; i++)
				beforeBuf[i][num] = false;
		}
	}
	else
	{
		//今フレームの結果を返り値に設定
		returnValue = result[checkType];

		//positionにポインタが渡されていたら入力座標を返す
		if (position != __null)
			*position = positionBuf;
	}

	return returnValue;
}

void Input::CallEveryFrame(void)
{
	for (int i = 0; i < 3; i++)
	{
		//更新が不要な状態に設定
		needRefrech[i] = false;
		//結果をfalseに設定
		result[i] = false;
	}

	return;
}
