#pragma once

// For use by Kaydee applications

#include "Core/Application.h"
#include "Core/Layer.h"
#include "Core/Log.h"

#include "Core/Timestep.h"

// UI
#include "ImGui/ImGuiLayer.h"
#include <imgui/imgui.h>

// Inputs
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButtonCodes.h"
#include "Renderer/OrthographicCameraController.h"

// Rendering
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/RenderCommand.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"
#include "Renderer/VertexArray.h"

#include "Renderer/OrthographicCamera.h"

// Scene
#include "Scene/Scene.h"
#include "Scene/Components.h"
#include "Scene/Entity.h"
#include "Scene/ScriptableEntity.h"

// Entry point
#include "Core/EntryPoint.h"
