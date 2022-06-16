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
	void SetMatScale(Matrix4& affineMat , Vector3 scale);				//スケーリング行列を設定する関数
	void SetMatRotation(Matrix4& affineMat , Vector3 rotation);			//回転行列を設定する関数
	void SetMatTranslation(Matrix4& affineMat , Vector3 translation);	//平行移動行列の設定をする関数

	//度数法⇔弧度法の関数
	float Dig2Rad(float dig);	//度数法を弧度法に変換する関数
	float Rad2Dig(float rad);	//弧度法を度数法に変換する関数

	//WorldTransformを更新する関数
	void UpdateWorldTransform(WorldTransform& worldTransform);

}