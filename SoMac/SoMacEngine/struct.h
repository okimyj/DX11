#pragma once
#include "global.h"

typedef XMMATRIX Matrix;
//typedef XMFLOAT3 Vec3;
typedef XMFLOAT4 Vec4;
typedef XMFLOAT2 Vec2;
struct Vec3 : XMFLOAT3{
	Vec3() : XMFLOAT3(0.f, 0.f, 0.f){}
	Vec3(float _x, float _y, float _z) :XMFLOAT3(_x, _y, _z) { }
	Vec3(FXMVECTOR _xmVec) : XMFLOAT3(0.f,0.f,0.f) 
	{
		XMStoreFloat3(this, _xmVec);
	}
	
	XMVECTOR Convert()
	{
		return XMLoadFloat3((XMFLOAT3*)this);
	}
	float Distance()
	{
		// ��Ÿ��� ����.
		return sqrt(x*x + y*y + z*z);
	}
	void Normalize()
	{
		// ������ ��Ҹ� ������ ���̷� ������.
		float fDist = Distance();
		if (fDist == 0.f)
			return;
		x /= fDist;
		y /= fDist;
		z /= fDist;
	}
	// ����.
	float Dot(const Vec3& _other)
	{
		return (x*_other.x) + (y*_other.y) + (z*_other.z);
	}

	const Vec3& operator = (FXMVECTOR _xmvec)
	{
		XMStoreFloat3(this, _xmvec);
		return (*this);
	}
	float& operator[](int _iIdx)
	{
		switch (_iIdx)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			assert(NULL);
		}
	}
	//== operator + ====================================================//
	const Vec3 operator + (const Vec3& _other)
	{
		return Vec3(x + _other.x, y + _other.y, z + _other.z);
	}
	const Vec3 operator + (const FXMVECTOR& _other)
	{
		return Vec3(x + _other.vector4_f32[0], y + _other.vector4_f32[1], z + _other.vector4_f32[2]);
	}
	const Vec3 operator += (const Vec3 _other)
	{
		x += _other.x;
		y += _other.y;
		z += _other.z;
		return (*this);
	}
	//== operator - ====================================================//
	const Vec3 operator - (const Vec3& _other)
	{
		return Vec3(x - _other.x, y - _other.y, z - _other.z);
	}
	const Vec3 operator - (const FXMVECTOR& _other)
	{
		return Vec3(x - _other.vector4_f32[0], y - _other.vector4_f32[1], z - _other.vector4_f32[2]);
	}
	const Vec3 operator -= (const Vec3 _other)
	{
		x -= _other.x;
		y -= _other.y;
		z -= _other.z;
		return (*this);
	}

	//== operator * ====================================================//
	const Vec3 operator * (const Vec3& _other)
	{
		return Vec3(x * _other.x, y * _other.y, z * _other.z);
	}
	const Vec3 operator * (const FXMVECTOR& _other)
	{
		return Vec3(x * _other.vector4_f32[0], y * _other.vector4_f32[1], z * _other.vector4_f32[2]);
	}
	const Vec3 operator *= (const Vec3 _other)
	{
		x *= _other.x;
		y *= _other.y;
		z *= _other.z;
		return (*this);
	}

	//== operator / ====================================================//
	const Vec3 operator / (const Vec3& _other)
	{
		Vec3 vRet(
			_other.x == 0.f ? 0.f:x/_other.x
			, _other.y == 0.f ? 0.f : y / _other.y
			, _other.z == 0.f ? 0.f : z / _other.z
		);
		
		return vRet;
	}
	const Vec3 operator / (const FXMVECTOR& _other)
	{
		Vec3 vRet(
			_other.vector4_f32[0] == 0.f ? 0.f : x / _other.vector4_f32[0]
			, _other.vector4_f32[1] == 0.f ? 0.f : y / _other.vector4_f32[1]
			, _other.vector4_f32[2] == 0.f ? 0.f : z / _other.vector4_f32[2]
		);
		
		return vRet;
	}
	const Vec3 operator /= (const Vec3 _other)
	{
		x = _other.x == 0.f ? 0.f : x / _other.x;
		y = _other.y == 0.f ? 0.f : y / _other.y;
		z = _other.z == 0.f ? 0.f : z / _other.z;
		
		return (*this);
	}

};

// ����ü�� �⺻������ ���� ū �ڷ����� ũ�⸦ �޸� �Ҵ� �������� ��´�.
// �׷��ٸ� �Ʒ��� ����ü�� ũ��� ���� 32byte �� �Ǿ�� �ϴµ� 28byte �̴�.
// #pragma once pack(n) �� �����س����� �� �ڷ����� ũ�⿡ �� �°� �޸� �Ҵ� �ȴ�.
// directX ���� ��� �Ǿ��ְ���.
typedef struct _tabVTX 
{
	Vec3	vPos;
	Vec2 vUV;
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



// Device ���� constant buffer�� �����ϱ� ���� ����ü. 
struct CBUFFER
{
	ID3D11Buffer* pBuffer;
	UINT			iRegister;
	UINT					iSize;

};

//== Shader Param ==//
typedef struct _tagSP
{
	SHADER_PARAM		eShaderParam;
	UINT						iRegister;
	UINT						iTiming;
}tShaderParam;

//== Constant Buffer  ==//
typedef struct _tagTransform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;
}tTransform;

// == Anim Buffer ==//
struct tAnimInfo
{
	Vec4 vUV;
	Vec4 vAnim;
};