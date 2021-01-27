// TCP服务器.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <Windows.h>

#pragma comment(lib,"WS2_32.lib")
int main()
{
    WSADATA data;
    WORD w = MAKEWORD(2, 0);
    char sztext[] = "欢迎使用日志处理程序\r\n";
    ::WSAStartup(w, &data);//1, 必须初始化：
    SOCKET s, s1;
    s = ::socket(AF_INET, SOCK_STREAM, 0);//2, 创建套接字句柄；
    sockaddr_in addr, addr2;
    int n = sizeof(addr2);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    ::bind(s, (sockaddr*)&addr, sizeof(addr));//3，绑定地址信息；
    ::listen(s, 5);

    std::cout << "服务器已经启动!\n";
    while(TRUE)
    {
        s1 = ::accept(s, (sockaddr*)&addr2, &n);
        if (s1 != NULL)
        {
//  error C4996 : 'inet_ntoa' : Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
                //
            printf("%s 已经连接上来\r\n", inet_ntoa(addr2.sin_addr)); 
            ::send(s1, sztext, sizeof(sztext), 0);
        }
        ::closesocket(s);
        ::closesocket(s1);
        ::WSACleanup();
        if (getchar())
        {
            return 0;
        }
        else {
            ::Sleep(100);
        }
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
