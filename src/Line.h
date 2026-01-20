#pragma once
#include "Struct.h"

//---------------------------------------------------------------------------------
//	定数
//---------------------------------------------------------------------------------
const int   JUDGE_MAX	= 4;												//最大判定数
const int   UI_LINE_MAX = 2;												//UIのライン
const int   LINE_MAX	= 4;												//ライン数(幅の分割数)
const float ONE_LINE_W = (float)SCREEN_W / (float)(UI_LINE_MAX + LINE_MAX);	//1ラインの幅(少数点以下で細かく取得)
const float ONE_LINE_HALF_W = ONE_LINE_W / 2.0f;							//1ラインの半分の幅

//判定番号
enum
{
	PERFECT = 0,//0
	GOOD,		//1
	BAD,		//2
	MISS,		//3
};

//---------------------------------------------------------------------------------
//	関数
//---------------------------------------------------------------------------------
void Line_Init();	//初期化処理
void Line_Update();	//更新処理
void Line_Render(RGB ui_color);	//描画処理

//値を返すメンバ関数
int Line_Check_Button(int line_num);//入力キー

//---------------------------------------------------------------------------------
//	Line class
//　ラインと判定ラインを作成するクラス
//---------------------------------------------------------------------------------
class Line
{
public:
	//メンバ関数
	void Init(float pos_x, float pos_y, Box_F line_box, Box_F judge_line_box);	//初期化処理
	void Update(int notes_index, int key, int notes_type, int line);			//更新処理
	void Render(RGB ui_color);				//描画処理

	//デストラクタ

	//値を代入するメンバ関数
	void Set_Pos_(float x, float y);//座標
	void Set_Line_Size(float x, float y, float w, float h);//ラインサイズ
	void Set_Judge_Size(int index, float x, float y, float w, float h);//判定サイズ

	//値を返すメンバ関数
	Box_F Line_Box();			//ラインサイズ
	Box_F Judge_Line_Box();		//判定ラインサイズ
	Box_F Judge_Box(int index); //判定サイズ
	int Key();					//入力キー

private:
	//メンバ変数
	//座標
	Float_Pos pos_ = { 0 };

	//ラインサイズ
	Box_F line_box_ = { 0 };

	//判定ラインサイズ
	Box_F judge_line_box_ = { 0 };

	//判定サイズ
	Box_F judge_box_[JUDGE_MAX] = { 0 };

	//入力キー
	int key_ = 0;
};
