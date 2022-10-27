#include "CBT.h"

#include "Layers/EditorLayer.h"

class ExampleLayer : public CBT::Layer
{

public:
	ExampleLayer() : Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		CBT_INFO("ExampleLayer::Update");
		
	}

	void OnEvent(CBT::Event& event)
	{
		CBT_TRACE("{0}", event);
	}

};

class Sandbox : public CBT::Application
{
public:
	Sandbox()
	{
		//SE TIENE QUE ARREGLAR ESTO
		PushLayer(new EditorLayer());
	}

	~Sandbox()
	{

	}
};

CBT::Application* CBT::CreateApplication()
{
	return new Sandbox();
}