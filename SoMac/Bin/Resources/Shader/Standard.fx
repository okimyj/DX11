// Semantic ฐüทร https://msdn.microsoft.com/en-us/library/windows/desktop/bb509647(v=vs.85).aspx .
cbuffer TransformBuffer : register(b0)
{
	matrix g_matWorld;
	matrix g_matView;
	matrix g_matProj;
}

struct VS_INPUT
{
	float3 vPos : POSITION;
	float4 vColor : COLOR;
};

struct VS_OUTPUT
{
	float4 vPos : SV_POSITION;
	float4 vColor : COLOR;
};

struct PS_OUTPUT
{
	float4 vColor : SV_Target;
};

VS_OUTPUT VS_Color(VS_INPUT _input)
{
	VS_OUTPUT output = (VS_OUTPUT)0.f;
	// TODO ;
	float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
	float4 vViewPos = mul(vWorldPos, g_matView);
	float4 vProjPos = mul(vViewPos, g_matProj);

	output.vPos = vProjPos;
	output.vColor = _input.vColor;
	return output;
}

PS_OUTPUT PS_Color(VS_OUTPUT _input)
{
	PS_OUTPUT output = (PS_OUTPUT)0.f;
	output.vColor = _input.vColor;
	return output;
}