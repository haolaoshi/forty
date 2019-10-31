@ECHO OFF
CLS
::!!!!工作目录设置为 D:\VIRTUAL\

::virtualAgent服务发部地址 http://127.0.0.1:8080/virtualAgent/(可能是需要改成实际tomcat发布地址)
set virtualsvr=http://127.0.0.1:8080/virtualAgent/VirtualAgentLogin?method=login&
echo 正在执行签入批处理
echo.

For /F "tokens=1* delims=:" %%i In ('Findstr /n .* D:\VIRTUAL\USERLIST.txt') Do (
  ping 127.0.0.1 -n 3 > nul  
  echo %%j
  curl --url %virtualsvr%%%j 
  echo.
) 
echo.