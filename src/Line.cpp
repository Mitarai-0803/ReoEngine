#include "Main.h"
#include "Game.h"
#include "Struct.h"
#include "Function.h"
#include "Notes.h"
#include "Line.h"

//---------------------------------------------------------------------------------
//	ローカル変数
//---------------------------------------------------------------------------------
namespace
{
	//座標
	Float_Pos pos = {0};

	//ラインサイズ
	Box_F line_box = { 0 };

	//判定ラインサイズ
	Box_F judge_line_box = { 0 };

	//判定サイズ
	Box_F judge_box[JUDGE_MAX] = {0};

	//長押しノーツの座標
	Box_I long_notes_box[LINE_MAX];
}

//---------------------------------------------------------------------------------
//	インスタンスの生成
//---------------------------------------------------------------------------------
Line line[LINE_MAX];//ライン

//---------------------------------------------------------------------------------
//	関数
//---------------------------------------------------------------------------------
void Line_Init()//初期化処理
{
	//ラインサイズ
	line_box = { 0.0f,0.0f,ONE_LINE_W,SCREEN_H };

	//判定ラインサイズ
	judge_line_box = { 0, (SCREEN_H - 100) - 5,ONE_LINE_W, (SCREEN_H - 100) + 5 };

	//長押しノーツの座標
	for (int i = 0; i < LINE_MAX; i++)
	{
		long_notes_box[i] = {0,0,0,0};
	}

	//ライン数
	for (int i = 0; i < LINE_MAX; i++)
	{
		if (i == 2 || i == 3)
		{
			//座標
			pos = { (i + 2) * ONE_LINE_W,0.0f };
		}
		else
		{
			//座標
			pos = { i * ONE_LINE_W,0.0f };
		}

		//初期化
		line[i].Init(pos.x, pos.y, line_box, judge_line_box);

		//判定の四角座標
		//下の判定の左上の高さからどれだけ離れているかで当たり判定を取っている。
		line[i].Set_Judge_Size(PERFECT	, judge_line_box.x, judge_line_box.y - 30				, judge_line_box.w, judge_line_box.h + 10);		  //パーフェクト
		line[i].Set_Judge_Size(GOOD		, judge_line_box.x, line[i].Judge_Box(PERFECT).y - 30	, judge_line_box.w, line[i].Judge_Box(PERFECT).y);//グッド
		line[i].Set_Judge_Size(BAD		, judge_line_box.x, line[i].Judge_Box(GOOD).y - 30		, judge_line_box.w, line[i].Judge_Box(GOOD).y);	  //バッド
		line[i].Set_Judge_Size(MISS		, judge_line_box.x, line[i].Judge_Box(PERFECT).h		, judge_line_box.w, SCREEN_H);					  //ミス
	}
}

void Line_Update()//更新処理
{
	//長押しノーツの座標
	for (int i = 0; i < LINE_MAX; i++)
	{
		long_notes_box[i] = { 0,0,0,0 };
	}

	for (int i = 0; i < NOTES_MAX; i++)
	{
		Notets_Type();

		//それぞれにキー設定
		line[0].Update(i,KEY_INPUT_A,Notets_Type(),Line_Num());
		line[1].Update(i,KEY_INPUT_S,Notets_Type(),Line_Num());
		line[2].Update(i,KEY_INPUT_D,Notets_Type(),Line_Num());
		line[3].Update(i,KEY_INPUT_F,Notets_Type(),Line_Num());
	}
}

void Line_Render(RGB ui_color)//描画処理
{
	//ライン数
	for (int i = 0; i < LINE_MAX; i++)
	{
		line[i].Render(ui_color);
	}
}

//---------------------------------------------------------------------------------
//	値を返す関数
//---------------------------------------------------------------------------------
int Line_Check_Button(int line_num)//入力キー
{
	return line[line_num].Key();
}

//---------------------------------------------------------------------------------
//	メンバ関数
//---------------------------------------------------------------------------------
void Line::Init(float pos_x, float pos_y, Box_F line_box, Box_F judge_line_box)//初期化処理
{
	//座標
	pos_ = { pos_x,pos_y };

	//ラインサイズ
	line_box_ = { line_box };

	//判定ラインサイズ
	judge_line_box_ = judge_line_box;
}

void Line::Update(int notes_index, int key, int notes_type,int line)//更新処理
{
	//動くモードなら
	if (Notes_Mode(notes_index) == MOVE_MODE)
	{
		//ノーツタイプが長押しなら
		if (notes_type == LONG_NOTES)
		{
			//座標設定
			long_notes_box[line] = { ONE_LINE_HALF_W * line - NOTES_W,-NOTES_H,Notes_Pos_X(notes_index),Notes_Pos_Y(notes_index) };
		}

		//ノーツのY座標が判定ラインより上なら
		if (Notes_Pos_Y(notes_index) <= SCREEN_H)
		{
			//キーが押された時
			if (PushHitKey(key))
			{
				//ノーツと判定ライン(線)の当たり判定
				//ミス
				if (Check_Judge_Line(notes_index, pos_.x + judge_box_[3].x, pos_.y + judge_box_[3].y, judge_box_[3].w, judge_box_[3].h))
				{
					//ノーツの判定処理
					Notes_Judge(notes_index, MISS);
				}
				//パーフェクト
				else if (Check_Judge_Line(notes_index, pos_.x + judge_box_[0].x, pos_.y + judge_box_[0].y, judge_box_[0].w,  judge_box_[0].h))
				{
					//ノーツの判定処理
					Notes_Judge(notes_index, PERFECT);
				}
				//グッド
				else if (Check_Judge_Line(notes_index, pos_.x + judge_box_[1].x, pos_.y + judge_box_[1].y, judge_box_[1].w,judge_box_[1].h))
				{
					//ノーツの判定処理
					Notes_Judge(notes_index, GOOD);
				}
				//バッド
				else if (Check_Judge_Line(notes_index, pos_.x + judge_box_[2].x, pos_.y + judge_box_[2].y, judge_box_[2].w,judge_box_[2].h))
				{
					//ノーツの判定処理
					Notes_Judge(notes_index, BAD);
				}
			}
		}
		else
		{
			//ミス
			if (Check_Judge_Line(notes_index, pos_.x + judge_box_[3].x, pos_.y + judge_box_[3].y,  judge_box_[3].w, judge_box_[3].h))
			{
				//ノーツの判定処理
				Notes_Judge(notes_index, MISS);
			}
		}
	}

	//入力キーを取得
	key_ = key;
}

void Line::Render(RGB ui_color)//描画処理
{
	//===========================	デバッグ	==============================
	//DrawFillBox(pos_.x + judge_box_[3].x, pos_.y + judge_box_[3].y, pos_.x + judge_box_[3].w, pos_.y + judge_box_[3].h, GetColor(100, 100, 100));	//ミスライン(四角)の描画
	//DrawFillBox(pos_.x + judge_box_[2].x, pos_.y + judge_box_[2].y, pos_.x + judge_box_[2].w, pos_.y + judge_box_[2].h, GetColor(150, 255, 255));	//バッドライン(四角)の描画
	//DrawFillBox(pos_.x + judge_box_[1].x, pos_.y + judge_box_[1].y, pos_.x + judge_box_[1].w, pos_.y + judge_box_[1].h, GetColor(255, 255, 150));	//グッドライン(四角)の描画
	//DrawFillBox(pos_.x + judge_box_[0].x, pos_.y + judge_box_[0].y, pos_.x + judge_box_[0].w, pos_.y + judge_box_[0].h, GetColor(255, 150, 255));	//パーフェクトライン(四角)の描画

	//判定ライン(四角)の描画
	DrawBoxAA(pos_.x + judge_line_box_.x, pos_.y + judge_line_box_.y, pos_.x + judge_line_box_.w, pos_.y + judge_line_box_.h, GetColor(ui_color.r, ui_color.g, ui_color.b), true);

	//1ラインの四角の描画
	DrawBoxAA(pos_.x + line_box_.x, pos_.y + line_box_.y, pos_.x + line_box_.w, pos_.y + line_box_.h, GetColor(ui_color.r, ui_color.g, ui_color.b), false);
}

//---------------------------------------------------------------------------------
//	値を代入するメンバ関数
//---------------------------------------------------------------------------------
void Line::Set_Pos_(float x, float y)//座標
{
	pos_.x = x;
	pos_.y = y;
}

void Line::Set_Line_Size(float x, float y, float w, float h)//ラインサイズ
{
	line_box_ = { x,y,w,h };
}

void Line::Set_Judge_Size(int index, float x, float y, float w, float h)//判定サイズ
{
	//最大数-1以下なら
	if (index < JUDGE_MAX)
	{
		//値をセット
		judge_box_[index] = { x,y,w,h };
	}
}

//---------------------------------------------------------------------------------
//	値を返すメンバ関数
//---------------------------------------------------------------------------------
Box_F Line::Line_Box()//ラインサイズ
{
	return line_box_;
}

Box_F Line::Judge_Line_Box()//判定ラインサイズ
{
	return judge_line_box_;
}

Box_F Line::Judge_Box(int index)//判定サイズ
{
	return judge_box_[index];
}

int Line::Key()//入力キー
{
	return key_;
}