/*******************************************************************************************************
�ļ�����EnumAndStructAndConst.h
��  �ܣ�����ؼ���ö�ٳ����ṹ�������Ķ���
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺13:39:08
*******************************************************************************************************/
#if !defined(ENUMANDSTRUCTANDCONST_H)
#define ENUMANDSTRUCTANDCONST_H

#pragma once

#include "common.h"

typedef enum _ENUM_QiZi{
	RShuai = 1, //��˧
	RShi = 2,   //����
	RXiang = 3, //����
	RMa = 4,    //����
	RChe = 5,   //�쳵
	RPao = 6,   //����
	RBing = 7,  //���
    NoQiZi = 0, //����
	RQi = 1,    //����
	BQi = -1,   //����
	BShuai = -1,//��˧
	BShi = -2,  //����
	BXiang = -3,//����
	BMa = -4,   //����
	BChe = -5,  //�ڳ�
	BPao = -6,  //����
	BBing = -7  //�ڱ�
} ENUM_QiZi;

typedef enum _ENUM_BianMa{BianMa, JieMa} ENUM_BianMa;

#define MAX_STRING_BUFFER 128

#endif //!defined(ENUMANDSTRUCTANDCONST_H)