#include <windows.h>
#include <stdio.h>
#include "afxmt.h" 


static int a1 = 0;
CCriticalSection m_Sec;

DWORD WINAPI myfun1(
	LPVOID	lpParameter
	);
DWORD WINAPI myfun2(
	LPVOID lpParameter
	);

CRITICAL_SECTION section;
 

int main()
{
	HANDLE h1,h2;
	h1 = ::CreateThread(NULL,0,myfun1,NULL,0,NULL);
	printf("线程1开始运行!\r\n");
	h2 = ::CreateThread(NULL,0,myfun2,NULL,0,NULL);
	printf("线程2开始运行！\r\n");
	 
	::CloseHandle(h1);
	::CloseHandle(h2);
		InitializeCriticalSection(&section);
		::Sleep(10000);
		printf("Quit When Press q\r\n");

	if(getchar() == 'q'){
		DeleteCriticalSection(&section);
		 
	}else
		return 0;
}

DWORD WINAPI myfun1(LPVOID lpParameter)
{
	while(1){
		EnterCriticalSection(&section);
		m_Sec.Lock();

		a1++;
		if(a1<100){
			::Sleep(1000); 
			printf("线程1正在运行 %d\r\n",a1);
			LeaveCriticalSection(&section);
			m_Sec.Unlock();
		}else{
			LeaveCriticalSection(&section);
			m_Sec.Unlock();
			break;
		}
	}
	return 0;
}

DWORD WINAPI myfun2(LPVOID lpParameter)
{
	while(1){
		EnterCriticalSection(&section);
		a1++;
		if(a1<100){
			::Sleep(1000);
			printf("线程2正在运行 %d\r\n",a1);
			LeaveCriticalSection(&section);
		}else{
			LeaveCriticalSection(&section);
			break;
		}
	}
	return 0;
}