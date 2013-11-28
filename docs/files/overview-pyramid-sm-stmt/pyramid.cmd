@echo off

set PY="C:\Python26\python.exe"
if not exist %PY% goto :py_not_found

set SM="C:\Program Files (x86)\SourceMonitor\SourceMonitor.exe"
if not exist %SM% goto :bin_not_found

set SM_BATCH_FILE=%1
if "%1" equ "" goto :usage
if not exist %SM_BATCH_FILE% goto :batch_not_found

set OUTPUT_DIR=%2
if "%2" equ "" goto :usage

set STMT_FLAG=%3
if "%3" equ "" goto :analyze

if "%3" neq "--stmt" goto :usage

:analyze
set PROJECT_FILE_PATH=%TEMP%\pyramid.smproj
set PROJECT_DETAILS_CSV_FILE_PATH=%TEMP%\project-details.csv
set METHOD_METRICS_CSV_FILE_PATH=%TEMP%\method-metrics.csv

echo analyzing source code...
%SM% /C %SM_BATCH_FILE%

rd /s /q %OUTPUT_DIR% >nul 2>&1
md %OUTPUT_DIR% >nul 2>&1

echo building pyramid...
%PY% pyramid.py %PROJECT_DETAILS_CSV_FILE_PATH% %METHOD_METRICS_CSV_FILE_PATH% --xslt pyramid.xsl %STMT_FLAG% > %OUTPUT_DIR%\pyramid.xml

copy /y templates\* %OUTPUT_DIR% >nul 2>&1

echo cleaning up...
del /q %PROJECT_FILE_PATH%
del /q %PROJECT_DETAILS_CSV_FILE_PATH%
del /q %METHOD_METRICS_CSV_FILE_PATH%

rem %OUTPUT_DIR%\pyramid.xml

echo done.
goto :eof

:usage
echo Usage: %~nx0 ^<sourcemonitor-command-file^> ^<output-dir^> [--stmt]
exit /b 1

:py_not_found
echo ERROR: Python not available.
exit /b 1

:bin_not_found
echo ERROR: SourceMonitor not available.
exit /b 1

:batch_not_found
echo ERROR: batch file "%SM_BATCH_FILE%" not found.
exit /b 1

