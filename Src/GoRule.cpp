/*******************************************************************************************************
�ļ�����GoRule.cpp
��  �ܣ��������
˼  ·��������������Ϸ���������������·���
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺21:38:52
*******************************************************************************************************/

#include "stdafx.h"
#include "GoRule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGoRule::CGoRule()
{}

CGoRule::~CGoRule()
{}

/*******************************************************************************************************
��������GoChess
��  �ܣ��ж��ܷ�ӵ㣨ifrom, jfrom�����㣨ito, jto������
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ�������桢JIANGDUIMIAN,�н���BEIJIANGJUN,������JIANGJUN,
        �������塢RETURNTRUE���������塢RETURNFALSE,    
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:34:32
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::GoChess(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	ENUM_ReturnValue m_RV;
	CPiece::ENUM_QiZi goneChessBoard[9][10];

	m_RV = ChessRule(ito, jto, ifrom, jfrom, ChessBoard);
	if(m_RV == RETURNTRUE)
	{
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 10; j++)
				goneChessBoard[i][j] = ChessBoard[i][j];
		//��������
		goneChessBoard[ito][jto] = goneChessBoard[ifrom][jfrom];
		goneChessBoard[ifrom][jfrom] = CPiece::NoQiZi;
		//�жϽ����桢�н�������
		m_RV = JiangJun(ito, jto, goneChessBoard);
	}

	return m_RV;
}

/*******************************************************************************************************
��������ChessRule
��  �ܣ��ֱ��жϸ������߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:53:57
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ChessRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	switch(ChessBoard[ifrom][jfrom])
	{
	case CPiece::BChe:
	case CPiece::RChe:
		return CheRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BMa:
	case CPiece::RMa:
		return MaRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BXiang:
	case CPiece::RXiang:
		return XiangRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BShi:
	case CPiece::RShi:
		return ShiRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BShuai:
	case CPiece::RShuai:
		return ShuaiRule(ito, jto, ifrom, jfrom, ChessBoard);
	case CPiece::BPao:
	case CPiece::RPao:
		return PaoRule(ito, jto, ifrom, jfrom, ChessBoard);
	case CPiece::BBing:
	case CPiece::RBing:
		return BingRule(ito, jto, ifrom, jfrom, ChessBoard);
	default:
		return RETURNFALSE;
	}
	return RETURNTRUE;
}

/*******************************************************************************************************
��������CheRule
��  �ܣ������߷�
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:30:51
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::CheRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if(ito == ifrom)
	{
		while(jfrom != jto)
		{
			jfrom += sig(jto - jfrom);
			if(CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (jfrom != jto))
				return RETURNFALSE;			
		}
		return RETURNTRUE;
	}
	if(jto == jfrom)
	{
		while(ifrom != ito)
		{
			ifrom += sig(ito - ifrom);
			if(CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (ifrom != ito))
				return RETURNFALSE;
		}
		return RETURNTRUE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������MaRule
��  �ܣ�����߷�
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:36:05
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::MaRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if(abs(ito - ifrom) == 1 && abs(jto - jfrom) == 2)
	{
		if(CPiece::IsNoQiZi(ChessBoard[ifrom][jfrom + sig(jto - jfrom)]))
			return RETURNTRUE;
		else
			return RETURNFALSE;	
	}
	if(abs(ito - ifrom) == 2 && abs(jto - jfrom) == 1)
	{
		if(CPiece::IsNoQiZi(ChessBoard[ifrom + sig(ito - ifrom)][jfrom]))
			return RETURNTRUE;
		else
			return RETURNFALSE;	
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������XiangRule
��  �ܣ�����߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺22:49:54
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::XiangRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if(abs(ito - ifrom) == 2 
		&& abs(jfrom - jto) == 2 
		&& CPiece::IsNoQiZi(ChessBoard[ifrom + sig(ito - ifrom)][jfrom + sig(jto - jfrom)]))
	{
		if(jfrom <= 4 && jto <=4)
			return RETURNTRUE;
		if(jfrom >=5 && jto >=5)
			return RETURNTRUE;
	}
	
	return RETURNFALSE;
}

/*******************************************************************************************************
��������ShiRule
��  �ܣ�ʿ���߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:07:29
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ShiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (abs(ifrom - ito) == 1
		&& abs(jfrom - jto) == 1
		&& ito >= 3 && ito <= 5)
	{
		if (jfrom >= 0 && jfrom <= 2 && jto >= 0 && jto <= 2)
			return RETURNTRUE;
		if (jfrom >= 7 && jfrom <= 9 && jto >= 7 && jto <= 9)
			return RETURNTRUE;
	}

	return RETURNFALSE;
}

/*******************************************************************************************************
��������ShuaiRule
��  �ܣ������߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:15:40
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ShuaiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (ito >= 3 && ito <= 5
		&& ((abs(ito - ifrom) == 1 && jto == jfrom)
			|| (abs(jto - jfrom) == 1 && ito == ifrom)))
	{
		if (/*jfrom >= 0 &&*/ jfrom <= 2 && /*jto >= 0 &&*/ jto <= 2)
			return RETURNTRUE;
		if (jfrom >= 7 /*&& jfrom <= 9 */&& jto >= 7/* && jto <= 9*/)
			return RETURNTRUE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������PaoRule
��  �ܣ��ڵ��߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:24:18
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::PaoRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if(ito == ifrom)
	{
		int iNum = 0;
		while(jfrom != jto)
		{
			jfrom += sig(jto - jfrom);
			if(CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (jfrom != jto))
				iNum++;
		}
		switch(iNum)
		{
		case 0:
			if(CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNTRUE;
		    else
				return RETURNFALSE;
			break;
		case 1:
			if(CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNFALSE;
		    else
				return RETURNTRUE;
			break;
		default:
			return RETURNFALSE;
		}
	}
	if(jto == jfrom)
	{
		int iNum = 0;
		while(ifrom != ito)
		{
			ifrom += sig(ito - ifrom);
			if(CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (ifrom != ito))
				iNum++;
			
		}
		switch(iNum)
		{
		case 0:
			if(CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNTRUE;
		    else
				return RETURNFALSE;
			break;
		case 1:
			if(CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNFALSE;
		    else
				return RETURNTRUE;
			break;
		default:
			return RETURNFALSE;
		}
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������BingRule
��  �ܣ������߷�
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ��������߷��� RETURNTRUE�����򷵻� RETURNFALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-1
ʱ  �䣺23:38:32
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::BingRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	bool bTopSide = false;
	bool bExit = false;
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (ChessBoard[i][j])
			{
			case CPiece::RShuai:
			case CPiece::RShi:
			case CPiece::BShuai:
			case CPiece::BShi:
				bTopSide = CPiece::IsSameSide(ChessBoard[i][j], ChessBoard[ifrom][jfrom]);
				bExit = true;
				break;
			default:
				break;
			}
		}
		if (bExit)
			break;
	}
	if (bTopSide)
	{
		if (jto - jfrom == 1 && ito == ifrom)
			return RETURNTRUE;
		if (jfrom > 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
			return RETURNTRUE;
	} else {
		if(jto - jfrom == -1 && ito == ifrom)		
			return RETURNTRUE;
		if(jfrom <= 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
			return RETURNTRUE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
��������JiangJun
��  �ܣ��жϽ����桢�н�������
��  ����
         int ito��Ŀ��������[0-8]
         int jto��Ŀ���������[0-9]
         int ifrom��Դ�������[0-8]
         int jfrom��Դ��������[0-9]
         CPiece::ENUM_QiZi ChessBoard[9][10]����������
����ֵ������ JIANGDUIMIAN��BEIJIANGJUN��JIANGJUN, RETURNTRUE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-2
ʱ  �䣺9:02:54
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::JiangJun(int ito, int jto, CPiece::ENUM_QiZi ChessBoard[][10])
{
	int iTopShuai = 0, jTopShuai = 0;
	int iBottomShuai = 0, jBottomShuai = 0;
	bool bExit = false;
	//�ҵ��µ�˧��λ��
	for(iBottomShuai = 3; iBottomShuai < 6; iBottomShuai++)
	{
		for (jBottomShuai = 7; jBottomShuai < 10; jBottomShuai++)
		{
			if (CPiece::IsShuai(ChessBoard[iBottomShuai][jBottomShuai]))
			{
				bExit = true;
				break;
			}
		}
		if (bExit) break;
	}
	bExit = false;
	//�������˧��λ��
	for(iTopShuai = 3; iTopShuai < 6; iTopShuai++)
	{
		for(jTopShuai = 0; jTopShuai < 3; jTopShuai++)
		{
			if (CPiece::IsShuai(ChessBoard[iTopShuai][jTopShuai]))
			{
				bExit = true;
				break;
			}
		}
		if (bExit) break;
	}
	TRACE("Top shuai:%d-%d;Bootom shuai:%d-%d\n", iTopShuai, jTopShuai, iBottomShuai, jBottomShuai);
	if (!CPiece::IsShuai(ChessBoard[iTopShuai][jTopShuai])
		|| !CPiece::IsShuai(ChessBoard[iBottomShuai][jBottomShuai]))
		return JIANGBEICHI;

	//�жϽ�����
	int i = 0, j = 0;
	if(iBottomShuai == iTopShuai)
	{
		j = jTopShuai;
		while(j != jBottomShuai)
		{
			j++;
			//�ж��м��Ƿ�����
			if(CPiece::IsExistQiZi(ChessBoard[iTopShuai][j]) && j != jBottomShuai)
			{
				i++;
				break;
			}
		}
		if(i == 0)
			return JIANGDUIMIAN;
	}

	//�жϱ��������жϽ���
	// ��ǰ������������һ�ߵ�
	if (CPiece::IsSameSide(ChessBoard[ito][jto], ChessBoard[iTopShuai][jTopShuai]))
	{
		//����
		i = iTopShuai;
		for (j = 0; j < 10; j++)
			if (CPiece::IsOtherSide(ChessBoard[iTopShuai][jTopShuai], ChessBoard[i][j]))
				if (ChessRule(iTopShuai, jTopShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;

		j = jTopShuai;
		for (i = 0; i < 9; i++)
			if (CPiece::IsOtherSide(ChessBoard[iTopShuai][jTopShuai], ChessBoard[i][j]))
				if (ChessRule(iTopShuai, jTopShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;

		//����
		i = iTopShuai - 1;
		j = jTopShuai - 2;
		if (j >= 0 && MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iTopShuai - 1;
		j = jTopShuai + 2;
		if (MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iTopShuai + 1;
		j = jTopShuai - 2;
		if (j >= 0 && MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iTopShuai + 1;
		j = jTopShuai + 2;
		if (MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iTopShuai - 2;
		j = jTopShuai - 1;
		if (j >= 0 && MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iTopShuai - 2;
		j = jTopShuai + 1;
		if (MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iTopShuai + 2;
		j = jTopShuai - 1;
		if (j >= 0 && MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iTopShuai + 2;
		j = jTopShuai + 1;
		if (MaJiangJun(iTopShuai, jTopShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		//����
		if (ChessRule(iBottomShuai, jBottomShuai, ito, jto, ChessBoard) == RETURNTRUE)
			return  JIANGJUN;
	}

	//��ǰ������������һ�ߵ�
	if (CPiece::IsSameSide(ChessBoard[ito][jto], ChessBoard[iBottomShuai][jBottomShuai]))
	{
		//������
		i = iBottomShuai;
		for (j = 0; j < 10; j++)
			if (CPiece::IsOtherSide(ChessBoard[iBottomShuai][jBottomShuai], ChessBoard[i][j]))
				if (ChessRule(iBottomShuai, jBottomShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		j = jBottomShuai;
		for (i = 0; i < 9; i++)
			if (CPiece::IsOtherSide(ChessBoard[iBottomShuai][jBottomShuai], ChessBoard[i][j]))
				if (ChessRule(iBottomShuai, jBottomShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		//��
		i = iBottomShuai - 1;
		j = jBottomShuai - 2;
		if (MaJiangJun(iBottomShuai, jBottomShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iBottomShuai - 1;
		j = jBottomShuai + 2;
		if (j < 10 && MaJiangJun(iBottomShuai, jBottomShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iBottomShuai + 1;
		j = jBottomShuai - 2;
		if (MaJiangJun(iBottomShuai, jBottomShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iBottomShuai + 1;
		j = jBottomShuai + 2;
		if (j < 10 && MaJiangJun(iBottomShuai, jBottomShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iBottomShuai - 2;
		j = jBottomShuai - 1;
		if (MaJiangJun(iBottomShuai, jBottomShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iBottomShuai - 2;
		j = jBottomShuai + 1;
		if (j < 10 && MaJiangJun(iBottomShuai, jBottomShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iBottomShuai + 2;
		j = jBottomShuai - 1;
		if (MaJiangJun(iBottomShuai, jBottomShuai, i, j, ChessBoard))
			return  BEIJIANGJUN;

		i = iBottomShuai + 2;
		j = jBottomShuai + 1;

		//����
		if (j < 10 && MaJiangJun(iTopShuai, jTopShuai, ito, jto, ChessBoard))
			return  BEIJIANGJUN;
	}
	
	return RETURNTRUE;
}

bool CGoRule::MaJiangJun(int iShuai, int jShuai, int iMa, int jMa, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if(CPiece::IsOtherSideMa(ChessBoard[iShuai][jShuai], ChessBoard[iMa][jMa]))
		if (ChessRule(iShuai, jShuai, iMa, jMa, ChessBoard) == RETURNTRUE)
			return  true;
	return false;
}