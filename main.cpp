#include <Novice.h>
#include "imgui.h"  // ImGuiヘッダをインクルード（環境によってパスは異なる）
#include <cmath>
#include <cstring>

const char kWindowTitle[] = "学籍番号";

// ---------------- Vector3 ----------------
struct Vector3 {
	float x, y, z;
};

// Vector3の演算子オーバーロード
Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

Vector3 operator*(const Vector3& vec, float scalar) {
	return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

Vector3 operator*(float scalar, const Vector3& vec) {
	return vec * scalar;
}

// ---------------- Matrix4x4 ----------------
struct Matrix4x4 {
	float m[4][4];
};

// 回転行列作成関数
Matrix4x4 MakeRotateXMatrix(float rad) {
	Matrix4x4 m = {};
	float c = cosf(rad);
	float s = sinf(rad);

	m.m[0][0] = 1.0f; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f; m.m[0][3] = 0.0f;
	m.m[1][0] = 0.0f; m.m[1][1] = c;    m.m[1][2] = s;   m.m[1][3] = 0.0f;
	m.m[2][0] = 0.0f; m.m[2][1] = -s;    m.m[2][2] = c;    m.m[2][3] = 0.0f;
	m.m[3][0] = 0.0f; m.m[3][1] = 0.0f; m.m[3][2] = 0.0f; m.m[3][3] = 1.0f;

	return m;
}

Matrix4x4 MakeRotateYMatrix(float rad) {
	Matrix4x4 m = {};
	float c = cosf(rad);
	float s = sinf(rad);

	m.m[0][0] = c;    m.m[0][1] = 0.0f; m.m[0][2] = -s;    m.m[0][3] = 0.0f;
	m.m[1][0] = 0.0f; m.m[1][1] = 1.0f; m.m[1][2] = 0.0f; m.m[1][3] = 0.0f;
	m.m[2][0] = s;   m.m[2][1] = 0.0f; m.m[2][2] = c;    m.m[2][3] = 0.0f;
	m.m[3][0] = 0.0f; m.m[3][1] = 0.0f; m.m[3][2] = 0.0f; m.m[3][3] = 1.0f;

	return m;
}

Matrix4x4 MakeRotateZMatrix(float rad) {
	Matrix4x4 m = {};
	float c = cosf(rad);
	float s = sinf(rad);

	m.m[0][0] = c;    m.m[0][1] = s;   m.m[0][2] = 0.0f; m.m[0][3] = 0.0f;
	m.m[1][0] = -s;    m.m[1][1] = c;    m.m[1][2] = 0.0f; m.m[1][3] = 0.0f;
	m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f; m.m[2][3] = 0.0f;
	m.m[3][0] = 0.0f; m.m[3][1] = 0.0f; m.m[3][2] = 0.0f; m.m[3][3] = 1.0f;

	return m;
}

// 行列の掛け算演算子
Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float sum = 0.0f;
			for (int k = 0; k < 4; ++k) {
				sum += lhs.m[i][k] * rhs.m[k][j];
			}
			result.m[i][j] = sum;
		}
	}
	return result;
}

// グローバル変数（初期化）
Vector3 a{ 0.2f,1.0f,0.0f };
Vector3 b{ 2.4f,3.1f,1.2f };
Vector3 c = a + b;
Vector3 d = a - b;
Vector3 e = a * 2.4f;
Vector3 rotate{ 0.4f,1.43f,-0.8f };
Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		ImGui::Begin("Window");
		ImGui::Text("c: %f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d: %f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e: %f, %f, %f", e.x, e.y, e.z);
		ImGui::Text("matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);

		ImGui::End();

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
