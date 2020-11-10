#pragma once

#include "includelib.h"

namespace FST
{
	struct RELATION	   // ����� :������->������� ����� ��������� ��
	{
		unsigned char symbol;	// ������ ��������
		short nnode;	// ����� ������� �������
		RELATION( unsigned char � = 0x00,  // ������ ��������
			short ns = NULL);   // ����� ���������												
	};
	struct NODE // ������� ����� ���������
	{
		short n_relation;	// ���������� ������������ �����
		RELATION *relations;	// ����������� �����
		NODE();
		NODE(
			short n,	// ���������� ������������ �����
			RELATION rel, ...	// ������ �����
		);
	};
	struct FST
	{
		unsigned char* string;		//������� (������, ���������� 0x00 ) 
		short position;		//������� ������� � ������� 
		short nstates;		//���������� ��������� ��������
		NODE* nodes;		//���� ���������: [0] -��������� ���������, [nstate-1]-��������
		short* rstates;		//��������� ��������� �������� �� ������ �������
		FST( 
			const unsigned  char* s,		//������� (������, ���������� 0x00 ) 
			short ns,		//���������� ��������� �������� 
			NODE n, ...		//������ ��������� (���� ���������)
		);
		FST(
			short ns,		//���������� ��������� �������� 
			NODE n, ...		//������ ��������� (���� ���������)
		);
		FST() {}
	};
	bool execute(		// ��������� ������������� ������� 
		FST& fst		//������������������ �������� �������
	);
};
