
// ChineseChessDlg.h : ͷ�ļ�
//

#pragma once
#include "Chess.h"


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
	CChess m_Chess;
	DECLARE_EVENTSINK_MAP()
	void MoveChessChess(short x, short y, long chess);
};
