@echo off
::!!!!����Ŀ¼����Ϊ D:\VIRTUAL\
schtasks /create /tn "������ϯÿ����ǩ" /tr D:\VIRTUAL\autorelogin.bat /sc DAILY  /st 03:00

start %systemroot%\tasks

echo �����ɹ�������...����ҳ�棭�����ߣ�����ƻ����򣻺˶�·����ÿ��ִ��ʱ���Ƿ���ȷ.