#include "InputManager.h"
#include <cstring>

//-----------------------------------------------------------
/// @brief 入力管理機能の名前空間
/// @details 全キー・マウス入力の状態取得およびフレーム管理を行う
//-----------------------------------------------------------
namespace InputManager {

	// 静的メンバ変数定義
	char InputManager::key_buffer_[256] = {};
	int InputManager::key_frame_[256] = {};
	int InputManager::mouse_left_frame_ = 0;
	int InputManager::mouse_right_frame_ = 0;
	int InputManager::mouse_wheel_rot_ = 0;

	//-------------------------------------------------------
	/// @brief 入力状態を更新する
	/// @details キーボード全キー・マウスボタン・ホイールの状態を取得し
	///          各キーやボタンの連続押下フレーム数を更新する
	//-------------------------------------------------------
	void InputManager::Update() {
		// 全キーの押下状態を取得
		GetHitKeyStateAll(key_buffer_);

		// 各キーのフレーム更新
		for (int i = 0; i < 256; i++) {
			key_frame_[i] = key_buffer_[i] ? key_frame_[i] + 1 : 0;
		}

		// マウスボタンフレーム更新
		mouse_left_frame_ = (GetMouseInput() & MOUSE_INPUT_LEFT) ? mouse_left_frame_ + 1 : 0;
		mouse_right_frame_ = (GetMouseInput() & MOUSE_INPUT_RIGHT) ? mouse_right_frame_ + 1 : 0;

		// マウスホイール更新
		mouse_wheel_rot_ = GetMouseWheelRotVol();
	}

	//-------------------------------------------------------
	/// @brief 指定キーが押された瞬間かを判定する
	/// @param key 判定するキーコード
	/// @return 押された瞬間なら true
	//-------------------------------------------------------
	bool InputManager::PushHitKey(int key) {
		return key_frame_[key] == 1;
	}

	//-------------------------------------------------------
	/// @brief 指定マウスボタンの押下状態を取得する
	/// @param button MOUSE_INPUT_LEFT など
	/// @return 押されているなら true
	//-------------------------------------------------------
	bool InputManager::CheckMouseInput(int button) {
		return (GetMouseInput() & button) != 0;
	}

	//-------------------------------------------------------
	/// @brief 指定マウスボタンが押された瞬間かを判定する
	/// @param button MOUSE_INPUT_LEFT など
	/// @return 押された瞬間なら true
	//-------------------------------------------------------
	bool InputManager::PushMouseInput(int button) {
		if ((button & MOUSE_INPUT_LEFT) && mouse_left_frame_ == 1) return true;
		if ((button & MOUSE_INPUT_RIGHT) && mouse_right_frame_ == 1) return true;
		return false;
	}

	//-------------------------------------------------------
	/// @brief マウスホイールの回転量を取得する
	/// @return ホイール回転量（1 = 上, -1 = 下, 0 = 変化なし）
	//-------------------------------------------------------
	int InputManager::GetMouseWheel() {
		return mouse_wheel_rot_;
	}

	//-------------------------------------------------------
	/// @brief マウスの X 座標を取得する
	/// @return マウスの X 座標（ピクセル）
	//-------------------------------------------------------
	int InputManager::GetMouseX() {
		int x, y;
		GetMousePoint(&x, &y);
		return x;
	}

	//-------------------------------------------------------
	/// @brief マウスの Y 座標を取得する
	/// @return マウスの Y 座標（ピクセル）
	//-------------------------------------------------------
	int InputManager::GetMouseY() {
		int x, y;
		GetMousePoint(&x, &y);
		return y;
	}
}
