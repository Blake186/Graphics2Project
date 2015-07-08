struct VertexOutPut
{
	float4 colorOut : COLOR;
	float4 projectedCoordinate : SV_POSITION;
	float2 m_UV : UVCOORD;
	float2 m_nrm : NmrCOORD;
};

cbuffer Animation
{
	float frame;
	float width;
	float totalframes;
	float height;
};

texture2D baseTexture : register(t0);
texture2D DetailTexture:register(t1);
SamplerState filters :register(s0);
float4 main(VertexOutPut colorFromRasterizer) : SV_TARGET
{
	(colorFromRasterizer.m_UV[0]) /= 4;
	if (height != 0)
	{
		
		colorFromRasterizer.m_UV[0] += (frame * (512 / 4)) / 512;
	}


	float4 baseColor = baseTexture.Sample(filters, colorFromRasterizer.m_UV);
		float4 FinalColor;
	FinalColor.a = baseColor.r;
	FinalColor.r = baseColor.g;
	FinalColor.g = baseColor.b;
	FinalColor.b = baseColor.a;

	return FinalColor;
}

