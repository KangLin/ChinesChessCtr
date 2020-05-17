#include "stdafx.h"
#include "ChessGame.h"

CChessGame::CChessGame()
{
	m_nIndex = -1;
	m_bFuPang = false;
}

CChessGame::~CChessGame()
{}

/*******************************************************************************************************
��������QiZiBianMa
��  �ܣ����ӱ����
��  ����
		 int *i�����̺�����[0-8]
		 int *j������������[0-9]
		 CPiece::ENUM_QiZi *QZ������
		 int *Code�����ӱ���
		 ENUM_BianMa��ö�ٳ�����BianMa:����(Ĭ��ֵ)��JieMa�����룩
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-2
ʱ  �䣺7:36:32
*******************************************************************************************************/
int CChessGame::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, INT32 *Code, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		*Code = *i | (*j << 4) | (*QZ << 8);
		TRACE(_T("i:%d;j:%d:qz:%X:code:%X"), *i, *j, *QZ, *Code);
		return *Code;

	case JieMa:
		*QZ = (CPiece::ENUM_QiZi) ((*Code & 0x0F00) >> 8);
		TRACE(_T("i:%d;j:%d:qz:%X:code:%X"), *i, *j, *QZ, *Code);
		*i = *Code & 0x000F;
		*j = (*Code & 0x00F0) >> 4;
		return 0;
	}
	
	return 0;
}

/**
 * ����һ��
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @param  int i����ǰ�����λ��,������[0-8]
 * @param  int j����ǰ�����λ��,������[0-9]
 * @param  qz ����
 *
 * @returns �ɹ����� 0 �����򷵻ط���
 */
int CChessGame::SaveStep(int i, int j, CPiece::ENUM_QiZi qz)
{
	int code;
	QiZiBianMa(&i, &j, &qz, &code);

	// ����������С
	if (m_nIndex + 1 < m_ChessGame.size())
	{
		m_ChessGame.resize(m_nIndex + 1);
	}

	m_ChessGame.push_back(code);//���浽�����
	m_nIndex++;

	return 0;
}

/**
 * ����һ��
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @returns �ɹ����� 0 �����򷵻ط���
 */
int CChessGame::RevokeStep()
{
	if (m_nIndex < 0)
		return -1;
	m_nIndex--;
	m_ChessGame.erase(--m_ChessGame.end());
	return 0;
}

/*******************************************************************************************************
��������GetPreviouStep
��  �ܣ��ϲ���
��  ������
����ֵ�����岽��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:19:51
*******************************************************************************************************/
int CChessGame::GetPreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz)
{
	if (m_nIndex < 0)
		return -1;

	QiZiBianMa(&i, &j, &qz, &m_ChessGame[m_nIndex], JieMa);
	m_nIndex--;
	return 0;
}

/**
 * Gets the next step
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @param [in,out] i 
 * @param [in,out] j 
 * @param [in,out] qz 
 * @returns The next step.
 */
int CChessGame::GetNextStep(int &i, int &j, CPiece::ENUM_QiZi &qz)
{
	if (m_ChessGame.size() <= m_nIndex + 1)
		return -1;

	QiZiBianMa(&i, &j, &qz, &m_ChessGame[++m_nIndex], JieMa);

	return 0;
	
}