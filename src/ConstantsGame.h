#pragma once
//============================================================================
//! @file   ConstantsGame.h
//! @brief  ゲーム内の定数定義
//! @details ゲーム内で使用する各種定数を定義します。
//! @author レオ
//============================================================================

//-----------------------------------------------------------
// 画面関連定数
//-----------------------------------------------------------
constexpr int   SCREEN_W      = 1280;               //!< 画面幅
constexpr int   SCREEN_H      = 720;                //!< 画面高さ
constexpr float HALF          = 0.5f;               //!< 半分の値
constexpr float TWICE         = 2.0f;               //!< 2倍の値
constexpr float HALF_SCREEN_W = SCREEN_W * HALF;    //!< 画面幅の半分
constexpr float HALF_SCREEN_H = SCREEN_H * HALF;    //!< 画面高さの半分

// 背景色
constexpr int BACKGROUND_R = 100;    //!< 背景色の赤成分
constexpr int BACKGROUND_G = 100;    //!< 背景色の緑成分
constexpr int BACKGROUND_B = 100;    //!< 背景色の青成分

//---------------------------------------------------------------
// 関数ファイルの定数
//---------------------------------------------------------------
// ミリ秒関連
constexpr int MS_PER_SEC = 1000;     //!< 1秒あたりのミリ秒
constexpr int MS_PER_MIN = 60000;    //!< 1分あたりのミリ秒

constexpr float PI = 3.14159265358979323846f;    //!< 円周率
