#pragma once

//---------------------------------------------------------------------------------
//	定数
//---------------------------------------------------------------------------------
const float NOTES_DEFAULT_SPEED = 10.0f;//ノーツのデフォルトのスピード
const float NOTES_W = 50.0f;//ノーツの幅
const float NOTES_H = 10.0f;//ノーツの高さ
const int   NOTES_MAX = 20;	//ノーツの数

//モード
enum
{
	MOVE_MODE = 0,//動く状態
	STOP_MODE,	  //動かない状態
	RESET_MODE	  //上に戻す状態(Y座標)
};

//---------------------------------------------------------------------------------
//	関数
//---------------------------------------------------------------------------------
void Notes_Init();		//初期化処理
void Notes_Update();	//更新処理
void Notes_Render();	//描画処理
void Notes_Exit();		//終了処理 

//値を代入するメンバ関数
void Notes_Set_Pos_X(float pos_x, int index);				//X座標の設定
void Notes_Set_Pos_Y(float pos_y, int index);				//Y座標の設定
void Notes_Set_Pos(float pos_x, float pos_y, int index);	//座標の設定
void Notes_Set_Mode(int mode, int index);					//モードの設定
void Notes_Set_Speed(float speed, int index);				//スピードの設定
void Notes_Reset_Speed(int index);							//スピードのリセット(デフォルト値に設定)
void Notes_Set_Color(int index, int r, int g, int b);		//ノーツの色を設定

//値を返す関数
float Notes_Pos_X(int index);//X座標
float Notes_Pos_Y(int index);//Y座標
int	  Notes_Mode(int index); //モード
int	  Judge_Str_Frame_Num(); //判定文字列を描画するフレーム数
int	  Judge_Num();			 //判定番号

//その他関数
void Notes_Judge(int index, int judge_mode);//ノーツの判定処理関数


//---------------------------------------------------------------------------------
//	ノーツclass
//	音ゲーのノーツの動きや画像を設定するクラス
//---------------------------------------------------------------------------------
class Notes
{
public:
	//メンバ関数
	void Init();    //初期化処理
	void Update();  //更新処理
	void Render();  //描画処理

	//デストラクタ
	~Notes();

	//値を代入するメンバ関数
	void Set_Pos_X(float pos_x);			 //X座標の設定
	void Set_Pos_Y(float pos_y);			 //Y座標の設定
	void Set_Pos(float pos_x, float pos_y);	 //座標の設定
	void Set_Mode(int mode);				 //座標の設定
	void Set_Speed(float speed);			 //スピードの設定
	void Reset_Speed();						 //スピードのリセット(デフォルト値に設定)
	void Set_Color(RGB color);				 //ノーツの色を設定

	//値を返すメンバ関数
	float Pos_X();//X座標
	float Pos_Y();//Y座標
	int   Mode(); //モード

private:
	//構造体
	struct PosF//座標用構造体
	{
		float x = 0.0f;
		float y = 0.0f;
	};

	//メンバ変数
	PosF   pos_;	//座標
	int	   mode_;	//モード
	float  speed_;	//スピード
	RGB	   color_;	//色
};
