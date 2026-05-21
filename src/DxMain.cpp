//============================================================================
//! @file   DxMain.cpp
//! @brief  アプリケーションエントリおよびメインループ
//! @details アプリケーションのエントリポイントとメインループを実装します。
//! @author レオ
//============================================================================
#include "DxMain.h"           //!< 定数利用
#include "Engine.h"           //!< ゲームエンジン関連
#include "GameScene.h"        //!< ゲームシーン
#include "SceneManager.h"     //!< シーンマネージャ
#include "InputManager.h"     //!< 入力管理
#include "Font.h"             //!< フォント管理
#include "ConstantsGame.h"    //!< ゲーム用定数ファイル

//-----------------------------------------------------------
//! @brief 初期化処理
//! @return true 初期化成功、false 初期化失敗
//-----------------------------------------------------------
bool Application::Init()
{
    SetOutApplicationLogValidFlag(FALSE);                            //!< ログ出力をしない
    ChangeWindowMode(TRUE);                                          //!< ウィンドウモードに設定
    SetBackgroundColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B);    //!< 背景色設定
    SetGraphMode(SCREEN_W, SCREEN_H, 32);                            //!< 画面サイズと色深度設定
    SetWindowTextDX("GameSample");                                   //!< ウィンドウテキスト設定
    SetWindowIconID(101);                                            //!< アイコン設定（リソースID）
    if(DxLib_Init() == -1)
        return false;    //!< 初期化失敗

    // フォント初期化
    Font::FontInit();

    // シーン登録（デフォルトシーン）
    auto gameScene = std::make_unique<Scene::GameScene>();
    m_scene_manager.AddScene(std::move(gameScene));

    // シーン初期化
    m_scene_manager.InitAll();

    return true;
}

//-----------------------------------------------------------
//! @brief メインループ実行
//-----------------------------------------------------------
void Application::Update()
{
    // メインループ：ESCキーが押されるまで続ける
    while(ProcessMessage() == 0 && !InputManager::PushHitKey(KEY_INPUT_ESCAPE)) {
        ClearDrawScreen();    //!< 描画バッファクリア

        InputManager::Update();    //!< 入力更新

        m_scene_manager.UpdateAll();    //!< シーン更新
        m_scene_manager.DrawAll();      //!< シーン描画

        ScreenFlip();    //!< バッファ反映
    }
}

//-----------------------------------------------------------
//! @brief 終了処理
//-----------------------------------------------------------
void Application::End()
{
    m_scene_manager.EndAll();    //!< シーン終了処理
    Font::FontExit();            //!< フォント終了
    DxLib_End();                 //!< DXライブラリ終了
}

//-----------------------------------------------------------
//! @brief アプリケーションエントリポイント
//! @return 終了コード（0:正常終了、-1:初期化失敗）
//-----------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // アプリケーションの実行
    Application app;

    // 初期化に失敗した場合はエラーコード -1 を返して終了
    if(!app.Init())
        return -1;

    // 初期化成功した場合はメインループを実行して正常終了
    app.Update();

    // 終了処理
    app.End();

    return 0;
}
