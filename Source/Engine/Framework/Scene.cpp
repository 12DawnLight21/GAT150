#include "Scene.h"
#include "Framework/Framework.h"

namespace umbra
{ 
	void Scene::Update(float dt)
	{
		//remove destroyed actors
		auto iter = m_actors.begin(); //contains our actor
		while (iter != m_actors.end())
		{
			(*iter)->Update(dt);
			((*iter)->destroyed) ? iter = m_actors.erase(iter) : iter++;
		}

		//check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++)
			{
				///new vvvvvv
				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

				if (!collision1 || !collision2) continue;

				if (collision1->CheckCollision(collision2))
					/// ^^^^^
				{
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
}