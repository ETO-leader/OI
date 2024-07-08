@echo off
:again
d.exe > io
a.exe < io > a
b.exe < io > b
fc a b > c
if errorlevel 1 echo WA
fc a b > c
if not errorlevel 1 echo AC
fc a b > c
if errorlevel 1 pause
goto again
