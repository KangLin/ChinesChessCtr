
#ifndef _CHESS_GAME_KL_2020_05_15_
#define _CHESS_GAME_KL_2020_05_15_

#pragma once

#include "Piece.h"
#include <vector>

/**
 * ���
 * �����ֵļ��ء����桢����
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CChessGame
{
public:
	CChessGame();
	virtual ~CChessGame();

	// ������ִ洢��С
	int SaveStep(int i, int j, CPiece::ENUM_QiZi qz); //���浱ǰ��
	int RevokeStep();								  //���ص�ǰ��

	// �ƶ�ָ��λ��
    int GetPreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz); //�õ���һ��
	int GetNextStep(int &i, int &j, CPiece::ENUM_QiZi &qz);	   //�õ���һ��

#define MAX_STRING_BUFFER 128
#define APPNAME  "Chinese chess control"
#define AUTHOR "Author: Kang Lin (kl222@126.com)"

	//�ļ�ͷ
	struct strFileHead {
		char szAppName[MAX_STRING_BUFFER];    //������,��Restart������
		char szAuthor[MAX_STRING_BUFFER];     //�������ߣ�����,��Restart������
		char dwVersion;                       //�汾,��Restart������
	};
	struct strFile {
		strFileHead head;
		time_t timeStart;                      //��ʼ�����ʱ��,��Restart������
		time_t timeEnd;                        //���������ʱ��,��Restart������
		char szRedName[MAX_STRING_BUFFER];    //�췽�û���
		char szBlackName[MAX_STRING_BUFFER];  //�ڷ��û���
		int iBuShu;                            //��������SaveChess������
	};

	int SaveChessGame(char* pFileName);          //�������
    int LoadChessGame(char* pFileName);          //װ����֣�������Ϊ����״̬
//int LoadChessStart(char* pFileName);     //װ����֣�������Ϊ��ʼ״̬
	//int ReStart();                               //���¿�ʼ

private:
	struct strCODE{
		char code[3];
	};
	typedef enum _ENUM_BianMa {
		BianMa, 
		JieMa
	} ENUM_BianMa;
	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *qz, strCODE *pCode, ENUM_BianMa bianma = BianMa);

	int m_nIndex;				  //���岽��
	bool m_bFuPang;				  //���̱�־
	std::vector<strCODE> m_ChessGame; //���

};

#endif //_CHESS_GAME_KL_2020_05_15_