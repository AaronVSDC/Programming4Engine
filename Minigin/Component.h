#pragma once
#include <memory>

namespace dae
{
	class GameObject; 

	class Component
	{
	public: 
		virtual ~Component() = default; 
		virtual void Update() {}
		virtual void Render() const {}

		//called when component is added to a GameObject
		virtual void Initialize() {}

		//keep pointer reference to owner
		void SetOwner(GameObject* owner) { m_pOwner = owner;  }
		GameObject* GetOwner() const { return m_pOwner;  }

	protected: 
		GameObject* m_pOwner; 




	};
}