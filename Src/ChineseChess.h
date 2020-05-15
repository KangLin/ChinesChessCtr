#ifndef _CHINESE_CHESS_H_KL_2020_05_13__
#define _CHINESE_CHESS_H_KL_2020_05_13__

#pragma once

#include <string>
#include <vector>

#include "EnumAndStructAndConst.h"
#include "GoRule.h"

class CChineseChess
{
public:
	CChineseChess();
	virtual ~CChineseChess();

	//����״̬
	typedef enum _ENUM_WalkState {
		RedReadly,
		RedWalked,
		BlackReadly,
		BlackWalked
	} ENUM_WalkState;

	//���̲���:��������徺������(2011)����һ�� ��1��
	typedef enum  _ENUM_BoardLayout{
		NoQi = 0,
		OnlyTopBlack = 1,
		OnlyBottomRed = 2,
		SwapRedBetweenBlack = 4,
		OnlyTopRed = OnlyTopBlack | SwapRedBetweenBlack,
		OnlyBottomBlack = OnlyBottomRed | SwapRedBetweenBlack,
		TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed,
		TopRedAndBottomBlack = TopBlackAndBottomRed | SwapRedBetweenBlack
	} ENUM_BoardLayout;
	int SetBoardLayout(ENUM_BoardLayout layout);
	int GetBoard(int &row, int &col);
	int GetBoardRow();
	int GetBoardColumn();

	bool GoChess(int i, int j);
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
		NoGo,     // ������
		Select    // ѡ��
	};
	virtual int onPromptSound(PROMPT_SOUND sound) = 0;
	virtual int onPromptMessage(char* pMessage, char* pTitle = nullptr) = 0;

	virtual int onCleanPrompt(int i, int j) = 0;
	virtual int onDrawPrompt(int i, int j) = 0;
	virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;

private:
	int Initial();
	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma = BianMa);
	bool IsValidPosition(int i, int j);

	/*
	    ��������

	     (0,0) ------------------> i �� x ����
		      |
			  |
			  |
			  |
			  |
			  |
			 \|/
			  
	      j �� y ����

	*/
	static const int m_BoardRow = 10;
	static const int m_BoardColumn = 9;
	CPiece::ENUM_QiZi m_ChessBoard[m_BoardColumn][m_BoardRow]; //���� m_ChessBoard[i][j]
	ENUM_BoardLayout m_BoardLayout;//���̲���
	ENUM_WalkState m_WalkState;    //����״̬���췽ѡ�壬�췽���壬�ڷ����壬�ڷ����壩

	// ��һ�����λ��
	int m_PreviouPositionX;
	int m_PreviouPositionY;
	int m_CurrentPositionX;
	int m_CurrentPositionY;

	int m_iBuShu;                  //���岽��
	bool m_bFuPang;                //���̱�־
	std::vector<int> m_QiJu;       //���

	CGoRule m_GoRule;
};

#endif //_CHINESE_CHESS_H_KL_2020_05_13__
