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

	// Normalized histogram 을 구한다. 즉, hist 배열의 범위는 [0, 1].
	DibHistogram(dib, hist);

	//-------------------------------------------------------------------------
	// 초기 임계값 결정 - 그레이스케일 값의 전체 평균
	//-------------------------------------------------------------------------

	int T, Told;

	float sum = 0.f;
	for (i = 0; i < 256; i++)
		sum += (i*hist[i]);

	T = (int)sum;

	//-------------------------------------------------------------------------
	// 반복에 의한 임계값 결정
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
	int  dir[8][2] = {      // 진행 방향을 나타내는 배열
		{ 1,  0 },
	{ 1,  1 },
	{ 0,  1 },
	{ -1,  1 },
	{ -1,  0 },
	{ -1, -1 },
	{ 0, -1 },
	{ 1, -1 }
	};

	// 외곽선 좌표를 저장할 구조체
	ContourPoints cp;
	cp.num = 0;

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			if (ptr[j][i] != 0) // 객체인 경우
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
						// 진행 방향에 있는 픽셀이 객체가 아닌 경우,
						// 시계 방향으로 진행 방향을 바꾸고 다시 시도한다.

						if (++d > 7) d = 0;
						cnt++;

						// 8방향 모두 배경(background)인 경우 
						if (cnt >= 8)
						{
							cp.x[cp.num] = x;
							cp.y[cp.num] = y;
							cp.num++;

							break;  // 외곽선 추적을 끝냄.
						}
					}
					else
					{
						// 진행 방향의 픽셀이 객체일 경우, 
						// 현재 점을 외곽선 정보에 저장

						cp.x[cp.num] = x;
						cp.y[cp.num] = y;
						cp.num++;

						if (cp.num >= MAX_CONTOUR)
							break;  // 외곽선 픽셀이 너무 많으면 강제 종료

									// 진행 방향으로 이동

						x = nx;
						y = ny;

						// 방향 정보 초기화

						cnt = 0;
						dold = d;
						d = (dold + 6) % 8;	// d = dold - 2 와 같은 형태
					}

					// 시작점으로 돌아왔고, 진행 방향이 초기화된 경우
					// 외곽선 추적을 끝낸다.
					if (x == i && y == j && d == 0)
					{
						break;
					}
				}

				// for 루프를 강제로 종료하기 위해 i, j 값을 조정한다.
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
