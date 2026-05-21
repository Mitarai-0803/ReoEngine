//============================================================================
//! @file   FontManager.cpp
//! @brief  フォント管理の実装
//! @details 各フォントサイズのロードとアンロードを行う実装を提供します。
//! @author レオ
//============================================================================
#include "FontManager.h"    // フォント管理の宣言
#include <DxLib.h>          // DXライブラリ利用

namespace Font {
//-----------------------------------------------------------
// Font をクラス化して管理（実装ファイル内に限定）
// FontManager の静的メンバ定義
//-----------------------------------------------------------
int FontManager::m_font_handles[FONT_MAX]{};

//-----------------------------------------------------------
//! @brief フォント初期化
//-----------------------------------------------------------
void FontManager::Init()
{
    m_font_handles[FONT_SIZE_70_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_70.dft");
    m_font_handles[FONT_SIZE_50_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_50.dft");
    m_font_handles[FONT_SIZE_40_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_40.dft");
    m_font_handles[FONT_SIZE_30_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_30.dft");
    m_font_handles[FONT_SIZE_25_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_25.dft");
    m_font_handles[FONT_SIZE_10_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_10.dft");
}

//-----------------------------------------------------------
//! @brief フォント解放
//-----------------------------------------------------------
void FontManager::Exit()
{
    for(int i = 0; i < FONT_MAX; ++i) {
        if(m_font_handles[i] != -1) {
            DeleteFontToHandle(m_font_handles[i]);
            m_font_handles[i] = -1;
        }
    }
}

//-----------------------------------------------------------
//! @brief フォントハンドル取得
//! @param font_index フォントインデックス
//! @return フォントハンドル
//-----------------------------------------------------------
int FontManager::GetFont(int font_index)
{
    if(font_index < 0 || font_index >= FONT_MAX)
        font_index = FONT_SIZE_70_INDEX;
    return m_font_handles[font_index];
}

//-----------------------------------------------------------
//! フォント初期化
//-----------------------------------------------------------
void FontInit()
{
    FontManager::Init();
}

//-----------------------------------------------------------
//! フォント解放
//-----------------------------------------------------------
void FontExit()
{
    FontManager::Exit();
}

//-----------------------------------------------------------
//! フォントハンドル取得
//-----------------------------------------------------------
int GetFont(int font_index)
{
    return FontManager::GetFont(font_index);
}

}    // namespace Font
