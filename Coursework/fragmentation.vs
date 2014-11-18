cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct VertexInputType
{
    float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;

};

PixelInputType FragmentationVertexShader(VertexInputType input)
{
	PixelInputType output;

	output.position = input.position;
	output.color = float4(1.0f,0.0f,0.0f,1.0f);

	return output;
}