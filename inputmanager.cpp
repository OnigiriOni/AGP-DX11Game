#include "inputmanager.h"

HRESULT InitialiseInput(HINSTANCE g_hInst, HWND g_hWnd)
{
	HRESULT hr;

	// Create the DirectInput device
	ZeroMemory(keyboardKeyStates, sizeof(keyboardKeyStates));
	hr = DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDirectInput, NULL);

	if (FAILED(hr))
	{
		return hr;
	}

	// Create the keyboard
	hr = g_pDirectInput->CreateDevice(GUID_SysKeyboard, &g_pKeyboardDevice, NULL);

	if (FAILED(hr))
	{
		return hr;
	}

	// Set the date format
	hr = g_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hr))
	{
		return hr;
	}

	// Set the cooperation level
	hr = g_pKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (FAILED(hr))
	{
		return hr;
	}

	// Start providing input  -  THIS FAILS IN DEBUG MODE
	hr = g_pKeyboardDevice->Acquire();

	if (FAILED(hr))
	{
		return hr;
	}

	return S_OK;
}

void ReadInputStates()
{
	HRESULT hr;

	// Get the device state
	hr = g_pKeyboardDevice->GetDeviceState(sizeof(keyboardKeyStates), (LPVOID) &keyboardKeyStates);

	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			g_pKeyboardDevice->Acquire();
		}
	}
}

bool IsKeyPressed(unsigned char keyCode)
{
	return keyboardKeyStates[keyCode] & 0x80;
}
