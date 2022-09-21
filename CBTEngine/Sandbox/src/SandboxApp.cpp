#include <CBT.h>


class Sandbox : public CBT::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

CBT::Application* CBT::CreateApplication()
{
	return new Sandbox();
}