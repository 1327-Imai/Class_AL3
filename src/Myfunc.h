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
	void SetMatScale(Matrix4& affineMat , Vector3 scale);				//�X�P�[�����O�s���ݒ肷��֐�
	void SetMatRotation(Matrix4& affineMat , Vector3 rotation);			//��]�s���ݒ肷��֐�
	void SetMatTranslation(Matrix4& affineMat , Vector3 translation);	//���s�ړ��s��̐ݒ������֐�

	//�x���@�̌ʓx�@�̊֐�
	float Dig2Rad(float dig);	//�x���@���ʓx�@�ɕϊ�����֐�
	float Rad2Dig(float rad);	//�ʓx�@��x���@�ɕϊ�����֐�

	//WorldTransform���X�V����֐�
	void UpdateWorldTransform(WorldTransform& worldTransform);

}