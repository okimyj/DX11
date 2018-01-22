#pragma once
#include "global.h"

typedef XMMATRIX Matrix;
typedef XMFLOAT3 Vec3;
typedef XMFLOAT4 Vec4;
typedef XMFLOAT2 Vec2;

// ����ü�� �⺻������ ���� ū �ڷ����� ũ�⸦ �޸� �Ҵ� �������� ��´�.
// �׷��ٸ� �Ʒ��� ����ü�� ũ��� ���� 32byte �� �Ǿ�� �ϴµ� 28byte �̴�.
// #pragma once pack(n) �� �����س����� �� �ڷ����� ũ�⿡ �� �°� �޸� �Ҵ� �ȴ�.
// directX ���� ��� �Ǿ��ְ���.
typedef struct _tabVTX 
{
	Vec3	vPos;
	Vec4 vColor;
}VTX;

typedef struct _tabIndex16
{
	WORD _1, _2, _3;
	_tabIndex16() 
		: _1(0), _2(0), _3(0) {}
	_tabIndex16(WORD __1, WORD __2, WORD __3)
		: _1(__1), _2(__2), _3(__3) {}
	static UINT size() {return sizeof(WORD);	}
	static DXGI_FORMAT format() { return DXGI_FORMAT_R16_UINT; }
}INDEX16;

typedef struct _tabIndex32
{
	DWORD _1, _2, _3;
	_tabIndex32()
		: _1(0), _2(0), _3(0) {}
	_tabIndex32(DWORD __1, DWORD __2, DWORD __3)
		: _1(__1), _2(__2), _3(__3) {}
	static UINT size() { return sizeof(DWORD); }
	static DXGI_FORMAT format() { return DXGI_FORMAT_R32_UINT; }
}INDEX32;

//== Constant Buffer  ==//
typedef struct _tagTransform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;
}tTransform;