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
	m_vertexCount = 8;

	// Set the number of indices in the index array.
	m_indexCount = 24;

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
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f,0.0f);  // Bottom left.
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
	vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left.
	vertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	
	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].texture = D3DXVECTOR2(1.0f, 0.0f);
	vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);	//Top Right
	vertices[3].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[3].normal = D3DXVECTOR3(0.0f,0.0f,-1.0f);

	vertices[4].position = D3DXVECTOR3(1.0f,-1.0f,2.0f);	//back bottom right
	vertices[4].texture = D3DXVECTOR2(1.0f,0.0f);
	vertices[4].normal = D3DXVECTOR3(1.0f,0.0f,0.0f);

	vertices[5].position = D3DXVECTOR3(1.0f,1.0f,2.0f);		//back top right
	vertices[5].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[5].normal = D3DXVECTOR3(1.0f,0.0f,0.0f);

	vertices[6].position = D3DXVECTOR3(-1.0f,1.0f,2.0f);	//back top left
	vertices[6].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[6].normal = D3DXVECTOR3(0.0f,0.0f,1.0f);

	vertices[7].position = D3DXVECTOR3(-1.0f,-1.0f,2.0f);	//back bottom left
	vertices[7].texture = D3DXVECTOR2(0.0f,0.0f);
	vertices[7].normal = D3DXVECTOR3(0.0f,0.0f,1.0f);
	
	// Load the index array with data.
	indices[0] = 1;  // Top left.				front quad
	indices[1] = 3;  // Bottom right.
	indices[2] = 0;  // Bottom left.
	indices[3] = 2;	//top right

	indices[4] = 6;								//left quad
	indices[5] = 1;
	indices[6]= 7;
	indices[7] = 0;

	indices[8] = 5;	//bottom left				back quad
	indices[9] = 6; //top left
	indices[10] =4; //bottom right
	indices[11] = 7; //top right

	indices[12] = 3;	//bottom left				right side quad
	indices[13] = 5;	//top left
	indices[14] = 2; //bottom right
	indices[15] = 4; //top right

	indices[16] = 6;								//Top quad
	indices[17] = 5;
	indices[18] = 1;
	indices[19] = 3;

	indices[20] = 0;							//Bottom quad
	indices[21] = 7;
	indices[22] = 2;
	indices[23] = 4;



	

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