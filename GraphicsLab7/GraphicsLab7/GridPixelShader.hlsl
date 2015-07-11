
struct VertexOutPut
{
	float4 colorOut : COLOR;
	float4 projectedCoordinate : SV_POSITION;
	float2 m_UV : UVCOORD;
	float2 m_nrm : NmrCOORD;
};

float4 main(VertexOutPut input) : SV_TARGET
{
	float4 FinalColor;
	FinalColor.a = input.colorOut.a;
	FinalColor.r = input.colorOut.r;
	FinalColor.g = input.colorOut.g;
	FinalColor.b = input.colorOut.b;


	return FinalColor;
}