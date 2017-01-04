// #include "biline_interpolation.h"

int getValue(char* srcBuf, int srcWidth, int srcHeight, int nChn, int x, int y)
{
	if (srcBuf == 0 || srcWidth <= x || srcHeight <= y || nChn != 1) return -1;
	int val = srcBuf[y * srcWidth * nChn + x];
	return val;
}

bool bilineInterpolation(char* srcBuf, int srcWidth, int srcHeight, char* dstBuf, int dstWidth, int dstHeight, int nchannel)
{
	if (srcBuf == 0 || srcWidth < 1 || srcHeight < 1 || nchannel != 1)
	{
		return false;
	}
	if (dstHeight < 1 || dstWidth < 1 || dstBuf == 0)
	{
		return false;
	}

	// 计算坐标转化系数
	float betaW = srcWidth / dstWidth;
	float betaH = srcHeight / dstHeight;
	float srcX = 0;
	float srcY = 0;
	int upLftX = 0, upLftY = 0;//upLeft dot

	// valPn(xy)
	float valPn00 = 0, valPn01 = 0, valPn10 = 0, valPn11 = 0;
	for (int h = 0; h < dstHeight; h++)
	{
		for (int w = 0; w < dstWidth; w++)
		{
			srcX = w * betaW;
			srcY = h * betaH;

			upLftX = int(srcX);
			upLftY = int(srcY);

			srcX -= upLftX;
			srcY -= upLftY;
			valPn00 = getValue(srcBuf, srcWidth, srcHeight, 1, upLftX, upLftY);
			valPn01 = getValue(srcBuf, srcWidth, srcHeight, 1, upLftX, upLftY + 1);
			valPn10 = getValue(srcBuf, srcWidth, srcHeight, 1, upLftX+1, upLftY);
			valPn01 = getValue(srcBuf, srcWidth, srcHeight, 1, upLftX+1, upLftY + 1);

			float val = (1 - srcX) * (1 - srcY) * valPn00 + srcX * (1 - srcY) * valPn10
				      + (1 - srcX) * srcY * valPn11 + srcX * srcY * valPn01;

			dstBuf[h * dstWidth*nchannel + w] = int(val);
		} // for ( int w = 0 ...
	} // for (int h = 0...
	
}
