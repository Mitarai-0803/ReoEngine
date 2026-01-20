#include "Main.h"
#include "Function.h"
#include "Image_Button.h"
#include "Game.h"
#include "Notes.h"

enum
{
	PLAY_BUTTON
};
//---------------------------------------------------------------------------------
//	インスタンスの生成
//---------------------------------------------------------------------------------
Image_Botton play_button;	//再生ボタン
Image_Botton stop_button;	//ストップボタン　

//---------------------------------------------------------------------------------
//	メンバ関数の値を渡す関数
//---------------------------------------------------------------------------------
void Image_ButtonInit()
{
	play_button.Init("EngineData/Image/UI/play.png", SCREEN_W / 2 - 50 / 2, 20);
	stop_button.Init("EngineData/Image/UI/stop.png", SCREEN_W / 2 - 50 / 2, 20);
}

void Image_ButtonUpdate()
{

	//音楽が流れているなら
	if (CheckSoundMem(Get_GrHandle()))
	{
		play_button.Update();

		//ボタンをクリックされたら
		if (play_button.Push_Mode())
		{
			//音源の再生を止める
			StopSoundMem(Get_GrHandle());
		}
	}
	//音楽が流れていないなら
	else
	{
		stop_button.Update();

		//ボタンをクリックされたら
		if (stop_button.Push_Mode())
		{
			//音源の再生(ループ再生)
			PlaySoundMem(Get_GrHandle(), DX_PLAYTYPE_LOOP);
		}
	}
}

void Image_ButtonRender()
{
	//音楽が流れているなら
	if (CheckSoundMem(Get_GrHandle()))
	{
		play_button.Render();
	}
	//音楽が流れていないなら
	else
	{
		stop_button.Render();
	}
}

//---------------------------------------------------------------------------------
//	メンバ関数
//---------------------------------------------------------------------------------
void Image_Botton::Init(const char* path, float x, float y)//初期化処理
{
	//画像の読み込み
	image_ = LoadGraph(path);
	//画像の幅と高さの取得
	GetGraphSizeF(image_, &size_.x, &size_.y);
	//座標の初期化
	pos_ = { x + (size_.x / 2.0f),y + (size_.y / 2.0f) };
	//画像のサイズの初期化
	scale_ = 0;
}

void Image_Botton::Update()//更新処理
{
	//マウスの座標の取得
	Float_Pos mouse = { (float)GetMouseX(),(float)GetMouseY() };

	//画像サイズの半分だけずらして当たり判定の用変数の作成
	Float_Pos pos = { pos_.x - (size_.x / 2.0f),pos_.y - (size_.y / 2.0f) };

	//マウスと文字(四角)が当たっていたら
	if (CheckPointBoxHit_F(mouse, pos, size_))
	{
		//クリックされたら
		if (PushMouseInput(MOUSE_INPUT_LEFT))
		{
			//押されている状態にする
			push_mode_ = MODE_ON;
		}
		else
		{
			//押されていない状態にする
			push_mode_ = MODE_OFF;
		}

		//画像の大きさを変える
		scale_ = 1.3f;
	}
	else
	{
		//画像の大きさを戻す
		scale_ = 1.0f;

		//押されていない状態にする
		push_mode_ = MODE_OFF;
	}
}

void Image_Botton::Render()//描画処理
{
	//ボタン画像の描画
	//DrawRotaGraph(pos_.x, pos_.y, scale_, 0.0f, image_, true);

	//当たり判定の描画
	//DrawLineBox(pos_.x - (size_.x / 2.0f), pos_.y-(size_.y / 2.0f), pos_.x + (size_.x / 2.0f), pos_.y + (size_.y / 2.0f), GetColor(255, 255, 255));
}

Image_Botton::~Image_Botton()//デストラクタ
{
	DeleteGraph(image_);
}

//---------------------------------------------------------------------------------
//	値を返すメンバ関数
//---------------------------------------------------------------------------------
bool Image_Botton::Push_Mode()//クリックの状態
{
	if (push_mode_ == MODE_ON)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Image_Botton::W()//幅
{
	return size_.x;
}

float Image_Botton::H()//高さ
{
	return size_.y;
}