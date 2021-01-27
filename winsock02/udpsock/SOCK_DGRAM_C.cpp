// UDP服务器.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib,"WS2_32.lib");



int main()
{
    WSADATA data;
    WORD w = MAKEWORD(2, 0);
    char sz_text[] = "欢迎您！";
    ::WSAStartup(w, &data);

    SOCKET s;
    s = ::socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr, addr2;
    int n = sizeof(addr2);
    char buff[10] = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
     
    printf("客户端已经启动\r\n");

    if (::sendto(s, sz_text, sizeof(sz_text), 0, (sockaddr*)&addr, n) != 0)
    {
        ::recvfrom(s, buff, 10, 0, (sockaddr*)&addr2, &n);
        printf(" 服务器说 : %s \r\n", buff);
        closesocket(s);
        WSACleanup();
    }
    if (getchar()) {
        return 0;
    }
    else {
        ::Sleep(500);
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
