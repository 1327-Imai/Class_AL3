#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete debugCamera_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	debugCamera_ = new DebugCamera(1280 , 720);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

#pragma region//アフィン変換
#pragma region//移動
	//原点からの距離を取得
	distanceFromOrigin = vertex[0];

	//原点まで移動する(現在の座標から原点からの距離を引く)
	for (int i = 0; i < 8; i++) {
		vertex[i] -= distanceFromOrigin;
	}

	//アフィン変換をする
	for (int i = 0; i < 8; i++) {
		boxMoved[i].x =
			affineTransrate.m[0][0] * vertex[i].x +
			affineTransrate.m[0][1] * vertex[i].y +
			affineTransrate.m[0][2] * vertex[i].z +
			affineTransrate.m[0][3] * 1;

		boxMoved[i].y =
			affineTransrate.m[1][0] * vertex[i].x +
			affineTransrate.m[1][1] * vertex[i].y +
			affineTransrate.m[1][2] * vertex[i].z +
			affineTransrate.m[1][3] * 1;

		boxMoved[i].z =
			affineTransrate.m[2][0] * vertex[i].x +
			affineTransrate.m[2][1] * vertex[i].y +
			affineTransrate.m[2][2] * vertex[i].z +
			affineTransrate.m[2][3] * 1;
	};

	//原点からの距離を足して元の位置に戻す
	for (int i = 0; i < 8; i++) {
		vertex[i] += distanceFromOrigin;
		boxMoved[i] += distanceFromOrigin;
	}
#pragma endregion//移動

#pragma region//X軸回転
	//原点からの距離を取得
	distanceFromOrigin = vertex[0];

	//原点まで移動する(現在の座標から原点からの距離を引く)
	for (int i = 0; i < 8; i++) {
		vertex[i] -= distanceFromOrigin;
	}

	//アフィン変換をする
	for (int i = 0; i < 8; i++) {
		boxRotatedX[i].x =
			affineRotationX.m[0][0] * vertex[i].x +
			affineRotationX.m[0][1] * vertex[i].y +
			affineRotationX.m[0][2] * vertex[i].z +
			affineRotationX.m[0][3] * 1;

		boxRotatedX[i].y =
			affineRotationX.m[1][0] * vertex[i].x +
			affineRotationX.m[1][1] * vertex[i].y +
			affineRotationX.m[1][2] * vertex[i].z +
			affineRotationX.m[1][3] * 1;

		boxRotatedX[i].z =
			affineRotationX.m[2][0] * vertex[i].x +
			affineRotationX.m[2][1] * vertex[i].y +
			affineRotationX.m[2][2] * vertex[i].z +
			affineRotationX.m[2][3] * 1;
	};

	//原点からの距離を足して元の位置に戻す
	for (int i = 0; i < 8; i++) {
		vertex[i] += distanceFromOrigin;
		boxRotatedX[i] += distanceFromOrigin;
	}
#pragma endregion//X軸回転

#pragma region//Y軸回転
	//原点からの距離を取得
	distanceFromOrigin = vertex[0];

	//原点まで移動する(現在の座標から原点からの距離を引く)
	for (int i = 0; i < 8; i++) {
		vertex[i] -= distanceFromOrigin;
	}

	//アフィン変換をする
	for (int i = 0; i < 8; i++) {
		boxRotatedY[i].x =
			affineRotationY.m[0][0] * vertex[i].x +
			affineRotationY.m[0][1] * vertex[i].y +
			affineRotationY.m[0][2] * vertex[i].z +
			affineRotationY.m[0][3] * 1;

		boxRotatedY[i].y =
			affineRotationY.m[1][0] * vertex[i].x +
			affineRotationY.m[1][1] * vertex[i].y +
			affineRotationY.m[1][2] * vertex[i].z +
			affineRotationY.m[1][3] * 1;

		boxRotatedY[i].z =
			affineRotationY.m[2][0] * vertex[i].x +
			affineRotationY.m[2][1] * vertex[i].y +
			affineRotationY.m[2][2] * vertex[i].z +
			affineRotationY.m[2][3] * 1;
	};

	//原点からの距離を足して元の位置に戻す
	for (int i = 0; i < 8; i++) {
		vertex[i] += distanceFromOrigin;
		boxRotatedY[i] += distanceFromOrigin;
	}
#pragma endregion//Y軸回転

#pragma region//Z軸回転
	//原点からの距離を取得
	distanceFromOrigin = vertex[0];

	//原点まで移動する(現在の座標から原点からの距離を引く)
	for (int i = 0; i < 8; i++) {
		//vertex[i] -= distanceFromOrigin;
	}

	//アフィン変換をする
	for (int i = 0; i < 8; i++) {
		boxRotatedZ[i].x =
			affineRotationZ.m[0][0] * vertex[i].x +
			affineRotationZ.m[0][1] * vertex[i].y +
			affineRotationZ.m[0][2] * vertex[i].z +
			affineRotationZ.m[0][3] * 1;

		boxRotatedZ[i].y =
			affineRotationZ.m[1][0] * vertex[i].x +
			affineRotationZ.m[1][1] * vertex[i].y +
			affineRotationZ.m[1][2] * vertex[i].z +
			affineRotationZ.m[1][3] * 1;

		boxRotatedZ[i].z =
			affineRotationZ.m[2][0] * vertex[i].x +
			affineRotationZ.m[2][1] * vertex[i].y +
			affineRotationZ.m[2][2] * vertex[i].z +
			affineRotationZ.m[2][3] * 1;
	};

	//原点からの距離を足して元の位置に戻す
	for (int i = 0; i < 8; i++) {
		vertex[i] += distanceFromOrigin;
		boxRotatedZ[i] += distanceFromOrigin;
	}
#pragma endregion//Z軸回転

#pragma region//拡大縮小
	//原点からの距離を取得
	distanceFromOrigin = vertex[0];

	//原点まで移動する(現在の座標から原点からの距離を引く)
	for (int i = 0; i < 8; i++) {
		vertex[i] -= distanceFromOrigin;
	}

	//アフィン変換をする
	for (int i = 0; i < 8; i++) {
		boxEnlarged[i].x = affineScale.m[0][0] * vertex[i].x +
			affineScale.m[0][1] * vertex[i].y +
			affineScale.m[0][2] * vertex[i].z +
			affineScale.m[0][3] * 1;

		boxEnlarged[i].y = affineScale.m[1][0] * vertex[i].x +
			affineScale.m[1][1] * vertex[i].y +
			affineScale.m[1][2] * vertex[i].z +
			affineScale.m[1][3] * 1;

		boxEnlarged[i].z = affineScale.m[2][0] * vertex[i].x +
			affineScale.m[2][1] * vertex[i].y +
			affineScale.m[2][2] * vertex[i].z +
			affineScale.m[2][3] * 1;
	};

	//原点からの距離を足して元の位置に戻す
	for (int i = 0; i < 8; i++) {
		vertex[i] += distanceFromOrigin;
		boxEnlarged[i] += distanceFromOrigin;
	}
#pragma endregion//拡大縮小

#pragma endregion//アフィン変換
}

void GameScene::Update() {

	debugCamera_->Update();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(vertex[edgeList[i][0]] , vertex[edgeList[i][1]] , WHITE);
		PrimitiveDrawer::GetInstance()->DrawLine3d(boxMoved[edgeList[i][0]] , boxMoved[edgeList[i][1]] , BLUE);
		PrimitiveDrawer::GetInstance()->DrawLine3d(boxRotatedX[edgeList[i][0]] , boxRotatedX[edgeList[i][1]] , RED);
		PrimitiveDrawer::GetInstance()->DrawLine3d(boxRotatedY[edgeList[i][0]] , boxRotatedY[edgeList[i][1]] , YELLOW);
		PrimitiveDrawer::GetInstance()->DrawLine3d(boxRotatedZ[edgeList[i][0]] , boxRotatedZ[edgeList[i][1]] , PURPLE);
		PrimitiveDrawer::GetInstance()->DrawLine3d(boxEnlarged[edgeList[i][0]] , boxEnlarged[edgeList[i][1]] , GREEN);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
