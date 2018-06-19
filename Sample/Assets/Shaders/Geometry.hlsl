
struct VS_INPUT
{
	float3 vPosition : vPosition;
	float3 vNormal : vNormal;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float3 fWorldPosition : POSITION;
	float3 fNormal : NORMAL;
};

struct PixelShaderOutput
{
	float4 Color    : SV_Target0;
	float4 Position : SV_Target1;
	float4 Normal   : SV_Target2;
};



struct SMaterial
{
	float3 AmbientColor;
	float3 DiffuseColor;
};

cbuffer Material
{
	SMaterial uMaterial;
};

cbuffer Scene
{
	float4x4 uModelMatrix;
	float4x4 uNormalMatrix;
	float4x4 uViewMatrix;
	float4x4 uProjectionMatrix;
};


// const float NEAR = 0.1; // projection matrix's near plane
// const float FAR = 50.0; // projection matrix's far plane
// float LinearizeDepth(float depth)
// {
// 	float z = depth * 2.0 - 1.0; // Back to NDC
// 	return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));
// }



PS_INPUT vertex(VS_INPUT input)
{
	PS_INPUT output;

	float4 WorldPosition = mul(uViewMatrix, mul(uModelMatrix, float4(input.vPosition, 1.0)));

	output.fWorldPosition = WorldPosition.xyz;
	output.fNormal = normalize(mul(uNormalMatrix, float4(input.vNormal, 0.0)).xyz);
	output.Position = mul(uProjectionMatrix, WorldPosition);

	return output;
}

PixelShaderOutput pixel(PS_INPUT input)
{
	PixelShaderOutput output;

	output.Color = float4(uMaterial.DiffuseColor, 0.0);
	output.Position.xyz = input.fWorldPosition;
	output.Position.a = /*LinearizeDepth*/(input.Position.z);
	output.Normal = float4(normalize(input.fNormal), 0.0);

	return output;
}
