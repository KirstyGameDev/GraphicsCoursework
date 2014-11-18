////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"

#define SCREEN_DEPTH 10
#define SCREEN_NEAR 1

float rotation = 0;

ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	m_superCamera = 0;
	
	m_Timer = 0;
	m_Position = 0;
	m_Mesh = 0;
	
	m_Light = 0;
	m_TessellationMesh = 0;
	m_Cube = 0;
	m_TessellationShader = 0;
	m_FragmentationShader = 0;

	tessellationAmount = 2;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	D3DXMATRIX baseViewMatrix;
	//char videoCard[128];
	//int videoMemory;

	//post processing initialise 
	int downSampleWidth, downSampleHeight;

	//Set the size to sample down to 
	downSampleWidth = screenWidth/2;
	downSampleHeight = screenHeight/2;
	
	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -8.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	//cameraX = 50.0f;
	//cameraY = 2.0f;
	//cameraZ = -7.0f;

	//m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	//Create the secondary camera object
	m_superCamera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	//Initialise the base view matrix for the camera
	m_superCamera->SetPosition(0.0f,0.0f,5.0f);
	m_superCamera->SetRotation(0.0f,180.0f,0.0f);
	m_superCamera->Render();

	// Create Mesh object
	m_Mesh = new MeshClass;

	// Initialise the mesh object
	result = m_Mesh->Initialize(m_Direct3D->GetDevice(), L"data/brick1.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the mesh object.", L"Error", MB_OK);
		return false;
	}

	meshRotationAngle = 5.0f;
	meshRotationSpeed = 0.025f;
	
	//Create the tessellated mesh object
	m_TessellationMesh = new TessellationMeshClass;

	//Initialise the tessellated mesh object
	result = m_TessellationMesh->Initialize(m_Direct3D->GetDevice(), L"data/brick1.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the tessellated mesh object", L"Error", MB_OK);
		return false;
	}


	//Create the tessellated cube object
	m_Cube = new TessellationMeshClass;

	//Initialize the tessellated mesh object
	result = m_Cube->Initialize(m_Direct3D->GetDevice(), L"data/brick1.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not intiialise the cube object", L"Error", MB_OK);
		return false;
	}

	//Create the tessellation shader object
	m_TessellationShader = new TessellationShaderClass;
	if(!m_TessellationShader)
	{
		return false;
	}

	//Initiliize the tessellation shader object
	result = m_TessellationShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not intiialise the tesselation shader object.", L"Error", MB_OK);
		return false;
	}

	//TODO get the fragmentation shader working
	//Create the fragmentation shader object
	//m_FragmentationShader = new FragmentationShaderClass;
	//if(!m_FragmentationShader)
	//{
	//	return false;
	//}

	////Initialize the fragmentation shader object

	//result = m_FragmentationShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the fragmentation shader object.", L"Error" , MB_OK);
	//	return false;
	//}

	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(0.0f, 0.0f, -10.0f);


	// Create the first light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the first light object.
	m_Light->SetAmbientColor(0.10f,0.10f,0.10f,1.0f);
	m_Light->SetDiffuseColor(1.0f,0.0f, 0.0f,1.0f);
	m_Light->SetDirection(0.0f,0.0f,-1.0f);

	return true;
}


void ApplicationClass::Shutdown()
{
	
	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}



	//Release the tessellation shader object
	if(m_TessellationShader)
	{
		m_TessellationShader->Shutdown();
		delete m_TessellationShader;
		m_TessellationShader = 0;
	}

	//Release the fragmentation shader object
	/*if(m_FragmentationShader)
	{
		m_FragmentationShader->Shutdown();
		delete m_FragmentationShader;
		m_FragmentationShader = 0;
	}
*/
	// Release the mesh object
	if(m_Mesh)
	{
		m_Mesh->Shutdown();
		delete m_Mesh;
		m_Mesh = 0;
	}

	//Release the cube object
	if(m_Cube)
	{
		m_Cube->Shutdown();
		delete m_Cube;
		m_Cube = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//Release the second camera object
	if(m_superCamera)
	{
		delete m_superCamera;
		m_superCamera = 0;
	}

	// Release the Direct3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	//Release the tessellation shader object
	if(m_TessellationShader)
	{
		m_TessellationShader->Shutdown();
		delete m_TessellationShader;
		m_TessellationShader = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;


	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();
	
	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}

	// Render the graphics.
	result = RenderGraphics();
	if(!result)
	{
		return false;
	}

	return result;
}


bool ApplicationClass::HandleInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	if(m_Input->IsAPressed())
		tessellationAmount++;

	if(m_Input->IsZPressed())
		tessellationAmount--;

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}


bool ApplicationClass::RenderGraphics()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	

	m_Mesh->Render(m_Direct3D->GetDeviceContext());

	result = m_TessellationShader->Render(m_Direct3D->GetDeviceContext(),  m_Mesh->GetIndexCount(),  worldMatrix, viewMatrix, projectionMatrix, tessellationAmount, m_Mesh->GetTexture());
	if (!result)
	{
		return false;
	}


	// Push mesh data onto gfx hardware
	D3DXMatrixTranslation(&worldMatrix, 0, 0 ,5);
	m_TessellationMesh->Render(m_Direct3D->GetDeviceContext());	
	
	//Render the Mesh using the light shader
	result = m_TessellationShader->Render(m_Direct3D->GetDeviceContext(),  m_TessellationMesh->GetIndexCount(),  worldMatrix, viewMatrix, projectionMatrix, tessellationAmount, m_TessellationMesh->GetTexture());
	if (!result)
	{
		return false;
	}


	D3DXMatrixTranslation(&worldMatrix, 2, 0, 0);

	m_Cube->Render(m_Direct3D->GetDeviceContext());

	//Render the Mesh using the light shader
	result = m_TessellationShader->Render(m_Direct3D->GetDeviceContext(),  m_Cube->GetIndexCount(),  worldMatrix, viewMatrix, projectionMatrix, tessellationAmount, m_Cube->GetTexture());
	if (!result)
	{
		return false;
	}

	D3DXMatrixTranslation(&worldMatrix,-2, 0 ,0);


	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();
		
	return true;
}



bool ApplicationClass::RenderScene()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	//Clear the buffers to begin the scene
	m_Direct3D->BeginScene(1.0f,0.0f,0.0f,0.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the world,view and ortho matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//Render the up sample window using the texture shader and the fill screen sized blurred render to texture resource
	/*/result = m_TessellationShader->Render(m_Direct3D->GetDeviceContext(), m_TessellationMesh->GetIndexCount(), worldMatrix,
		viewMatrix,projectionMatrix,2, );
	if(!result)
	{
		return false;
	}

*/
	//Present the rendered scene to screen
	m_Direct3D->EndScene();

	return true;


}

