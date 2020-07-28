#include "GameObject.h"

static int m_IdGenerator;

GameObject::GameObject(): Id(m_IdGenerator), Transform()
{
	m_IdGenerator++;
}

GameObject::~GameObject()
{
	delete this->Transform;
}
