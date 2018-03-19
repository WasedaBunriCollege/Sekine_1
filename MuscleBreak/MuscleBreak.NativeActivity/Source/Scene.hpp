/******************/
/**   関根 明良  **/
/** シーンクラス **/
/******************/

#pragma once

#include "DxLib.h"

#include "MuscleBreak.hpp"

/// <summary>
/// シーンの列挙
/// </summary>
struct SceneList
{
	enum
	{
		Load, Title, Description, Game, Result, Ranking
	};
};

/// <summary>
/// シーンクラス
/// </summary>
class Scene
{
private:

	/// <summary>
	/// 現在のシーン
	/// </summary>
	static int nowScene;

	/// <summary>
	/// 遷移先のシーン
	/// </summary>
	static int nextScene;

	/// <summary>
	/// 前回のシーン
	/// </summary>
	static int beforeScene;

	/// <summary>
	/// フェードの不透明度
	/// </summary>
	static int alpha;

	/// <summary>
	/// 静的クラスにするためにコンストラクタはprivate
	/// </summary>
	Scene();

public:

	/// <summary>
	/// フェードしているか
	/// </summary>
	static bool isFading;

	/// <summary>
	/// ロードシーン
	/// </summary>
	static void Load(void);

	/// <summary>
	/// タイトルシーン
	/// </summary>
	static void Title(void);

	/// <summary>
	/// 操作、ルール説明シーン
	/// </summary>
	static void Description(void);

	/// <summary>
	/// ゲームメイン
	/// </summary>
	static void Game(void);

	/// <summary>
	/// 結果シーン
	/// </summary>
	static void Result(void);

	/// <summary>
	/// ランキングシーン
	/// </summary>
	static void Ranking(void);

	/// <summary>
	/// 遷移先のシーン設定
	/// </summary>
	/// <param name="next">遷移先のシーン</param>
	static void NextScene(int next);

	/// <summary>
	/// シーン遷移時のフェード
	/// </summary>
	static void Fade(void);

	/// <summary>
	/// 現在のシーンを取得
	/// </summary>
	inline static int GetNowScene(void)
	{
		return nowScene;
	}

	/// <summary>
	/// ひとつ前のシーンを取得
	/// </summary>
	inline static int GetBeforeScene(void)
	{
		return beforeScene;
	}
};