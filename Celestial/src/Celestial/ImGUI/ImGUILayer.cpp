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
			 
			 + OnUpdate
			 + OnAttach
			 + OnDetach
			 + OnEvent

			 + OnMouseMovedEvent
       + OnMouseScrolledEvent

       + OnWindowResizeEvent
       + OnWindowCloseEvent

       + OnKeyPressedEvent
       + OnKeyReleasedEvent
       + OnKeyTypedEvent

*!/
/*****************************************************************************/
#include "clpch.h"
#include "ImGUILayer.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "GLFW/glfw3.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
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
	void ImGUILayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.f);
		m_Time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);



		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	/*****************************************************************************/
/*!
	\brief
		Called when layer is attached to the layer stack
*/
/*****************************************************************************/
	void ImGUILayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
		
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
	}

	/*****************************************************************************/
/*!
	\brief
		Called when an event is propogated to this layer by the layer stack,
		dispatches events to related On___Event() functions

	\param e
		The generic event to be dispatched and (potentially) handled
*/
/*****************************************************************************/
	void ImGUILayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnMouseScrolledEvent));

		dispatcher.Dispatch<WindowResizeEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnWindowResizeEvent));
		dispatcher.Dispatch<WindowCloseEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnWindowCloseEvent));

		dispatcher.Dispatch<KeyPressedEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(CL_BIND_EVENT_FN(ImGUILayer::OnKeyTypedEvent));
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a MouseButtonPressedEvent

	\param e
		The MouseButtonPressed event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a MouseButtonReleasedEvent

	\param e
		The MouseButtonReleased event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a MouseMovedEvent

	\param e
		The MouseMoved event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a MouseScrolledEvent

	\param e
		The MouseScrolled event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetY();
		io.MouseWheelH += e.GetX();

		return false;
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a WindowResizeEvent

	\param e
		The WindowResize event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a WindowClosedEvent (Currently does nothing)

	\param e
		The WindowClose event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		return false;
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a KeyPressedEvent

	\param e
		The KeyPressed event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	/*****************************************************************************/
/*!
	\brief
		Function callback for a KeyReleasedEvent

	\param e
		The KeyReleased event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}


	/*****************************************************************************/
/*!
	\brief
		Function callback for a KeyTypedEvent

	\param e
		The KeyTyped event to get data from

	\return
		Returns if the event is handled by this function.
		True = event has been handled and should stop propogating
		False = event has not been handled and will continue propogating
*/
/*****************************************************************************/
	bool ImGUILayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

}