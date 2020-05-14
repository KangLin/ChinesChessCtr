#include "ChineseChess.h"

CChineseChess::CChineseChess()
{}

CChineseChess::~CChineseChess()
{}

int CChineseChess::Initial()
{
	m_PreviouPositionX = m_PreviouPositionX = -1;
	m_CurrentPositionX = m_CurrentPositionY = -1;

	//------------------------------------------------------------------------
    //��������� ===��ʼ����ʼ���=== ���ܵ�����
    //

    //��ʼ�������
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
			m_ChessBoard[i][j] = NoQiZi;

	//�������̲���,���Ϻ���
	if (m_BoardLayout & OnlyTopBlack)
	{
		m_ChessBoard[0][0] = m_ChessBoard[8][0] = BChe;
		m_ChessBoard[1][0] = m_ChessBoard[7][0] = BMa;
		m_ChessBoard[2][0] = m_ChessBoard[6][0] = BXiang;
		m_ChessBoard[3][0] = m_ChessBoard[5][0] = BShi;
		m_ChessBoard[4][0] = BShuai;
		m_ChessBoard[1][2] = m_ChessBoard[7][2] = BPao;
		m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = BBing;
	}

	if (m_BoardLayout & OnlyBottomRed)
	{
		m_ChessBoard[0][9] = m_ChessBoard[8][9] = RChe;
		m_ChessBoard[1][9] = m_ChessBoard[7][9] = RMa;
		m_ChessBoard[2][9] = m_ChessBoard[6][9] = RXiang;
		m_ChessBoard[3][9] = m_ChessBoard[5][9] = RShi;
		m_ChessBoard[4][9] = RShuai;
		m_ChessBoard[1][7] = m_ChessBoard[7][7] = RPao;
		m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = RBing;
	}

	//
	//��������� ===��ʼ����ʼ���=== ���ܵ�����
	//------------------------------------------------------------------------

}

int CChineseChess::GetBoardRown()
{
	return m_BoardRow;
}

int CChineseChess::GetBoardColumn()
{
	return m_BoardColumn;
}

/*******************************************************************************************************
��������GetQiZiSide
��  �ܣ��õ������Ǻ���,���Ǻ���
��  ����
		 ENUM_QiZi qz��Ҫר�ϵ�����
����ֵ�����غ��廹�Ǻ��������
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺12:10:36
*******************************************************************************************************/
ENUM_QiZi GetQiZiSide(ENUM_QiZi qz)
{
	if (qz > NoQiZi)
		return RQi;
	if (qz < NoQiZi)
		return BQi;
	return NoQiZi;
}

/*******************************************************************************************************
��������GoChess
��  �ܣ�����
��  ����
		 int i�����̸������[0-8]
		 int j�����̸�������[0-9]
		 bool bEnvet���Ƿ񼤻��¼���Ĭ��ΪTRUE��
����ֵ���ɹ�����true�����򷵻�false��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:17:56
*******************************************************************************************************/
bool CChineseChess::GoChess(int i, int j, bool bEnvet)
{
	return false;
}

/*******************************************************************************************************
��������IsGoChess
��  �ܣ��ж��ܷ�����
��  ����
		 int i����ǰ�����λ��,������[0-8]
		 int j����ǰ�����λ��,������[0-9]
		 ENUM_QiZi qz����ǰ����
����ֵ������������巵�� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺10:47:40
*******************************************************************************************************/
bool CChineseChess::IsGoChess(int i, int j)
{
	if (i < 0 || i > m_BoardRow - 1 || j < 0 || j > m_BoardColumn - 1)
	{   //����
		return false;
	}

	switch (m_WalkState)
	{
	case RedReadly:
		return RQi == GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
		break;
	case RedWalked:
		//��������,����ѡȡ
		if (GetQiZiSide(m_ChessBoard[i][j]) == RQi)
		{
			m_iBuShu--;//�ض�����ʱ������һλ��
			m_WalkState = RedReadly;
			return true;
		}
		//�ж��ܷ�����
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case JIANGJUN://����
			onPromptSound(JiangJun);
			return true;
		case RETURNTRUE://��������
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case BEIJIANGJUN://����
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case JIANGDUIMIAN://������
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case RETURNFALSE://�Ƿ�����
			return false;
		}

		break;
	case BlackReadly:
		return BQi == GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
	case BlackWalked:
		//��������,����ѡȡ
		if (GetQiZiSide(m_ChessBoard[i][j]) == BQi)
		{
			m_iBuShu--;//�ض�����ʱ������һλ��
			m_WalkState = BlackReadly;
			return true;
		}
		//�ж��ܷ�����
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case JIANGJUN://����
			onPromptSound(JiangJun);
			return true;
			break;
		case RETURNTRUE://��������
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case BEIJIANGJUN://����
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case JIANGDUIMIAN://������
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case RETURNFALSE://�Ƿ�����
			return false;
			break;
		}

		break;
	}

	return true;
}
