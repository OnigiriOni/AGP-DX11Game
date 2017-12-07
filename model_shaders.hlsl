Texture2D texture0;
SamplerState sampler0;

cbuffer CBuffer0
{
	matrix WVPMatrix;	// 64 bytes
}	// total 64 bytes

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

VOut ModelVS(float4 position : POSITION, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	float4 default_color = {1, 1, 1, 1};
	output.color = default_color;
	output.position = mul(WVPMatrix, position);
	output.texcoord = texcoord;

	return output;
}

float4 ModelPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return texture0.Sample(sampler0, texcoord) * color;
}