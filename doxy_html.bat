@echo off
chcp 65001
REM =====================================================
REM Doxygen ドキュメント生成バッチ
REM =====================================================

REM 現在のフォルダをプロジェクトルートに設定
cd /d %~dp0/tool/Doxygen

REM Doxyfile でドキュメント生成
doxygen Doxyfile

REM 完了メッセージ
echo Doxygen ドキュメント生成完了

REM 生成したHTMLファイルの場所へ移動
cd /d %~dp0/tool/Doxygen/html

REM 生成したHTMLファイルを開く
index.html