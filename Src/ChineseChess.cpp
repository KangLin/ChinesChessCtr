#ifdef _AFXEXT
#include "MFC/framework.h"
#endif
#include "ChineseChess.h"

#if defined( _DEBUG) && defined(_MSC_VER)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CChineseChess::CChineseChess()
{
	m_bPromptSound = true;
	m_bPromptMessage = true;
	SetBoardLayout(TopBlackAndBottomRed);
}

CChineseChess::~CChineseChess()
{}

int CChineseChess::Initial()
{
	m_WalkState = RedReadly;
	m_PreviouPositionX = m_PreviouPositionX = -1;
	m_CurrentPositionX = m_CurrentPositionY = -1;
	return 0;
}

int CChineseChess::SetBoardLayout(ENUM_BoardLayout layout)
{
	Initial();
	m_BoardLayout = layout;

	//��ʼ�������
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
			m_ChessBoard[i][j] = CPiece::NoQiZi;

	if (m_BoardLayout & OnlyTopBlack)
	{
		if (m_BoardLayout & SwapRedBetweenBlack)
		{
			m_ChessBoard[0][0] = m_ChessBoard[8][0] = CPiece::RChe;
			m_ChessBoard[1][0] = m_ChessBoard[7][0] = CPiece::RMa;
			m_ChessBoard[2][0] = m_ChessBoard[6][0] = CPiece::RXiang;
			m_ChessBoard[3][0] = m_ChessBoard[5][0] = CPiece::RShi;
			m_ChessBoard[4][0] = CPiece::RShuai;
			m_ChessBoard[1][2] = m_ChessBoard[7][2] = CPiece::RPao;
			m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = CPiece::RBing;
		}
		else {
			m_ChessBoard[0][0] = m_ChessBoard[8][0] = CPiece::BChe;
			m_ChessBoard[1][0] = m_ChessBoard[7][0] = CPiece::BMa;
			m_ChessBoard[2][0] = m_ChessBoard[6][0] = CPiece::BXiang;
			m_ChessBoard[3][0] = m_ChessBoard[5][0] = CPiece::BShi;
			m_ChessBoard[4][0] = CPiece::BShuai;
			m_ChessBoard[1][2] = m_ChessBoard[7][2] = CPiece::BPao;
			m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = CPiece::BBing;
		}
	}

	if (m_BoardLayout & OnlyBottomRed)
	{
		if (m_BoardLayout & SwapRedBetweenBlack)
		{
			m_ChessBoard[0][9] = m_ChessBoard[8][9] = CPiece::BChe;
			m_ChessBoard[1][9] = m_ChessBoard[7][9] = CPiece::BMa;
			m_ChessBoard[2][9] = m_ChessBoard[6][9] = CPiece::BXiang;
			m_ChessBoard[3][9] = m_ChessBoard[5][9] = CPiece::BShi;
			m_ChessBoard[4][9] = CPiece::BShuai;
			m_ChessBoard[1][7] = m_ChessBoard[7][7] = CPiece::BPao;
			m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = CPiece::BBing;
		}
		else {
			m_ChessBoard[0][9] = m_ChessBoard[8][9] = CPiece::RChe;
			m_ChessBoard[1][9] = m_ChessBoard[7][9] = CPiece::RMa;
			m_ChessBoard[2][9] = m_ChessBoard[6][9] = CPiece::RXiang;
			m_ChessBoard[3][9] = m_ChessBoard[5][9] = CPiece::RShi;
			m_ChessBoard[4][9] = CPiece::RShuai;
			m_ChessBoard[1][7] = m_ChessBoard[7][7] = CPiece::RPao;
			m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = CPiece::RBing;
		}
	}


	return 0;
}

bool CChineseChess::IsValidPosition(int i, int j)
{
	if (i < 0 || i > 9 - 1 || j < 0 || j > 10 - 1)
	{   //����
		return false;
	}
	return true;
}

int CChineseChess::EnablePromptSound(bool sound)
{
	m_bPromptSound = sound;
	return 0;
}

int CChineseChess::EnablePromptMessage(bool bMsg)
{
	m_bPromptMessage = bMsg;
	return 0;
}

/**
 * ������ʾ��������ʾ��λ�����ó���Чֵ
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @param  int i����ǰ��ʾ���λ��,������[0-8]
 * @param  int j����ǰ��ʾ���λ��,������[0-9]
 *
 * @returns An int. 0���ɹ������㣺ʧ��
 */
int CChineseChess::CleanPrompt(int &i, int &j)
{
	if (-1 == i || -1 == j)
		return 0;
	int oI = i, oJ = j;
	i = -1;
	j = -1;
	onCleanPrompt(oI, oJ);
	return 0;
}

/*******************************************************************************************************
��������GoChess
��  �ܣ�����
��  ����
		 int i�����̸������[0-8]
		 int j�����̸�������[0-9]
		 bool bNext�� TRUE�����̣�FALSE����������
		              �����ǣ��������壬�����ŷ�������С�
					          �����򲻱���
����ֵ���ɹ�����true�����򷵻�false��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:17:56
*******************************************************************************************************/
bool CChineseChess::GoChess(int i, int j, bool bNext)
{
	if (IsGoChess(i, j))
	{ //����

		if (!bNext)
		{
			onGoChess(i, j, m_ChessBoard[i][j]);	   //�¼�
			m_Game.SaveStep(i, j, m_ChessBoard[i][j]); //���浽�����
		}
		
		// ��ʾ��ʾ��
		switch (m_WalkState)
		{
		case RedReadly:
			if (m_bPromptSound) onPromptSound(Select);

			CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;

			onDrawPrompt(i, j);

			m_WalkState = RedWalked;
			break;
		case RedWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = CPiece::NoQiZi;

			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);
			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);

			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
			if (m_bPromptSound) onPromptSound(Select);

			CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;
			onDrawPrompt(i, j);

			m_WalkState = BlackWalked;
			break;
		case BlackWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = CPiece::NoQiZi;

			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);
			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);

			m_WalkState = RedReadly;
			break;
		}
		return true;
	}
	else //������
	{
		if (m_bPromptSound) onPromptSound();
		return false;
	}
}

/*******************************************************************************************************
��������IsGoChess
��  �ܣ��ж��ܷ�����
��  ����
		 int i����ǰ�����λ��,������[0-8]
		 int j����ǰ�����λ��,������[0-9]
		 CPiece::ENUM_QiZi qz����ǰ����
����ֵ������������巵�� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺10:47:40
*******************************************************************************************************/
bool CChineseChess::IsGoChess(int i, int j)
{
	if(!IsValidPosition(i, j))
	{   //����
		return false;
	}

	switch (m_WalkState)
	{
	case RedReadly:
		return CPiece::IsRedQiZi(m_ChessBoard[i][j]) ? true : false;
	case RedWalked:
		//��������,����ѡȡ
		if (CPiece::IsRedQiZi(m_ChessBoard[i][j]))
		{
			m_Game.RevokeStep();
			m_WalkState = RedReadly;
			return true;
		}
		//�ж��ܷ�����
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://����
			if(m_bPromptSound) onPromptSound(JiangJun);
			return true;
		case CGoRule::RETURNTRUE://��������
			if (m_bPromptSound)
			{
				m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			}
			return true;
		case CGoRule::BEIJIANGJUN://����
			if(m_bPromptMessage) onPromptMessage(CGoRule::BEIJIANGJUN);
			return false;
		case CGoRule::JIANGDUIMIAN://������
			if (m_bPromptMessage) onPromptMessage(CGoRule::JIANGDUIMIAN);
			return false;
		case CGoRule::RETURNFALSE://�Ƿ�����
		default:
			return false;
		}

		break;
	case BlackReadly:
		return CPiece::IsBlackQiZi(m_ChessBoard[i][j]) ? true : false;
	case BlackWalked:
		//��������,����ѡȡ
		if (CPiece::IsBlackQiZi(m_ChessBoard[i][j]))
		{
			m_Game.RevokeStep();
			m_WalkState = BlackReadly;
			return true;
		}
		//�ж��ܷ�����
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://����
			if (m_bPromptSound) onPromptSound(JiangJun);
			return true;
		case CGoRule::RETURNTRUE://��������
			if (m_bPromptSound)
			{
				m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			}
			return true;
		case CGoRule::BEIJIANGJUN://����
			if (m_bPromptMessage) onPromptMessage(CGoRule::BEIJIANGJUN);
			return false;
		case CGoRule::JIANGDUIMIAN://������
			if (m_bPromptMessage) onPromptMessage(CGoRule::JIANGDUIMIAN);
			return false;
		case CGoRule::RETURNFALSE://�Ƿ�����
		default:
			return false;
		}

		break;
	}

	return false;
}

/*******************************************************************************************************
��������NextStep
��  �ܣ��²���
��  ������
����ֵ�����岽��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:19:33
*******************************************************************************************************/
int CChineseChess::NextStep()
{
	int i, j;
	CPiece::ENUM_QiZi qz;
	if (m_Game.GetNextStep(i, j, qz))
	{
		if (m_bPromptSound) onPromptSound();
		return -1;
	}
	
	if (GoChess(i, j, true))
		return 0;

	return -2;
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
int CChineseChess::PreviouStep()
{
	int i, j;
	CPiece::ENUM_QiZi qz;

	switch (m_WalkState)
	{
	case RedWalked:
	case BlackWalked:
		CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
		CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);
		if (m_Game.GetPreviouStep(i, j, qz))
		{
			if (m_bPromptSound) onPromptSound();
		}
	case RedReadly:
	case BlackReadly:
		CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
		CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

		if (m_Game.GetPreviouStep(i, j, qz))
		{
			if (m_bPromptSound) onPromptSound();
			return -1;
		}
		m_ChessBoard[i][j] = qz;
		m_CurrentPositionX = i;
		m_CurrentPositionY = j;
		CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

		if (m_Game.GetPreviouStep(i, j, qz))
		{
			if (m_bPromptSound) onPromptSound();
			return -1;
		}
		m_ChessBoard[i][j] = qz;
		m_PreviouPositionX = i;
		m_PreviouPositionY = j;

		if (IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);

		switch (m_WalkState)
		{
		case RedReadly:
		case RedWalked:
			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
		case BlackWalked:
			m_WalkState = RedReadly;
		}
		break;
	}

	return 0;
}

int CChineseChess::SaveChessGame(const char* pszFile)
{
	return m_Game.SaveChessGame(pszFile, m_BoardLayout);
}

int CChineseChess::LoadChessGame(const char* pszFile)
{
	int nRet = 0;
	char layout;
	nRet = m_Game.LoadChessGame(pszFile, layout);
	if (nRet) return nRet;
	
	SetBoardLayout((ENUM_BoardLayout)layout);

	return nRet;
}