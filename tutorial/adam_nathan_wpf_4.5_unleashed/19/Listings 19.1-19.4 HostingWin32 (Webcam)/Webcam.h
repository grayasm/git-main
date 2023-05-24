#if !defined(WEBCAM_H)
#define WEBCAM_H

#include <wtypes.h>

class Webcam  
{
public:
	static HRESULT Initialize(int width, int height);
	static HRESULT AttachToWindow(HWND hwnd);
	static HRESULT Start();
	static HRESULT Pause();
	static HRESULT Stop();
	static HRESULT Repaint();
	static HRESULT Terminate();
	static int GetWidth();
	static int GetHeight();
};
#endif // !defined(WEBCAM_H)