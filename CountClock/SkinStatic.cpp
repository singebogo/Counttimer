// SkinStatic.cpp : implementation file
//

#include "stdafx.h"
#include <Windows.h>

#include "SkinStatic.h"
#include "CountClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinStatic

CSkinStatic::CSkinStatic()
{
	m_clor = RGB(255,0,0);
}

CSkinStatic::~CSkinStatic()
{
}


BEGIN_MESSAGE_MAP(CSkinStatic, CStatic)
	//{{AFX_MSG_MAP(CSkinStatic)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinStatic message handlers

void CSkinStatic::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	CStatic::PreSubclassWindow();
	DWORD dwStyle = GetStyle();  
    SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW);  
}



void CSkinStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC = pDC->SaveDC();

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_clor);
	// 取得位置
	CRect client_rect;
	GetClientRect(client_rect);

	// 取得文本
	CString szText;
	GetWindowText(szText);

	// 取得字体，并选入设备文件
	CFont *pFont, *pOldFont;
	pFont = GetFont();
	pOldFont = pDC->SelectObject(pFont);

	pDC->TextOut(0, 0, szText);

	pDC->SelectObject(pOldFont);
	pDC->RestoreDC(nSaveDC);
}
