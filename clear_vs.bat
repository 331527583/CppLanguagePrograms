@echo off
echo ----------------------------------------------------------------
echo *                      Visual C++                              *
echo *          ����Visual Studio�����в���Ҫ���ļ�                 *
echo *          �����.bat�ļ������ڹ���Ŀ¼��                      *
echo *          ���������¸�ʽ�ļ���                                *
echo *          *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp           *
echo *          *.pdb *.bsc *.ilk *.res *.ncb *.opt *.suo           *
echo *          *.manifest *.dep *.sdf *.tlog *.log *.ipch          *
echo *          *.lastbuildstate  *.user *.suo                      *
echo ----------------------------------------------------------------
echo ���������ʼ����
pause

del /F /Q /S *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res *rc *cache
del /F /Q /S *.ncb *.opt *.suo *.manifest *.dep *.sdf *.tlog *.log *.ipch *.lastbuildstate
del /F /Q /S *.user *.suo

for /r %%a in (.) do (
set list=%%a
setlocal enabledelayedexpansion
if "!list:~-8,6!"=="-Debug" rd /q /s "!list:~0,-2!"
if "!list:~-10,8!"=="-Release" rd /q /s "!list:~0,-2!"
endlocal
)

rd /q /s "build/!bin"
rd /q /s "build/!tmp"
rd /q /s "build/debug"
rd /q /s "build/release"
rd /q /s ipch

echo �ļ�������ϣ�����
pause