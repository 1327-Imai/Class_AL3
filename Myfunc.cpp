#include "Myfunc.h"

using namespace Myfunc;

#pragma region//���[���h�ϊ��s��𐶐�����֐�

void setMatScale(Matrix4& affineMat , Vector3 scale) {
	//�X�P�[�����O�s���錾
	Matrix4 matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	affineMat *= matScale;

}

void setMatRotation(Matrix4& affineMat , Vector3 rotation) {

	//��]�s���錾
	Matrix4 matRotX = {
		1 , 0 , 0 , 0 ,
		0 , cos(rotation.x) , sin(rotation.x) , 0 ,
		0 , -sin(rotation.x) , cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	Matrix4 matRotY = {
		cos(rotation.y) , 0 , -sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		sin(rotation.y) , 0 , cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	Matrix4 matRotZ = {
		cos(rotation.z) , sin(rotation.z) , 0 , 0 ,
		-sin(rotation.z) , cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	affineMat *= matRotX;
	affineMat *= matRotY;
	affineMat *= matRotZ;

}

void setMatTranslation(Matrix4& affineMat , Vector3 translation) {

	Matrix4 matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	affineMat *= matTranslation;
}

#pragma endregion