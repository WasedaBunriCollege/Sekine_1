/**********************/
/**    関根 明良     **/
/** ランキングクラス **/
/**********************/

#pragma once

#include "DxLib.h"

/// <summary>
/// ランキング
/// </summary>
class Ranking
{
private:

	/// <summary>
	/// 保存ファイルのパス
	/// </summary>
	static char dataPath[256];

	/// <summary>
	/// ランキングの値
	/// </summary>
	static int sheet[10];

	/// <summary>
	/// 静的クラスにするためにコンストラクタはprivate
	/// </summary>
	Ranking();

public:

	/// <summary>
	/// データの読み込み
	/// </summary>
	static void LoadData(void);

	/// <summary>
	/// データの書き込み
	/// </summary>
	static void SaveData(void);

	/// <summary>
	/// ランキングの追加
	/// </summary>
	/// <param name="_sheet">追加する値</param>
	/// <returns>追加した値がランクに入っているか</returns>
	static bool AddRank(int _sheet);

	/// <summary>
	/// データの削除
	/// </summary>
	static void Reset(void);

	/// <summary>
	/// 保存ファイルのパス
	/// </summary>
	/// <returns>パスの文字列</returns>
	inline static char * GetPath(void)
	{
		return dataPath;
	}
	
	/// <summary>
	/// 値の取得
	/// </summary>
	/// <param name="num">取得したい順位</param>
	/// <returns>取得した値</returns>
	inline static int GetSheets(int num)
	{
		return sheet[num];
	}
};