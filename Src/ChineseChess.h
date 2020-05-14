#pragma once

#include <string>

#include "EnumAndStructAndConst.h"
#include "GoRule.h"

class CChineseChess
{
public:
	CChineseChess();
	virtual ~CChineseChess();

	//����״̬
	enum ENUM_WalkState { RedReadly, RedWalked, BlackReadly, BlackWalked };
	//���̲���:��������徺������(2011)����һ�� ��1��
	enum ENUM_BoardLayout {
		NoQi = 0,
		OnlyTopBlack = 1,
		OnlyBottomRed = 2,
		SwapRedBetweenBlack = 4,
		OnlyTopRed = OnlyTopBlack | SwapRedBetweenBlack,
		OnlyBottomBlack = OnlyBottomRed | SwapRedBetweenBlack,
		TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed,
		TopRedAndBottomBlack = OnlyTopRed | OnlyBottomBlack | SwapRedBetweenBlack
	};

	int GetBoardRown();
	int GetBoardColumn();

	bool GoChess(int i, int j, bool bEvent = true);
	bool IsGoChess(int i, int j);
	//int NextStep();                              //��һ��
	//int PreviouStep();                           //��һ��
	//int ReStart();                               //���¿�ʼ
	//int SaveChess(char* pFileName);          //�������
	//int LoadChess(char* pFileName);          //װ����֣�������Ϊ����״̬
	//int LoadChessStart(char* pFileName);     //װ����֣�������Ϊ��ʼ״̬

protected:
	enum PROMPT_SOUND {
		JiangJun, // ����
		Eat,      // ����
		Go,       // ����
		Select    // ѡ��
	};
	virtual int onPromptSound(PROMPT_SOUND sound) = 0;
	virtual int onPromptMessage(char* pMessage, char* pTitle = nullptr) = 0;

private:
	int Initial();

private:
	static const int m_BoardRow = 9;
	static const int m_BoardColumn = 10;

	ENUM_QiZi m_ChessBoard[m_BoardRow][m_BoardColumn]; //���� m_ChessBoard[i][j]
	ENUM_BoardLayout m_BoardLayout;//���̲���
	ENUM_WalkState m_WalkState;    //����״̬���췽ѡ�壬�췽���壬�ڷ����壬�ڷ����壩

	int m_iBuShu;                  //���岽��
	bool m_bFuPang;                //���̱�־

	// ��һ�����λ��
	int m_PreviouPositionX;
	int m_PreviouPositionY;
	int m_CurrentPositionX;
	int m_CurrentPositionY;

	CGoRule m_GoRule;
};

