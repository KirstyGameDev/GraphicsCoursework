#include "tessellationMesh.h"

TessellationMeshClass::TessellationMeshClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
}


TessellationMeshClass::TessellationMeshClass(const TessellationMeshClass& other)
{
}


TessellationMeshClass::~TessellationMeshClass()
{
}

bool TessellationMeshClass::Initialize(ID3D11Device* device, WCHAR* textureFilename)
{
	bool result;


	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

bool TessellationMeshClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	// Set the number of vertices in the vertex array.
	m_vertexCount = 16;

	// Set the number of indices in the index array.
	m_indexCount = 16;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f,0.0f);  // Bottom left.			//Front quad
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
	vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left.
	vertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	
	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);	//Top Right
	vertices[3].texture = D3DXVECTOR2(1.0f,0.0f);
	vertices[3].normal = D3DXVECTOR3(0.0f,0.0f,-1.0f);

	vertices[4].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);	//Top Left						Right Quad
	vertices[4].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[4].normal = D3DXVECTOR3(1.0f,0.0f,0.0f);
															
	vertices[5].position = D3DXVECTOR3(1.0f,-1.0f,0.0f);	//Bottom left
	vertices[5].texture = D3DXVECTOR2(0.0f,1.0f);
	vertices[5].normal = D3DXVECTOR3(1.0f,0.0f,0.0f);

	vertices[6].position = D3DXVECTOR3(1.0f,1.0f,2.0f);		//Top Right
	vertices[6].texture = D3DXVECTOR2(1.0f,0.0f);
	vertices[6].normal = D3DXVECTOR3(1.0f,0.0f,0.0f);

	vertices[7].position = D3DXVECTOR3(1.0f,-1.0f,2.0f);	//Bottom right
	vertices[7].texture = D3DXVECTOR2(1.0f,1.0f);
	vertices[7].normal = D3DXVECTOR3(0.0f,0.0f,1.0f);

	vertices[8].position = D3DXVECTOR3(1.0f,1.0f,2.0f);	// TopLeft						Back Quad
	vertices[8].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[8].normal = D3DXVECTOR3(0.0f,0.0f,1.0f);

	vertices[9].position = D3DXVECTOR3(1.0f,-1.0f, 2.0f);	//Bottom Left
	vertices[9].texture = D3DXVECTOR2(0.0f,1.0f);
	vertices[9].normal = D3DXVECTOR3(0.0f,0.0f,1.0f);

	vertices[10].position = D3DXVECTOR3(-1.0f, 1.0f, 2.0f);	//Top Right
	vertices[10].texture = D3DXVECTOR2(1.0f,0.0f);
	vertices[10].normal = D3DXVECTOR3(0.0f,0.0f,1.0f);

	vertices[11].position = D3DXVECTOR3(-1.0f, -1.0f, 2.0f);	//Bottom Right
	vertices[11].texture = D3DXVECTOR2(1.0f,1.0f);
	vertices[11].normal = D3DXVECTOR3(0.0f,0.0f,1.0f);

	vertices[12].position = D3DXVECTOR3(-1.0f, 1.0f, 2.0f);		//Top Left					Left Quad
	vertices[12].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[12].normal = D3DXVECTOR3(-1.0f,0.0f,0.0f);

	vertices[13].position = D3DXVECTOR3(-1.0f, -1.0f, 2.0f);	//Bottom left
	vertices[13].texture = D3DXVECTOR2(0.0f,1.0f);
	vertices[13].normal = D3DXVECTOR3(-1.0f,0.0f,0.0f);

	vertices[14].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);	//Top Right
	vertices[14].texture = D3DXVECTOR2(1.0f,0.0f);
	vertices[14].normal = D3DXVECTOR3(-1.0f,0.0f,0.0f);

	vertices[15].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);	//Bottom Right
	vertices[15].texture = D3DXVECTOR2(1.0f,1.0f);
	vertices[15].normal = D3DXVECTOR3(-1.0f,0.0f,0.0f);
	
	// Load the index array with data.
	indices[0] = 1;  // Top left.				front quad
	indices[1] = 3;  // Bottom right.
	indices[2] = 0;  // Bottom left.
	indices[3] = 2;	//top right

	indices[4] = 4;								//right quad
	indices[5] = 6;
	indices[6]= 5;
	indices[7] = 7;

	indices[8] = 8;	//bottom left				back quad
	indices[9] = 10; //top left
	indices[10] =9; //bottom right
	indices[11] = 11; //top right

	indices[12] = 12;	//bottom left				right side quad
	indices[13] = 14;	//top left
	indices[14] = 13; //bottom right
	indices[15] = 15; //top right

	//indices[16] = 6;								//Top quad
	//indices[17] = 5;
	//indices[18] = 1;
	//indices[19] = 3;

	//indices[20] = 0;							//Bottom quad
	//indices[21] = 7;
	//indices[22] = 2;
	//indices[23] = 4;



	

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void TessellationMeshClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

void TessellationMeshClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	return;
}