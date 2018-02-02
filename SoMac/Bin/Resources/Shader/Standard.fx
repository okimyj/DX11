#include "values.fx"
// Semantic ฐüทร https://msdn.microsoft.com/en-us/library/windows/desktop/bb509647(v=vs.85).aspx .
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