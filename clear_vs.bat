@echo off
echo ----------------------------------------------------------------
echo *                      Visual C++                              *
echo *          ����Visual Studio�����в���Ҫ���ļ�                 *
echo *          �����.bat�ļ������ڹ���Ŀ¼��                      *
echo *          ִ��ǰ�ȹرմ򿪸ù��̵�Visual Studio               *
echo *          ���������¸�ʽ�ļ���                                *
echo *          *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp           *
echo *          *.pdb *.bsc *.ilk *.res *.ncb *.opt *.suo           *
echo *          *.manifest *.dep *.sdf *.tlog *.log *.ipch          *
echo *          *.lastbuildstate  *.user *.suo                      *
echo ----------------------------------------------------------------
echo ���������ʼ����
pause

del /F /Q /S *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res 
del /F /Q /S *.ncb *.opt *.suo *.manifest *.dep *.sdf *.tlog *.log *.ipch *.lastbuildstate
del /F /Q /S *.user *.suo

echo �ļ�������ϣ�����
pause