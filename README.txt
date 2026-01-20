概要

ReoEngine は簡易的な自作ゲームエンジンの試作コードです。
C++14 準拠で記述されており、エンティティ（GameObject）とコンポーネント（ComponentBase）を使った
基本的なライフサイクル管理を提供します。3D 対応のために簡易 Transform（位置・回転・スケール）を追加済みです。

ライセンス

このリポジトリのコードは自由に参照・改変して構いません。商用利用や配布の際は、プロジェクトに適したライセンスを追記してください。

動作要件

- C++ コンパイラ（C++14 対応）
- Visual Studio のプロジェクト（付属する .vcxproj でビルドできます）

ビルド方法（Visual Studio）

1. リポジトリをクローンまたはダウンロード
2. Visual Studio でプロジェクトファイルを開く
3. ビルドを実行

簡単な使い方
- `ReoEngine::Engine` がシーン内オブジェクトの所有者（unique_ptr ベース）になります。

  ```cpp
  ReoEngine::Engine engine;

  // オブジェクトを作成して名前を設定
  auto obj = std::make_unique<GameObject>();
  obj->SetName("Player");

  // アクセス用に生ポインタを保持（非所有）
  GameObject* objPtr = obj.get();

  // 所有権を engine に移動
  engine.AddObject(std::move(obj));

  // objPtr は非所有ポインタなので、engine がオブジェクトを破棄すると無効化される点に注意
  objPtr->GetTransform().SetPosition(0.0f, 1.0f, 0.0f);
  ```

- コンポーネントの追加

  `GameObject::AddComponent<T>(...)` は `std::shared_ptr<T>` を返します。追加時にコンポーネントの `Init()` が呼ばれます。

  ```cpp
  auto meshComp = objPtr->AddComponent<MeshComponent>(/* コンストラクタ引数 */);
  ```

- ライフサイクル

  - `GameObject::Init()` は内部の全コンポーネントの `Init()` を呼びます。デストラクタでは `End()` を呼びます。
  - `ReoEngine::Engine::UpdateAll()` / `ReoEngine::Engine::DrawAll()` / `ReoEngine::Engine::EndAll()` を順次呼ぶことでシーン内全オブジェクトの同名処理を実行します。

設計上の注意点

- 所有権
  - 現在 `ReoEngine::Engine` が `std::unique_ptr<GameObject>` でオブジェクトを所有します。外部で参照を保持する場合は生ポインタ（`GameObject*`）を使うか、将来 `weak_ptr` ベースに設計変更してください。

- コンポーネント所有
  - `AddComponent` は `shared_ptr` を使ってコンポーネントを保持します。現状 `ComponentBase` にオーナ参照は実装されていません。コンポーネント側からオーナ（GameObject）を参照したい場合は `ComponentBase` に `SetOwner(GameObject*)` を追加することを検討してください。

- Transform
  - 現在は簡易のオイラー角（度）で回転を保持しています。必要ならクォータニオンに変更して gimbal lock を回避してください。

今後の拡張案（サンプル）

- `ComponentBase` にオーナ参照（`SetOwner`）を追加して、コンポーネントが所属オブジェクトの Transform や他コンポーネントにアクセスできるようにする
- `MeshComponent` / `RendererComponent` の実装を追加して 3D レンダリングパスを組み込む
- エンティティ ID / ハンドル方式の導入による安全な参照管理

サンプル: 簡易的な使用例

以下は `ReoEngine` の簡易的な利用例です。Engine 作成からオブジェクト追加、コンポーネント追加、別オブジェクトへのデータ受け渡しまでを示します。

```cpp
#include <iostream>
#include <memory>

// ReoEngine のヘッダをインクルード
#include "Engine.h"
#include "GameObject.h"
#include "ComponentBase.h"

// ValueComponent: 値を保持する簡易コンポーネント
struct ValueComponent : public ComponentBase {
    int value_;

    ValueComponent(int v) : value_(v) {}

    int GetValue() const { return value_; }

    void Init() override {}
    void Update() override {}
    void Draw() override {}
    void End() override {}
};

// ReceiverComponent: 他オブジェクトから値を取得して表示するコンポーネント
struct ReceiverComponent : public ComponentBase {
    GameObject* target_; // 参照先オブジェクト（非所有ポインタ）
    int cachedValue_ = 0;

    ReceiverComponent(GameObject* target) : target_(target) {}

    void Init() override {}

    void Update() override {
        if (!target_) return;
        // target の ValueComponent を取得して値を参照
        auto v = target_->GetComponent<ValueComponent>();
        if (v) {
            cachedValue_ = v->GetValue();
        }
    }

    void Draw() override {
        // 画面ではなくコンソール出力で確認
        std::cout << "Receiver cached value: " << cachedValue_ << std::endl;
    }

    void End() override {}
};

int main() {
    // エンジン作成
    ReoEngine::Engine engine;

    // オブジェクト A (Sender) を作成して ValueComponent を追加
    auto objA = std::make_unique<GameObject>();
    objA->SetName("Sender");
    GameObject* aPtr = objA.get(); // 所有権移動前に生ポインタを保存
    aPtr->AddComponent<ValueComponent>(42); // 値 42 を保持

    // オブジェクト B (Receiver) を作成して ReceiverComponent を追加
    auto objB = std::make_unique<GameObject>();
    objB->SetName("Receiver");
    GameObject* bPtr = objB.get();
    // ReceiverComponent に objA を参照として渡す
    bPtr->AddComponent<ReceiverComponent>(aPtr);

    // 所有権をエンジンに移動
    engine.AddObject(std::move(objA));
    engine.AddObject(std::move(objB));

    // 簡易ループ: 更新と描画を1フレーム分実行
    engine.UpdateAll();
    engine.DrawAll();

    // エンジン終了処理
    engine.EndAll();

    return 0;
}
```

このコードは理解しやすい最小限の例を示しています。実際の利用ではエラー処理、所有権の明確化、スレッド考慮、コンポーネントのオーナ設定などを追加してください。

