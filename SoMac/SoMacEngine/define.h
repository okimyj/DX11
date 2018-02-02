#pragma once

#define WINSIZE_X 800
#define WINSIZE_Y 450

#define SINGLE(Type) public : \
									static Type* GetInst()\
									{\
										static Type mgr;\
										return &mgr;\
									}\
								private:\
									Type();\
									~Type();


#define RET_FAILED -1
#define RET_SUCCESS 1


#define SAFE_RELEASE(p) if(NULL != p) p->Release();
#define SAFE_DELETE(p) if(NULL != p) delete p; p = NULL;
#define SAFE_DELETE_ARR(p) if(NULL != p) delete[] p; p=NULL; 

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define MAX_LAYER 32

#define LAYER_DEFAULT L"Default"
#define LAYER_TRANSPARENT L"Transparent"
#define LAYER_CAMERA L"Camera"

// Script는 여러개가 붙을 수 있어서 추가 안함. 
enum class COMPONENT_TYPE
{
	TRANSFORM,
	MESHRENDER,
	CAMERA,
	COLLIDER,
	TEXTURE_ANIMATOR,
	END,
};

enum class SHADER_TYPE
{
	ST_VERTEX = 0x01,
	ST_HULL = 0x02,
	ST_DOMAIN = 0x04,
	ST_GEOMETRY = 0x08,
	ST_COMPUTE = 0x10,
	ST_PIXEL = 0x20,
};

enum class RASTERIZE_TYPE
{
	FRONT,
	BACK,
	WIRE,
	NONE,
	END,
};

enum class SHADER_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,
	INT_END,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,
	FLOAT_END,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,
	VEC4_END,

	TEXTURE_0,
	TEXTURE_1,
	TEXTURE_2,
	TEXTURE_3,
	TEXTURE_END,
	END,
};