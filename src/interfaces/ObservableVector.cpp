#include "ObservableVector.h"

ObservableVector::~ObservableVector()
{

}

void ObservableVector::Attach(IObserver* observer)
{
	m_Observers.push_back(observer);
}

void ObservableVector::Detach(IObserver* observer)
{
	m_Observers.remove(observer);
}

void ObservableVector::Notify()
{
	auto it = m_Observers.begin();

	while (it != m_Observers.end())
	{
		(*it)->Update();
		++it;
	}
}
