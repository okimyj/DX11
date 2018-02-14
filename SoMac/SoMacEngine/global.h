#pragma once
#define _XM_NO_INTRINSICS_
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#include "..\External\include\DirectXTex.h"
#pragma comment(lib, "DirectXTex")


#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <time.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

#include "define.h"
#include "func.h"
#include "struct.h"

extern tTransform g_Transform;
extern UINT g_SPRegister[(UINT)SHADER_PARAM::END];			// shader param register index.
extern wchar_t* g_SPName[(UINT)SHADER_PARAM::END];		// shader param register name.

extern bool g_bShowCollider;