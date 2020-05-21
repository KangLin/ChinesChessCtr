
#ifndef _CHESS_GAME_KL_2020_05_15_
#define _CHESS_GAME_KL_2020_05_15_

#pragma once

#include <vector>
#include <string>
#include "Piece.h"
#include "chinesechess_export.h"

/**
 * ���
 * �����ֵļ��ء����桢����
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CHINESECHESS_EXPORT CChessGame
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

	time_t GetStartTime();
	int SetStartTime(time_t t);
	time_t GetEndTime();
	int SetEndTime(time_t t);

	std::string GetRedName();
	int SetRedName(const char* pszName);
	std::string GetBlackName();
	int SetBlackName(const char* pszName);

#define MAX_STRING_BUFFER 128
#define APPNAME  "Chinese chess control"
#define AUTHOR "Author: Kang Lin (kl222@126.com)"

	enum GAME_TYPE
	{
		NORMAL = 1,
		CHANGJU = 2
	};

	//�ļ�ͷ
	struct strFileHead {
		char szAppName[MAX_STRING_BUFFER];    //������,��Restart������
		char szAuthor[MAX_STRING_BUFFER];     //�������ߣ�����,��Restart������
		char dwVersion;                       //�汾,��Restart������
	};
	struct strFile {
		strFileHead head;					 
		struct tm timeStart;				 //��ʼ�����ʱ��,��Restart������
		struct tm timeEnd;					 //���������ʱ��,��Restart������
		char szRedName[MAX_STRING_BUFFER];	 //�췽�û���
		char szBlackName[MAX_STRING_BUFFER]; //�ڷ��û���
		char GameType;						 //�������
		int iBuShu;							 //��������SaveChess������
		char boardLayout;					 //���̲���(CChineseChess::ENUM_BoardLayout)
	};										 

	/**
	 * Saves the chess game
	 *
	 * @author KangLin(kl222@126.com)
	 * @date 2020/5/19
	 *
	 * @param  pFileName Filename of the file.
	 * @param  layout    ���̲���(CChineseChess::ENUM_BoardLayout)
	 *
	 * @returns An int.
	 */
	int SaveChessGame(const char* pFileName, char layout);	//�������
    int LoadChessGame(const char* pFileName, char &layout);	//װ����֣�������Ϊ����״̬

private:
	struct strCODE{
		char code[3];
	};
	typedef enum _ENUM_BianMa {
		BianMa, 
		JieMa
	} ENUM_BianMa;
	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *qz, strCODE *pCode, ENUM_BianMa bianma = BianMa);

	int m_nIndex;					  //���岽��
	bool m_bFuPang;					  //���̱�־
	std::vector<strCODE> m_ChessGame; //���

	struct tm m_tmStart;		  //��ʼʱ��
	struct tm m_tmEnd;			  //����ʱ��
	std::string m_szRedName;  //�췽��
	std::string m_szBlackName;//�ڷ���
};

#endif //_CHESS_GAME_KL_2020_05_15_