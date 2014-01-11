#include "XDMain.h"
#include "XDDirector.h"
#include 


//#include "Render.h"
//#include "InputController.h"
//#include "ResManager.h"

/*<------ Class ���� Static ���� ���� ------>*/
// XDScene* Render :: pScene = NULL;
// vector<XDSprite*> Render :: sceneObject;
// int Render :: dTime = NULL;

// CachedBitmap* Render :: pCBit = NULL;
// bool InputController :: keys[256];
// std::map<wstring, Image* > ResManager :: image_map;

// XDScene* XDDirector::_pScene = NULL;


/*<------  ----->*/
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); 
/*<--- ���α׷� ������ Ÿ��Ʋ ���� -->*/
HWND hWndMain; // HWND : ������ �ڵ��� ��� ���� Ÿ��, ����) HANDLE : �����ڵ� Ÿ��
// hWND �� ����(static)�� �� ����� �۵� ����
/*<------  ----->*/


// �츮�� Console ���� ����ϴ� int main �� ������, ������ â�� ����� winMain
// winMain �⺻���ڴ� �Ʒ��� ����.
// WinMain ���� ���α׷��� �����ϸ� �������� ó���� WndProc �Լ����� �Ѵ�.
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
       ,LPSTR lpszCmdParam,int nCmdShow) 
{
	HINSTANCE g_hInst = hInstance; // �ڵ� �ν��Ͻ� , H �� �����ϴ� �ڷ����� �� �ڵ�
	LPCTSTR lpszClass = TEXT("XNDON"); // TEXT("����") => L"����" => _T("����");


	/*<--- ������( �Է°� ����� �� �� �ֵ��� ���ش�.) Ŭ���� --->*/
    WNDCLASS WndClass;

	WndClass.cbClsExtra=0;
    WndClass.cbWndExtra=0; 
    WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1); //������ ������ ����
	WndClass.hCursor = LoadCursor(NULL,IDC_ARROW); // ���콺 Ŀ��
    WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION); // �ּ�ȭ�� ��� ������
	WndClass.hInstance = hInstance; // ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ, WinMain�� ���ڰ� ���
	WndClass.lpfnWndProc = WndProc; // �������� �޼���ó���Լ� ����, ���������� �̸� WndProc ���
	WndClass.lpszClassName = lpszClass; // ������ Ŭ������ �̸� ���� : �������� �̸�
	WndClass.lpszMenuName=NULL; // ���α׷��� ����� �޴� ����, �ڵ�� ����� ���� �ƴ� ���ҽ� �����Ϳ� ���� ����� �� �� ��ũ�� ����������. NULL �� ������� ����
	WndClass.style=CS_HREDRAW | CS_VREDRAW; // �����찡 ����, �������� ũ�Ⱑ ���� ��� �ٽ� �׸���.
	RegisterClass(&WndClass); // ������ Ŭ���� ���

	// ������ ����
	HWND hWnd;
	hWnd = CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW, 
		0 , 0, CL_WIN_WIDTH_PIXEL, CL_WIN_HEIGHT_PIXEL, NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	XDDirector::hWnd = hWnd;
	/*<--- ������ Ŭ���� ��� �� ���� �Ϸ� --->*/
	
	/*<----- GdiPlus ���� ----->*/
	ULONG_PTR gpToken;
    Gdiplus::GdiplusStartupInput gpsi;
    if ( Gdiplus::GdiplusStartup(&gpToken,&gpsi,NULL) != Gdiplus::Ok) {
		MessageBox(NULL,TEXT("GDI+ ���̺귯���� �ʱ�ȭ�� �� �����ϴ�."),
		TEXT("�˸�"),MB_OK);
		return 0;
	} 
	/*<------------------------>*/	

	
//	XDScene scene;
//	Render::setScene(&scene);	


	MSG Message;
    while ( GetMessage(&Message,NULL,0,0) )
	{
//		TranslateMessage(&Message); // TranslateMessage �Լ��� ���޵� �޽����� WM_KEYDOWN������ ������ Ű�� ����Ű���� �˻��� ���� ������ ���� ��� WM_CHAR �޽����� ����� �޽��� ť�� �����̴� ������ �Ѵ�. ���� ���� �Է��� �ƴ� ���� �ƹ� �ϵ� ���� ������ �� �޽����� DispatchMessage �Լ��� ���� WndProc���� ��������.
		DispatchMessage(&Message);  // �Էµ� ������ �ƽ�Ű �ڵ带 wParam���� ����
    }

	// BOOL GetMessage( LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax); 
    // �� �Լ��� �ý����� �����ϴ� �޽��� ť���� �޽����� �о���δ�. �о���� �޽����� ù��° �μ��� �����ϴ� MSG ����ü�� ����ȴ�. �� �Լ��� �о���� �޽����� ���α׷��� �����϶�� WM_QUIT�� ��� False�� �����ϸ� �� ���� �޽����̸� True�� �����Ѵ�. ���� WM_QUIT �޽����� ������ ������, �� ���α׷��� ����� ������ ��ü while ������ ��� ����ȴ�. ������ �� ���� �μ��� �о���� �޽����� ������ �����ϴµ� �� ������ �����Ƿ� �ϴ� �����ϱ�� �Ѵ�.

	// BOOL TranslateMessage( CONST MSG *lpMsg); 
	// Ű���� �Է� �޽����� �����Ͽ� ���α׷����� ���� �� �� �ֵ��� �� �ش�. ��������� Ű������ � Ű�� �������ٰų� �������� �� Ű���� �޽����� �߻���Ű�µ� �� �Լ��� Ű������ ����(WM_KEYDOWN)�� ������(WM_KEYUP)�� ���������� �߻��� �� ���ڰ� �ԷµǾ��ٴ� �޽���(WM_CHAR)�� ����� ������ �Ѵ�. ���� ��� AŰ�� ���� �� �ٽ� AŰ�� ���� A���ڰ� �ԷµǾ��ٴ� �޽����� ����� ����.

	// LONG DispatchMessage( CONST MSG *lpmsg); 
	// �ý��� �޽��� ť���� ���� �޽����� ���α׷��� �޽��� ó�� �Լ�(WndProc)�� �����Ѵ�. �� �Լ��� ���� �޽����� ���α׷����� ���޵Ǹ� ���α׷������� ���޵� �޽����� �����Ͽ� ���� ������ �����ϰ� �ȴ�.
	// �޽��� �������� �ϴ� ���� �޽����� ������, �ʿ��� ��� �ణ ���¸� �ٲ� �� ���� ���α׷����� �����ϴ� �� ���̴�. �� ������ WM_QUIT �޽����� ���޵� ������, �� ���α׷��� ����ɶ����� �ݺ��ȴ�. �ᱹ �޽��� ������ �ϴ� ���̶� �޽��� ť���� �޽����� ���� �޽��� ó�� �Լ��� �����ִ� �� ���̴�.
	// ���� �޽��� ó���� ������ �޽��� ó�� �Լ�(WndProc)���� �����Ѵ�. �޽����� �ý����� ��ȭ�� ���� �����̸� MSG��� ����ü�� �����ȴ�. MSG ����ü�� ������ ���� ���ǵǾ� �ִ�.

	/*<----- GDI+ ���� ----->*/
	Gdiplus::GdiplusShutdown(gpToken);
	/*<--------------------->*/

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{	
	/*
	���콺 ��� ������ ������
	vector<LPARAM> leftmousemove ;
	vector<LPARAM> rightmousemove;
	bool leftdown = FALSE;
	bool rightdown = FALSE;
	*/

//	HANDLE hTimer;
	switch (iMessage) {
	case WM_CREATE:
		XDDirector::_lastTime = clock();
		SetTimer( hWnd, 1, 30, NULL );
		SendMessage(hWnd, WM_TIMER, 1, 0); //�޼����� ���� WndProc �� �θ��� �Լ� ���ڴ� WndProc �� ���޵Ǵ� ���ڿ� ����.
//		hTimer= (HANDLE) SetTimer( hWnd, 1, 10, NULL );
//		XDDirector::set_hWndMain( hWnd );
//		hWndMain = hWnd;
//		hdc = GetDC(hWnd);		 
		// SetTimer() ���� Ÿ�̸� ��ġ, KillTimer() ���� Ÿ�̸� ����
		// �켱������ �����Ƿ� ��Ȯ���� ���ؼ��� Ÿ�̸� �ݹ� �Լ� ��� => �׹�° ���ڿ� �ݹ��Լ� ����
      	return 0;

	 case WM_KEYUP:
//		InputController::keys[wParam] = FALSE;		
		return 0;
	 case WM_KEYDOWN:
//		InputController::keys[wParam] = TRUE;
		return 0;
	/* ���콺 ��� ������ ������
	 case WM_LBUTTONDOWN:
		 leftdown = TRUE;
		 leftmousemove.clear();
		 leftmousemove.push_back(lParam);
		 return 0;

	 case WM_LBUTTONUP:
		 leftdown = FALSE;

		
		 return 0;

	 case WM_MOUSEMOVE:
		 if(leftdown==TRUE)
			leftmousemove.push_back(lParam);
		 return 0;
	*/

	case WM_TIMER:
		XDDirector::_dTime = XDDirector::_lastTime - clock();
		XDDirector::_lastTime = clock();
		XDDirector::Update( );
		InvalidateRect(hWnd,NULL,FALSE);
		return 0;
	
	// ������ WM_PAINT �޽����� �߻����� �־�� �� ������ InvalidateRect(hWnd,NULL,FALSE); �Լ��� ȣ�� 
	// BOOL InvlidateRect(HWND hWnd, CONST RECT *lpRect, BOOL bErase); 
	// �� �Լ��� �������� �۾� ������ ��ȿȭ���� ��������� �Ͽ��� WM_PAINT �޽����� �ش� ������� �������� �Ѵ�. ù��° �μ� hWnd�� ��ȿȭ�� ����� �Ǵ� ������, �� �ٽ� �׷����� �� �������� �ڵ��̴�. �� ���� WndProc�� ȣ��� �� ���޵Ǵ� ù��° �μ� hWnd�� �״�� �� �ָ� �ȴ�.
	// �ι�° �μ� lpRect�� ��ȿȭ�� ����� �Ǵ� �簢 ������ �� �ֵ� �� ���� NULL�̸� �������� �� ������ ��ȿȭ�ȴ�. �� ������ ��ȿȭ�ϸ� �����찡 ������ �ٽ� �׷����Ƿ� Ȯ���ϰ� �׷������ �ϰ����� �׸�ŭ ����ӵ��� �ʾ����� �ȴ�. �ӵ��� �ִ��� ���̷��� ����� �ּ����� �������� ����Ͽ� ��ȿȭ�ϴ� ���� ����. ���������� �� ������ �� ��ȿȭ�Ͽ� ��� �ٽ� �׸����� �Ͽ��µ� ���� ��ü�� �����ϱ� ������ �ӵ��� ���ϴ� ���� �� ������ �׸� �� ���� ����� �ƴϴ�.
	// ����° �μ� bErase�� ��ȿȭ�Ǳ� ���� ����� ��� ���� �� �ٽ� �׸� ������ �ƴϸ� ����� ������ �ʰ� �׸� �������� �����Ѵ�. �� ���� TRUE�̸� ����� ���� �� �ٽ� �׸��� FALSE�̸� ����� ������ ����ä�� �ٽ� �׸���. Key ������ ��� ���ڿ��� ��� �þ ���� ���������� ���ڰ� ���� ������ �� �μ��� FALSE�� �����Ͽ����� ���������� �κ��� �ִٸ� �� �μ��� TRUE�� �Ǿ�� �Ѵ�. ������ ������ ���� ������ ����.
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc=BeginPaint(hWnd, &ps);
		XDDirector::OnPaint(hdc);
		EndPaint(hWnd, &ps);
//		Render::draw( hdc );
//		Graphics &G
//		XDDirector::OnPaint()
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

// DC(Device Context)�� ��¿� �ʿ��� ��� ������ ������ ������ ����ü�̸� GDI ��⿡ ���� �����ȴ�. � ��Ʈ�� ����� ���ΰ�, ���� ����� ����, ä�� ���̿� ����, ��� ��� ����� ��� ��¿� �ʿ��� �������̴�. ȭ�� ��¿� DC�� �ʿ��� ������ �����ϱ� ���� ��� ���� ��� ������ ����.


//void CALLBACK update(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
/*
void update(int dt)
{
	//HDC hdc = GetDC(XDDirector::get_hWndMain());
	HDC hdc = GetDC(hWndMain);
	
	Graphics G(hdc);
	using namespace Gdiplus;

    SolidBrush RESET( Color(255,255,255,255) );
	G.FillRectangle(&RESET,0,0,1280,760);

	Font F(L"����",20,FontStyleRegular,UnitPixel);

//	TCHAR *Hangul=L"�ѱ� ���ڿ�";
	TCHAR szWidth[128];
	RectF bound;
	SolidBrush B(Color(0,0,0));
//	G.DrawString(Hangul,-1,&F,PointF(0,00),&B);
//	G.MeasureString(Hangul,-1,&F,PointF(0,0),&bound);
	_stprintf_s(szWidth,TEXT("dwTime:%u, ������ : %.2lf"), dt, 1000.0/(dt) ); // swprintf == _stprintf_s
	
	G.DrawString(szWidth,-1,&F, PointF(0,6),&B);

//	ReleaseDC(hWndMain, hdc);
//	Render::draw(hdc);
//	Render::sceneUpdate( );
}
*/
