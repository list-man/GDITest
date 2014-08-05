#pragma once

class CSSEHelper
{
public:
	static BOOL IsSupportSSE();
	static void MemCopy(LPVOID pDest, LPVOID pSrc, int nSize);

private:
	static void MemCopySSE(LPVOID pDest, LPVOID pSrc, int nSize);
	static int m_nSupportSSE;
};
