#pragma once
#include "Struct.h"

//	オブジェクト1をオブジェクト2の方向に向けてその角度を返す関数
float Object_Point_To_Direction(Float_Pos now_obj_1_pos, Float_Pos goal_obj_2_pos, float dir, const float ROT_SPEED);

//端まで行ったらカメラを止める
void Camera_Stop(float pos_x, float pos_y, float w, float h, float camera_x, float camera_y);

//	画像１を画像２の上下左右に外へ出ないようにする
void fRota_Clamp_image (Float_Pos& image_1, int& w_1, int& h_1, Float_Pos image_2, int w_2, int h_2);

//	画面の外に行かないようにする関数
void fRota_Clamp_Screen(Float_Pos& pos1, int& w_1, int& h_1, float& window_w, float& window_h);

//	点と四角の当たり判定
bool CheckPointBoxHit_F(Float_Pos& point, Float_Pos& pos, Float_Pos& size);

//	２点の長さを取得する関数
float GetDistance(float x1, float y1, float x2, float y2);

//	円同士の当たり判定
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2);

//	点と円の当たり判定
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r);

//	四角同士の当たり判定
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

//	点と四角の当たり判定
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h);

//	度をラジアンに変換する関数
float TO_RADIAN(float degree);

//	ラジアンを度に変換する関数
float TO_DEGREE(float radian);

//	長さ 1.0f の線を rot 分回転させたときに rot に沿っている分の長さを取得する関数
float GetLength_RotSotte(float rot);

//	長さ 1.0f の線を rot 分回転させたときに rot の向かいにある分の長さを取得する関数
float GetLength_RotMukai(float rot);
