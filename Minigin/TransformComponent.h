#pragma once
#include "Component.h"
#include <glm.hpp>
namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent() = default; 
		virtual ~TransformComponent() = default; 

		void SetPosition(float x, float y, float z = 0.f)
		{
			m_Position = { x,y,z }; 
		}
		const glm::vec3& GetPosition() const { return m_Position;  }

	private:
		glm::vec3 m_Position{}; 
	};



}