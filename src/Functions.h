#pragma once
//============================================================================
//! @file   Functions.h
//! @brief  ユーティリティ関数群の宣言
//! @author レオ
//============================================================================
#include "DxMain.h"
#include <string>
#include <numbers>
#include <math.h>
#include <algorithm>
#include "hlsl++.h"
using namespace hlslpp;
using namespace std;

namespace MyLibrary {
//---------------------------------------------------------------
//! @brief ミリ秒を秒に変換
//! @param  [in]     milli      ミリ秒
//! @return               秒表記の浮動小数点値
//---------------------------------------------------------------
float ConvertMilliToSec(int milli);

//---------------------------------------------------------------
//! @brief ミリ秒を分に変換
//! @param  [in]     milli      ミリ秒
//! @return               分表記の浮動小数点値
//---------------------------------------------------------------
float ConvertMilliToMinute(int milli);

//---------------------------------------------------------------
//! @brief ファイルパスから拡張子を取得
//! @param  [in]     filepath   ファイルパス（nullptr可）
//! @return               拡張子文字列（見つからない場合は空文字）
//---------------------------------------------------------------
std::string GetFileExtension(const char* filepath);

//---------------------------------------------------------------
//! @brief オブジェクトの向き（ラジアン）を求める（回転補間あり）
//! @param  [in]     now_pos    現在位置
//! @param  [in]     goal_pos   目標位置
//! @param  [in]     dir        現在の角度（ラジアン）
//! @param  [in]     rot_speed  回転速度（度/フレーム）
//! @return               移動後の向き（ラジアン）
//---------------------------------------------------------------
float ObjectPointToDirection(float2 now_pos, float2 goal_pos, float dir, float rot_speed);

//---------------------------------------------------------------
//! @brief カメラの停止制御（指定範囲外ではスクロールしない）
//! @param  [in]     pos_x      対象 X 座標
//! @param  [in]     pos_y      対象 Y 座標
//! @param  [in]     w          対象幅
//! @param  [in]     h          対象高さ
//! @param  [in,out] cam_x      カメラ X（参照で更新）
//! @param  [in,out] cam_y      カメラ Y（参照で更新）
//---------------------------------------------------------------
void CameraStop(float pos_x, float pos_y, float w, float h, float& cam_x, float& cam_y);

//---------------------------------------------------------------
//! @brief 位置を指定エリア内に制限します
//! @param  [in,out] target_pos  対象位置（参照で更新）
//! @param  [in]     target_w    対象幅
//! @param  [in]     target_h    対象高さ
//! @param  [in]     area_w      エリア幅
//! @param  [in]     area_h      エリア高さ
//---------------------------------------------------------------
void ClampPositionToArea(float2& target_pos, int target_w, int target_h, float area_w, float area_h);

//---------------------------------------------------------------
//! @brief 点と矩形の当たり判定（浮動小数）
//! @param  [in]     point      判定点
//! @param  [in]     pos        矩形左上位置
//! @param  [in]     size       矩形サイズ
//! @return               当たっていれば true
//---------------------------------------------------------------
bool CheckPointBoxHitF(const float2& point, const float2& pos, const float2& size);

//---------------------------------------------------------------
//! @brief 点と矩形の当たり判定（座標指定）
//! @param  [in]     point_x    点の X
//! @param  [in]     point_y    点の Y
//! @param  [in]     box_x      矩形左上 X
//! @param  [in]     box_y      矩形左上 Y
//! @param  [in]     box_w      矩形幅
//! @param  [in]     box_h      矩形高
//! @return               当たっていれば true
//---------------------------------------------------------------
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h);

//---------------------------------------------------------------
//! @brief 矩形同士の当たり判定
//! @param  [in]     x1          矩形1の左上 X
//! @param  [in]     y1          矩形1の左上 Y
//! @param  [in]     w1          矩形1の幅
//! @param  [in]     h1          矩形1の高さ
//! @param  [in]     x2          矩形2の左上 X
//! @param  [in]     y2          矩形2の左上 Y
//! @param  [in]     w2          矩形2の幅
//! @param  [in]     h2          矩形2の高さ
//! @return               当たっていれば true
//---------------------------------------------------------------
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

//---------------------------------------------------------------
//! @brief 円同士の当たり判定
//! @param  [in]     x1          円1の中心 X
//! @param  [in]     y1          円1の中心 Y
//! @param  [in]     r1          円1の半径
//! @param  [in]     x2          円2の中心 X
//! @param  [in]     y2          円2の中心 Y
//! @param  [in]     r2          円2の半径
//! @return               当たっていれば true
//---------------------------------------------------------------
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2);

//---------------------------------------------------------------
//! @brief 点と円の当たり判定
//! @param  [in]     point_x    点の X
//! @param  [in]     point_y    点の Y
//! @param  [in]     circle_x    円の中心 X
//! @param  [in]     circle_y    円の中心 Y
//! @param  [in]     circle_r    円の半径
//! @return               当たっていれば true
//---------------------------------------------------------------
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r);

//---------------------------------------------------------------
//! @brief 円を描画（XZ平面）
//! @param  [in]     center     中心位置
//! @param  [in]     radius     半径
//! @param  [in]     color      色
//! @param  [in]     fill       塗りつぶしフラグ
//---------------------------------------------------------------
void DrawCircle3D_XZ(float3 center, float radius, int color, bool fill = false);

//---------------------------------------------------------------
//! @brief 矩形を描画（XZ方向）
//! @param  [in]     center     中心位置
//! @param  [in]     half_w     半分の幅
//! @param  [in]     half_h     半分の高さ
//! @param  [in]     color      色
//! @param  [in]     fill       塗りつぶしフラグ
//---------------------------------------------------------------
void DrawBox3D_XZ(float3 center, float half_w, float half_h, int color, bool fill = false);

//-----------------------------------------------------------
//! @brief XZ 平面上の円同士の当たり判定を行なう
//! @param  [in] center1  円 1 の中心位置
//! @param  [in] radius1  円 1 の半径
//! @param  [in] center2  円 2 の中心位置
//! @param  [in] radius2  円 2 の半径
//! @return 当たっていれば true
//-----------------------------------------------------------
bool CheckCircleXZHit(float3& center1, float radius1, float3& center2, float radius2);

//-----------------------------------------------------------
//! @brief 球同士の当たり判定を行なう
//! @param  [in] center1  球 1 の中心位置
//! @param  [in] radius1  球 1 の半径
//! @param  [in] center2  球 2 の中心位置
//! @param  [in] radius2  球 2 の半径
//! @return 当たっていれば true
//-----------------------------------------------------------
bool CheckBallHit(float3& center1, float radius1, float3& center2, float radius2);

//-----------------------------------------------------------
//! @brief 3D の AABB 同士の当たり判定を行なう
//! @param  [in] box_pos1  ボックス 1 の中心位置
//! @param  [in] box_size1 ボックス 1 の半サイズ
//! @param  [in] box_pos2  ボックス 2 の中心位置
//! @param  [in] box_size2 ボックス 2 の半サイズ
//! @return 当たっていれば true
//-----------------------------------------------------------
bool CheckBoxHit3D(float3& box_pos1, float3& box_size1, float3& box_pos2, float3& box_size2);

//-----------------------------------------------------------
//! @brief 点と 3D ボックスの当たり判定を行なう
//! @param  [in] point    判定対象の点
//! @param  [in] box_pos  ボックスの中心位置
//! @param  [in] box_size ボックスの半サイズ
//! @return               当たっていれば true
//-----------------------------------------------------------
bool CheckPointBoxHit3D(float3& point, float3& box_pos, float3& box_size);

//-----------------------------------------------------------
//! @brief 球と AABB（ボックス）の当たり判定を行なう
//! @param  [in] ball_pos   球の中心位置
//! @param  [in] ball_radius 球の半径
//! @param  [in] box_pos    ボックスの中心位置
//! @param  [in] box_size  ボックスの半サイズ
//! @return               当たっていれば true
//-----------------------------------------------------------
bool CheckBallBoxHit(float3& ball_pos, float ball_radius, float3& box_pos, float3& box_size);

//-----------------------------------------------------------
//! @brief 線分と点の最近接位置を取得します（3D）
//! @param  [in] line_start  線分の開始位置
//! @param  [in] line_goal   線分の終了位置
//! @param  [in] point       判定対象の点
//! @return                線分上の最近接位置（float3）
//-----------------------------------------------------------
float3 GetFloat3LinePointNearPosition(float3& line_start, float3& line_goal, float3& point);

//-----------------------------------------------------------
//! @brief 線分と点の最近接距離を返す（3D）
//! @param  [in] line_start  線分の開始位置
//! @param  [in] line_goal   線分の終了位置
//! @param  [in] point       判定対象の点
//! @return                最近接距離
//-----------------------------------------------------------
float GetFloat3LinePointNearDistance(float3& line_start, float3& line_goal, float3& point);

//-----------------------------------------------------------
//! @brief 線分と球の当たり判定を行なう（3D）
//! @param  [in] line_start  線分の開始位置
//! @param  [in] line_goal   線分の終了位置
//! @param  [in] ball_pos    球の中心位置
//! @param  [in] ball_radius 球の半径
//! @return                当たっていれば true
//-----------------------------------------------------------
bool CheckLineBallHit(float3& line_start, float3& line_goal, float3& ball_pos, float ball_radius);

//-----------------------------------------------------------
//! @brief ２つの float2 の距離を求める
//! @param  [in] pos1  1つ目の座標
//! @param  [in] pos2  2つ目の座標
//! @return            2点間の距離
//! @note              戻り値は float 型
//-----------------------------------------------------------
float GetFloat2Distance(float2& pos1, float2& pos2);

//-----------------------------------------------------------
//! @brief ２つの float2 の内積を求める
//! @param  [in] v1  1つ目のベクトル
//! @param  [in] v2  2つ目のベクトル
//! @return          内積（float）
//-----------------------------------------------------------
float GetFloat2Dot(float2& v1, float2& v2);

//-----------------------------------------------------------
//! @brief ２つの float2 の外積を求める
//! @param  [in] v1  1つ目のベクトル
//! @param  [in] v2  2つ目のベクトル
//! @return          外積（スカラー）
//-----------------------------------------------------------
float GetFloat2Cross(float2& v1, float2& v2);

//-----------------------------------------------------------
//! @brief ２つの float3 の距離を求める
//! @param  [in] pos1  1つ目の座標
//! @param  [in] pos2  2つ目の座標
//! @return            2点間の距離（float）
//-----------------------------------------------------------
float GetFloat3Distance(float3& pos1, float3& pos2);

//-----------------------------------------------------------
//! @brief ２つの float3 の内積を求める
//! @param  [in] v1  1つ目のベクトル
//! @param  [in] v2  2つ目のベクトル
//! @return          内積（float）
//-----------------------------------------------------------
float GetFloat3Dot(float3& v1, float3& v2);

//-----------------------------------------------------------
//! @brief ２つの float3 の外積を求める
//! @param  [in] v1  1つ目のベクトル
//! @param  [in] v2  2つ目のベクトル
//! @return          外積（float3）
//-----------------------------------------------------------
float3 GetFloat3Cross(float3& v1, float3& v2);

//-----------------------------------------------------------
//! @brief float3 を MATRIX で変換した float3 を返す
//! @param  [in] v    変換するベクトル
//! @param  [in] mat  変換行列
//! @return          変換後の float3
//-----------------------------------------------------------
float3 GetFloat3VTransform(float3& v, MATRIX& mat);

//-----------------------------------------------------------
//! @brief 平面上の円同士の当たり判定を行なう（float2 版）
//-----------------------------------------------------------
bool CheckCircleHit(float2& center1, float radius1, float2& center2, float radius2);

//-----------------------------------------------------------
//! @brief 点と円の当たり判定を行なう（float2 版）
//-----------------------------------------------------------
bool CheckPointCircleHit(float2& point, float2& center, float radius);

//-----------------------------------------------------------
//! @brief 四角同士の当たり判定を行なう（float2 版）
//-----------------------------------------------------------
bool CheckBoxHit(float2& box_pos1, float2& box_size1, float2& box_pos2, float2& box_size2);

//-----------------------------------------------------------
//! @brief 点と四角の当たり判定を行なう（float2 版）
//-----------------------------------------------------------
bool CheckPointBoxHit(float2& point, float2& box_pos, float2& box_size);

//-----------------------------------------------------------
//! @brief 円と四角の当たり判定を行なう（float2 版）
//-----------------------------------------------------------
bool CheckCircleBoxHit(float2& circle, float radius, float2& box_pos, float2& box_size);

//-----------------------------------------------------------
//! @brief 点と三角形の当たり判定を行なう（2D）
//-----------------------------------------------------------
bool CheckPointTriangleHit(float2& point, float2& triangle_pos1, float2& triangle_pos2, float2& triangle_pos3);

//-----------------------------------------------------------
//! @brief 線分と点の最近接位置を取得します（2D）
//-----------------------------------------------------------
float2 GetFloat2LinePointNearPosition(float2& line_start, float2& line_goal, float2& point);

//-----------------------------------------------------------
//! @brief 線分と点の最近接距離を返す（2D）
//-----------------------------------------------------------
float GetFloat2LinePointNearDistance(float2& line_start, float2& line_goal, float2& point);

//-----------------------------------------------------------
//! @brief 線分と円の当たり判定を行なう（2D）
//-----------------------------------------------------------
bool CheckLineCircleHit(float2& line_start, float2& line_goal, float2& circle_pos, float circle_radius);

//-----------------------------------------------------------
//! @brief 2 点間の距離を返す
//! @param  [in] x1   点1 の X 座標
//! @param  [in] y1   点1 の Y 座標
//! @param  [in] x2   点2 の X 座標
//! @param  [in] y2   点2 の Y 座標
//! @return          2 点間の距離（float）
//-----------------------------------------------------------
float GetDistance(float x1, float y1, float x2, float y2);

//-----------------------------------------------------------
//! @brief 四角同士の当たり判定を行なう（float 版）
//-----------------------------------------------------------
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

//-----------------------------------------------------------
//! @brief 点と四角の当たり判定を行なう（float 版）
//-----------------------------------------------------------
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h);

//-----------------------------------------------------------
//! @brief 円と四角の当たり判定を行う（float 版）
//-----------------------------------------------------------
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h);

//---------------------------------------------------------------
//! @brief ２つの float2 の距離を求める
//! @param  [in]     pos1       位置1
//! @param  [in]     pos2       位置2
//! @return               距離
//---------------------------------------------------------------
float GetFloat2Distance(float2& pos1, float2& pos2);

//---------------------------------------------------------------
//! @brief ２つの float2 の内積を求める
//! @param  [in]     v1        ベクトル1
//! @param  [in]     v2        ベクトル2
//! @return               内積
//---------------------------------------------------------------
float GetFloat2Dot(float2& v1, float2& v2);

//---------------------------------------------------------------
//! @brief ２つの float2 の外積を求める
//! @param  [in]     v1        ベクトル1
//! @param  [in]     v2        ベクトル2
//! @return               外積
//---------------------------------------------------------------
float GetFloat2Cross(float2& v1, float2& v2);

//-----------------------------------------------------------
//! @brief ２つの float3 の距離を求める
//! @param  [in] pos1  1つ目の座標
//! @param  [in] pos2  2つ目の座標
//! @return            2点間の距離
//-----------------------------------------------------------
float GetFloat3Distance(float3& pos1, float3& pos2);

//-----------------------------------------------------------
//! @brief ２つの float3 の内積を求める
//! @param  [in] v1  1つ目のベクトル
//! @param  [in] v2  2つ目のベクトル
//! @return          内積
//-----------------------------------------------------------
float GetFloat3Dot(float3& v1, float3& v2);

//-----------------------------------------------------------
//! @brief ２つの float3 の外積を求める
//! @param  [in] v1  1つ目のベクトル
//! @param  [in] v2  2つ目のベクトル
//! @return          外積（ベクトル）
//-----------------------------------------------------------
float3 GetFloat3Cross(float3& v1, float3& v2);

//-----------------------------------------------------------
//! @brief float3 を MATRIX で変換した float3 を返す
//! @param  [in] v    変換するベクトル
//! @param  [in] mat  変換行列
//! @return          変換後の float3
//-----------------------------------------------------------
float3 GetFloat3VTransform(float3& v, MATRIX& mat);

//---------------------------------------------------------------
//! @brief 度をラジアンに変換
//! @param  [in]     degree     度
//! @return               ラジアン
//---------------------------------------------------------------
float TORADIAN(float degree);

//---------------------------------------------------------------
//! ラジアンを度に変換
//! @param  [in]     radian     ラジアン
//! @return               度
//---------------------------------------------------------------
float TODEGREE(float radian);

//---------------------------------------------------------------
//! @brief 正規化
//! @param  [in]     vec        正規化するベクトル
//! @return               正規化後のベクトル
//---------------------------------------------------------------
float2 Normalize(const float2& vec);

//---------------------------------------------------------------
//! @brief 正規化
//! @param  [in]     vec        正規化するベクトル
//! @return               正規化後のベクトル
//---------------------------------------------------------------
float3 Normalize(const float3& vec);

//---------------------------------------------------------------
//! 回転に沿った長さ（cos）を取得
//! @param  [in]     rot        回転（ラジアン）
//! @return               cos(rot)
//---------------------------------------------------------------
float GetLengthAlongRotation(float rot);

//---------------------------------------------------------------
//! 回転に垂直な長さ（sin）を取得
//! @param  [in]     rot        回転（ラジアン）
//! @return               sin(rot)
//---------------------------------------------------------------
float GetLengthOppositeRotation(float rot);

}    // namespace MyLibrary
