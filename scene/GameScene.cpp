﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

using namespace DirectX;

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(回転角用)
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	//乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	// 3Dモデルの生成
	model_ = Model::Create();

	// X,Y,Z方向のスケーリングを設定
	worldTransform_[PartID::Root].scale_ = { 1.0f, 1.0f, 1.0f };

	//親
	worldTransform_[PartID::Root].Initialize();

	//脊椎
	worldTransform_[PartID::Spine].translation_ = { 0,4.5f,0 };
	worldTransform_[PartID::Spine].parent_ = &worldTransform_[PartID::Root];
	worldTransform_[PartID::Spine].Initialize();

	//上半身
	//胸
	worldTransform_[PartID::Chest].translation_ = { 0,0,0 };
	worldTransform_[PartID::Chest].parent_ = &worldTransform_[PartID::Spine];
	worldTransform_[PartID::Chest].Initialize();

	//頭
	worldTransform_[PartID::Head].translation_ = { 0,3.0f,0 };
	worldTransform_[PartID::Head].parent_ = &worldTransform_[PartID::Chest];
	worldTransform_[PartID::Head].Initialize();

	//左腕
	worldTransform_[PartID::ArmL].translation_ = { 3.0f,0,0 };
	worldTransform_[PartID::ArmL].parent_ = &worldTransform_[PartID::Chest];
	worldTransform_[PartID::ArmL].Initialize();

	//右腕
	worldTransform_[PartID::ArmR].translation_ = { -3.0f,0,0 };
	worldTransform_[PartID::ArmR].parent_ = &worldTransform_[PartID::Chest];
	worldTransform_[PartID::ArmR].Initialize();

	//下半身
	//尻
	worldTransform_[PartID::Hip].translation_ = { 0,-3.0f,0 };
	worldTransform_[PartID::Hip].parent_ = &worldTransform_[PartID::Spine];
	worldTransform_[PartID::Hip].Initialize();

	//左足
	worldTransform_[PartID::LegL].translation_ = { 3.0f,-3.0f,0 };
	worldTransform_[PartID::LegL].parent_ = &worldTransform_[PartID::Hip];
	worldTransform_[PartID::LegL].Initialize();

	//右足
	worldTransform_[PartID::LegR].translation_ = { -3.0f,-3.0f,0 };
	worldTransform_[PartID::LegR].parent_ = &worldTransform_[PartID::Hip];
	worldTransform_[PartID::LegR].Initialize();

	////カメラ垂直方向視野角を設定
	//viewProjection_.fovAngleY = XMConvertToRadians(45.0f);

	////アスペクト比を設定
	////viewProjection_.aspectRatio = 1.0f;

	////ニアクリップ距離を設定
	//viewProjection_.nearZ = 53.0f;

	////ファークリップ距離を設定
	//viewProjection_.farZ = 53.0f;

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {

#pragma region//資料02-02連続移動処理
	////視点移動処理
	//	//視点の移動ベクトル
	//	XMFLOAT3 move = { 0,0,0 };

	//	//視点の移動速さ
	//	const float kEyeSpeed = 0.2f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_W)) {
	//		move = { 0,0,kEyeSpeed };
	//	}
	//	else if (input_->PushKey(DIK_S)) {
	//		move = { 0,0,-kEyeSpeed };
	//	}
	//	//視点移動(ベクトルの加算)
	//	viewProjection_.eye.x+=move.x;
	//	viewProjection_.eye.y+=move.y;
	//	viewProjection_.eye.z+=move.z;

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	////注視点移動処理
	//	//注視点の移動ベクトル
	//	XMFLOAT3 move = { 0,0,0 };

	//	//注視点の移動速さ
	//	const float kTargetSpeed = 0.2f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_LEFT)) {
	//		move = { -kTargetSpeed,0,0 };
	//	}
	//	else if (input_->PushKey(DIK_RIGHT)) {
	//		move = { kTargetSpeed,0,0 };
	//	}
	//	//注視点移動(ベクトルの加算)
	//	viewProjection_.target.x += move.x;
	//	viewProjection_.target.y += move.y;
	//	viewProjection_.target.z += move.z;

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	////上方向回転処理
	//	//上方向の回転速さ(ラジアン/flame)
	//	const float kUpRotSpeed = 0.05f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_SPACE)) {
	//		viewAngle += kUpRotSpeed;
	//		//2πを超えたら0に戻す
	//		viewAngle = fmodf(viewAngle,XM_2PI);
	//	}

	//	//上方向ベクトルを計算(半径2の円周上の座標)
	//	viewProjection_.up = { cosf(viewAngle),sinf(viewAngle),0.0f };

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

		//デバッグテキストの表示
	debugText_->SetPos(50, 70);
	debugText_->Printf(
		"eye:(%f,%f,%f)",
		viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z);

	debugText_->SetPos(50, 85);
	debugText_->Printf(
		"target:(%f,%f,%f)",
		viewProjection_.target.x,
		viewProjection_.target.y,
		viewProjection_.target.z);

	debugText_->SetPos(50, 100);
	debugText_->Printf(
		"up:(%f,%f,%f)",
		viewProjection_.up.x,
		viewProjection_.up.y,
		viewProjection_.up.z);
#pragma endregion//資料02-02連続移動処理

#pragma region//資料02-03連続処理
	////FoV変更処理
	//{
	//	//上キーで視野角が広がる
	//	if (input_->PushKey(DIK_W)) {
	//		viewProjection_.fovAngleY += 0.01f;
	//		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
	//	}
	//	//下キーで視野角が狭まる
	//	else if (input_->PushKey(DIK_S)) {
	//		viewProjection_.fovAngleY -= 0.01f;
	//		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	//	}

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

		//デバッグテキストの表示
	debugText_->SetPos(50, 115);
	debugText_->Printf(
		"fovAngleY(Degree):%f",
		XMConvertToDegrees(viewProjection_.fovAngleY));
	//}

	////クリップ距離変更処理
	//{
	//	//上下キーでニアクリップ距離を増減
	//	if (input_->PushKey(DIK_UP)) {
	//		viewProjection_.nearZ += 0.1f;
	//	}
	//	else if (input_->PushKey(DIK_DOWN)) {
	//		viewProjection_.nearZ -= 0.1f;
	//	}
	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

		//デバッグテキストの表示
	debugText_->SetPos(50, 130);
	debugText_->Printf(
		"nearZ:%f",
		viewProjection_.nearZ);

	//}
#pragma endregion//資料02-03連続処理

	//キャラクター移動処理
	{
		//キャラクターの移動ベクトル
		XMFLOAT3 move = { 0,0,0 };

		//キャラクターの移動速さ
		const float kCharacterSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_LEFT)) {
			move = { -kCharacterSpeed,0,0 };
		}
		else if (input_->PushKey(DIK_RIGHT)) {
			move = { kCharacterSpeed,0,0 };
		}

		//注視点移動(ベクトルの加算)
		worldTransform_[PartID::Root].translation_.x += move.x;
		worldTransform_[PartID::Root].translation_.y += move.y;
		worldTransform_[PartID::Root].translation_.z += move.z;

		//更新
		worldTransform_[PartID::Root].UpdateMatrix();
		worldTransform_[PartID::Spine].UpdateMatrix();
		worldTransform_[PartID::Chest].UpdateMatrix();
		worldTransform_[PartID::Head].UpdateMatrix();
		worldTransform_[PartID::ArmL].UpdateMatrix();
		worldTransform_[PartID::ArmR].UpdateMatrix();
		worldTransform_[PartID::Hip].UpdateMatrix();
		worldTransform_[PartID::LegL].UpdateMatrix();
		worldTransform_[PartID::LegR].UpdateMatrix();


	}

	//上半身回転処理
	{
		//上半身の回転速さ
		const float kChestRotSpeed = 0.05f;

		if (input_->PushKey(DIK_U)) {
			worldTransform_[PartID::Chest].rotation_.y -= kChestRotSpeed;
		}
		else if (input_->PushKey(DIK_I)) {
			worldTransform_[PartID::Chest].rotation_.y += kChestRotSpeed;
		}

	}

	//下半身回転処理
	{
		//下半身の回転速さ
		const float kHipRotSpeed = 0.05f;

		if (input_->PushKey(DIK_J)) {
			worldTransform_[PartID::Hip].rotation_.y -= kHipRotSpeed;
		}
		else if (input_->PushKey(DIK_K)) {
			worldTransform_[PartID::Hip].rotation_.y += kHipRotSpeed;
		}

	}

	//デバッグテキストの表示
	debugText_->SetPos(50, 145);
	debugText_->Printf(
		"Root:(%f,%f,%f)",
		worldTransform_[PartID::Root].translation_.x,
		worldTransform_[PartID::Root].translation_.y,
		worldTransform_[PartID::Root].translation_.z);

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
	// 3Dモデル描画
	//model_->Draw(worldTransform_[PartID::Root], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartID::Spine], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartID::Chest], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartID::Head], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartID::ArmL], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartID::ArmR], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartID::Hip], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartID::LegL], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartID::LegR], viewProjection_, textureHandle_);

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
