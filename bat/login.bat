@ECHO OFF
CLS
::!!!!����Ŀ¼����Ϊ D:\VIRTUAL\

::virtualAgent���񷢲���ַ http://127.0.0.1:8080/virtualAgent/(��������Ҫ�ĳ�ʵ��tomcat������ַ)
set virtualsvr=http://127.0.0.1:8080/virtualAgent/VirtualAgentLogin?method=login&
echo ����ִ��ǩ��������
echo.

For /F "tokens=1* delims=:" %%i In ('Findstr /n .* D:\VIRTUAL\USERLIST.txt') Do (
  ping 127.0.0.1 -n 3 > nul  
  echo %%j
  curl --url %virtualsvr%%%j 
  echo.
) 
echo.