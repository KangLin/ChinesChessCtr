/*******************************************************************************************************
�ļ�����Piece.h
��  �ܣ�������
��������Visual C++ 6.0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2020-05-15
ʱ  �䣺15:25:10
*******************************************************************************************************/

#ifndef __PIECE_H_KL_2020_05_15__
#define __PIECE_H_KL_2020_05_15__

#pragma once
#include "Common.h"
#include "chinesechess_export.h"

class CHINESECHESS_EXPORT CPiece
{
public:
	CPiece();
	virtual ~CPiece();

	/*
	�ĸ�λ��ʾ���ӣ�����1λ��ʾ��ɫ	
	*/
	typedef enum _ENUM_QiZi {
		RShuai = 1,             //��˧
		RShi = 2,               //����
		RXiang = 3,             //����
		RMa = 4,                //����
		RChe = 5,               //�쳵
		RPao = 6,               //����
		RBing = 7,              //���
		NoQiZi = 0,             //����
		BShuai = 0x8 | RShuai,  //��˧
		BShi = 0x08 | RShi,     //����
		BXiang = 0x08 | RXiang, //����
		BMa = 0x08 | RMa,       //����
		BChe = 0x08 | RChe,     //�ڳ�
		BPao = 0x08 | RPao,     //����
		BBing = 0x08 | RBing    //�ڱ�
	} ENUM_QiZi;

	//static ENUM_QiZi GetQiZiSide(ENUM_QiZi qz);
	static bool IsRedQiZi(ENUM_QiZi qz);
	static bool IsBlackQiZi(ENUM_QiZi qz);

	static bool IsExistQiZi(ENUM_QiZi qz);
	static bool IsNoQiZi(ENUM_QiZi qz);

	static bool IsSameSide(ENUM_QiZi me, ENUM_QiZi other);
	static bool IsOtherSide(ENUM_QiZi me, ENUM_QiZi other);

	static bool IsOtherSideMa(ENUM_QiZi me, ENUM_QiZi otherMa);
	static bool IsShuai(ENUM_QiZi qz);
	static bool IsShi(ENUM_QiZi qz);
};

#endif //__PIECE_H_KL_2020_05_15__