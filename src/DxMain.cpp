#include "DxLib.h"              //!< DXライブラリ利用
#include "DxMain.h"             //!< 定数利用
#include "Engine.h"             //!< ゲームエンジン関連
#include "GameScene.h"          //!< ゲームシーン
#include "InputManager.h"       //!< 入力管理
#include "Font.h"               //!< フォント管理

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //-------------------------------------------------------
    // DXライブラリ初期化
    //-------------------------------------------------------
    ChangeWindowMode(TRUE);               //!< ウィンドウモードに設定
    SetBackgroundColor(100, 100, 100);    //!< 背景色設定
    SetGraphMode(SCREEN_W, SCREEN_H, 32); //!< 画面サイズと色深度設定

    if (DxLib_Init() == -1) return -1;    //!< 初期化失敗時は終了

    SetDragFileValidFlag(TRUE);           //!< D&Dによるファイル読み込みを有効化

    //-------------------------------------------------------
    // フォント初期化
    //-------------------------------------------------------
    Font::FontInit();

    //-------------------------------------------------------
    // ゲームシーン作成と初期化
    //-------------------------------------------------------
    auto engine_scene = std::make_unique<Scene::GameScene>();
    engine_scene->Init();

    //-------------------------------------------------------
    // メインループ
    //-------------------------------------------------------
    while (ProcessMessage() == 0 && !InputManager::InputManager::PushHitKey(KEY_INPUT_ESCAPE))
    {
        ClearDrawScreen();                                      //!< 描画バッファクリア

        InputManager::InputManager::Update();                   //!< 入力更新

        engine_scene->Update();                                 //!< シーン更新
        engine_scene->Draw();                                   //!< シーン描画

        ScreenFlip();                                           //!< バッファ反映
    }

    //-------------------------------------------------------
    // 終了処理
    //-------------------------------------------------------
    engine_scene->End();                                       //!< シーン終了処理
    Font::FontExit();                                                //!< フォント終了
    DxLib_End();                                               //!< DXライブラリ終了
    return 0;
}
