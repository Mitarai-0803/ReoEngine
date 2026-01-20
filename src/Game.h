#pragma once

#define SCREEN_W	1300
#define SCREEN_H	700

//定数
const int FPS = 60;//フレームレート

//ノーツタイプ
enum
{
	NORMAL_NOTES,	//普通ノーツ
	TWO_NOTES,		//同時押し
	LONG_NOTES		//長押し
};

//判定文字列の座標
const int JUDGE_STR_POS_X = 50;				//X座標
const int JUDGE_STR_POS_Y = SCREEN_H - 150;	//Y座標

//当たってるかを返す判定関数
bool Check_Judge_Line(int index, float judge_line_x, float judge_line_y, float judge_line_w, float judge_line_h);
//ノーツタイプを返す
int	Notets_Type();
//ライン番号を返す
int Line_Num();

//ドラッグ＆ドロップされたハンドルを返す関数
int Get_GrHandle();

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理 