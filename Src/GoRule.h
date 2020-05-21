/*******************************************************************************************************
�ļ�����GoRule.h
��  �ܣ��������
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-18
ʱ  �䣺9:55:40
*******************************************************************************************************/

#if !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
#define AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Piece.h"

class CHINESECHESS_EXPORT CGoRule
{
public:
	CGoRule();
	virtual ~CGoRule();
    
	typedef enum _ENUM_ReturnValue {
		RETURNFALSE,    //���󣬲�����
		BEIJIANGJUN,    //������
		JIANGDUIMIAN,   //������
		JIANGJUN,       //����
		JIANGBEICHI,    //���ѱ���
		RETURNTRUE      //��������
	} ENUM_ReturnValue;
	ENUM_ReturnValue GoChess(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);

private:
	ENUM_ReturnValue ChessRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]); 

	// ������
	ENUM_ReturnValue BingRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// �ڹ���
	ENUM_ReturnValue PaoRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// ˧����
	ENUM_ReturnValue ShuaiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// �˹���
	ENUM_ReturnValue ShiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// �����
	ENUM_ReturnValue XiangRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// �����
	ENUM_ReturnValue MaRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// ������
	ENUM_ReturnValue CheRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);

	// ����
	ENUM_ReturnValue JiangJun(int ito, int jto, CPiece::ENUM_QiZi ChessBoard[][10]);

	// ����
	bool MaJiangJun(int iShuai, int jShuai, int iMa, int jMa, CPiece::ENUM_QiZi ChessBoard[][10]);
};

#endif // !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
