#include <cobalt/engine.hpp>

#include <memory>
#include <iomanip>
#include <iostream>

#include <Windows.h>

#include "DiligentCore/Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#include "DiligentCore/Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#include "DiligentCore/Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#include "DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h"
#include "DiligentCore/Common/interface/RefCntAutoPtr.hpp"

#include "GLFW/glfw3.h"

using namespace Diligent;

static const char* vsSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};
void main(in  uint    VertId : SV_VertexID,
          out PSInput PSIn) 
{
    float4 Pos[3];
    Pos[0] = float4(-0.5, -0.5, 0.0, 1.0);
    Pos[1] = float4( 0.0, +0.5, 0.0, 1.0);
    Pos[2] = float4(+0.5, -0.5, 0.0, 1.0);
    float3 Col[3];
    Col[0] = float3(1.0, 0.0, 0.0); // red
    Col[1] = float3(0.0, 1.0, 0.0); // green
    Col[2] = float3(0.0, 0.0, 1.0); // blue
    PSIn.Pos   = Pos[VertId];
    PSIn.Color = Col[VertId];
}
)";

// Pixel shader simply outputs interpolated vertex color
static const char* PSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};
struct PSOutput
{ 
    float4 Color : SV_TARGET; 
};
void main(in  PSInput  PSIn,
          out PSOutput PSOut)
{
    PSOut.Color = float4(PSIn.Color.rgb, 1.0);
}
)";


class Tutorial00App
{
public:
	Tutorial00App();

	~Tutorial00App();

	bool InitializeDiligentEngine(HWND hWnd);

	bool ProcessCommandLine(const char* CmdLine);


	void CreateResources();

	void Render();

	void Present();

	void WindowResize(Uint32 Width, Uint32 Height);

	RENDER_DEVICE_TYPE GetDeviceType() const;

private:
    RefCntAutoPtr<IRenderDevice>  m_pDevice;
    RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
    RefCntAutoPtr<ISwapChain>     m_pSwapChain;
    RefCntAutoPtr<IPipelineState> m_pPSO;
    RENDER_DEVICE_TYPE            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
};

std::unique_ptr<Tutorial00App> gPTheApp;

LRESULT CALLBACK messageProc(HWND, UINT, WPARAM, LPARAM);
// Main
/*int WINAPI main(HINSTANCE instance, HINSTANCE, LPSTR, int cmdShow)
{
#if defined(_DEBUG) || defined(DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    g_pTheApp.reset(new Tutorial00App);

    const auto* cmdLine = GetCommandLineA();
    if (!g_pTheApp->ProcessCommandLine(cmdLine))
        return -1;

    std::wstring Title(L"Cobalt Engine");
    switch (g_pTheApp->GetDeviceType())
    {
    case RENDER_DEVICE_TYPE_D3D11: Title.append(L" (D3D11)"); break;
    case RENDER_DEVICE_TYPE_D3D12: Title.append(L" (D3D12)"); break;
    case RENDER_DEVICE_TYPE_GL: Title.append(L" (GL)"); break;
    case RENDER_DEVICE_TYPE_VULKAN: Title.append(L" (VK)"); break;
    }
    // Register our window class
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, MessageProc,
                       0L, 0L, instance, NULL, NULL, NULL, NULL, L"SampleApp", NULL };
    RegisterClassEx(&wcex);

    // Create a window
    LONG WindowWidth = 1280;
    LONG WindowHeight = 1024;
    RECT rc = { 0, 0, WindowWidth, WindowHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    HWND wnd = CreateWindow(L"SampleApp", Title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, instance, NULL);
    if (!wnd)
    {
        MessageBox(NULL, L"Cannot create window", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }
    ShowWindow(wnd, SW_NORMAL);
    UpdateWindow(wnd);

    if (!g_pTheApp->InitializeDiligentEngine(wnd))
        return -1;

    g_pTheApp->CreateResources();

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            g_pTheApp->Render();
            g_pTheApp->Present();
        }
    }

    g_pTheApp.reset();

    return (int)msg.wParam;
}*/

Tutorial00App::Tutorial00App()
{
} // Called every time the NativeNativeAppBase receives a message
Tutorial00App::~Tutorial00App()
{
	m_pImmediateContext->Flush();
}

bool Tutorial00App::InitializeDiligentEngine(HWND hWnd)
{
	SwapChainDesc SCDesc;
	switch (m_DeviceType)
	{
#if D3D11_SUPPORTED
	case RENDER_DEVICE_TYPE_D3D11:
		{
			EngineD3D11CreateInfo EngineCI;
#    if ENGINE_DLL
			// Load the dll and import GetEngineFactoryD3D11() function
			auto* GetEngineFactoryD3D11 = LoadGraphicsEngineD3D11();
#    endif
			auto* pFactoryD3D11 = GetEngineFactoryD3D11();
			pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
			Win32NativeWindow Window{hWnd};
			pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window,
			                                    &m_pSwapChain);
		}
		break;
#endif


#if D3D12_SUPPORTED
	case RENDER_DEVICE_TYPE_D3D12:
		{
#    if ENGINE_DLL
			// Load the dll and import GetEngineFactoryD3D12() function
			auto GetEngineFactoryD3D12 = LoadGraphicsEngineD3D12();
#    endif
			EngineD3D12CreateInfo EngineCI;

			auto* pFactoryD3D12 = GetEngineFactoryD3D12();
			pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
			Win32NativeWindow Window{hWnd};
			pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window,
			                                    &m_pSwapChain);
		}
		break;
#endif


#if GL_SUPPORTED
	case RENDER_DEVICE_TYPE_GL:
		{
#    if EXPLICITLY_LOAD_ENGINE_GL_DLL
			// Load the dll and import GetEngineFactoryOpenGL() function
			auto GetEngineFactoryOpenGL = LoadGraphicsEngineOpenGL();
#    endif
			auto* pFactoryOpenGL = GetEngineFactoryOpenGL();

			EngineGLCreateInfo EngineCI;
			EngineCI.Window.hWnd = hWnd;

			pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext, SCDesc,
			                                           &m_pSwapChain);
		}
		break;
#endif


#if VULKAN_SUPPORTED
	case RENDER_DEVICE_TYPE_VULKAN:
		{
#    if EXPLICITLY_LOAD_ENGINE_VK_DLL
			// Load the dll and import GetEngineFactoryVk() function
			auto GetEngineFactoryVk = LoadGraphicsEngineVk();
#    endif
			EngineVkCreateInfo EngineCI;

			auto* pFactoryVk = GetEngineFactoryVk();
			pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);

			if (!m_pSwapChain && hWnd != nullptr)
			{
				Win32NativeWindow Window{hWnd};
				pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
			}
		}
		break;
#endif


	default:
		std::cerr << "Unknown/unsupported device type";
		return false;
		break;
	}

	return true;
}

bool Tutorial00App::ProcessCommandLine(const char* CmdLine)
{
	const auto* Key = "-mode ";
	const auto* pos = strstr(CmdLine, Key);
	if (pos != nullptr)
	{
		pos += strlen(Key);
		if (_stricmp(pos, "D3D11") == 0)
		{
#if D3D11_SUPPORTED
			m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
#else
                std::cerr << "Direct3D11 is not supported. Please select another device type";
                return false;
#endif
		}
		else if (_stricmp(pos, "D3D12") == 0)
		{
#if D3D12_SUPPORTED
			m_DeviceType = RENDER_DEVICE_TYPE_D3D12;
#else
                std::cerr << "Direct3D12 is not supported. Please select another device type";
                return false;
#endif
		}
		else if (_stricmp(pos, "GL") == 0)
		{
#if GL_SUPPORTED
			m_DeviceType = RENDER_DEVICE_TYPE_GL;
#else
                std::cerr << "OpenGL is not supported. Please select another device type";
                return false;
#endif
		}
		else if (_stricmp(pos, "VK") == 0)
		{
#if VULKAN_SUPPORTED
			m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
#else
                std::cerr << "Vulkan is not supported. Please select another device type";
                return false;
#endif
		}
		else
		{
			std::cerr << "Unknown device type. Only the following types are supported: D3D11, D3D12, GL, VK";
			return false;
		}
	}
	else
	{
		m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
	}
	return true;
}

void Tutorial00App::CreateResources()
{
	// Pipeline state object encompasses configuration of all GPU stages
	GraphicsPipelineStateCreateInfo PSOCreateInfo;

	// Pipeline state name is used by the engine to report issues.
	// It is always a good idea to give objects descriptive names.
	PSOCreateInfo.PSODesc.Name = "Simple triangle PSO";

	// This is a graphics pipeline
	PSOCreateInfo.PSODesc.PipelineType = PIPELINE_TYPE_GRAPHICS;

	// clang-format off
	// This tutorial will render to a single render target
	PSOCreateInfo.GraphicsPipeline.NumRenderTargets = 1;
	// Set render target format which is the format of the swap chain's color buffer
	PSOCreateInfo.GraphicsPipeline.RTVFormats[0] = m_pSwapChain->GetDesc().ColorBufferFormat;
	// Use the depth buffer format from the swap chain
	PSOCreateInfo.GraphicsPipeline.DSVFormat = m_pSwapChain->GetDesc().DepthBufferFormat;
	// Primitive topology defines what kind of primitives will be rendered by this pipeline state
	PSOCreateInfo.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	// No back face culling for this tutorial
	PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_NONE;
	// Disable depth testing
	PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = False;
	// clang-format on

	ShaderCreateInfo ShaderCI;
	// Tell the system that the shader source code is in HLSL.
	// For OpenGL, the engine will convert this into GLSL under the hood
	ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
	// OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
	ShaderCI.UseCombinedTextureSamplers = true;
	// Create a vertex shader
	RefCntAutoPtr<IShader> pVS;
	{
		ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
		ShaderCI.EntryPoint = "main";
		ShaderCI.Desc.Name = "Triangle vertex shader";
		ShaderCI.Source = vsSource;
		m_pDevice->CreateShader(ShaderCI, &pVS);
	}

	// Create a pixel shader
	RefCntAutoPtr<IShader> pPS;
	{
		ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
		ShaderCI.EntryPoint = "main";
		ShaderCI.Desc.Name = "Triangle pixel shader";
		ShaderCI.Source = PSSource;
		m_pDevice->CreateShader(ShaderCI, &pPS);
	}

	// Finally, create the pipeline state
	PSOCreateInfo.pVS = pVS;
	PSOCreateInfo.pPS = pPS;
	m_pDevice->CreateGraphicsPipelineState(PSOCreateInfo, &m_pPSO);
}

void Tutorial00App::Render()
{
	// Set render targets before issuing any draw command.
	// Note that Present() unbinds the back buffer if it is set as render target.
	auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
	auto* pDSV = m_pSwapChain->GetDepthBufferDSV();
	m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	// Clear the back buffer
	const float ClearColor[] = {0.350f, 0.350f, 0.350f, 1.0f};
	// Let the engine perform required state transitions
	m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	// Set the pipeline state in the immediate context
	m_pImmediateContext->SetPipelineState(m_pPSO);

	// Typically we should now call CommitShaderResources(), however shaders in this example don't
	// use any resources.

	DrawAttribs drawAttrs;
	drawAttrs.NumVertices = 3; // Render 3 vertices
	m_pImmediateContext->Draw(drawAttrs);
}

void Tutorial00App::Present()
{
	m_pSwapChain->Present();
}

void Tutorial00App::WindowResize(Uint32 Width, Uint32 Height)
{
	if (m_pSwapChain)
		m_pSwapChain->Resize(Width, Height);
}

RENDER_DEVICE_TYPE Tutorial00App::GetDeviceType() const
{
	return m_DeviceType;
}

LRESULT CALLBACK MessageProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(wnd, &ps);
        EndPaint(wnd, &ps);
        return 0;
    }
    case WM_SIZE: // Window size has been changed
        if (gPTheApp)
        {
            gPTheApp->WindowResize(LOWORD(lParam), HIWORD(lParam));
        }
        return 0;

    case WM_CHAR:
        if (wParam == VK_ESCAPE)
            PostQuitMessage(0);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

        lpMMI->ptMinTrackSize.x = 320;
        lpMMI->ptMinTrackSize.y = 240;
        return 0;
    }

    default:
        return DefWindowProc(wnd, message, wParam, lParam);
    }
}
