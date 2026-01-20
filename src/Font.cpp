#include "Font.h"
#include <DxLib.h>//!< DXライブラリ利用

namespace Font
{
	//---------------------------------------------------------------------------------
	/// @brief フォント初期化
	/// @details 各サイズのフォントデータをロードし、内部のフォントハンドルに保持します。
	///          DxLib 初期化 (DxLib_Init) 後に呼び出してください。
	//---------------------------------------------------------------------------------
	void FontInit()
	{
		font_handle[FONT_SIZE_70_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_70.dft");
		font_handle[FONT_SIZE_50_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_50.dft");
		font_handle[FONT_SIZE_40_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_40.dft");
		font_handle[FONT_SIZE_30_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_30.dft");
		font_handle[FONT_SIZE_25_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_25.dft");
		font_handle[FONT_SIZE_10_INDEX] = LoadFontDataToHandle("EngineData/Font/FOT_RaglanPunch_10.dft");
	}

	//---------------------------------------------------------------------------------
	/// @brief フォント解放
	/// @details FontInit で確保したフォントハンドルをすべて解放します。
	///          アプリケーション終了時に呼び出してください。
	//---------------------------------------------------------------------------------
	void FontExit()
	{
		for (int i = 0; i < FONT_MAX; i++)
		{
			if (font_handle[i] != -1)
			{
				DeleteFontToHandle(font_handle[i]);
				font_handle[i] = -1; // 解放済みとしてマーク
			}
		}
	}

	//---------------------------------------------------------------------------------
	/// @brief フォントハンドル取得
	/// @param font_index フォントサイズインデックス
	/// @return 指定インデックスのフォントハンドル。範囲外の場合はデフォルトのハンドルを返す。
	//---------------------------------------------------------------------------------
	int GetFont(int font_index)
	{
		if (font_index < 0 || font_index >= FONT_MAX)
			font_index = FONT_SIZE_70_INDEX; // デフォルトフォント

		return font_handle[font_index];
	}
}