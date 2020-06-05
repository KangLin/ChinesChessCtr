#pragma once

#include "ChineseChess.h"
// CChineseChessView

#ifdef USE_PNG
#include<atlimage.h>
#endif

class AFX_EXT_CLASS CChineseChessHandler
{
public:
	CChineseChessHandler() {}
	~CChineseChessHandler() {}
	
	/**
	 * Executes the go chess action
	 *
	 * @author KangLin(kl222@126.com)
	 * @date 2020/5/24
	 *
	 * @param  int i����ǰ�����λ��,������[0-8]
     * @param  int j����ǰ�����λ��,������[0-9]
	 * @param  CPiece::ENUM_QiZi chess������
	 *
	 * @returns An int.
	 *
	 * @see CPiece::ENUM_QiZi
	 */
	virtual int OnGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;
};

class AFX_EXT_CLASS CChineseChessView : public CView, public CChineseChess
{
	DECLARE_DYNAMIC(CChineseChessView)

public:
	CChineseChessView();
	virtual ~CChineseChessView();
	void AboutBox();

	int SetQiPangColor(COLORREF col);
	COLORREF GetQiPangColor();
	int SetTiShiBoxColor(COLORREF col);
	COLORREF GetTiShiBoxColor();
	virtual int SaveChessGame(LPCTSTR pszFile);
	virtual int LoadChessGame(LPCTSTR pszFile);
	virtual int SetRedName(LPCTSTR pszName);
	virtual int SetBlackName(LPCTSTR pszName);
	virtual int SetGameTags(LPCTSTR pszTags);

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
	//���Ӻ���
	CBitmap m_Chu;
	CBitmap m_He;
	CBitmap m_Han;
	CBitmap m_Jie;
	CBitmap m_Copyright;

	//����ͼƬ
#ifdef USE_PNG
	CImage m_RedShuai;     //��˧
	CImage m_RedShi;       //����
	CImage m_RedXiang;     //����
	CImage m_RedMa;        //����
	CImage m_RedChe;       //�쳵
	CImage m_RedBing;      //���
	CImage m_RedPao;       //����

	CImage m_BlackShuai;   //��˧
	CImage m_BlackShi;     //����
	CImage m_BlackXiang;   //����
	CImage m_BlackMa;      //����
	CImage m_BlackChe;     //�ڳ�
	CImage m_BlackBing;    //�ڱ�
	CImage m_BlackPao;     //����
#else
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
#endif

#ifdef USE_PNG
	// ����Դ�м���ͼƬ�� CImage
	BOOL LoadImageFromResource(CImage *pImage, UINT ID, LPCTSTR pType = _T("PNG"));
	BOOL LoadImageFromResource(CImage *pImage, LPCTSTR pID, LPCTSTR pType = _T("PNG"));
#endif

	//����ת��
	enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);

	//������λ
	enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi);
	void DrawQiPang(CDC *pdc, CRect rcBounds);
#ifdef USE_PNG
	BOOL DrawImage(CDC *pdc, int i, int j, CImage* pImage);
#endif
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);

	void InvalidateRectage(int i, int j);

	BOOL SetQiPang(int width, int height);
	BOOL PromptSound(LPCTSTR ID = NULL);

	CChineseChessHandler* m_pGoChessHandler;
};
