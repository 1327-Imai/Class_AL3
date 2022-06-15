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

namespace Myfunc {

	//ワールド変換行列を生成する関数
	void SetMatScale(Matrix4& affineMat , Vector3 scale);
	void SetMatRotation(Matrix4& affineMat , Vector3 rotation);
	void SetMatTranslation(Matrix4& affineMat , Vector3 translation);

	//度数法⇔弧度法の関数
	float dig2rad(float dig);
	float rad2dig(float rad);

	//子のWorldTransformを更新する関数
	void UpdateChildeWorldTransform(WorldTransform& worldTransform);

}