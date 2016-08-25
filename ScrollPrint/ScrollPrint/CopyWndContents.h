#pragma once

class CCopyWndContents
{
public:
	virtual ~CCopyWndContents();

	BOOL DoCopy(CBitmap& bmp);

protected:
	CCopyWndContents(CWnd& wnd);

protected:
	CWnd& m_wnd;

protected:
	virtual void DoPageDown();
	virtual void DoPageRight();
	virtual void DoPrint(CDC& dc);
	virtual CSize CalcContentsSize() const;
	virtual CSize CalcPageSize() const;

	CSize GetContentsSize() const { return m_sizeContent; }
	CSize GetPageSize() const { return m_sizePage; }

	static void DoPrint(HWND hwnd, HDC hdc, DWORD dwFlags = PRF_CLIENT);

private:
	CSize m_sizeContent, m_sizePage;

private:
	int PageDown(int nCurVertPos);
	int PageRight(int nCurHorzPos);
};

class CCopyTreeCtrlContents : public CCopyWndContents
{
public:
	CCopyTreeCtrlContents(CTreeCtrl& tree);
	virtual ~CCopyTreeCtrlContents();

protected:
	int m_nItemHeight;

protected:
	virtual void DoPageDown();
	virtual void DoPageRight();
	virtual CSize CalcContentsSize() const;
	virtual CSize CalcPageSize() const;
};

class CCopyListCtrlContents : public CCopyWndContents
{
public:
	CCopyListCtrlContents(CListCtrl& list);
	virtual ~CCopyListCtrlContents();

protected:
	int m_nItemHeight;

protected:
	virtual void DoPageDown();
	virtual void DoPageRight();
	virtual void DoPrint(CDC& dc);
	virtual CSize CalcContentsSize() const;
	virtual CSize CalcPageSize() const;

	// helpers
	int CalcHeaderHeight() const;
};

class CCopyHeaderCtrlContents : public CCopyWndContents
{
public:
	CCopyHeaderCtrlContents(CHeaderCtrl& hdr);
	virtual ~CCopyHeaderCtrlContents();
};

class CCopyEditContents : public CCopyWndContents
{
public:
	CCopyEditContents(CEdit& edit);
	virtual ~CCopyEditContents();

protected:
	int m_nLineHeight, m_nLineCount;

protected:
	virtual void DoPageDown();
	virtual void DoPageRight();
	virtual CSize CalcContentsSize() const;
	virtual CSize CalcPageSize() const;
};
