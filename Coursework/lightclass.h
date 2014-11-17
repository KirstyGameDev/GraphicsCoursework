#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

#include <d3dx10math.h>

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetAmbientColor(float,float,float,float);
	void SetDiffuseColor(float, float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);
	void SetDirection(float, float, float);
	void SetPosition(float,float,float);
	void SetAttenuation(float, float, float, float);
	void SetConstant(float);
	void SetLinear(float);
	void SetQuadratic(float);
	void SetRange(float);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();
	D3DXVECTOR4 GetDirection();
	D3DXVECTOR4 GetPosition();
	D3DXVECTOR4 GetAttenuation();
	float GetConstant();
	float GetLinear();
	float GetQuadratic();
	float GetRange();
	
private:
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_ambientColor;
	float m_specularPower;
	D3DXVECTOR4 m_specularColor;
	D3DXVECTOR4 m_direction;
	D3DXVECTOR4 m_position;
	float m_pointConstant;
	float m_pointLinear;
	float m_pointQuadratic;
	float m_pointRange;
	D3DXVECTOR4 m_Attenuation;

};

#endif