#pragma once

#include "ChineseChess.h"
// CChineseChessView


class AFX_EXT_CLASS CChineseChessHandler
{
public:
	CChineseChessHandler() {}
	~CChineseChessHandler() {}

	virtual int OnGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;
};

class AFX_EXT_CLASS CChineseChessView : public CView, public CChineseChess
{
	DECLARE_DYNAMIC(CChineseChessView)

public:
	CChineseChessView();
	virtual ~CChineseChessView();
	void AboutBox();

	virtual int SaveChessGame(LPCTSTR pszFile);
	virtual int LoadChessGame(LPCTSTR pszFile);
	virtual int SetRedName(LPCTSTR pszName);
	virtual int SetBlackName(LPCTSTR pszName);

	int SetChineseChessHandler(CChineseChessHandler* handler);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual void OnDraw(CDC* pDC);

protected:
	virtual int onPromptSound(PROMPT_SOUND sound);
	virtual int onPromptMessage(CGoRule::ENUM_ReturnValue val);

	virtual int onCleanPrompt(int i, int j);
	virtual int onDrawPrompt(int i, int j);
	virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess);

private:
	LONG m_QiPangStartX;   //���̵Ŀ�ʼ������
	LONG m_QiPangStartY;   //���̵Ŀ�ʼ������
	LONG m_QiPangDistance; //���̸�ľ���
	
	COLORREF m_QiPangColor;
	COLORREF m_TiShiBoxColor;
	
	CBitmap m_QiPangPicture;			  //���̱���ͼƬ
	//CPictureHolder m_QiPangPictureHolder; //���̱���ͼƬ��CPictureHolder����

	//����ͼƬ
	CBitmap m_RedShuai;     //��˧
	CBitmap m_RedShi;       //����
	CBitmap m_RedXiang;     //����
	CBitmap m_RedMa;        //����
	CBitmap m_RedChe;       //�쳵
	CBitmap m_RedBing;      //���
	CBitmap m_RedPao;       //����

	CBitmap m_BlackShuai;   //��˧
	CBitmap m_BlackShi;     //����
	CBitmap m_BlackXiang;   //����
	CBitmap m_BlackMa;      //����
	CBitmap m_BlackChe;     //�ڳ�
	CBitmap m_BlackBing;    //�ڱ�
	CBitmap m_BlackPao;     //����


	//����ת��
	enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);

	//������λ
	enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);
	BOOL DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi);
	void DrawQiPang(CDC *pdc, CRect rcBounds);

	void InvalidateRectage(int i, int j);

	BOOL SetQiPang(int width, int height);
	BOOL PromptSound(LPCTSTR ID = NULL);

	CChineseChessHandler* m_pGoChessHandler;
};


