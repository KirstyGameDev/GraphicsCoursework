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
	m_RenderTexture = 0;
	m_DownSampleTexture = 0;
	m_UpSampleTexture = 0;
	m_HorizontalBlurTexture = 0;
	m_VerticalBlurTexture = 0;
	m_DownSampleWindow = 0;
	m_UpSampleWindow = 0;
	m_HorizontalBlurShader = 0;
	m_VerticalBlurShader = 0;

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

	//Create the horizon shader object
	m_HorizontalBlurShader = new HorizontalBlurShaderClass;
	if(!m_HorizontalBlurShader)
	{
		return false;
	}

	//Initialize the horizontal shader object
	result = m_HorizontalBlurShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur shader object.", L"Error", MB_OK);
		return false;
	}

	//Create the vertical blur shader object
	m_VerticalBlurShader = new VerticalBlurShaderClass;
	if(!m_VerticalBlurShader)
	{
		return false;
	}

	//Initalize the vertical blur shader object
	result = m_VerticalBlurShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the vertical blur shader object.", L"Error", MB_OK);
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



	//Set up RenderTexture
	m_RenderTexture = new RenderTextureClass;
	if(!m_RenderTexture)
	{
		return false;
	}

	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), screenWidth,screenHeight,SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the render texture object.", L"Error", MB_OK);
		return false;
	}

	//Set up down sample textre
	m_DownSampleTexture = new RenderTextureClass;
	if(!m_DownSampleTexture)
	{
		return false;
	}

	result = m_DownSampleTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the down sample texture object", L"Error", MB_OK);
		return false;
	}
	
	//Set up the up sample texture
	m_UpSampleTexture = new RenderTextureClass;
	if(!m_UpSampleTexture)
	{
		return false;
	}

	result = m_UpSampleTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the up sample texture object", L"Error", MB_OK);
		return false;
	}

	//Set up horizontal blur texture
	m_HorizontalBlurTexture = new RenderTextureClass;
	if(!m_HorizontalBlurTexture)
	{
		return false;
	}

	result = m_HorizontalBlurTexture->Initialize(m_Direct3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the horizontal blur texture object", L"Error", MB_OK);
		return false;
	}

	//Set up vertical blur texture
	m_VerticalBlurTexture = new RenderTextureClass;
	if(!m_VerticalBlurTexture)
	{
		return false;
	}

	result = m_VerticalBlurTexture->Initialize(m_Direct3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the vertical blur texture object", L"Error", MB_OK);
		return false;
	}

	//Set up target window
	m_TargetWindow = new TargetWindowClass;
	if(!m_TargetWindow)
	{
		return false;
	}

	result = m_TargetWindow->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, screenWidth/2, screenHeight/2);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the target windows object.", L"Error", MB_OK);
		return false;
	}

	//Set up down sample window
	m_DownSampleWindow = new TargetWindowClass;
	if(!m_DownSampleWindow)
	{
		return false;
	}

	result = m_DownSampleWindow->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, downSampleWidth, downSampleHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not intialise the target windows object.", L"Error", MB_OK);
		return false;
	}

	//Set up up sample window
	m_UpSampleWindow = new TargetWindowClass;
	if(!m_UpSampleWindow)
	{
		return false;
	}

	result = m_UpSampleWindow->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the target windows object.", L"Error", MB_OK);
		return false;

	}
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

	//Release the horizontal blur shader object
	if(m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader->Shutdown();
		delete m_HorizontalBlurShader;
		m_HorizontalBlurShader = 0;
	}

	//Release the vertical blur shader object
	if(m_VerticalBlurShader)
	{
		m_VerticalBlurShader->Shutdown();
		delete m_VerticalBlurShader;
		m_VerticalBlurShader = 0;
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

	//Render the scene to a render to texture
	result = RenderToTexture();
	if(!result)
	{
		return false;
	}

	//Next downsamle the render texture to a smaller size texture
	result = DownSampleTexture();
	if(!result)
	{
		return false;
	}

	//Perform horizontal blur on the down sampled render texture
	result = RenderHorizontalBlurToTexture();
	if(!result)
	{
		return false;
	}

	//Now perform a vertical blue on the down sampled render texture
	result = RenderVerticalBlurToTexture();
	if(!result)
	{
		return false;
	}

	//Up sample the final blurred render texture to screen size again
	result = UpSampleTexture();
	if(!result)
	{
		return false;
	}


	//Render the blurred upsamples render texture to the screen.
	result = RenderScene();
	if(!result)
	{
		return false;
	}
	/*
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
		*/
	return true;
}

bool ApplicationClass::RenderToTexture()
{
	D3DMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	//Set the render target to be the render to texture
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the render to texture
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 1.0f,0.0f,0.0f,1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the world view and projection matrices from the camera and d3d objects
	m_Camera->GetViewMatrix(&viewMatrix);
	m_Direct3D->GetWorldMatrix(&worldMatrix);
	m_Direct3D->GetProjectionMatrix(&projectionMatrix);

	//Put the model onto the graphics pipeline to prepare them for drawing.
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

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

}

bool ApplicationClass::RenderScene()
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;

	//Clear the buffers to begin the scene
	m_Direct3D->BeginScene(1.0f,0.0f,0.0f,0.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the world,view and ortho matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	//Turn off the Z Buffering to begin all 2D rendering
	m_Direct3D->TurnZBufferOff();

	//Put the up sample window vertex buffer on the graphics pipeline to prepare it for drawing
	m_UpSampleWindow->Render(m_Direct3D->GetDeviceContext());
	
	//Render the up sample window 
	result = m_TessellationShader->Render(m_Direct3D->GetDeviceContext(), m_UpSampleWindow->GetIndexCount(), worldMatrix,
		viewMatrix,orthoMatrix, tessellationAmount, m_UpSampleTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	//Turn Z buffering back on since all rendering is done
	m_Direct3D->TurnZBufferOn();

	//Present the rendered scene to screen
	m_Direct3D->EndScene();

	return true;


}

bool ApplicationClass::DownSampleTexture()
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;

	//Set the render target to be the render to texture
	m_DownSampleTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the render to texture
	m_DownSampleTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f,0.0f,0.0f,1.0f);
	
	//Generate the view matrix based on the camera's position
	m_Camera->Render();
	
	//Get the world and view matrixes from the camera and d3d objects
	m_Camera->GetBaseViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Get the ortho matrix from the render to texture since texture has different 
	//dimensions being that it is smaller
	m_DownSampleTexture->GetOrthoMatrix(orthoMatrix);

	//Turn off the Z buffer to being all 2D rendering
	m_Direct3D->TurnZBufferOff();

	//Put the small ortho window vertex and index buffers on the graphics pipeline to
	//prepare them for drawing
	m_DownSampleWindow->Render(m_Direct3D->GetDeviceContext());

	//Render the small ortho window using the texture shader and the render to
	//texture of the scene as the texture resource
	result = m_TessellationShader->Render(m_Direct3D->GetDeviceContext(), m_DownSampleWindow->GetIndexCount(), 
		worldMatrix, viewMatrix, orthoMatrix, tessellationAmount, m_RenderTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	//Turn the Z buffer back on now that all 2D rendering has been completed
	m_Direct3D->TurnZBufferOn();

	//Reset the render target back to the orginal back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

	return true;
}
bool ApplicationClass::RenderHorizontalBlurToTexture()
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	float screenSizeX;
	bool result;

	//Store the screen width in a float that will be used in the horizontal blur shader
	screenSizeX = (float)m_HorizontalBlurTexture->GetTextureWidth();

	//Set the render target to be the render to texture.
	m_HorizontalBlurTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the render to texture.
	m_HorizontalBlurTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f,0.0f,0.0f,1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the world and view matrices from the camera and d3d objects
	m_Camera->GetBaseViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Get the ortho matrix from the render to texture since texture has different dimensions
	m_HorizontalBlurTexture->GetOrthoMatrix(orthoMatrix);

	//Turn off the z buffer to being all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	//Put the down sample window vertex buffer on the graphics pipeline to prepare them for drawing
	m_DownSampleWindow->Render(m_Direct3D->GetDeviceContext());

	//Render the down sample window using the horizontal blue shader and the down sampled render to 
	//texture resource
	result = m_HorizontalBlurShader->Render(m_Direct3D->GetDeviceContext(), m_DownSampleWindow->GetIndexCount(),
		worldMatrix,viewMatrix,orthoMatrix, m_DownSampleTexture->GetShaderResourceView(), 
		screenSizeX);
	if(!result)
	{
		return false;
	}


	//Turn the z buffer back on now that all 2D rendeing has completed
	m_Direct3D->TurnZBufferOn();

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

	return true;
}

bool ApplicationClass::RenderVerticalBlurToTexture()
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	float screenSizeY;
	bool result;

	//Store the screen height in a float that will be used in the vertical blur shader
	screenSizeY = (float)m_VerticalBlurTexture->GetTextureHeight();

	//Set the render target to be the render to texture
	m_VerticalBlurTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the render to texture
	m_VerticalBlurTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f,0.0f,0.0f,1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the world and view matrices from the camera and d3d objects
	m_Camera->GetBaseViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Get the ortho matrix from the render to texture since texture has different dimentions
	m_VerticalBlurTexture->GetOrthoMatrix(orthoMatrix);

	//Turn off the Z buffer to begin 2D rendering.
	m_Direct3D->TurnZBufferOff();

	//Put the down sample window vertex buffer on the graphics pipeline to prepare them for drawing
	m_DownSampleWindow->Render(m_Direct3D->GetDeviceContext());

	//Render the down sample window using the vertical blur shader and the horizontal blurred render to texture resource
	result = m_VerticalBlurShader->Render(m_Direct3D->GetDeviceContext(), m_DownSampleWindow->GetIndexCount(), worldMatrix, 
		viewMatrix, orthoMatrix, m_HorizontalBlurTexture->GetShaderResourceView(), screenSizeY);
	if(!result)
	{
		return false;
	}

	//Turn the Z buffer back on nwo all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	//Reset the render target back to the original back buffer and not the render to texture anymore
	m_Direct3D->SetBackBufferRenderTarget();

	return true;
}

bool ApplicationClass::UpSampleTexture()
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;

	//Set the render target to be the render to texture
	m_UpSampleTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	//Clear the render to texture
	m_UpSampleTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f,0.0f,0.0f,1.0f);

	//Generate the view matrix based on the camera's position
	m_Camera->Render();

	//Get the world and view matrices from the camera and d3d objects
	m_Camera->GetBaseViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);

	//Get the ortho matrix from the render to texture since texture has different dimensions
	m_UpSampleTexture->GetOrthoMatrix(orthoMatrix);

	//Turn off the z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	//Put the up sample window vertex buffer on the graphics pipeline to prepare them for drawing
	m_UpSampleWindow->Render(m_Direct3D->GetDeviceContext());

	//Render the up sample window using the texture shader and the samall sized final blurred
	//render to texture resource.
	result = m_TessellationShader->Render(m_Direct3D->GetDeviceContext(), m_UpSampleWindow->GetIndexCount(), 
		worldMatrix, viewMatrix, orthoMatrix, tessellationAmount, m_VerticalBlurTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	//Turn the z buffer back on now that all 2D rendering has completed
	m_Direct3D->TurnZBufferOn();

	//Rest the render taret back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	return true;

}