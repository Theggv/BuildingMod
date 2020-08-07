#include "RendererComponent.h"

Material* RendererComponent::GetMaterial()
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
