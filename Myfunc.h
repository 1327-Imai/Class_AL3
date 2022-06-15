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

	//���[���h�ϊ��s��𐶐�����֐�
	void SetMatScale(Matrix4& affineMat , Vector3 scale);
	void SetMatRotation(Matrix4& affineMat , Vector3 rotation);
	void SetMatTranslation(Matrix4& affineMat , Vector3 translation);

	//�x���@�̌ʓx�@�̊֐�
	float dig2rad(float dig);
	float rad2dig(float rad);

	//�q��WorldTransform���X�V����֐�
	void UpdateChildeWorldTransform(WorldTransform& worldTransform);

}