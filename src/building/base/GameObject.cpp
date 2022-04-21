#include "GameObject.h"

// initial object id
static int m_IdGenerator = 1024;

GameObject::GameObject() : Id(m_IdGenerator)
{
    m_IdGenerator++;
    m_transform = std::make_unique<ObservableTransform>();
}

ObservableTransform *GameObject::GetTransform()
{
    return m_transform.get();
}

void GameObject::AddLink(int followPointId, Link link)
{
    m_links[followPointId].push_back(link);
}

void GameObject::RemoveLink(int objectId)
{
    for (auto [key, arr] : m_links)
    {
        for (auto it = arr.begin(); it != arr.end();)
        {
            auto obj = it->object.lock();

            if (!obj)
                it = arr.erase(it);
            else if (obj->Id == objectId)
                it = arr.erase(it);
            else
                ++it;
        }
    }
}

std::vector<std::pair<int, Link>> GameObject::GetLinks()
{
    std::vector<std::pair<int, Link>> links;

    for (auto [key, value] : m_links)
    {
        for (auto &link : value)
            links.push_back({key, link});
    }

    return links;
}
