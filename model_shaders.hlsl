Texture2D texture0;
SamplerState sampler0;

cbuffer CBuffer0
{
	matrix WVPMatrix;				// 64 bytes
	float4 directionalLightVector;	// 16 bytes
	float4 directionalLightColour;	// 16 bytes
	float4 ambientLightColour;		// 16 bytes
}	// total 112 bytes

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

VOut ModelVS(float4 position : POSITION, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	//float4 default_color = {1, 1, 1, 1};
	//output.color = default_color;

	float diffuse_amount = dot(directionalLightVector, normal);
	diffuse_amount = saturate(diffuse_amount);
	output.color = ambientLightColour + (directionalLightColour * diffuse_amount);
	
	output.position = mul(WVPMatrix, position);
	output.texcoord = texcoord;

	return output;
}

float4 ModelPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return texture0.Sample(sampler0, texcoord) * color;
}