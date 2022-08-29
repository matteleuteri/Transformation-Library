#include "headers/Winmain.h"

static void handleKeyDown(WPARAM wParam)
{
    if(wParam == VK_RIGHT) 
    {
        go->animationController->setAnimation("EXAMPLE2");
    }
    else if(wParam == VK_LEFT) 
    {
        go->animationController->setAnimation("EXAMPLE1");
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (uMsg)
    {
        case WM_CLOSE: 
        {
            isRunning = false;
            // if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK) 
            DestroyWindow(hwnd);
            break;
        } 
        case WM_DESTROY:
        {
            isRunning = false;
            PostQuitMessage(0);
            break;
        }
        case WM_KEYDOWN:
        {
            handleKeyDown(wParam);
            return 0;
        } 
        //case WM_KEYUP:
        //{
            //handleKeyUp(wParam);
          //  return 0;
        //} 
        default: 
        {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        } 
    }
    return result;
}

void createResources(HWND hwnd, RECT* rc) 
{
    ID2D1Factory* pD2DFactory = nullptr;
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    D2D1_SIZE_U clientSize = D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, clientSize), &renderTarget);
    CoInitializeEx(NULL, COINIT_MULTITHREADED); 
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));    
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[]  = L"Animation Library";
    
    WNDCLASS wc = { };
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = CLASS_NAME;

    if(RegisterClass(&wc))
    {
        HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Animation Library", 
                    WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 
                    CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
        if(hwnd) 
        {
            isRunning = true;
            RECT rc;
            GetClientRect(hwnd, &rc);

            std::filesystem::path p = std::filesystem::current_path().remove_filename();
            p /= "assets";

            createResources(hwnd, &rc);

            auto animationController = std::make_unique<AnimationController>(renderTarget, hwnd, &rc, p);
            animationController->loadAnimation(pIWICFactory, { "run1.png", "run2.png", "run3.png", 
                        "run4.png", "run5.png", "run4.png", "run3.png", "run2.png" },
                        "EXAMPLE1", GetTickCount(), 100);

            animationController->loadAnimation(pIWICFactory, { "jump1.png", "jump2.png", "jump3.png", 
                        "jump4.png", "jump5.png", "jump6.png", "jump7.png", "jump6.png", 
                        "jump5.png", "jump4.png", "jump3.png", "jump2.png", "jump1.png" },
                        "EXAMPLE2", GetTickCount(), 100);
            
            animationController->setAnimation("EXAMPLE1");
            go = std::make_unique<GameObject>(animationController.get(), 200.0f, 200.0f, 0.5f);

            int32_t startTime = GetTickCount();
            int32_t endTime;
            while(isRunning)
            {
                MSG msg;
                while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    if(msg.message == WM_QUIT)
                    {
                        isRunning = false;
                        break;
                    }
                    TranslateMessage(&msg);
                    DispatchMessageA(&msg);
                }
                endTime = GetTickCount();
                if(endTime - startTime > 100)
                {
                    renderTarget->BeginDraw();
                    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));  
                    go->animationController->animate(GetTickCount(), go->x, go->y);
                    renderTarget->EndDraw();
                    // scene->updateState(hwnd, endTime, startTime);
                    // scene->renderState(hwnd, renderTarget, pTextFormat_);                    
                    startTime = endTime;
                }
            }
        }
    }
    return 0;
}
