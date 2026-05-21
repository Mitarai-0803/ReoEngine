// 必ずインクルードされるヘッダーと定義
// ※注意※ このヘッダーが参照されているファイル更新されるとフルビルドになるため
//          更新頻度が高いソースは追加しないこと。
#pragma once

//==============================================================
// Windows
//==============================================================
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//==============================================================
// C Runtime
//==============================================================
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cmath>

//==============================================================
// STL
//==============================================================
#include <string>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <memory>
#include <optional>
#include <variant>
#include <functional>

#include <algorithm>
#include <utility>

#include <fstream>
#include <sstream>
#include <iostream>

//==============================================================
// DXライブラリ
//==============================================================
#include <DxLib.h>

//==============================================================
// HLSL++
//==============================================================
#include <hlsl++.h>

//==============================================================
// ImGui
//==============================================================
#include <imgui.h>
