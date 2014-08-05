#include "StdAfx.h"
#include "SSEHelper.h"

int CSSEHelper::m_nSupportSSE = -1;

int g_imageloadtime = 0;
int g_imageloadcount = 0;
extern "C" void ssememcpy(void* pDest, void* pSrc, int nSize)
{
	CSSEHelper::MemCopy(pDest, pSrc, nSize);
}

BOOL CSSEHelper::IsSupportSSE()
{
	if(m_nSupportSSE == -1)
	{
		__try 
		{
			__asm 
			{
				xorpd xmm0, xmm0        // executing SSE instruction
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) 
		{
			if (_exception_code() == STATUS_ILLEGAL_INSTRUCTION) 
			{
				m_nSupportSSE = 0;
			}
			m_nSupportSSE = 0;
		}
		if(m_nSupportSSE == -1)
		{
			m_nSupportSSE = 1;
		}
	}
	return m_nSupportSSE == 1;
}

void CSSEHelper::MemCopy(LPVOID pDest, LPVOID pSrc, int nSize)
{
	int iStartTick = ::GetTickCount();
	if(IsSupportSSE())
	{
		MemCopySSE(pDest, pSrc, nSize);
	}
	else
	{
		memcpy(pDest, pSrc, nSize);
	}

	g_imageloadtime += ::GetTickCount() - iStartTick;
	g_imageloadcount += nSize;
}

void CSSEHelper::MemCopySSE(LPVOID pDest, LPVOID pSrc, int nSize)
{
	int nSSESize = nSize >> 4;
	int nTemp = nSSESize << 4;
	nSize -= nTemp;
	if(nSSESize)
	{
		__asm
		{
			push ecx
				push edx
				push eax
				mov	eax, [pSrc]
			mov edx, [pDest]
			mov ecx, [nSSESize]		
memcpy_process:
			movups xmm0, [eax]
			add eax, 10h
				movups [edx], xmm0
				add edx, 10h
				dec ecx
				jnz memcpy_process
				pop eax
				pop edx
				pop ecx
				emms
		}
	}
	if(nSize)
	{
		memcpy((BYTE *)pDest + nTemp, (BYTE *)pSrc + nTemp, nSize);
	}
}