#pragma once
#include <dinput.h>

// Global pointer
static IDirectInput8*			g_pDirectInput;
static IDirectInputDevice8*		g_pKeyboardDevice;

// Global variables
static unsigned char			keyboardKeyStates[256];

// Global methods
HRESULT InitialiseInput(HINSTANCE g_hInst, HWND g_hWnd);
void ReadInputStates();
bool IsKeyPressed(unsigned char keyCode);