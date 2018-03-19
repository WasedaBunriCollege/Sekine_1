/*****************/
/**  関根 明良  **/
/**   数学関係  **/
/*****************/

#pragma once

#ifndef _USE_MATH_DEFINES

#define _USE_MATH_DEFINES

#endif

#include <cmath>

#include "DxLib.h"

/// <summary>
/// 円周率
/// </summary>
const static double PI = M_PI;

/// <summary>
/// デグリーからラジアンに変換
/// </summary>
/// <param name="deg">デグリーの値</param>
/// <returns>ラジアンの値</returns>
inline double DegToRad(double deg)
{
	return deg * PI / 180.f;
}
/// <summary>
/// ラジアンからデグリーに変換
/// </summary>
/// <param name="rad">ラジアンの値</param>
/// <returns>デグリーの値</returns>
inline double RadToDeg(double rad)
{
	return rad * 180.f / PI;
}

///<summary>
///二次元ベクトル
///</summary>
class Vector2
{
private:

	/// <summary>
	/// magnitudeの再計算
	/// </summary>
	inline void Recalc(void)
	{
		magnitude = sqrt(pow(x, 2.0) + pow(y, 2.0));

		return;
	}

public:

	/// <summary>
	/// 二次元ベクトルのxとyの値
	/// </summary>
	double x, y;
	/// <summary>
	/// ベクトルの大きさ
	/// </summary>
	double magnitude;

	/// <summary>
	/// ゼロの値
	/// </summary>
	static const Vector2 zero;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Vector2();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_x">xの値</param>
	/// <param name="_y">yの値</param>
	Vector2(double _x, double _y);

	///<summary>
	///xとyの値の文字列を返します。
	///</summary>
	const char * ToString(void);

	///<summary>
	///二点間の距離の値を返します。
	///</summary>
	double Distance(Vector2 _pos);
	///<summary>
	///二点間の距離の値を返します。
	///</summary>
	double Distance(int _x, int _y);
	///<summary>
	///二点間の距離の値を返します。
	///</summary>
	static double Distance(Vector2 _pos1, Vector2 _pos2);
	///<summary>
	///二点間の距離の値を返します。
	///</summary>
	static double Distance(int _x, int _y, Vector2 _pos);
	///<summary>
	///二点間の距離の値を返します。
	///</summary>
	static double Distance(int _x1, int _y1, int _x2, int _y2);

	///<summary>
	///二点間の角度の値を返します。
	///</summary>
	double Angle(Vector2 _pos);
	///<summary>
	///二点間の角度の値を返します。
	///</summary>
	double Angle(int _x, int _y);
	///<summary>
	///二点間の角度の値を返します。
	///</summary>
	static double Angle(Vector2 _pos1, Vector2 _pos2);
	///<summary>
	///二点間の角度の値を返します。
	///</summary>
	static double Angle(int _x, int _y, Vector2 _pos);
	///<summary>
	///二点間の角度の値を返します。
	///</summary>
	static double Angle(int _x1, int _y1, int _x2, int _y2);

	///<summary>
	///正規化した値を返します。
	///</summary>
	Vector2 Normalize(void);
	///<summary>
	///正規化した値を返します。
	///</summary>
	static Vector2 Normalize(Vector2 _value);
	///<summary>
	///正規化した値を返します。
	///</summary>
	static Vector2 Normalize(int _x, int _y);

	const Vector2 operator - () const;

	const Vector2 operator + (const Vector2 & vec) const;
	const Vector2 operator - (const Vector2 & vec) const;
	const Vector2 operator * (const Vector2 & vec) const;
	const Vector2 operator / (const Vector2 & vec) const;

	const Vector2 operator + (const int & vec) const;
	const Vector2 operator + (const double & vec) const;
	const Vector2 operator - (const int & vec) const;
	const Vector2 operator - (const double & vec) const;
	const Vector2 operator * (const int & vec) const;
	const Vector2 operator * (const double & vec) const;
	const Vector2 operator / (const int & vec) const;
	const Vector2 operator / (const double & vec) const;

	inline Vector2 & operator += (const Vector2 & vec)
	{
		x += vec.x;
		y += vec.y;

		Recalc();

		return *this;
	}
	inline Vector2 & operator -= (const Vector2 & vec)
	{
		x -= vec.x;
		y -= vec.y;

		Recalc();

		return *this;
	}
	inline Vector2 & operator *= (const Vector2 & vec)
	{
		x *= vec.x;
		y *= vec.y;

		Recalc();

		return *this;
	}
	inline Vector2 & operator /= (const Vector2 & vec)
	{
		x /= vec.x;
		y /= vec.y;

		Recalc();

		return *this;
	}

	inline Vector2 & operator += (const int & vec)
	{
		x += vec;
		y += vec;

		Recalc();

		return *this;
	}
	inline Vector2 & operator += (const double & vec)
	{
		x += vec;
		y += vec;

		Recalc();

		return *this;
	}
	inline Vector2 & operator -= (const int & vec)
	{
		x -= vec;
		y -= vec;

		Recalc();

		return *this;
	}
	inline Vector2 & operator -= (const double & vec)
	{
		x -= vec;
		y -= vec;

		Recalc();

		return *this;
	}
	inline Vector2 & operator *= (const int & vec)
	{
		x *= vec;
		y *= vec;

		Recalc();

		return *this;
	}
	inline Vector2 & operator *= (const double & vec)
	{
		x *= vec;
		y *= vec;

		Recalc();

		return *this;
	}
	inline Vector2 & operator /= (const int & vec)
	{
		x /= vec;
		y /= vec;

		Recalc();

		return *this;
	}
	inline Vector2 & operator /= (const double & vec)
	{
		x /= vec;
		y /= vec;

		Recalc();

		return *this;
	}

	bool operator == (const Vector2 & vec) const;
	bool operator != (const Vector2 & vec) const;

};