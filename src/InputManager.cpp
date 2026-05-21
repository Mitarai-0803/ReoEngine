//============================================================================
//! @file   InputManager.cpp
//! @brief  入力管理の実装
//! @details キーボード・マウスの状態を毎フレーム取得し、使用しやすい API を提供します。
//! @author レオ
//============================================================================
#include "InputManager.h"
#include <cstring>

namespace InputManager {

// ヘッダで extern 宣言した静的変数の実体定義
char key_buffer_[256]{};
int  key_frame_[256]{};
int  mouse_left_frame_{};
int  mouse_right_frame_{};
int  mouse_wheel_rot_{};

//-----------------------------------------------------------
//! @brief 更新処理
//-----------------------------------------------------------
void Update()
{
    // キー入力状態を取得
    GetHitKeyStateAll(key_buffer_);

    // キーフレームカウンタ更新
    for(int i = 0; i < 256; i++) {
        key_frame_[i] = key_buffer_[i] ? key_frame_[i] + 1 : 0;
    }

    // マウスボタン状態更新
    mouse_left_frame_  = (GetMouseInput() & MOUSE_INPUT_LEFT) ? mouse_left_frame_ + 1 : 0;
    mouse_right_frame_ = (GetMouseInput() & MOUSE_INPUT_RIGHT) ? mouse_right_frame_ + 1 : 0;

    // マウスホイール回転量取得
    mouse_wheel_rot_ = GetMouseWheelRotVol();
}

//-----------------------------------------------------------
//! @brief 押下瞬間判定
// @param key 判定するキーコード
// @return 押下した瞬間なら true
//-----------------------------------------------------------
bool PushHitKey(int key)
{
    return key_frame_[key] == 1;
}

//-----------------------------------------------------------
//! @brief マウスボタン押下中判定
// @param button MOUSE_INPUT_LEFT 等
// @return 押下中なら true
//-----------------------------------------------------------
bool CheckMouseInput(int button)
{
    return (GetMouseInput() & button) != 0;
}

//-----------------------------------------------------------
//! @brief マウスボタン押下瞬間判定
// @param button MOUSE_INPUT_LEFT 等
// @return 押下した瞬間なら true
//-----------------------------------------------------------
bool PushMouseInput(int button)
{
    if((button & MOUSE_INPUT_LEFT) && mouse_left_frame_ == 1)
        return true;
    if((button & MOUSE_INPUT_RIGHT) && mouse_right_frame_ == 1)
        return true;
    return false;
}

//-----------------------------------------------------------
//! @brief マウスホイール回転量取得
// @return 1以上 = 奥回転, 0 = 回していない, -1以下 = 手前回転
//-----------------------------------------------------------
int GetMouseWheel()
{
    return mouse_wheel_rot_;
}

//-----------------------------------------------------------
//! @brief マウス X 座標取得
// @return X 座標
//-----------------------------------------------------------
int GetMouseX()
{
    int x, y;
    GetMousePoint(&x, &y);
    return x;
}

//-----------------------------------------------------------
//! @brief マウス Y 座標取得
// @return Y 座標
//-----------------------------------------------------------
int GetMouseY()
{
    int x, y;
    GetMousePoint(&x, &y);
    return y;
}

}    // namespace InputManager
