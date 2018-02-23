
cbuffer TransformBuffer : register(b0)
{
	matrix g_matWorld;
	matrix g_matView;
	matrix g_matProj;
}

cbuffer INT : register(b1)
{
	int g_int_0;
	int g_int_1;
	int g_int_2;
	int g_int_3;
}

cbuffer FLOAT : register(b2)
{
	float g_float_0;
	float g_float_1;
	float g_float_2;
	float g_float_3;
}

cbuffer VEC4 : register(b3)
{
	float4 g_vec4_0;
	float4 g_vec4_1;
	float4 g_vec4_2;
	float4 g_vec4_3;
}

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
SamplerState g_default_sampler : register(s0);				// 아무것도 들어오지 않으면 default로 0으로 되어있는 놈을 사용한다.


// Animation Constant buffer. (16byte 단위로 선언되어야 함. 그래서 g_vec4_anim에 값 1개만 필요한데 그냥 float4로 잡은 것.).
cbuffer VEC4 : register(b13)
{
	float4 g_vec4_uv; // xy(uv), z(width), w(height).
	float4 g_vec4_anim; // x(Animator 유무).
}

Texture2D g_tex_anim : register(t16);