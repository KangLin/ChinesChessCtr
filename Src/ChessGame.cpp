#include "stdafx.h"
#include "ChessGame.h"

CChessGame::CChessGame()
{
	m_iBuShu = -1;
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
int CChessGame::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		*Code = (*i + *j * 10 + *QZ * 100);
		return *Code;
		break;
	case JieMa:
		*QZ = (CPiece::ENUM_QiZi) (*Code / 100);
		TRACE(_T("CODE=%d,QZ=%d\n"), *Code, *QZ);
		int v;
		v = *Code % 100;
		*j = v / 10;
		*i = v % 10;
		return 0;
	}
	return 0;
}

int CChessGame::NextStep(int i, int j, CPiece::ENUM_QiZi qz)
{
	int code;
	QiZiBianMa(&i, &j, &qz, &code);
	m_iBuShu++;
	if (!m_bFuPang)
	{   //���浽�����
		if (m_iBuShu < m_QiJu.size())
		{
			m_QiJu[m_iBuShu] = code;
		}
		else//����
		{
			m_QiJu.push_back(code);//���浽�����
		}
	}
	return 0;
}

/*******************************************************************************************************
��������PreviouStep
��  �ܣ��ϲ���
��  ������
����ֵ�����岽��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:19:51
*******************************************************************************************************/
int CChessGame::PreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz)
{
	if (m_iBuShu < 0)
		return -1;

	QiZiBianMa(&i, &j, &qz, &m_QiJu[m_iBuShu], JieMa);
	
	return 0;
}