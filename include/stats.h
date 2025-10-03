#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <sys/resource.h>
#include <unistd.h>

double getRAMUsage();
void initStats(GLFWwindow *window);
void renderStats();