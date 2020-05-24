
// ChineseChessDlg.h : ͷ�ļ�
//

#pragma once
#include "chess.h"
#include "afxwin.h"


// CChineseChessDlg �Ի���
class CChineseChessDlg : public CDialogEx
{
// ����
public:
	CChineseChessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHINESECHESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedPreviou();
	afx_msg void OnBnClickedNext();

	DECLARE_MESSAGE_MAP()

	DECLARE_EVENTSINK_MAP()
	void EventGoChess(short i, short j, long qz);

private:
	CChess m_Chess;
	int ReSize(int cx, int cy);

	CButton m_btnPreviou;
	CButton m_btnNext;

};
