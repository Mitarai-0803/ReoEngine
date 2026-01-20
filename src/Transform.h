#pragma once

//----------------------------------------------------------------------------
//! @file   Transform.h
//! @brief  位置・回転・スケールを保持するトランスフォーム定義
//! @detail 2D/3D 両対応の簡易トランスフォームを提供します。座標は右手系を想定しています。
//----------------------------------------------------------------------------

#include <cmath>

//============================================================================
//! @class  Vector3
//! 3 次元ベクトルを表現する構造体です。
//============================================================================
struct Vector3 {
    float x = 0.0f; //!< X 成分
    float y = 0.0f; //!< Y 成分
    float z = 0.0f; //!< Z 成分

    Vector3() = default;
    Vector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

    // ベクトル加算
    Vector3 operator+(const Vector3& other) const {
        return Vector3{x + other.x, y + other.y, z + other.z};
    }

    // ベクトル減算
    Vector3 operator-(const Vector3& other) const {
        return Vector3{x - other.x, y - other.y, z - other.z};
    }

    // スカラー倍
    Vector3 operator*(float s) const {
        return Vector3{x * s, y * s, z * s};
    }
};

//============================================================================
//! @class  Transform
//! 位置・回転（オイラー角）・スケールを保持する簡易トランスフォームです。
//============================================================================
struct Transform {
    Vector3 position; //!< ワールド空間の位置
    Vector3 rotation; //!< 回転（度単位のオイラー角: pitch(x), yaw(y), roll(z)）
    Vector3 scale{1.0f, 1.0f, 1.0f}; //!< スケール

    Transform() = default;

    // 位置設定
    void SetPosition(float x, float y, float z = 0.0f) {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    // 位置加算
    void Translate(float dx, float dy, float dz = 0.0f) {
        position.x += dx;
        position.y += dy;
        position.z += dz;
    }

    // 回転設定（度）
    void SetRotation(float pitch, float yaw, float roll = 0.0f) {
        rotation.x = pitch;
        rotation.y = yaw;
        rotation.z = roll;
    }

    // 回転加算（度）
    void Rotate(float dpitch, float dyaw, float droll = 0.0f) {
        rotation.x += dpitch;
        rotation.y += dyaw;
        rotation.z += droll;
    }

    // スケール設定
    void SetScale(float sx, float sy, float sz = 1.0f) {
        scale.x = sx;
        scale.y = sy;
        scale.z = sz;
    }
};
