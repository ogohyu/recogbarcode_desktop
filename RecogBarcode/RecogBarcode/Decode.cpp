#include "stdafx.h"
#include "Decode.h"

//�����ȭ�� ���ڵ� ��ġ�� �°� ũ��
void CropHyundaiDP(CDib& dib)
{
	CDib cpy = dib;

	register int i, j;

	int startX = 1633;
	int startY = 414;
	int endX = 2236;
	int endY = 496;

	int nw = endX - startX;
	int nh = endY - startY;

	dib.CreateGrayImage(nw, nh);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			ptr2[j][i] = ptr1[j + startY][i + startX];
		}
}

//�����ȭ�� ���ڵ� ���(ITF)�� �°� ���ڵ�
CString DCHyundaiDP(CDib& dib)
{
	int ITFTable[10] = { 11221, 21112, 12112, 22111, 11212, 21211, 12211, 11122, 21121, 12121 };
	register int i, j;

	int w = dib.GetWidth();
	BYTE** ptr = dib.GetPtr();

	BOOL snrBin = 0, snrBinTemp = 0; //���� ���̳ʸ� ��, ���� ���̳ʸ� ��

	int snrNum[87]; //ó�� Bar���� �� Bar���� ī������ ���� 87 (���鵵 �� ��, ���̴� �� ��)
	int snrCnt = 0; //������ SNR�� ����

	//�ٿ� ���� ������ ������� �ȼ� ���� ��
	for (i = 0; i < w; i++)
	{
		snrBinTemp = snrBin;
		if (ptr[20][i] == 255) snrBin = 0; //�ȼ� ���� ����̸� 0
		else snrBin = 1;


		if (snrBin == 1) //�ȼ� ���� �������̸�
		{
			if (snrBinTemp == 1) snrNum[snrCnt - 1]++;
			else snrNum[snrCnt++] = 1;
		}
		else
		{
			if (snrCnt == 0 || snrCnt == 87) continue; //�� �� ����� �� �� ���� ���� ����
			if (snrBinTemp == 0) snrNum[snrCnt - 1]++;
			else snrNum[snrCnt++] = 1;
		}
	}

	//�ȼ� ������ ���� �ٿ� ������ ���� ĭ���� ���� ĭ���� ��
	for (i = 0; i < snrCnt; i++)
	{
		if (i % 2 == 0) //��
		{
			if (snrNum[i] > 6) snrNum[i] = 2;
			else snrNum[i] = 1;
		}
		else //����
		{
			if (snrNum[i] > 7) snrNum[i] = 2;
			else snrNum[i] = 1;
		}
	}

	
	CString strSNR = _T("");
	for (i = 4; i < snrCnt - 3;) //start�� end�� ���� Bar�� Blank�� ���̸� ����Ͽ� ���ڵ� ���̺�� �� �� ���ںο�
	{
		int Bar = (snrNum[i] * 10000) + (snrNum[i + 2] * 1000) + (snrNum[i + 4] * 100) + (snrNum[i + 6] * 10) + snrNum[i + 8];
		int Blank = (snrNum[i + 1] * 10000) + (snrNum[i + 3] * 1000) + (snrNum[i + 5] * 100) + (snrNum[i + 7] * 10) + snrNum[i + 9];

		
		for (j = 0; j < 10; j++)
		{
			if (ITFTable[j] == Bar) Bar = j;
			if (ITFTable[j] == Blank) Blank = j;
		}

		i += 10;

		CString strTemp;
		strTemp.Format(_T("%d"), Bar);
		strSNR += strTemp;
		strTemp.Format(_T("%d"), Blank);
		strSNR += strTemp;
	}

	strSNR = strSNR.Left(15);
	return strSNR;
}

//���̺��� ���ڵ� ��ġ�� �°� ũ��
void CropSavezone(CDib& dib)
{
	CDib cpy = dib;

	register int i, j;

	int startX = 1241;
	int startY = 431;
	int endX = 2074;
	int endY = 483;

	int nw = endX - startX;
	int nh = endY - startY;

	dib.CreateGrayImage(nw, nh);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			ptr2[j][i] = ptr1[j + startY][i + startX];
		}
}

//���̺��� ���ڵ� ���(ITF)�� �°� ���ڵ�
CString DCSavezone(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	BYTE** ptr = dib.GetPtr();

	BOOL snrBin = 0, snrBinTemp = 0; //���� ���̳ʸ� ��, ���� ���̳ʸ� ��

	int snrNum[139]; //ó�� Bar���� �� Bar���� ī������ ���� 87 (���鵵 �� ��, ���̴� �� ��)
	int snrCnt = 0; //������ SNR�� ����

	//�ٿ� ���� ������ ������� �ȼ� ���� ��
	for (i = 0; i < w; i++)
	{
		snrBinTemp = snrBin;
		if (ptr[20][i] == 255) snrBin = 0; //�ȼ� ���� ����̸� 0
		else snrBin = 1;


		if (snrBin == 1) //�ȼ� ���� �������̸�
		{
			if (snrBinTemp == 1) snrNum[snrCnt - 1]++;
			else snrNum[snrCnt++] = 1;
		}
		else
		{
			if (snrCnt == 0 || snrCnt == 139) continue; //�� �� ����� �� �� ���� ���� ����
			if (snrBinTemp == 0) snrNum[snrCnt - 1]++;
			else snrNum[snrCnt++] = 1;
		}
	}
	
	//�ȼ� ������ ���� �ٿ� ������ ���� ĭ���� ���� ĭ���� ��
	for (i = 0; i < snrCnt; i++)
	{
		if (i % 2 == 0) //��
		{
			if (snrNum[i] > 7) snrNum[i] = 2;
			else snrNum[i] = 1;
		}
		else //����
		{
			if (snrNum[i] > 9) snrNum[i] = 2;
			else snrNum[i] = 1;
		}
	}
	
	CString strSNR = _T("");
	for (i = 10; i < snrCnt - 9;) //start�� end�� ���� SNR�� ���̸� ����Ͽ� ���ڵ� ���̺�� �� �� ���ںο�
	{
		unsigned int SNR = (snrNum[i] * 100000000) + (snrNum[i + 1] * 10000000) + (snrNum[i + 2] * 1000000) + (snrNum[i + 3] * 100000) + (snrNum[i + 4] * 10000) + (snrNum[i + 5] * 1000) + (snrNum[i + 6] * 100) + (snrNum[i + 7] * 10) + snrNum[i + 8];

		int Code39Table[10] = { 111221211, 211211112, 112211112, 212211111, 111221112, 211221111, 112221111, 111211212, 211211211, 112211211 };

		for (j = 0; j < 10; j++)
		{
			if (Code39Table[j] == SNR) SNR = j;
		}

		i += 10;

		CString strTemp;
		strTemp.Format(_T("%d"), SNR);
		strSNR += strTemp;
	}
	return strSNR;
}