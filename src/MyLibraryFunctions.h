//----------------------------------------------------------------------------
//! @file   MyLibraryFunctions.h
//! @brief  汎用ユーティリティの宣言
//! @detail 時間変換、当たり判定、角度変換、カメラ制御などの共通関数を提供します。
//----------------------------------------------------------------------------
#pragma once
#include "Structs.h"
#include "DxMain.h"
#include <string>
#include <numbers>
#include <math.h>
#include <algorithm>

namespace MyLibrary
{
    //---------------------------------------------------------------
	//  定数定義
    //---------------------------------------------------------------
    // 時間変換定数
    constexpr int MS_PER_SEC = 1000;   //!< 1秒のミリ秒数
    constexpr int MS_PER_MIN = 60000;  //!< 1分のミリ秒数

    // 数学関係
    constexpr float PI = 3.14159265358979323846f; //!< 円周率

    //---------------------------------------------------------------
    //  関数定義
    //---------------------------------------------------------------
    //! ミリ秒を秒に変換します。
    float ConvertMilliToSec(int milli); // ミリ秒を秒に変換

    //! ミリ秒を分に変換します。
    float ConvertMilliToMinute(int milli); // ミリ秒を分に変換

    //! ファイルパスから拡張子を取得します。
    std::string GetFileExtension(const char* filepath); // ファイルパスから拡張子を取得

    //! オブジェクトの方向計算と回転更新を行います。
    float ObjectPointToDirection(FloatPos now_pos, FloatPos goal_pos, float dir, float rot_speed); // オブジェクトの方向計算と回転更新

    //! カメラの停止位置を計算します。
    void CameraStop(float pos_x, float pos_y, float w, float h, float& cam_x, float& cam_y); // カメラ停止位置計算

    //! 位置を矩形エリア内に制限します。
    void ClampPositionToArea(FloatPos& target_pos, int target_w, int target_h, float area_w, float area_h); // 位置を矩形エリア内に制限

    //! 浮動小数点座標の点と矩形の当たり判定を行います。
    bool CheckPointBoxHitF(const FloatPos& point, const FloatPos& pos, const FloatSize& size); // 浮動小数点座標の点と矩形の当たり判定

    //! 点と矩形の当たり判定を行います。
    bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h); // 点と矩形の当たり判定

    //! 矩形同士の当たり判定を行います。
    bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2); // 矩形同士の当たり判定

    //! 円同士の当たり判定を行います。
    bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2); // 円同士の当たり判定

    //! 点と円の当たり判定を行います。
    bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r); // 点と円の当たり判定

    //! 度をラジアンに変換します。
    float TORADIAN(float degree); // 度をラジアンに変換

    //! ラジアンを度に変換します。
    float TODEGREE(float radian); // ラジアンを度に変換

    //! 回転に沿った成分を取得します。
    float GetLengthAlongRotation(float rot); // 回転に沿った長さ取得

    //! 回転に対する直交成分を取得します。
    float GetLengthOppositeRotation(float rot); // 回転に対する直交成分取得
}
