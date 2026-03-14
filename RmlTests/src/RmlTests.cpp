// RmlTests.cpp: define o ponto de entrada para o aplicativo.
//

#include "Application.hpp"

int main(int argc, char** argv)
{
    RmlTests::Application* app = new RmlTests::Application();
    app->Run();
    delete app;
    return 0;
}
