#pragma once
#define _XM_NO_INTRINSICS_
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")


#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

#include "define.h"
#include "func.h"
#include "struct.h"

extern tTransform g_Transform;