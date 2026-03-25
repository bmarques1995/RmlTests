#include "Application.hpp"

#ifdef WIN32
#include <windows.h>
#endif

#include <cassert>
#include "RmlInline.hpp"
#include <fstream>

RmlTests::Application* RmlTests::Application::s_Instance = nullptr;

RmlTests::Application::Application() :
    m_API(RmlTests::GRAPHICS_API::D3D11),
    m_Running(true)
{
    if (s_Instance != nullptr)
    {
        return;
    }
    EnableSingleton(this);


    m_Window.reset(RmlTests::Window::Create(1280, 720, "SDL3 + D3D11"));
    m_Context.reset(RmlTests::GraphicsContext::Create(m_API, std::any_cast<HWND>(m_Window->GetNativePointer()), m_Window->GetWidth(), m_Window->GetHeight()));
    m_Context->SetClearColor(.0f, .5f, .25f, 1.0f);
    m_RMLSystemInterface.reset(RmlTests::Window::CreateRMLSystemInterface(m_Window));
    m_RMLRenderInterface.reset(RmlTests::GraphicsContext::CreateRMLRenderInterface(m_API, m_Context->GetControllers()));

    Rml::SetSystemInterface(m_RMLSystemInterface.get());
    Rml::SetRenderInterface(m_RMLRenderInterface.get());
    {
        Rml::Initialise();
        m_RmlContext = Rml::CreateContext("main", Rml::Vector2i(m_Window->GetWidth(), m_Window->GetHeight()));
        assert(m_RmlContext != nullptr);
        std::vector<uint8_t> robotoMediumFont;
        assert(LoadBytes("C:/Users/bruno/AppData/Local/Microsoft/Windows/Fonts/Roboto-Medium.ttf", &robotoMediumFont));
        Rml::Span<const Rml::byte> robotoMediumFontRml(robotoMediumFont.data(), robotoMediumFont.size());
        auto result = Rml::LoadFontFace(robotoMediumFontRml, "Roboto-Medium", Rml::Style::FontStyle::Normal, Rml::Style::FontWeight::Auto);
        assert(result);

        m_Document = m_RmlContext->LoadDocumentFromMemory(InlineRmls::rmlSample, "inline.rml");
        assert(m_Document != nullptr);
        m_Document->Show();
    }
}

RmlTests::Application::~Application()
{
    m_Document->Close();
    m_RmlContext->Update();
    Rml::RemoveContext("main");
    Rml::Shutdown();
    m_RMLRenderInterface.reset();
    m_RMLSystemInterface.reset();
    m_Context.reset();
    m_Window.reset();
}

void RmlTests::Application::Run()
{
	while (m_Running)
	{
        m_Window->Update();
        m_Context->ReceiveCommands();
        m_RmlContext->Render();
        m_Context->DispatchCommands();
        m_Context->Present();
	}
}

void RmlTests::Application::ProcessQuit()
{
	m_Running = false;
}

void RmlTests::Application::ProcessResize(uint32_t width, uint32_t height)
{
    m_Context->OnResize(width, height);
}

RmlTests::Application* RmlTests::Application::GetInstance()
{
    return s_Instance;
}

Rml::Context* RmlTests::Application::GetRmlContext()
{
    return m_RmlContext;
}

bool RmlTests::Application::LoadBytes(std::string_view path, std::vector<uint8_t>* outBuffer)
{
    bool loaded = false;
    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try
    {
        fileStream.open(path.data(), std::ios::binary);
        loaded = true;
    }
    catch (...)
    {
        return loaded;
    }
    auto start = fileStream.tellg();
    fileStream.seekg(0, std::ios::end);
    uint64_t fsize = fileStream.tellg() - start;
    fileStream.seekg(0, std::ios::beg);
    outBuffer->reserve(fsize);
    outBuffer->resize(fsize);
    fileStream.read(reinterpret_cast<char*>(&(*outBuffer)[0]), fsize);
    return loaded;
}

void RmlTests::Application::EnableSingleton(Application* app)
{
    if(s_Instance == nullptr)
        s_Instance = app;
}
