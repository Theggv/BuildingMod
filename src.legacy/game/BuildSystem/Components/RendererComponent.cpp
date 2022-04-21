#include "RendererComponent.h"

RendererComponent::RendererComponent(double fixAngle) : m_FixAngle(fixAngle)
{
}

double RendererComponent::GetFixAngle()
{
	return m_FixAngle;
}

Material *RendererComponent::GetMaterial()
{
	return m_Material;
}

string RendererComponent::GetModel()
{
	return m_Model;
}

void RendererComponent::SetModel(string model)
{
	m_Model = model;
}
