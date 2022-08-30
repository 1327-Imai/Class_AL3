#pragma once

#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "src/Myfunc.h"
#include "src/Player.h"
#include "src/Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public:
	//パーツID
	enum PartId {
		kRoot ,		//大元
		kSpine ,	//脊椎
		kChest ,	//胸
		kHead ,		//頭
		kArm_L ,	//左腕
		kArm_R ,	//右腕
		kHip ,		//尻
		kLeg_L ,	//左足
		kLeg_R ,	//右足

		kNumPartId
	};

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	const float PI = 3.141592f;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	Model* model_ = nullptr;

	//ワールドトランスフォーム
	//自キャラ
	std::unique_ptr<Player> player_ = std::make_unique<Player>();

	//敵
	std::unique_ptr <Enemy> enemy_ = std::make_unique<Enemy>();

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	int isDebugCameraActive_ = false;	//デバッグカメラ有効フラグ

};
