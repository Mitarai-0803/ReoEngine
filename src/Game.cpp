#include "Font.h"
#include "Function.h"
#include "Game.h"
#include "Image_Button.h"
#include "Main.h"
#include "Notes.h"
#include "Line.h"

#define BUFFERLENGTH 14
#define SOUNDLENGTH	100

namespace
{
	//音量
	int volume = 100;

	//画像番号用変数
	int GrHandle = 0;

	//流すかどうか 1=流す 0=流さない
	int music_num = 1;

	//文字列の長さ(幅)
	int str_w = 0;

	//フレーム数カウント用変数
	int frame_count = 0;

	//UIの色変数
	RGB ui_color;

	//文字列の色変数
	RGB str_color;

	//スコア
	int score = 0;

	//背景画像
	int bg_image = 0;

	//ノーツ番号
	int notes_index = 0;

	//ノーツタイプ番号
	int notes_type = 0;

	//音源の再生時間
	int music_play_time = 0;

	//判定文字列座標
	Int_Pos judge_str_pos = { 0 };

	//ライン番号
	int line_num = 0;

	//サウンドビジュアライザー関係の変数
	Int_Pos sound_visualizer_pos;
	int SoundHandle;
	int SoftSoundHandle;
	float ParamList[BUFFERLENGTH];
	int SamplePos;

	//何回目のノーツか
	int notes_num = 0;
}

//判定に当たってるかを返す判定関数
bool Check_Judge_Line(int index, float judge_line_x, float judge_line_y, float judge_line_w, float judge_line_h)
{
	//ノーツと判定ライン(線)の当たり判定
	if (CheckBoxHit(judge_line_x, judge_line_y, judge_line_w, judge_line_h,
		Notes_Pos_X(index) - NOTES_W, Notes_Pos_Y(index) - NOTES_H, NOTES_W, NOTES_H))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//判定文字列の描画関数
void Judge_String_Render()
{
	//判定文字列を描画するフレーム数が0以外の値が入っているなら
	if (Judge_Str_Frame_Num() != 0)
	{
		//判定番号によって出す文字列を変える処理
		switch (Judge_Num())
		{
		case PERFECT:
			DrawStringToHandle(JUDGE_STR_POS_X, JUDGE_STR_POS_Y, "PERFECT", GetColor(255, 150, 255), GetFont(2));
			break;

		case GOOD:
			DrawStringToHandle(JUDGE_STR_POS_X, JUDGE_STR_POS_Y, "GOOD", GetColor(255, 255, 150), GetFont(2));
			break;

		case BAD:
			DrawStringToHandle(JUDGE_STR_POS_X, JUDGE_STR_POS_Y, "BAD", GetColor(150, 255, 255), GetFont(2);
			break;

		case MISS:
			DrawStringToHandle(JUDGE_STR_POS_X, JUDGE_STR_POS_Y, "MISS", GetColor(155, 155, 155), GetFont(2));
			break;
		}
	}
}

//流す位置を変える関数
void Line_Change()
{
	//ライン番号によって流す位置を変える
	switch (line_num)
	{
		//座標の設定
	case 0://左
		Notes_Set_Pos_X(ONE_LINE_HALF_W, notes_index);
		break;

	case 1://中左
		Notes_Set_Pos_X(ONE_LINE_HALF_W * 3.0f, notes_index);
		break;

	case 2://中右
		Notes_Set_Pos_X(ONE_LINE_HALF_W * 9.0f, notes_index);
		break;

	case 3://右
		Notes_Set_Pos_X(ONE_LINE_HALF_W * 11.0f, notes_index);
		break;
	}
}

//ノーツタイプを返す
int Notets_Type()
{
	return notes_type;
}

//ライン番号を返す
int Line_Num()
{
	return line_num;
}

//ライン番号を入れるとその列の入力キーを返す関数
int Line_Check_Key(int line)
{
	return Line_Check_Button(line);
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	// ファイルのドラッグ＆ドロップを許可する
	SetDragFileValidFlag(TRUE);

	//フォント
	FontInit();

	//ノーツの初期化処理
	Notes_Init();

	//UIの色変数
	ui_color = { 196, 98, 118 };

	//文字列の色変数
	str_color = { 255, 255, 255 };

	//ライン初期化処理
	Line_Init();

	//背景画像
	//bg_image = LoadGraph("Music_data/AKAGE/maxresdefault.jpg");

	//判定の四角座標
	Box_I box_pos[JUDGE_MAX] = { 0 };

	// サウンドファイルをソフトサウンドハンドルとして読み込み
	SoftSoundHandle = LoadSoftSound("data/Oh.ogg");

	// ソフトサウンドハンドルからサウンドハンドルを作成
	SoundHandle = LoadSoundMemFromSoftSound(SoftSoundHandle);

	// サウンドの再生開始
	PlaySoundMem(SoundHandle, DX_PLAYTYPE_LOOP);

	//音量の設定
	ChangeVolumeSoundMem(60, SoundHandle);

	//サウンドビジュアライザーの座標
	sound_visualizer_pos = { (3 * (int)ONE_LINE_W),130 };
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	// 現在の再生位置を取得
	SamplePos = GetCurrentPositionSoundMem(SoundHandle);

	// サウンドハンドルの音の総時間を取得する(単位はミリ秒)
	//int GetSoundTotalTime(int SoundHandle);

	// 現在の再生位置から 4096 サンプルを使用して周波数分布を得る
	GetFFTVibrationSoftSound(SoftSoundHandle, -1, SamplePos, 4096, ParamList, BUFFERLENGTH);

	//フレームのカウント
	frame_count++;

	//ノーツの更新処理
	Notes_Update();

	//判定文字列座標
	judge_str_pos = { 0 };

	//右キーが押された時
	if (PushHitKey(KEY_INPUT_LEFT))
	{
		line_num--;
	}

	//左キーが押された時
	if (PushHitKey(KEY_INPUT_RIGHT))
	{
		line_num++;
	}

	//上キーが押された時
	if (PushHitKey(KEY_INPUT_UP))
	{
		notes_type++;
	}

	//下キーが押された時
	if (PushHitKey(KEY_INPUT_DOWN))
	{
		notes_type--;
	}

	//フレームのカウントが60になったら
	if (frame_count % 60 == 0)
	{
		//次のノーツを流す
		notes_index++;

		//ノーツ番号が最大値なら
		if (notes_index >= NOTES_MAX - 1)
		{
			//ノーツ番号を0リセット
			notes_index = 0;
		}

		//ノーツのタイプ番号によって処理を変える
		switch (notes_type)
		{
		case NORMAL_NOTES://普通ノーツ
			//色を設定
			Notes_Set_Color(notes_index, 0, 255, 0);
			break;

		case TWO_NOTES://同時押し
			//色を設定
			Notes_Set_Color(notes_index, 0, 255, 255);

			//ライン番号によって流す位置を変える
			line_num = 3;
			Line_Change();

			//ノーツのモードを動く状態にする
			Notes_Set_Mode(MOVE_MODE, notes_index);

			//ノーツの流す位置を変更
			line_num = 0;

			//次のノーツを流す
			notes_index++;

			//ノーツ番号が最大値なら
			if (notes_index > NOTES_MAX)
			{
				//ノーツ番号を0リセット
				notes_index = 0;
			}
			break;

		case LONG_NOTES://長押し
			//色を設定
			Notes_Set_Color(notes_index, 255, 100, 100);

			//1回目なら
			if (notes_num == 0)
			{
				notes_num = 1;
			}
			//2回目なら
			else if (notes_num == 1)
			{
				//そのラインのボタンが押されている状態
				if (Line_Check_Key(line_num))
				{
					notes_num = 0;
				}
			}
		}

		//ライン番号によって流す位置を変える
		Line_Change();

		//ノーツのモードを動く状態にする
		Notes_Set_Mode(MOVE_MODE, notes_index);
	}

	//ラインの更新処理
	Line_Update();
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//===========================	UI	==============================
	//背景の四角の描画
	DrawFillBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255));

	//===========================	デバッグ	==============================

	//今の流すライン番号
	DrawFormatStringToHandle(0, 0, GetColor(0, 0, 0), font_handle[4], "今の流すライン番号:%d", line_num);
	//今のノーツタイプ番号
	DrawFormatStringToHandle(0, 30, GetColor(0, 0, 0), font_handle[4], "今のノーツタイプ番号:%d", notes_type);

	//===========================	UI	==============================
	//ラインの更新処理
	Line_Render(ui_color);

	//判定文字列の描画
	Judge_String_Render();

	//ノーツの描画処理
	Notes_Render();

	//UI用の四角の描画
	DrawBoxAA(2.0f * ONE_LINE_W, 0, 4.0f * ONE_LINE_W, SCREEN_H, GetColor(ui_color.r, ui_color.g, ui_color.b), true);

	//スコア文字列の描画
	str_w = GetDrawFormatStringWidthToHandle(font_handle[2], "%d", score);
	DrawFormatStringToHandle(SCREEN_W / 2 - str_w / 2, SCREEN_H - 140, GetColor(str_color.r, str_color.g, str_color.b), font_handle[2], "%d", score);

	//音源の再生秒数
	str_w = GetDrawFormatStringWidthToHandle(font_handle[1], "%02d：%02d", (frame_count / 60) / 60, (frame_count / 60) % 60);
	DrawFormatStringToHandle(SCREEN_W / 2 - str_w / 2, SCREEN_H - 80, GetColor(str_color.r, str_color.g, str_color.b), font_handle[1], "%02d：%02d", (frame_count / 60) / 60, (frame_count / 60) % 60);

	//音源の再生秒数
	//str_w = GetDrawFormatStringWidthToHandle(font_handle[1], "%02d", GetCurrentPositionSoundMem(SoundHandle) / 1000);
	//DrawFormatStringToHandle(SCREEN_W / 2, SCREEN_H - 50, GetColor(0, 0, 0), font_handle[1], "%02d", (GetCurrentPositionSoundMem(SoundHandle) / 1000) / 60 - frame_count / 60);
	str_w = GetDrawFormatStringWidthToHandle(font_handle[1], "%02d", (SamplePos / 600) / 100);
	DrawFormatStringToHandle(SCREEN_W/2, SCREEN_H-50, GetColor(0, 0, 0), font_handle[1], "%02d", (SamplePos / 600) / 100);
	GetNowCount();

	//周波数分布を画面に描画する
	for (int i = 0; i < BUFFERLENGTH / 2; i++)
	{
		float Param;

		// 関数から取得できる値を描画に適した値に調整
		Param = (float)pow(ParamList[i], 0.6) * 8.0f;

		// 縦線を描画上
		DrawBox(sound_visualizer_pos.x - (int)(Param * SOUNDLENGTH), ((BUFFERLENGTH - 1) - i) * 30 + sound_visualizer_pos.y,
			sound_visualizer_pos.x + (int)(Param * SOUNDLENGTH), ((BUFFERLENGTH - 1) - i) * 30 + 20 + sound_visualizer_pos.y, GetColor(255, 255, 255), TRUE);

		// 縦線を描画
		DrawBox(sound_visualizer_pos.x - (int)(Param * SOUNDLENGTH), i * 30 + sound_visualizer_pos.y,
			sound_visualizer_pos.x + (int)(Param * SOUNDLENGTH), (i * 30) + 20 + sound_visualizer_pos.y, GetColor(255, 255, 255), TRUE);
	}
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	// 画像ハンドルが入っているならメモリー上から削除する
	if (GrHandle != 0)
	{
		DeleteGraph(GrHandle);
	}

	//フォント
	FontExit();

	//ノーツの終了処理
	Notes_Exit();
}

//ドラッグ＆ドロップされたハンドルを返す関数
int Get_GrHandle()
{
	return GrHandle;
}