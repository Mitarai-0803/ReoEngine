#include "Main.h"
#include "Game.h"
#include "Struct.h"
#include "Function.h"

//---------------------------------------------------------------------------------
//	繰り返し使う・使える関数
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//	オブジェクト1をオブジェクト2の方向に向けてその角度を返す関数
//---------------------------------------------------------------------------------
float Object_Point_To_Direction(Float_Pos now_obj_1_pos, Float_Pos goal_obj_2_pos, float dir, const float ROT_SPEED)
{
	//角度変数
	float now_dir = TO_DEGREE(dir);

	//マークの向きをだんだん変えていく
	//１：今の座標(now_obj_1_pos)から目標座標(goal_obj_2_pos)への角度を求める
	
	//１－１：今の座標から目標座標までどのくらいか
	float x = goal_obj_2_pos.x - now_obj_1_pos.x;
	float y = goal_obj_2_pos.y - now_obj_1_pos.y;

	//１－２：その値を使って角度を求める(この角度が最終的に向きたい角度)
	//		(float2f)ラジアン角を返す関数なので｢度｣に変換する
	float goal_rot = TO_DEGREE(atan2f(y, x)) + 90.0f;

	//２：今の角度(now_dir)から目標の角度(goal_rot)までどのくらいの差があるか
	float next_rot = goal_rot - now_dir;

	//２－１：上で求めた角度の差を-180～180にしたい
	//		 １８０度を超えていたら１週分(360度)引く
	while (next_rot >= 180.0f) next_rot -= 360.0f;
	//		-１８０度を超えていたら１週分(360度)足す
	while (next_rot < -180.0f) next_rot += 360.0f;

	//３：その差のほうへ回転させる(プラスなら右回転・マイナスなら左回転)
	if (next_rot > 0.0f)now_dir += ROT_SPEED;
	if (next_rot < 0.0f)now_dir -= ROT_SPEED;
	//上の処理だと目標の角度の付近を行ったり来たりしてしまう
	if (next_rot >= ROT_SPEED)			//角度の差がプラス方向に回転スピード以上だったら
	{
		now_dir += ROT_SPEED;			//プレス回転させる
	}
	else if (next_rot <= -ROT_SPEED)	//差が回転スピードよりもさらにマイナスだったら
	{
		now_dir -= ROT_SPEED;			//マイナス回転させる
	}
	else								//じゃなかったら(ほぼ正面の時は)
	{
		now_dir = goal_rot;				//目標の角度にする
	}

	return TO_RADIAN(now_dir);
}

//---------------------------------------------------------------------------------
//	//端まで行ったらカメラを止める
//---------------------------------------------------------------------------------
//端まで行ったらカメラを止める
void Camera_Stop(float pos_x, float pos_y, float w, float h, float camera_x, float camera_y)
{
	//端じゃなければカメラを動かす
	if (pos_x > SCREEN_W / 2.0f && pos_x < w - (SCREEN_W / 2.0f))//横
	{
		camera_x = SCREEN_W / 2.0f - pos_x;//カメラを動かす
	}

	if (pos_y > SCREEN_H / 2.0f && pos_y < h - (SCREEN_H / 2.0f))//縦
	{
		camera_y = SCREEN_H / 2.0f - pos_y;//カメラを動かす
	}
}

//---------------------------------------------------------------------------------
//	//画像１を画像２の上下左右に外へ出ないようにする(中心座標で画像サイズ)
//---------------------------------------------------------------------------------
void fRota_Clamp_image(Float_Pos& image_1, int& w_1, int& h_1, Float_Pos image_2, int w_2, int h_2)
{
	// pos1をPos2の外へ行かないようにする
	if (image_1.x < 0.0f + (w_1 / 2.0f))	// 左端を越えないようにする
		image_1.x = 0.0f + (w_1 / 2.0f);

	if (image_1.x > w_2 - (w_1 / 2.0f))	// 右端を越えないようにする
		image_1.x = w_2 - (w_1 / 2.0f);

	if (image_1.y < 0.0f + (h_1 / 2.0f))	// 上端を越えないようにする
		image_1.y = 0.0f + (h_1 / 2.0f);

	if (image_1.y > h_2 - (h_1 / 2.0f))	// 下端を越えないようにする
		image_1.y = h_2 - (h_1 / 2.0f);
}

//---------------------------------------------------------------------------------
//	//画面の外に行かないようにする関数(中心座標)
//---------------------------------------------------------------------------------
void fRota_Clamp_Screen(Float_Pos& pos1, int& w_1, int& h_1, float& window_w, float& window_h)
{
	// pos1を画面の外へ行かないようにする
	if (pos1.x < 0.0f + (w_1 / 2.0f)) // 左端を越えないようにする
		pos1.x = 0.0f + (w_1 / 2.0f);

	if (pos1.x > window_w - (w_1 / 2.0f)) // 右端を越えないようにする
		pos1.x = window_w - (w_1 / 2.0f);

	if (pos1.y < 0.0f + (h_1 / 2.0f)) // 上端を越えないようにする
		pos1.y = 0.0f + (h_1 / 2.0f);

	if (pos1.y > window_h - (h_1 / 2.0f)) // 下端を越えないようにする	
		pos1.y = window_h - (h_1 / 2.0f);
}


//---------------------------------------------------------------------------------
//	点と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointBoxHit_F(Float_Pos& point, Float_Pos& pos, Float_Pos& size)
{
	if (point.x >= pos.x && point.x <= pos.x + size.x)
	{
		if (point.y >= pos.y && point.y <= pos.y + size.y)
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	２点の長さを取得する関数
//---------------------------------------------------------------------------------
float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float distance = sqrtf(x * x + y * y);
	return distance;
}

//---------------------------------------------------------------------------------
//	円同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float distance = GetDistance(x1, y1, x2, y2);
	float radius = r1 + r2;
	if (distance <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と円の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r)
{
	float distance = GetDistance(point_x, point_y, circle_x, circle_y);
	if (distance <= circle_r) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	四角同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (x1 + w1 >= x2 && x1 <= x2 + w2) {
		if (y1 + h1 >= y2 && y1 <= y2 + h2) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h)
{
	if (point_x >= box_x && point_x <= box_x + box_w) {
		if (point_y >= box_y && point_y <= box_y + box_h) {
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------
//	度をラジアンに変換する関数
//---------------------------------------------------------------------------------
float TO_RADIAN(float degree)
{
	return degree * 3.14159265f / 180.0f;
}

//---------------------------------------------------------------------------------
//	ラジアンを度に変換する関数
//---------------------------------------------------------------------------------
float TO_DEGREE(float radian)
{
	return radian * 180.0f / 3.14159265f;
}

//---------------------------------------------------------------------------------
//	長さ 1.0f の線を rot 分回転させたときに rot に沿っている分の長さを取得する関数
//---------------------------------------------------------------------------------
float GetLength_RotSotte(float rot)
{
	//	cos（コサイン）関数です
	return cosf(rot);
}

//---------------------------------------------------------------------------------
//	長さ 1.0f の線を rot 分回転させたときに rot の向かいにある分の長さを取得する関数
//---------------------------------------------------------------------------------
float GetLength_RotMukai(float rot)
{
	//	sin（サイン）関数です
	return sinf(rot);
}
