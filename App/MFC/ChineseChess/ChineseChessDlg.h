
// ChineseChessDlg.h : ͷ�ļ�
//

#pragma once

#include "CDChineseChessControl.h"
#include "afxwin.h"


// CChineseChessDlg �Ի���
class CChineseChessDlg : public CDialogEx
{
// ����
public:
	CChineseChessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHINESECHESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedPreviou();
	afx_msg void OnBnClickedNext();
private:
	CDChineseChessControl m_Chess;
	CButton m_btnPreviou;
	CButton m_btnNext;
	int ReSize(int x, int y);
};
