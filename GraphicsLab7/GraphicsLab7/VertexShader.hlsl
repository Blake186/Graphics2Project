#pragma pack_matrix(row_major)

struct VertexInput
{
	float4 m_postionL : POSITION;
	float4 m_color : COLOR;
	float2 UV :UVCOORD;
	float2 m_nrm : NmrCOORD;
};


struct VertexOutPut
{
	float4 m_Color : COLOR;

	float4 m_PositionH : SV_POSITION;

	float2 m_UV : UVCOORD;
	float2 m_nrm : NmrCOORD;
};

cbuffer OBJECT : register(b0)
{

	float4x4 WorldMatrix;


}

cbuffer SCENE :register(b1)
{
	float4x4 viewMatrix;
	float4x4 ProjectionMatrix;


}


VertexOutPut main(VertexInput input)
{
	VertexOutPut m_output = (VertexOutPut)0;
	float4 m_local = float4(input.m_postionL.xyz, 1);// float4(input.m_postionL.xyz, 1);

		m_local = mul(m_local, WorldMatrix);
	m_local = mul(m_local, viewMatrix);
	m_local = mul(m_local, ProjectionMatrix);
	m_output.m_Color = input.m_color;
	m_output.m_UV = input.UV;
	m_output.m_nrm = input.m_nrm;
	m_output.m_PositionH = m_local;
	return m_output;


}

