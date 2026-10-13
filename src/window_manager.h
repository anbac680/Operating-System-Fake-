
#pragma once

#include "window.h"

void InitWindowManager();
void UpdateWindowManager(bool allowMouseInput = true);
void DrawWindowManager();
void CloseWindowManager();

void OpenNanoWindow(WindowType type);