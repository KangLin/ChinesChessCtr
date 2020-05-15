/*******************************************************************************************************
�ļ�����GoRule.h
��  �ܣ��������
˼  ·��������������Ϸ���������������·���
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-18
ʱ  �䣺9:55:40
*******************************************************************************************************/

#if !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
#define AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_

#include "EnumAndStructAndConst.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGoRule  
{
public:
	CGoRule();
	virtual ~CGoRule();
    
	static ENUM_QiZi GetQiZiSide(ENUM_QiZi qz);

	typedef enum _ENUM_ReturnValue {
		RETURNFALSE,    //���󣬲�����
		BEIJIANGJUN,    //������
		JIANGDUIMIAN,   //������
		JIANGJUN,       //����
		RETURNTRUE      //��������
	} ENUM_ReturnValue;
	ENUM_ReturnValue GoChess(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);

private:
	ENUM_ReturnValue JiangJun(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue ChessRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue BingRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue PaoRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue ShuaiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue ShiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue XiangRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue MaRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue CheRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);

	bool IsOtherSide(ENUM_QiZi me, ENUM_QiZi other);
	bool IsOtherSideMa(ENUM_QiZi me, ENUM_QiZi otherMa);

};

#endif // !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
