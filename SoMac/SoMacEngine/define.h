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