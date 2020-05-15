#include "stdafx.h"
#include "Piece.h"

CPiece::CPiece()
{}

CPiece::~CPiece()
{}

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
CPiece::ENUM_QiZi CPiece::GetQiZiSide(ENUM_QiZi qz)
{
	if (qz > NoQiZi)
		return RQi;
	if (qz < NoQiZi)
		return BQi;
	return NoQiZi;
}

bool CPiece::IsRedQiZi(ENUM_QiZi qz)
{
	if (NoQiZi == qz) return false;
	return qz > NoQiZi;
}

bool CPiece::IsBlackQiZi(ENUM_QiZi qz)
{
	if (NoQiZi == qz) return false;
	return qz < NoQiZi;
}

bool CPiece::IsExistQiZi(ENUM_QiZi qz)
{
	return NoQiZi != qz;
}

bool CPiece::IsNoQiZi(ENUM_QiZi qz)
{
	return NoQiZi == qz;
}

bool CPiece::IsSameSide(ENUM_QiZi me, ENUM_QiZi other)
{
	CPiece::ENUM_QiZi meSide = GetQiZiSide(me);
	CPiece::ENUM_QiZi otherSide = GetQiZiSide(other);
	if (NoQiZi == meSide || NoQiZi == otherSide)
		return false;
	return meSide == otherSide;
}

bool CPiece::IsOtherSide(ENUM_QiZi me, ENUM_QiZi other)
{
	CPiece::ENUM_QiZi meSide = GetQiZiSide(me);
	CPiece::ENUM_QiZi otherSide = GetQiZiSide(other);
	if (NoQiZi == meSide || NoQiZi == otherSide)
		return false;
	return meSide != otherSide;
}

bool CPiece::IsOtherSideMa(ENUM_QiZi me, ENUM_QiZi otherMa)
{
	if (IsOtherSide(me, otherMa))
		return otherMa == RMa || otherMa == BMa;
	return false;
}

bool CPiece::IsShuai(ENUM_QiZi qz)
{
	if (RShuai == qz || BShuai == qz)
		return true;
	return false;
}

bool CPiece::IsShi(ENUM_QiZi qz)
{
	if (RShi == qz || BShi == qz)
		return true;
	return false;
}
