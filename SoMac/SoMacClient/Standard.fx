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
	output.vPos = float4(_input.vPos, 1.f);
	output.vColor = _input.vColor;
	return output;
}

PS_OUTPUT PS_Color(VS_OUTPUT _input)
{
	PS_OUTPUT output = (PS_OUTPUT)0.f;
	output.vColor = _input.vColor;
	return output;
}