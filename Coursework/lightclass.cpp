#include "lightclass.h"


LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}


void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = D3DXVECTOR4(red,green,blue,alpha);
	return;
}

void LightClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = D3DXVECTOR4(red,green,blue,alpha);
	return;
}

void LightClass::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}

void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR4(x, y, z,0);
	return;
}

void LightClass::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR4(x, y, z, 0);
	return;
}

void LightClass::SetConstant(float constant)
{
	m_pointConstant = constant;
	return;
}

void LightClass::SetLinear(float linear) 
{
	m_pointLinear = linear;
	return;
}

void LightClass::SetQuadratic(float quadratic)
{
	m_pointQuadratic = quadratic;
	return;
}

void LightClass::SetRange(float range)
{
	m_pointRange = range;
	return;
}

void LightClass::SetAttenuation(float constant, float linear, float quadratic, float range)
{
	m_Attenuation = D3DXVECTOR4(constant, linear, quadratic, range);
	return;
}

D3DXVECTOR4 LightClass::GetAttenuation()
{
	return m_Attenuation;
}
D3DXVECTOR4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}

D3DXVECTOR4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}

D3DXVECTOR4 LightClass::GetSpecularColor()
{
	return m_specularColor;
}

float LightClass::GetSpecularPower()
{
	return m_specularPower;
}

D3DXVECTOR4 LightClass::GetDirection()
{
	return m_direction;
}

D3DXVECTOR4 LightClass::GetPosition()
{
	return m_position;
}

float LightClass::GetConstant()
{
	return m_pointConstant;
}

float LightClass::GetLinear()
{
	return m_pointLinear;
}

float LightClass::GetQuadratic()
{
	return m_pointQuadratic;
}

float LightClass::GetRange()
{
	return m_pointRange;
}
