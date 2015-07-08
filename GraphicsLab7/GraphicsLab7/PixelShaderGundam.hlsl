struct VertexOutPut
{
	float4 colorOut : COLOR;
	float4 projectedCoordinate : SV_POSITION;
	float2 m_UV : UVCOORD;
	float2 m_nrm : NmrCOORD;
};

texture2D baseTexture : register(t0);
texture2D DetailTexture:register(t1);
SamplerState filters :register(s0);
float4 main(VertexOutPut colorFromRasterizer) : SV_TARGET
{
	float4 baseColor = baseTexture.Sample(filters, colorFromRasterizer.m_UV);
	float4 FinalColor;
	FinalColor.a = baseColor.a;
	FinalColor.r = baseColor.r;
	FinalColor.g = baseColor.g;
	FinalColor.b = baseColor.b;

	return baseColor;
}