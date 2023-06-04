#pragma once

#include "Log/Log.h"

Engine::Application* CreateApplication();

/**
 * Program entry point
 * @return status code
 */
int main()
{
	Engine::Log::Init();

	Engine::Application* app = CreateApplication();
	app->Run();
	delete app;
	return 0;
}

