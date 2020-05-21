/**
 * @file ChineseChess.h.
 *
 * �й�������
 * 
 */
 
#ifndef _CHINESE_CHESS_H_KL_2020_05_13__
#define _CHINESE_CHESS_H_KL_2020_05_13__

#pragma once

#include "GoRule.h"
#include "ChessGame.h"

#include "chinesechess_export.h"

/**
 * �й�������
 * - ʵ���й�����Ļ�������
 * - ʵ�ָ���  
 * - ʵ�ָ������  
 * 
 * ���沿������Ӧ�Ľ���������ʵ����Ӧ�����⺯��
 * 
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CHINESECHESS_EXPORT CChineseChess
{
public:
	CChineseChess();
	virtual ~CChineseChess();

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

	/**
	 * Go chess
	 *
	 * @author KangLin(kl222@126.com)
	 * @date 2020/5/17
	 *
     * @param  int i����ǰ�����λ��,������[0-8]
     * @param  int j����ǰ�����λ��,������[0-9]
	 * @param  bNext (Optional) ָʾ�Ƿ�����NextStep�е���
	 * 				 ������� NextStep �е��ã������ڸ���
	 * 				 ������ǡ���������������
	 *
	 * @returns True if it succeeds, false if it fails.
	 */
	bool GoChess(int i, int j, bool bNext = false);	//����

	// ���̲���
	int NextStep();	   //��һ��
	int PreviouStep(); //��һ��

	//�������
	int SaveChessGame(const char* pszFile);
	int LoadChessGame(const char* pszFile);

	int EnablePromptSound(bool sound = true);
	int EnablePromptMessage(bool bMsg = true);

protected:
	// �������⺯���ɽ���ʵ�������
	
	// ��ʾ��
	enum PROMPT_SOUND {
		JiangJun, // ����
		Eat,      // ����
		Go,       // ����
		NoGo,     // ������
		Select    // ѡ��
	};
	virtual int onPromptSound(PROMPT_SOUND sound = NoGo) = 0;
	// ��ʾ������Ϣ
	virtual int onPromptMessage(CGoRule::ENUM_ReturnValue val) = 0;
	// �����ʾ��
	virtual int onCleanPrompt(int i, int j) = 0;
	// ����ʾ��
	virtual int onDrawPrompt(int i, int j) = 0;
	// �����¼�
	// @see ��������
	virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;

private:
	// �жϵ�ǰ�ŷ��Ƿ�Ϸ�
	bool IsGoChess(int i, int j);

	CGoRule m_GoRule;  //�������
	CChessGame m_Game; //���

	bool m_bPromptSound;
	bool m_bPromptMessage;

protected:
	/*
	    @brief ��������

	    [0][0] ------------------> i �� x ����
		      |
			  |
			  |
			  |
			  |
			  |
			 \|/                 [9][10]
			  
	      j �� y ����

	*/
	CPiece::ENUM_QiZi m_ChessBoard[9][10]; //���� m_ChessBoard[i][j]
	ENUM_BoardLayout m_BoardLayout;		   //���̲���

	//����״̬
	typedef enum _ENUM_WalkState {
		RedReadly,
		RedWalked,
		BlackReadly,
		BlackWalked
	} ENUM_WalkState;			
	ENUM_WalkState m_WalkState;	//����״̬���췽ѡ�壬�췽���壬�ڷ����壬�ڷ����壩

	// ��ʾ��
	// ��һ�����λ��
	int m_PreviouPositionX;
	int m_PreviouPositionY;
	int m_CurrentPositionX;
	int m_CurrentPositionY;
	int CleanPrompt(int &i, int &j); //����ָ��λ�õ���ʾ��

	bool IsValidPosition(int i, int j);

	int Initial();
	
};

#endif //_CHINESE_CHESS_H_KL_2020_05_13__
