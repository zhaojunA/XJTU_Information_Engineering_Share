##################################begin####################
@echo off
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c%~s0::","","runas",1)(window.close)
title Xshell启动器
set atime=%date:~0,4%-%date:~5,2%-%date:~8,2%
 
#设置系统时间
date 2017-12-31
 
#改成你的xshell启动路径
start ""  "D:\Xftp\Xftp.exe"
 
echo 启动软件中...
ping 0.0.0.0 -n 10> null
echo 同步时间中，完成后自动关闭窗口...
 
date %atime%
exit
 