#include "stdafx.h"
#include "Webcam.h"

#include <d3d9.h>
#include <dshow.h>
#include <vmr9.h>

int _width = 0;
int _height = 0;
IGraphBuilder* _graphBuilder = NULL;
IMediaControl* _mediaControl = NULL;
IVMRWindowlessControl* _windowlessControl = NULL;
IBaseFilter* _baseFilter = NULL;
IPin* _pin = NULL;
bool _initialized = false;
HWND _hwnd = NULL;

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_ERASEBKGND:
			DefWindowProc(hwnd, msg, wParam, lParam);
			Webcam::Repaint();
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

HRESULT Webcam::Initialize(int width, int height)
{
	_width = width;
	_height = height;

	// Create and register the Window Class
	WNDCLASS wc;
	wc.style         = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = GetModuleHandle(NULL);
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_SCROLLBAR+1);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"WebcamClass";

	RegisterClass(&wc);

    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&_graphBuilder);

	if (FAILED(hr))
		return hr;

	IBaseFilter* pBaseFilter = NULL;
	ICreateDevEnum* pCreateDevEnum = NULL;
	IEnumMediaTypes* pEnumMediaTypes = NULL;
	IEnumMoniker* pEnumMoniker = NULL;
	IEnumPins* pEnumPins = NULL;
	IVMRFilterConfig* pFilterConfig = NULL;
	IMoniker* pMoniker = NULL;
	IAMStreamConfig* pStreamConfig = NULL;

	__try
	{
		hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void**)&pBaseFilter);
		if (FAILED(hr))
			return hr;

		hr = _graphBuilder->AddFilter(pBaseFilter, L"Video Mixing Renderer");
		if (FAILED(hr))
			return hr;

		hr = pBaseFilter->QueryInterface(IID_IVMRFilterConfig, (void**)&pFilterConfig);
		if (FAILED(hr))
			return hr;

		hr = pFilterConfig->SetRenderingMode(VMRMode_Windowless);
		if (FAILED(hr))
			return hr;

		hr = pBaseFilter->QueryInterface(IID_IVMRWindowlessControl, (void**)&_windowlessControl);
		if (FAILED(hr))
			return hr;

		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);
		if (FAILED(hr))
			return hr;

		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumMoniker, 0);
		if (hr != NOERROR) 
		{
			// No video capture device could be found.
			return E_FAIL;
		}

		// Just grab the first device:
		ULONG fetched;
		hr = pEnumMoniker->Next(1, &pMoniker, &fetched);
		if (FAILED(hr))
			return hr;
		
		hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&_baseFilter);
		if (FAILED(hr))
			return hr;

		hr = _graphBuilder->AddFilter(_baseFilter, L"Video Capture");
		if (FAILED(hr))
			return hr;

		hr = _baseFilter->EnumPins(&pEnumPins);
		if (FAILED(hr))
			return hr;

		hr = pEnumPins->Reset();
		if (FAILED(hr))
			return hr;

		hr = pEnumPins->Next(1, &_pin, NULL); 
		if (FAILED(hr))
			return hr;
		
        hr = _graphBuilder->QueryInterface(IID_IMediaControl, (void **)&_mediaControl);
		if (FAILED(hr))
			return hr;

		AM_MEDIA_TYPE* type = NULL;

		hr = _pin->EnumMediaTypes(&pEnumMediaTypes);
		if(SUCCEEDED(hr))
		{
			while(pEnumMediaTypes->Next(1, &type, 0) == S_OK)
			{
				if(type->formattype == FORMAT_VideoInfo)
				{
					VIDEOINFOHEADER *vih = (VIDEOINFOHEADER *)type->pbFormat;

					if(vih->bmiHeader.biWidth == width && vih->bmiHeader.biHeight == height)
					{
						hr = _pin->QueryInterface(IID_IAMStreamConfig, (void **) &pStreamConfig);
						if(SUCCEEDED(hr))
						{
							if(type != NULL)
							{
								hr=pStreamConfig->SetFormat(type);

								if (type != NULL)
								{
									if (type->cbFormat != NULL) CoTaskMemFree((PVOID)type->pbFormat);
									if (type->pUnk != NULL) type->pUnk->Release();
									CoTaskMemFree((PVOID)type);
								}
							}
						}
						break;
					}

					if (type != NULL)
					{
						if (type->cbFormat != NULL) CoTaskMemFree((PVOID)type->pbFormat);
						if (type->pUnk != NULL) type->pUnk->Release();
						CoTaskMemFree((PVOID)type);
					}
				}
			}
		}
		_initialized = true;
	}
	__finally
	{
		if (pBaseFilter) pBaseFilter->Release();
		if (pCreateDevEnum) pCreateDevEnum->Release();
		if (pEnumMediaTypes) pEnumMediaTypes->Release();
		if (pEnumMoniker) pEnumMoniker->Release();
		if (pEnumPins) pEnumPins->Release();
		if (pFilterConfig) pFilterConfig->Release();
		if (pMoniker) pMoniker->Release();
		if (pStreamConfig) pStreamConfig->Release();
	}
	return hr;
}

HRESULT Webcam::AttachToWindow(HWND hwnd)
{
	if (!_initialized || !_windowlessControl)
		return E_FAIL;

	_hwnd = hwnd;

	// Position and size the video
	RECT rcDest;
	rcDest.left = 0;
	rcDest.right = _width;
	rcDest.top = 0;
	rcDest.bottom = _height;
	_windowlessControl->SetVideoClippingWindow(hwnd);
	return _windowlessControl->SetVideoPosition(NULL, &rcDest);
}

HRESULT Webcam::Start()
{
	if (!_initialized || !_graphBuilder || !_mediaControl)
		return E_FAIL;

	_graphBuilder->Render(_pin);
	return _mediaControl->Run();
}

HRESULT Webcam::Pause()
{
	if (!_initialized || !_mediaControl)
		return E_FAIL;

	return _mediaControl->Pause();
}

HRESULT Webcam::Stop()
{
	if (!_initialized || !_mediaControl)
		return E_FAIL;

	return _mediaControl->Stop();
}

HRESULT Webcam::Repaint()
{
	if (!_initialized || !_windowlessControl)
		return E_FAIL;

	HDC hdc = GetDC(_hwnd);
	return _windowlessControl->RepaintVideo(_hwnd, hdc);
}

HRESULT Webcam::Terminate()
{
    HRESULT hr = Webcam::Stop();

	if(_pin)
	{
		_pin->Disconnect();
		_pin->Release();
	}
	if (_graphBuilder) _graphBuilder->Release();
	if (_mediaControl) _mediaControl->Release();
	if (_windowlessControl) _windowlessControl->Release();
	if (_baseFilter) _baseFilter->Release();

	return hr;
}

int Webcam::GetWidth()
{
	return _width;
}

int Webcam::GetHeight()
{
	return _height;
}