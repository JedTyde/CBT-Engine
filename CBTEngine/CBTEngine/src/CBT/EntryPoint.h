#pragma once

#ifdef CBT_PLATFORM_WINDOWS

extern CBT::Application* CBT::CreateApplication();

int main(int argc, char** argv) 
{
	printf("engine\n");
	auto app = CBT::CreateApplication();
	app->Run();
	delete app;
}

#endif // CBT_PLATFORM_WINDOWS
