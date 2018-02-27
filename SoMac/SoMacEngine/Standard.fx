#include "values.fx"
// Semantic 관련 https://msdn.microsoft.com/en-us/library/windows/desktop/bb509647(v=vs.85).aspx .

struct PS_OUTPUT
{
	float4 vColor : SV_Target;
};
// == Vertext Color Shader == //
struct VS_COLOR_INPUT
{
	float3 vPos : POSITION;
	float4 vColor : COLOR;
};

struct VS_COLOR_OUTPUT
{
	float4 vPos : SV_POSITION;
	float4 vColor : COLOR;
};

VS_COLOR_OUTPUT VS_Color(VS_COLOR_INPUT _input)
{
	VS_COLOR_OUTPUT output = (VS_COLOR_OUTPUT)0.f;
	// TODO ;
	float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
	float4 vViewPos = mul(vWorldPos, g_matView);
	float4 vProjPos = mul(vViewPos, g_matProj);

	output.vPos = vProjPos;
	output.vColor = _input.vColor;
	return output;
}

PS_OUTPUT PS_Color(VS_COLOR_OUTPUT _input)
{
	PS_OUTPUT output = (PS_OUTPUT)0.f;
	output.vColor = _input.vColor;
	return output;
}

// == Texture Shader == //
// g_tex_0
// g_int_0
// ============== //
struct VS_TEXTURE_INPUT
{
	float3 vPos : POSITION;
	float2 vUV : TEXCOORD;
};

struct VS_TEXTURE_OUTPUT
{
	float4 vPos : SV_POSITION;
	float2 vUV : TEXCOORD;
};

VS_TEXTURE_OUTPUT VS_Texture(VS_TEXTURE_INPUT _input)
{
	VS_TEXTURE_OUTPUT output = (VS_TEXTURE_OUTPUT)0.f;
	float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
	float4 vViewPos = mul(vWorldPos, g_matView);
	float4 vProjPos = mul(vViewPos, g_matProj);
	output.vPos = vProjPos;
	output.vUV = _input.vUV;
	return output;
}

PS_OUTPUT PS_Texture(VS_TEXTURE_OUTPUT _input)
{
	PS_OUTPUT output = (PS_OUTPUT)0.f;
	float4 vCol = g_tex_0.Sample(g_default_sampler, _input.vUV);
	
	if (g_int_0)
	{
		vCol.rgb = (vCol.r + vCol.g + vCol.b) / 3.f;
	}
	output.vColor = vCol;	
	return output;
}

PS_OUTPUT PS_Cartoon_Texture(VS_TEXTURE_OUTPUT _input)
{
	PS_OUTPUT output = (PS_OUTPUT)0.f;
	
	
	float4 vCol = g_tex_0.Sample(g_default_sampler, _input.vUV);
	vCol = ceil(vCol * 8) / 8.0f;

	if (g_int_0)
	{
		vCol.rgb = (vCol.r + vCol.g + vCol.b) / 3.f;
	}

	output.vColor = vCol;
	return output;
}

//== Collider Shader ========//
// g_int_0
//====================//
struct VS_COLLIDER_OUTPUT
{
	float4 vPos : SV_POSITION;
};

VS_COLLIDER_OUTPUT VS_Collider(float3 vPos : POSITION)
{
	VS_COLLIDER_OUTPUT output = (VS_COLLIDER_OUTPUT) 0.f;

	float4 vWorldPos = mul(float4(vPos, 1.f), g_matWorld);
	float4 vViewPos = mul(vWorldPos, g_matView);
	float4 vProjPos = mul(vViewPos, g_matProj);

	output.vPos = vProjPos;

	return output;
}
PS_OUTPUT PS_Collider(VS_COLLIDER_OUTPUT _input)
{
	PS_OUTPUT output = (PS_OUTPUT) 0.f;

	if (g_int_0)
	{
		output.vColor = float4(1.f, 0.f, 0.f, 1.f);
	}
	else
	{
		output.vColor = float4(0.f, 1.f, 0.f, 1.f);
	}

	return output;
}



// == Standard 2DTexture Shader == //
// g_int_0 : gray scale.
// g_int_1 : Animation 인지 아닌지. 1, 0
// g_tex_0 : Texture
// g_vec4_0 : x, y (Left Top UV), z(width), w(height)
// ============== //
struct VS_STD_INPUT
{
	float3 vPos : POSITION;
	float2 vUV : TEXCOORD;
};

struct VS_STD_OUTPUT
{
	float4 vPos : SV_POSITION;
	float2 vUV : TEXCOORD;
};

VS_STD_OUTPUT VS_Std2D(VS_STD_INPUT _input)
{
	VS_STD_OUTPUT output = (VS_STD_OUTPUT)0.f;
	float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
	float4 vViewPos = mul(vWorldPos, g_matView);
	float4 vProjPos = mul(vViewPos, g_matProj);
	output.vPos = vProjPos;
	output.vUV = _input.vUV;
	return output;
}

PS_OUTPUT PS_Std2D(VS_STD_OUTPUT _input)
{
	PS_OUTPUT output = (PS_OUTPUT)0.f;
	float4 vCol = (float4)0.f;
	// animator 기반인지(1), 일반 texture 기반인지(0).
	if (g_vec4_anim.x)
	{
		// _input.vUV 이게 보간 되어서 들어온 값이니까 이걸 이용 해서 비율을 알아내자.
		// g_vec4_0.x = Left // g_vec4_0.y = Top 
		// g_vec4_0.z = width // g_vec4_0.w = height
		// left_top 에 width와 height 에 보간되어 온 비율을 곱한값을 더하면 나오겠지.
		float2 vUV = float2(g_vec4_uv.x + (g_vec4_uv.z * _input.vUV.x)
			, g_vec4_uv.y + (g_vec4_uv.w * _input.vUV.y));

		vCol = g_tex_anim.Sample(g_default_sampler, vUV);
	}
	else
		vCol = g_tex_0.Sample(g_default_sampler, _input.vUV);

	

	if (g_int_0)
	{
		vCol.rgb = (vCol.r + vCol.g + vCol.b) / 3.f;
	}
	output.vColor = vCol;
	return output;
}
