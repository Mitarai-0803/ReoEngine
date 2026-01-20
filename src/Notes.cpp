#include "Main.h"
#include "Game.h"
#include "Font.h"
#include "Line.h"
#include "Image_Button.h"
#include "Notes.h"

//---------------------------------------------------------------------------------
//	ローカル変数
//---------------------------------------------------------------------------------
namespace
{
	//判定文字列を描画するフレーム数
	int judge_str_frame_num = 0;

	//判定番号
	int judge_num = 0;
}

//---------------------------------------------------------------------------------
//	インスタンスの生成
//---------------------------------------------------------------------------------
//ノーツ
Notes notes[NOTES_MAX];

//---------------------------------------------------------------------------------
//	関数
//---------------------------------------------------------------------------------
void Notes_Init()//初期化処理
{
	//判定文字列を描画するフレーム数の初期化
	judge_str_frame_num = 0;

	//判定番号
	judge_num = 0;

	for (int i = 0; i < NOTES_MAX; i++)
	{
		notes[i].Init();
	}
}

void Notes_Update()//更新処理
{
	//判定文字列を描画するフレーム数
	//何か0以外の値が入っているなら
	if (judge_str_frame_num != 0)
	{
		//カウントを減らす
		judge_str_frame_num--;
	}

	for (int i = 0; i < NOTES_MAX; i++)
	{
		notes[i].Update();
	}
}

void Notes_Render()//描画処理
{
	for (int i = 0; i < NOTES_MAX; i++)
	{
		notes[i].Render();
	}
}

void Notes_Exit()//終了処理
{
	for (int i = 0; i < NOTES_MAX; i++)
	{
		notes[i].~Notes();
	}
}

//ノーツの判定処理関数
void Notes_Judge(int index, int judge_mode)
{
	//フレーム数を設定
	judge_str_frame_num = 60;
	//判定番号を設定
	judge_num = judge_mode;

	//ノーツを上に戻す
	Notes_Set_Mode(RESET_MODE, index);
}

//---------------------------------------------------------------------------------
//	値を代入する関数
//---------------------------------------------------------------------------------
void Notes_Set_Pos_X(float pos_x, int index)//X座標の設定
{
	notes[index].Set_Pos_X(pos_x);
}

void Notes_Set_Pos_Y(float pos_y, int index)//Y座標の設定
{
	notes[index].Set_Pos_Y(pos_y);
}

void Notes_Set_Pos(float pos_x, float pos_y, int index)//座標の設定
{
	notes[index].Set_Pos(pos_x, pos_y);
}

void Notes_Set_Mode(int mode, int index)//モードの設定
{
	notes[index].Set_Mode(mode);
}

void Notes_Set_Speed(float speed, int index)//スピードの設定
{
	notes[index].Set_Speed(speed);
}

void Notes_Reset_Speed(int index)//スピードのリセット(デフォルト値に設定)
{
	notes[index].Reset_Speed();
}

void Notes_Set_Color(int index, int r, int g, int b)//ノーツの色を設定
{
	RGB color = { r, g, r };
	notes[index].Set_Color(color);
}

//---------------------------------------------------------------------------------
//	値を返す関数
//---------------------------------------------------------------------------------
float Notes_Pos_X(int index)//X座標
{
	return notes[index].Pos_X();
}

float Notes_Pos_Y(int index)//Y座標
{
	return notes[index].Pos_Y();
}

int Notes_Mode(int index)//モード
{
	return notes[index].Mode();
}

int Judge_Str_Frame_Num()//判定文字列を描画するフレーム数
{
	return judge_str_frame_num;
}

int Judge_Num()//判定番号
{
	return judge_num;
}
//---------------------------------------------------------------------------------
//	メンバ関数
//---------------------------------------------------------------------------------
void Notes::Init()//初期化処理
{
	//座標の設定
	pos_ = { ONE_LINE_HALF_W * 3.0f,-NOTES_H };

	//モードの設定(動かない状態)
	mode_ = STOP_MODE;

	//スピードの設定
	speed_ = NOTES_DEFAULT_SPEED;

	//色の設定
	color_ = { 0,255,0 };
}

void Notes::Update()//更新処理
{
	//モードごとの処理
	switch (mode_)
	{
	case MOVE_MODE://動く状態
		//下に移動させる
		pos_.y += speed_;
		//画面外に行ったら
		if (pos_.y - NOTES_W >= SCREEN_H)
		{
			//動かない状態にする
			mode_ = STOP_MODE;
		}
		break;

	case STOP_MODE://動かない状態
		//何もしない
		break;

	case RESET_MODE://上に戻す状態
		//座標を上に戻す
		pos_.y = -NOTES_W;
		//動かない状態にする
		mode_ = STOP_MODE;
		break;
	}
}

void Notes::Render()//描画処理
{
	//ノーツの描画
	DrawBoxAA(pos_.x - NOTES_W, pos_.y - NOTES_H, pos_.x + NOTES_W, pos_.y + NOTES_H, GetColor(color_.r, color_.g, color_.b), true);
}

Notes::~Notes()//デストラクタ
{
}

//---------------------------------------------------------------------------------
//	値を代入するメンバ関数
//---------------------------------------------------------------------------------
void Notes::Set_Pos_X(float pos_x)//X座標の設定
{
	pos_.x = pos_x;
}

void Notes::Set_Pos_Y(float pos_y)//Y座標の設定
{
	pos_.y = pos_y;
}

void Notes::Set_Pos(float pos_x, float pos_y)//座標の設定
{
	pos_ = { pos_x,pos_y };
}

void Notes::Set_Mode(int mode)//モードの設定
{
	mode_ = mode;
}

void Notes::Set_Speed(float speed)//スピードの設定
{
	speed_ = speed;
}

void Notes::Reset_Speed()//スピードのリセット(デフォルト値に設定)
{
	speed_ = NOTES_DEFAULT_SPEED;
}

void Notes::Set_Color(RGB color)//ノーツの色を設定
{
	color_ = color;
}

//---------------------------------------------------------------------------------
//	値を返すメンバ関数
//---------------------------------------------------------------------------------
float Notes::Pos_X()//X座標
{
	return pos_.x;
}

float Notes::Pos_Y()//Y座標
{
	return pos_.y;
}

int Notes::Mode()//モード
{
	return mode_;
}
