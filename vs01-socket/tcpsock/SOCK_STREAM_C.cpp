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
    char sztext[100] = { 0 };
    ::WSAStartup(w, &data);
    SOCKET s ;
    s = ::socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr, addr2;
    int n = sizeof(addr2);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
     

    std::cout << "客户端已经启动!\n";
    ::connect(s, (sockaddr*)&addr, sizeof(addr));
    ::recv(s, sztext, sizeof(sztext), 0);
    printf("%s\r\n", sztext);
    ::closesocket(s);
    ::WSACleanup();
    if (getchar())
    {
        return 0;
    }
    else {
        ::Sleep(100);
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
