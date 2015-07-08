#pragma pack_matrix(row_major)
struct Gridinput
{
	float4 m_position : POSITION;



};



struct GridOutput
{
	float4 m_position : SV_POSITION;



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



GridOutput main(Gridinput _input)
{
	GridOutput m_output = (GridOutput)1;

	float4 m_local = float4(_input.m_position.xyz, 1);

		m_local = mul(m_local, WorldMatrix);

	m_local = mul(m_local, viewMatrix);

	m_local = mul(m_local, ProjectionMatrix);

	m_output.m_position = m_local;

	return m_output;
}