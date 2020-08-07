#include "RendererComponent.h"

Material* RendererComponent::GetMaterial()
{
	return m_Material;
}

void RendererComponent::UpdateTransform()
{
	auto pos = m_parent->GetTransform()->GetPosition();
}
