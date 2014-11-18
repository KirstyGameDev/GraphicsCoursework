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

[maxvertexcount(64)]

void FragmentationGeometryShader(triangle PixelInputType input[3], inout TriangleStream <PixelInputType> triStream)
{
	PixelInputType output = (PixelInputType)0;
	for(uint i = 0; i < 3; i++)
	{
		output.position = input[i].position;
		//output.position = lerp(input[i].position, input[i].position * 3.0 , i); 
		output.color = float4(0.0f,1.0f,0.0f,1.0f);
		triStream.Append(output);
	}

	
	triStream.RestartStrip();

}


	