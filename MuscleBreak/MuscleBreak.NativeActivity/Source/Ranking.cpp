/**********************/
/**    関根 明良     **/
/** ランキングクラス **/
/**********************/

#include "Ranking.hpp"

char Ranking::dataPath[256];

int Ranking::sheet[10];

void Ranking::LoadData(void)
{
	//ファイル構造体のポインタ
	FILE * fp;

	//データ保存用のディレクトリを取得
	GetInternalDataPath(dataPath, sizeof dataPath);

	//ファイル名を指定してファイルのパスを設定
	strcatDx(dataPath, "/RankingData.dat");

	//ファイルを読み込み専用で開く
	fp = fopen(dataPath, "r");

	//ファイルが無かったら読み書き設定で開きファイルを作成
	if (fp == __null)
		fp = fopen(dataPath, "w+");

	for (int i = 0; i < 10; i++)
	{
		//ファイルの終了位置まで1行ずつ読み込む
		if (fscanf(fp, "%d\n", &sheet[i]) == EOF)
			break;
	}

	//ファイルを閉じる
	fclose(fp);

	return;
}

void Ranking::SaveData(void)
{
	//ファイル構造体のポインタ
	FILE * fp;

	//ファイルを書き込み専用で開く
	fp = fopen(dataPath, "w");

	//データを書き込む
	for (int i = 0; i < 10; i++)
		fprintf(fp, "%d\n", sheet[i]);

	//ファイルを閉じる
	fclose(fp);

	return;
}

bool Ranking::AddRank(int _sheet)
{
	for (int i = 0; i < 10; i++)
	{
		//新しいデータがi番目以上なら
		if (_sheet >= sheet[i])
		{
			//i番目以降を1つずつずらす
			for (int j = 9; j > i; j--)
				sheet[j] = sheet[j - 1];

			//i番目に新しいデータを挿入
			sheet[i] = _sheet;

			//ランクインしたことを返す
			return true;
		}
	}

	//ランクインしなかったことを返す
	return false;
}

void Ranking::Reset(void)
{
	//値を全てリセット
	for (int i = 0; i < 10; i++)
		sheet[i] = 0;

	//データを保存
	SaveData();
}
