# ReoEngine

![Badge](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white) 

ゲーム制作の効率化エンジン

## ✨ Features
#### 【.cmdファイルについて】
**Cleanup.cmd**<br>
作成したソリューション関係が入った(.buildファイル)を削除しクリーンな状態に戻します。

**DoxyHtml.cmd**<br>
Doxgenファイルを作成し、仕様書ページをHTMLで自動作成できます。

**Line.cmd**<br>
srcファイル内にあるcppやhファイルに書かれた文字の行数をカウントし、総合計が確認できます。

**Meke.cmd**<br>
.slnと.vcxproj等のVisualStudioの起動に必要なファイルを自動生成できます。※詳しくはプリメイクの設定とフィルタの設定についてを参照

**Open.cmd**<br>
Make.cmdで作成したソリューションを開きます。

## プリメイクの設定とフィルタの設定について
src 内のファイルを自動走査して
```
Object
 └ BoxObject
    ├ BoxObject.cpp
    └ BoxObject.h
```
このような形にVisualStudioのフィルタを設定、ソリューションを作成します。
基本的な作成されるフィルターは以下の通りです。<br>
・Object<br>
・Component<br>
・Scene<br>
例：PlayerObject→Objectファイルに入ります。<br>
上記の単語が含まれていないなら<br>
・ System<br>
へ入れられます。<br>

### 【簡単なフレームワークの説明】
基本設計はコンポーネントベースアーキテクチャです。
シーンマネージャー、シーン、オブジェクト、コンポーネントなどがあります。

---
## 【使用ライブラリの説明】
・cereal
C++用シリアライズライブラリ
・ゲームサンプル
　サンプルプロジェクト

・hlsl++
　HLSL風ベクトル・行列演算ライブラリ

・ImGui様
　GUIライブラリ

・ImGuizmo
　3Dギズモ操作ライブラリ

・imgui-neo-sequencer
　タイムライン/シーケンサーUI

・implot
　グラフ描画ライブラリ

・ジョルト物理学
　物理エンジン

・meshoptimizer
　メッシュ最適化ライブラリ

・シグスロット
　シグナル/イベントライブラリ

・ゲームサンプル.sln
　Visual Studio ソリューションファイル


## 🚀 Installation
```bash
1.このプロジェクトをクローン
2.Make.cmdを使用してソリューションを作成
3.Open.cmdを使ってプロジェクトを開く
```

## 📝 License
This project is licensed under the MIT.
