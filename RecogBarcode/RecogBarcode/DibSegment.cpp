#include "StdAfx.h"
#include "Dib.h"
#include "DibSegment.h"
#include "DibEnhancement.h"

void DibBinarization(CDib& dib, int th)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			ptr[j][i] = (ptr[j][i] > th) ? 255 : 0;
		}
}

int DibBinarizationIterative(CDib& dib)
{
	register int i;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	float hist[256] = { 0, };

	// Normalized histogram �� ���Ѵ�. ��, hist �迭�� ������ [0, 1].
	DibHistogram(dib, hist);

	//-------------------------------------------------------------------------
	// �ʱ� �Ӱ谪 ���� - �׷��̽����� ���� ��ü ���
	//-------------------------------------------------------------------------

	int T, Told;

	float sum = 0.f;
	for (i = 0; i < 256; i++)
		sum += (i*hist[i]);

	T = (int)sum;

	//-------------------------------------------------------------------------
	// �ݺ��� ���� �Ӱ谪 ����
	//-------------------------------------------------------------------------

	float a1, b1, u1, a2, b2, u2;
	do {
		Told = T;

		a1 = b1 = 0;
		for (i = 0; i <= Told; i++)
		{
			a1 += (i*hist[i]);
			b1 += hist[i];
		}
		u1 = a1 / b1;

		a2 = b2 = 0;
		for (i = Told + 1; i < 256; i++)
		{
			a2 += (i*hist[i]);
			b2 += hist[i];
		}
		u2 = a2 / b2;

		if (b1 == 0) b1 = 1.f;
		if (b2 == 0) b2 = 1.f;

		T = (int)((u1 + u2) / 2);
	} while (T != Told);

	return T;
}

ContourPoints DibContourTracing(CDib& dib)
{
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	BYTE** ptr = dib.GetPtr();

	int x, y, nx, ny;
	int dold, d, cnt;
	int  dir[8][2] = {      // ���� ������ ��Ÿ���� �迭
		{ 1,  0 },
	{ 1,  1 },
	{ 0,  1 },
	{ -1,  1 },
	{ -1,  0 },
	{ -1, -1 },
	{ 0, -1 },
	{ 1, -1 }
	};

	// �ܰ��� ��ǥ�� ������ ����ü
	ContourPoints cp;
	cp.num = 0;

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			if (ptr[j][i] != 0) // ��ü�� ���
			{
				x = i;
				y = j;

				dold = d = cnt = 0;

				while (1)
				{
					nx = x + dir[d][0];
					ny = y + dir[d][1];

					if (nx < 0 || nx >= w || ny < 0 || ny >= h || ptr[ny][nx] == 0)
					{
						// ���� ���⿡ �ִ� �ȼ��� ��ü�� �ƴ� ���,
						// �ð� �������� ���� ������ �ٲٰ� �ٽ� �õ��Ѵ�.

						if (++d > 7) d = 0;
						cnt++;

						// 8���� ��� ���(background)�� ��� 
						if (cnt >= 8)
						{
							cp.x[cp.num] = x;
							cp.y[cp.num] = y;
							cp.num++;

							break;  // �ܰ��� ������ ����.
						}
					}
					else
					{
						// ���� ������ �ȼ��� ��ü�� ���, 
						// ���� ���� �ܰ��� ������ ����

						cp.x[cp.num] = x;
						cp.y[cp.num] = y;
						cp.num++;

						if (cp.num >= MAX_CONTOUR)
							break;  // �ܰ��� �ȼ��� �ʹ� ������ ���� ����

									// ���� �������� �̵�

						x = nx;
						y = ny;

						// ���� ���� �ʱ�ȭ

						cnt = 0;
						dold = d;
						d = (dold + 6) % 8;	// d = dold - 2 �� ���� ����
					}

					// ���������� ���ƿ԰�, ���� ������ �ʱ�ȭ�� ���
					// �ܰ��� ������ ������.
					if (x == i && y == j && d == 0)
					{
						break;
					}
				}

				// for ������ ������ �����ϱ� ���� i, j ���� �����Ѵ�.
				i = w; j = h;
			}
		}

	return cp;
}

void DibCrop(CDib& dib, int startX, int startY, int endX, int endY)
{
	CDib cpy = dib;

	register int i, j;

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

void DibSort(CDib& dib)
{
	CDib cpy = dib;
	register int i, j;

	int w = dib.GetWidth();
	int h = dib.GetHeight();

	dib.CreateGrayImage(w, h);

	BYTE** ptr1 = cpy.GetPtr();
	BYTE** ptr2 = dib.GetPtr();

	for (i = 0; i < w; i++)
	{
		int flag = 0;
		unsigned int sum = 0;
		for (j = 0; j < h; j++)
		{
			sum += ptr1[j][i];
		}
		sum /= h;
		if (sum >= 128) flag = 1;
		for (j = 0; j < h; j++)
		{
			if (flag == 1) ptr2[j][i] = 255;
			else ptr2[j][i] = 0;
		}
	}
}
