@echo off
::!!!!工作目录设置为 D:\VIRTUAL\
schtasks /create /tn "虚拟座席每日重签" /tr D:\VIRTUAL\autorelogin.bat /sc DAILY  /st 03:00

start %systemroot%\tasks

echo 创建成功，请检查...控制页面－管理工具－任务计划程序；核对路径和每日执行时间是否正确.