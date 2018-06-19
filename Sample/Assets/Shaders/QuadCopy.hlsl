
struct VS_INPUT
{
	float3 vPosition : vPosition;
};

struct PS_INPUT
{
	float4 Position : SV_Position;
	float2 fTexCoords : TexCoord;
};


PS_INPUT vertex(VS_INPUT input)
{
	PS_INPUT output;

	output.Position = float4(input.vPosition, 1.0);
	output.fTexCoords = input.vPosition.xy / 2.0 + float2(0.5, 0.5);

	return output;
}


Texture2D uTexture : register(t0);
SamplerState uTextureSampler : register(s0);

float4 pixel(PS_INPUT input) : SV_Target
{
	return float4(uTexture.Sample(uTextureSampler, input.fTexCoords).rgb, 1.0);
}
