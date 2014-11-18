////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#include <D3dx9math.h>
///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
//#include "textureshaderclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "meshclass.h"
#include "lightclass.h"
//#include "lightshaderclass.h"
#include "rendertextureclass.h"
#include "targetwindowclass.h"
#include "horizontalblurshaderclass.h"
#include "verticalblurshaderclass.h"
#include "tessellationshaderclass.h"
#include "tessellationMesh.h"
#include "fragmentationshaderclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput(float);
	bool RenderGraphics();
	bool RenderToTexture();
	bool DownSampleTexture();
	bool RenderHorizontalBlurToTexture();
	bool RenderVerticalBlurToTexture();
	bool UpSampleTexture();
	bool RenderScene();


private:
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera, *m_superCamera;
	//TextureShaderClass* m_TextureShader;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	MeshClass* m_Mesh;
	//LightShaderClass* m_LightShader;
	LightClass* m_Light;
	RenderTextureClass* m_RenderTexture, *m_DownSampleTexture,*m_UpSampleTexture, *m_HorizontalBlurTexture, *m_VerticalBlurTexture;
	TargetWindowClass* m_TargetWindow, *m_DownSampleWindow, *m_UpSampleWindow;
	HorizontalBlurShaderClass* m_HorizontalBlurShader;
	VerticalBlurShaderClass* m_VerticalBlurShader;

	float meshRotationAngle, meshRotationSpeed;

	TessellationMeshClass* m_TessellationMesh, *m_Cube;
	TessellationShaderClass* m_TessellationShader;

	int tessellationAmount;

	FragmentationShaderClass* m_FragmentationShader;
};

#endif