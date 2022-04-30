/*****************************************************************************/
/*!
\file   ImGUILayer.cpp
\author Sam Marsden
\par    email: smarsden1999\@gmail.com
\date   4/26/2022
\brief
		This file contains the definition for the Celestial-specific ImGUI Layer

		Functions include:

			 + ImGUILayer
			 + ~ImGUILayer
			 
			 + OnImGUIRender
			 + OnAttach
			 + OnDetach

*!/
/*****************************************************************************/
#include "clpch.h"

#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ImGUILayer.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "GLFW/glfw3.h"
#include "Celestial/Application.h"

//! ** TEMPORARY **
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Celestial
{

#define BIND_EVENT_FN(x) std::bind(&ImGUILayer::x, this, std::placeholders::_1)

	/*****************************************************************************/
/*!
	\brief
		Default Constructor
*/
/*****************************************************************************/
	ImGUILayer::ImGUILayer()
		: Layer("ImGUI Layer")
	{
	}

	/*****************************************************************************/
/*!
	\brief
		Destructor
*/
/*****************************************************************************/
	ImGUILayer::~ImGUILayer()
	{
	}

	/*****************************************************************************/
/*!
	\brief
		Called each frame, when the layer stack updates
*/
/*****************************************************************************/
	void ImGUILayer::OnImGUIRender()
	{
		bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	/*****************************************************************************/
/*!
	\brief
		Called when layer is attached to the layer stack
*/
/*****************************************************************************/
	void ImGUILayer::OnAttach()
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.f;
			style.Colors[ImGuiCol_WindowBg].w = 1.f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	/*****************************************************************************/
/*!
	\brief
		Called when the layer is dettached to the layer stack
*/
/*****************************************************************************/
	void ImGUILayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}

	void ImGUILayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGUILayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::Get();
		Celestial::Window& window = app.GetWindow();

		io.DisplaySize = ImVec2((float)window.GetWidth(), (float)window.GetHeight());

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();

			ImGui::UpdatePlatformWindows();

			ImGui::RenderPlatformWindowsDefault();

			glfwMakeContextCurrent(backup_current_context);
		}
	}

}