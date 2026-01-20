//----------------------------------------------------------------------------
//! @file   MyLibraryFunctions.cpp
//! @brief  ユーティリティ関数群の実装
//! @detail 時間変換、当たり判定、角度変換、カメラ制御などの共通関数を実装します。
//----------------------------------------------------------------------------
#include "MyLibraryFunctions.h"

namespace MyLibrary
{
	//----------------------------------------------------------------------------
	//! ミリ秒を秒に変換します。
	//----------------------------------------------------------------------------
	float ConvertMilliToSec(int milli)
	{
		// 注意: 先にfloatにキャストしてから割ることで精度を保つ
		return static_cast<float>(milli) / static_cast<float>(MS_PER_SEC);
	}

	//----------------------------------------------------------------------------
	//! ミリ秒を分に変換します。
	//----------------------------------------------------------------------------
	float ConvertMilliToMinute(int milli)
	{
		return static_cast<float>(milli) / static_cast<float>(MS_PER_MIN); // 1分 = 60秒 * 1000ミリ秒
	}

	//----------------------------------------------------------------------------
	//! ファイルパスから拡張子を取得します。
	//----------------------------------------------------------------------------
	std::string GetFileExtension(const char* filepath)
	{
		std::string path(filepath);
		size_t pos = path.rfind('.');
		if (pos == std::string::npos || pos == path.length() - 1) return "";
		return path.substr(pos + 1);
	}

	//----------------------------------------------------------------------------
	//! 目標方向に向かうための回転を計算します。
	//----------------------------------------------------------------------------
	float ObjectPointToDirection(FloatPos now_pos, FloatPos goal_pos, float dir, float rot_speed)
	{
		float now_dir = TODEGREE(dir); // ラジアン → 度
		float dx = goal_pos.x - now_pos.x;
		float dy = goal_pos.y - now_pos.y;
		float goal_dir = TODEGREE(atan2f(dy, dx)) + 90.0f; // 目標角度

		float diff = goal_dir - now_dir;
		while (diff >= 180.0f) diff -= 360.0f;
		while (diff < -180.0f) diff += 360.0f;

		if (diff > rot_speed) now_dir += rot_speed;
		else if (diff < -rot_speed) now_dir -= rot_speed;
		else now_dir = goal_dir;

		return TORADIAN(now_dir); // 度 → ラジアン
	}

	//----------------------------------------------------------------------------
	//! カメラ停止位置を計算します。
	//----------------------------------------------------------------------------
	void CameraStop(float pos_x, float pos_y, float w, float h, float& cam_x, float& cam_y)
	{
		if (pos_x > HALF_SCREEN_W && pos_x < w - HALF_SCREEN_W)
			cam_x = HALF_SCREEN_W - pos_x;

		if (pos_y > HALF_SCREEN_H && pos_y < h - HALF_SCREEN_H)
			cam_y = HALF_SCREEN_H - pos_y;
	}

	//----------------------------------------------------------------------------
	//! 位置を矩形エリア内に制限します。
	//----------------------------------------------------------------------------
	void ClampPositionToArea(FloatPos& target_pos, int target_w, int target_h, float area_w, float area_h)
	{
		target_pos.x = std::max(static_cast<float>(target_w) * HALF, std::min(target_pos.x, area_w - target_w * HALF));
		target_pos.y = std::max(static_cast<float>(target_h) * HALF, std::min(target_pos.y, area_h - target_h * HALF));
	}

	//----------------------------------------------------------------------------
	//! 浮動小数点座標の点と矩形の当たり判定を行います。
	//----------------------------------------------------------------------------
	bool CheckPointBoxHitF(const FloatPos& point, const FloatPos& rect_pos, const FloatSize& rect_size)
	{
		return (point.x >= rect_pos.x && point.x <= rect_pos.x + rect_size.w) &&
			(point.y >= rect_pos.y && point.y <= rect_pos.y + rect_size.h);
	}

	//----------------------------------------------------------------------------
	//! 点と矩形の当たり判定を行います。
	//----------------------------------------------------------------------------
	bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h)
	{
		return (point_x >= box_x && point_x <= box_x + box_w) &&
			(point_y >= box_y && point_y <= box_y + box_h);
	}

	//----------------------------------------------------------------------------
	//! 矩形同士の当たり判定を行います。
	//----------------------------------------------------------------------------
	bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
	{
		return (x1 + w1 >= x2 && x1 <= x2 + w2) &&
			(y1 + h1 >= y2 && y1 <= y2 + h2);
	}

	//----------------------------------------------------------------------------
	//! 円同士の当たり判定を行います。
	//----------------------------------------------------------------------------
	bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2)
	{
		float dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		return dist <= (r1 + r2);
	}

	//----------------------------------------------------------------------------
	//! 点と円の当たり判定を行います。
	//----------------------------------------------------------------------------
	bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r)
	{
		float dist = sqrt((point_x - circle_x) * (point_x - circle_x) + (point_y - circle_y) * (point_y - circle_y));
		return dist <= circle_r;
	}

	//----------------------------------------------------------------------------
	//! 度をラジアンに変換します。
	//----------------------------------------------------------------------------
	float TORADIAN(float degree) { return degree * PI / 180.0f; }
	//----------------------------------------------------------------------------
	//! ラジアンを度に変換します。
	//----------------------------------------------------------------------------
	float TODEGREE(float radian) { return radian * 180.0f / PI; }

	//----------------------------------------------------------------------------
	//! 回転に沿った成分を取得します。
	//----------------------------------------------------------------------------
	float GetLengthAlongRotation(float rot) { return cosf(rot); } // 回転に沿った長さ取得
	//----------------------------------------------------------------------------
	//! 回転に対する直交成分を取得します。
	//----------------------------------------------------------------------------
	float GetLengthOppositeRotation(float rot) { return sinf(rot); } // 回転に対する直交成分取得
}
