#pragma once

#include "CBT/Core.h"
#include "CBT/Events/Event.h"

#include <string>

namespace CBT
{
	class CBT_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate() {}
		virtual void OnEvent() {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}