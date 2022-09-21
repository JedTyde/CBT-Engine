#pragma once

#ifdef CBT_PLATFORM_WINDOWS

extern CBT::Application* CBT::CreateApplication();

int main(int argc, char** argv) 
{
	CBT::Log::Init();
	CBT_CORE_WARN("Initialized Log!");
	int a = 5;
	CBT_INFO("Hello Var={0}", a);

	printf("engine\n");
	auto app = CBT::CreateApplication();
	app->Run();
	delete app;
}

#endif // CBT_PLATFORM_WINDOWS
