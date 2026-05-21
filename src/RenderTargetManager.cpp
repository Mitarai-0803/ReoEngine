//============================================================================
//! @file   RenderTargetManager.cpp
//! @brief  レンダーターゲット管理の実装
//! @details DxLib のスクリーンハンドルを用いて名前付きレンダーターゲットを管理
//! @author レオ
//============================================================================
#include "RenderTargetManager.h"    // レンダーターゲット管理の宣言
#include "DxMain.h"                 // DxLib 利用
#include <unordered_map>            // 管理用のハッシュマップ
#include <string>                   // 文字列
#include <memory>                   // スマートポインタ

namespace Graphics {
//-----------------------------------------------------------
//! @brief Impl 構造体（実装詳細）
//-----------------------------------------------------------
struct RenderTargetManager::Impl
{
    std::unordered_map<std::string, int> handles;       //!< 管理名 -> グラフィックハンドル
    std::string                          activeName;    //!< 現在アクティブなターゲット名
};

//-----------------------------------------------------------
//! @brief コンストラクタ
//-----------------------------------------------------------
RenderTargetManager::RenderTargetManager()
    : m_impl(std::make_unique<Impl>())
{
}

//-----------------------------------------------------------
//! @brief デストラクタ
//-----------------------------------------------------------
RenderTargetManager::~RenderTargetManager()
{
    ReleaseAll();
}

//-----------------------------------------------------------
//! @brief レンダーターゲット作成
//-----------------------------------------------------------
int RenderTargetManager::CreateRenderTarget(const std::string& name, int width, int height, bool useAlpha)
{
    if(m_impl->handles.find(name) != m_impl->handles.end())
        return m_impl->handles[name];

    int handle = MakeScreen(width, height, useAlpha ? TRUE : FALSE);
    if(handle == -1)
        return -1;

    m_impl->handles[name] = handle;
    return handle;
}

//-----------------------------------------------------------
//! @brief レンダーターゲットをアクティブにする
//-----------------------------------------------------------
bool RenderTargetManager::SetActive(const std::string& name)
{
    auto it = m_impl->handles.find(name);
    if(it == m_impl->handles.end())
        return false;

    SetDrawScreen(it->second);
    m_impl->activeName = name;
    return true;
}

//-----------------------------------------------------------
//! @brief 描画先をバックバッファに戻す
//-----------------------------------------------------------
void RenderTargetManager::ResetToScreen()
{
    SetDrawScreen(DX_SCREEN_BACK);
    m_impl->activeName.clear();
}

//-----------------------------------------------------------
//! @brief 指定ターゲットを画面に描画する
//-----------------------------------------------------------
void RenderTargetManager::Present(const std::string& name, int x, int y)
{
    auto it = m_impl->handles.find(name);
    if(it == m_impl->handles.end())
        return;

    int h = it->second;
    DrawGraph(x, y, h, TRUE);
}

//-----------------------------------------------------------
//! @brief 指定ターゲットを解放する
//-----------------------------------------------------------
void RenderTargetManager::Release(const std::string& name)
{
    auto it = m_impl->handles.find(name);
    if(it == m_impl->handles.end())
        return;

    DeleteGraph(it->second);
    m_impl->handles.erase(it);
}

//-----------------------------------------------------------
//! @brief 全てのターゲットを解放する
//-----------------------------------------------------------
void RenderTargetManager::ReleaseAll()
{
    for(auto& kv : m_impl->handles) {
        DeleteGraph(kv.second);
    }
    m_impl->handles.clear();
}

//-----------------------------------------------------------
//! @brief ターゲットハンドル取得
//-----------------------------------------------------------
int RenderTargetManager::GetHandle(const std::string& name) const
{
    auto it = m_impl->handles.find(name);
    if(it == m_impl->handles.end())
        return -1;
    return it->second;
}
}    // namespace Graphics
