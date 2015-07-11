struct VertexOutPut
{
	float4 colorOut : COLOR;
	float4 projectedCoordinate : SV_POSITION;
	float3 m_UV : UVCOORD;
	float2 m_nrm : NmrCOORD;
};





TextureCube Skybox:register(t0);

SamplerState filters :register(s0);

float4 main(VertexOutPut input) : SV_TARGET
{

	return Skybox.Sample(filters, input.m_UV);
}