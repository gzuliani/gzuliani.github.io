@echo off

set PY="C:\Python26\python.exe"
if not exist %PY% goto :py_not_found

set CCCC="%ProgramFiles(x86)%\CCCC\cccc.exe"
if not exist %CCCC% goto :bin_not_found

set PROJECT_NAME=%~1
if "%PROJECT_NAME%" equ "" goto :usage
shift

set PROJECT_VERSION=%~1
if "%PROJECT_VERSION%" equ "" goto :usage
shift

set OUTPUT_DIR=%~1
if "%OUTPUT_DIR%" equ "" goto :usage
shift

rd /s /q "%OUTPUT_DIR%" >nul 2>&1
md "%OUTPUT_DIR%" >nul 2>&1

if "%2"=="" goto :usage

rem estimating the number of packages as the subdirs of the main source dir
set NOP=0
for /d %%a in (%2\*) do set /a NOP=NOP+1

echo scanning source files...
set FILE_LIST=%TEMP%\cccc.lst
echo. >nul 2>%FILE_LIST%

:loop
if "%1"=="" goto :cccc
dir /s /b %1 >> %FILE_LIST%
shift
goto :loop
echo %FILE_LIST%

:cccc
echo analyzing source code...
set CCCC_OUTPUT_DIR=%TEMP%\.cccc
rd /s /q %CCCC_OUTPUT_DIR% >nul 2>&1
md %CCCC_OUTPUT_DIR% >nul 2>&1

rem report_mask flags:
rem
rem p = Procedural Metrics Summary: LOC, MVG, COM, L_C, M_C
rem P = Procedural Metrics Detail: LOC, MVG, COM, L_C, M_C per method
rem o = Object Oriented Design: WMC1, WMCv, DIT,NOC, CBO
rem r = Structural Metrics Summary: Fan-out, Fan-in, IF4
rem R = Structural Metrics Detail: Clients, Suppliers
rem j = Other Extents: LOC, COM, MVG for any unparsed items

type %FILE_LIST% | %CCCC% --outdir=%CCCC_OUTPUT_DIR% --report_mask=por - >nul 2>&1
del /q %FILE_LIST% >nul 2>&1

echo building pyramid...
%PY% pyramid.py %CCCC_OUTPUT_DIR%\cccc.xml --xslt pyramid.xsl --nop %NOP% --name="%PROJECT_NAME%" --version="%PROJECT_VERSION%" > "%OUTPUT_DIR%\pyramid.xml"

copy /y ..\templates\* "%OUTPUT_DIR%" >nul 2>&1

echo cleaning up...
rd /q /s %CCCC_OUTPUT_DIR% >nul 2>&1

rem "%OUTPUT_DIR%\pyramid.xml"

echo done.
goto :eof

:usage
echo Usage: %~nx0 ^<project-name^> ^<project-version^> ^<output-dir^> ^<source-dir^>+
exit /b 1

:py_not_found
echo ERROR: Python not available.
exit /b 1

:bin_not_found
echo ERROR: CCCC not available.
exit /b 1
