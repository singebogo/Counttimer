#if !defined(AFX_SKINSTATIC_H__A2597F5F_FFE2_4D14_9001_B50BA6C2678B__INCLUDED_)
#define AFX_SKINSTATIC_H__A2597F5F_FFE2_4D14_9001_B50BA6C2678B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinStatic window

class CSkinStatic : public CStatic
{
// Construction
public:
	CSkinStatic();
	COLORREF m_clor;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinStatic)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinStatic)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSTATIC_H__A2597F5F_FFE2_4D14_9001_B50BA6C2678B__INCLUDED_)
