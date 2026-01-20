#pragma once

//---------------------------------------------------------------------------------
//	構造体
//---------------------------------------------------------------------------------

//座標
//float型
struct Float_Pos
{
	float x;	//X座標
	float y;	//Y座標
};
//int型
struct Int_Pos
{
	int x;	//X座標
	int y;	//Y座標
};


//画像番号,高さ,幅,角度
//float型
struct Image_Input_F
{
	int	  image;	//画像
	float w;		//幅
	float h;		//高さ
	float rot;		//角度(度)
};

//int型
struct Image_Input_I
{
	int	image;	//画像
	int	w;		//幅
	int	h;		//高さ
	float rot;	//角度(度)
};

//座標,画像番号,高さ,幅,角度
//float型
struct Image_Property_F
{
	Float_Pos	pos;	//座標
	int		  image;	//画像
	int		  w;		//幅
	int		  h;		//高さ
	float     rot;		//角度(度)
};

//四角の左上座標と右下の座標
//float型
struct Box_F
{
	float  x = 0;
	float  y = 0;
	float  w = 0;
	float  h = 0;
};

//int型
struct Box_I
{
	float  x = 0;
	float  y = 0;
	float  w = 0;
	float  h = 0;
};

//円の座標と半径
//float型
struct Circle_F
{
	Float_Pos pos;//座標
	float  radius;//半径
};

//色(RGB)
struct RGB
{
	int r = 0;
	int g = 0;
	int b = 0;
};

//ミサイル用(配列にするものをまとめたもの)
struct Shot_Input//座標,角度,モード(ミサイル用)
{
	float x;	//X座標
	float y;	//Y座標
	float rot;	//角度
	int   mode; //モード
};

//リスト用
//float型
struct List_Box
{
	int image = 0;//画像
	float   x = 0;//X座標
	float   y = 0;//Y座標
	float   w = 0;//幅
	float   h = 0;//高さ
};
