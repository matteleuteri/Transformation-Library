#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>
#include <filesystem>
#include <array>

#include <d2d1.h>
#include <vector>
#include <memory>

#include <combaseapi.h>
#include <Objbase.h>
#include "GameObject.h"

static bool isRunning;
std::unique_ptr<GameObject> go;
IWICImagingFactory* pIWICFactory;
ID2D1HwndRenderTarget* renderTarget;
