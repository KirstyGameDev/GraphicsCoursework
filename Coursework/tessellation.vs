struct VertexInputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct HullInputType
{
    float3 position : POSITION;
	float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

HullInputType ColorVertexShader(VertexInputType input)
{
    HullInputType output;

	 // Pass the vertex position into the hull shader.
    output.position = input.position;
    
	//Store the tex coords for the pixel shader
	output.tex = input.tex;

    // Pass the input normal into the hull shader.
    output.normal = input.normal;
    
    return output;
}
