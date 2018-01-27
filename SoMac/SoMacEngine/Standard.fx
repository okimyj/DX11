// Semantic 관련 https://msdn.microsoft.com/en-us/library/windows/desktop/bb509647(v=vs.85).aspx .
cbuffer TransformBuffer : register(b0)
{
	matrix g_matWorld;
	matrix g_matView;
	matrix g_matProj;
}
Texture2D g_tex_0 : register(t0);
SamplerState g_default_sampler : register(s0);				// 아무것도 들어오지 않으면 default로 0으로 되어있는 놈을 사용한다.

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
	output.vColor = g_tex_0.Sample(g_default_sampler, _input.vUV);
	return output;
}