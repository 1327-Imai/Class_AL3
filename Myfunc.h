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

	//ƒ[ƒ‹ƒh•ÏŠ·s—ñ‚ğ¶¬‚·‚éŠÖ”
	void setMatScale(Matrix4& affineMat , Vector3 scale);
	void setMatRotation(Matrix4& affineMat , Vector3 rotation);
	void setMatTranslation(Matrix4& affineMat , Vector3 translation);

}