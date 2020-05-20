
#include "ChessGame.h"
#include <fstream>

#if defined( _DEBUG) && defined(_MSC_VER)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

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
		 CPiece::ENUM_QiZi *qz������
		 strCODE *pCode�����ӱ���
		 ENUM_BianMa��ö�ٳ�����BianMa:����(Ĭ��ֵ)��JieMa�����룩
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-2
ʱ  �䣺7:36:32
*******************************************************************************************************/
int CChessGame::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *qz, strCODE *pCode, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		pCode->code[0] = *i;
		pCode->code[1] = *j;
		pCode->code[2] = *qz;
		break;
	case JieMa:
		*i = pCode->code[0];
		*j = pCode->code[1];
		*qz = static_cast<CPiece::ENUM_QiZi>(pCode->code[2]);
		break;
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
	strCODE code;
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
 * @param  int i����ǰ�����λ��,������[0-8]
 * @param  int j����ǰ�����λ��,������[0-9]
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

int CChessGame::SaveChessGame(const char* szFile, char layout)
{
	if (!szFile) return -1;
	strFile head;
	strcpy_s(head.head.szAppName, APPNAME);
	strcpy_s(head.head.szAuthor, AUTHOR);
	head.head.dwVersion = 1;
	head.iBuShu = m_ChessGame.size();
	head.boardLayout = layout;

	std::ofstream out(szFile);
	if (!out.is_open())
		return -2;
	out.write((char*)&head, sizeof(strFile));
	std::vector<strCODE>::iterator it;
	for (it = m_ChessGame.begin(); it != m_ChessGame.end(); it++)
	{
		out.write(it->code, sizeof(strCODE));
	}
	out.close();
	return 0;
}

int CChessGame::LoadChessGame(const char* szFile, char &layout)
{
	int nRet = 0;
	if (!szFile) return -1;

	strFile head;
	std::ifstream in(szFile);
	if (!in.is_open())
		return -2;

	in.read((char*)&head, sizeof(strFile));
	layout = head.boardLayout;
	do{
		if (strcmp(head.head.szAppName, APPNAME))
		{
			nRet = -3;
			break;
		}
		if (strcmp(head.head.szAuthor, AUTHOR))
		{
			nRet = -4;
			break;
		}

		m_ChessGame.clear();
		m_nIndex = head.iBuShu;

		while (m_nIndex--)
		{
			strCODE code;
			in.read((char*)&code, sizeof(strCODE));
			m_ChessGame.push_back(code);
		}
		m_nIndex = -1;
	} while (0);

	in.close();
	return nRet;;
}