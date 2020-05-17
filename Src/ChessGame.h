
#ifndef _CHESS_GAME_KL_2020_05_15_
#define _CHESS_GAME_KL_2020_05_15_

#pragma once

#include "Piece.h"
#include <vector>

class CChessGame
{
public:
	CChessGame();
	virtual ~CChessGame();

	int SaveStep(int i, int j, CPiece::ENUM_QiZi qz); //���浱ǰ��
	int RevokeStep();								  //���ص�ǰ��

    int GetPreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz); //�õ���һ��
	int GetNextStep(int &i, int &j, CPiece::ENUM_QiZi &qz);	   //�õ���һ��

//int ReStart();                               //���¿�ʼ
//int SaveChess(char* pFileName);          //�������
//int LoadChess(char* pFileName);          //װ����֣�������Ϊ����״̬
//int LoadChessStart(char* pFileName);     //װ����֣�������Ϊ��ʼ״̬

private:
	typedef enum _ENUM_BianMa {
		BianMa, 
		JieMa
	} ENUM_BianMa;
	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, INT32 *Code, ENUM_BianMa bianma = BianMa);

	int m_nIndex;				  //���岽��
	bool m_bFuPang;				  //���̱�־
	std::vector<int> m_ChessGame; //���

};

#endif //_CHESS_GAME_KL_2020_05_15_