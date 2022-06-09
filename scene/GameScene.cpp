#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;
	delete debugCamera_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	//3Dモデルの生成
	model_ = Model::Create();

#pragma region//乱数生成の下準備
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の設定
	std::uniform_real_distribution<float> rotDist(-PI , PI);
	std::uniform_real_distribution<float> posDist(-10 , 10);
#pragma endregion

#pragma region//worldTransform
	//ワールドトランスフォームの初期化
	//親(0番)
	worldTransforms_[0].Initialize();

	//子(1番)
	worldTransforms_[1].Initialize();
	worldTransforms_[1].translation_ = {0 , 4.5 , 0};
	worldTransforms_[1].parent_ = &worldTransforms_[0];

#pragma endregion

#pragma region//viewProjection
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
#pragma endregion 
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280 , 720);

	//軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);

	//軸方向表示が参考にするビュープロジェクションを設定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {

#pragma region//worldTransform

	{
		//キャラクターの移動ベクトル
		Vector3 move = {0 , 0 , 0};

		float characterSpeed = 0.5f;

		//左か右キーを押していたらmove(移動量)を変化させる
		if (input_->PushKey(DIK_RIGHT)) {
			move.x += characterSpeed;
		}
		if (input_->PushKey(DIK_LEFT)) {
			move.x -= characterSpeed;
		}

		//moveを加算
		worldTransforms_[0].translation_ += move;

		//アフィン変換用の行列を宣言
		Matrix4 affineMat = MathUtility::Matrix4Identity();

		//ワールド行列の計算
		Myfunc::SetMatTranslation(affineMat , worldTransforms_[0].translation_);
		worldTransforms_[0].matWorld_ *= affineMat;

		//行列の転送
		worldTransforms_->TransferMatrix();

		//デバッグ表示
		debugText_->SetPos(50 , 50);
		debugText_->Printf(
			"Translation:(%f,%f,%f)" ,
			worldTransforms_[0].translation_.x ,
			worldTransforms_[0].translation_.y ,
			worldTransforms_[0].translation_.z
		);
	}

#pragma endregion

#pragma region//viewProjection

	////視点移動処理
	//{
	//	Vector3 move = {0 , 0 , 0};

	//	//視点移動の速さ
	//	const float kEyeSpeed = 0.2f;

	//	//押した方向で移動ベクトルの変更
	//	if (input_->PushKey(DIK_W)) {
	//		move.z += kEyeSpeed;
	//	}

	//	if (input_->PushKey(DIK_S)) {
	//		move.z -= kEyeSpeed;
	//	}

	//	//視点移動
	//	viewProjection_.eye += move;

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	デバッグ表示
	//debugText_->SetPos(50 , 50);
	//debugText_->Printf(
	//	"eye:(%f,%f,%f)" ,
	//	viewProjection_.eye.x ,
	//	viewProjection_.eye.y ,
	//	viewProjection_.eye.z
	//);
	//}

	////上方向回転処理
	//{
	//	Vector3 move = {0 , 0 , 0};

	//	//上方向回転の速さ
	//	const float kTargetSpeed = 0.2f;

	//	//押した方向で移動ベクトルの変更
	//	if (input_->PushKey(DIK_LEFT)) {
	//		move.x -= kTargetSpeed;
	//	}

	//	if (input_->PushKey(DIK_RIGHT)) {
	//		move.x += kTargetSpeed;
	//	}

	//	//上方向回転
	//	viewProjection_.target += move;

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	デバッグ表示
	//debugText_->SetPos(50 , 65);
	//debugText_->Printf(
	//	"target:(%f,%f,%f)" ,
	//	viewProjection_.target.x ,
	//	viewProjection_.target.y ,
	//	viewProjection_.target.z
	//);
	//}

	////上方向回転処理
	//{
	//	//上方向回転の速さ
	//	const float kUpRotSpeed = 0.05f;

	//	//押した方向で移動ベクトルの変更
	//	if (input_->PushKey(DIK_SPACE)) {
	//		viewangle += kUpRotSpeed;
	//		//2πを超えたら0に戻す
	//		viewangle = fmodf(viewangle , PI * 2.0f);
	//	}

	//	//上方向回転
	//	viewProjection_.up = {cosf(viewangle) , sinf(viewangle) , 0.0f};

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	デバッグ表示
	//debugText_->SetPos(50 , 80);
	//debugText_->Printf(
	//	"up:(%f,%f,%f)" ,
	//	viewProjection_.up.x ,
	//	viewProjection_.up.y ,
	//	viewProjection_.up.z
	//);
	//}

	//fov変換処理
	//{
	//	//上キーで視野が広がる
	//	if (input_->PushKey(DIK_UP)) {
	//		if (viewProjection_.fovAngleY < PI) {
	//			viewProjection_.fovAngleY += PI / 180;
	//		}
	//	}
	//	//下キーで視野が狭まる
	//	if (input_->PushKey(DIK_DOWN)) {
	//		if (0 < viewProjection_.fovAngleY) {
	//			viewProjection_.fovAngleY -= PI / 180;
	//		}
	//	}

	//	viewProjection_.UpdateMatrix();

	//	デバッグ表示
	//	debugText_->SetPos(50 , 95);
	//	debugText_->Printf(
	//		"fovAngleY(Degree):%f" ,
	//		Myfunc::rad2dig(viewProjection_.fovAngleY)
	//	);
	//}

	//クリップ距離変更処理
	//{
	//	上下キーでクリップ距離を増減
	//	if (input_->PushKey(DIK_UP)) {
	//		viewProjection_.nearZ += 0.1f;
	//	}
	//	if (input_->PushKey(DIK_DOWN)) {
	//		viewProjection_.nearZ -= 0.1f;
	//	}

	//	viewProjection_.UpdateMatrix();

	//	デバッグ表示
	//	debugText_->SetPos(50 , 110);
	//	debugText_->Printf(
	//		"nearZ:%f" ,
	//		viewProjection_.nearZ
	//	);
	//}

#pragma endregion

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
	//3Dモデル描画
	for (WorldTransform& worldTransform_ : worldTransforms_) {
		model_->Draw(worldTransform_ , viewProjection_ , textureHandle_);
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

	//デバッグカメラの更新
	//debugCamera_->Update();

#pragma endregion
}