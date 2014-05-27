@echo off

if "%1"=="" goto :usage
if "%1"=="-h" goto :usage
if "%1"=="--help" goto :usage
if "%1"=="/?" goto :usage

set REPORT_DIR=%1

rd /s /q %REPORT_DIR% 2>nul
md %REPORT_DIR% 2>nul

set PYTHON=C:\Python26\python.exe
set GNUPLOT="%ProgramFiles%\gnuplot\bin\gnuplot.exe"

set HOME_DIR=%~dp0%
set UTILS_DIR=%HOME_DIR%\utils

set DB_FILE=%TEMP%\mm.db
del /q %DB_FILE%

rem build the db
%PYTHON% %UTILS_DIR%\build-db.py .. %DB_FILE%
if %ERRORLEVEL% NEQ 0 goto :error

rem run the queries
set TEMP_DIR=%TEMP%\stathg
md %TEMP_DIR%
echo TEMP_DIR=%TEMP_DIR%
%PYTHON% %UTILS_DIR%\run-queries.py %DB_FILE% %TEMP_DIR%
if %ERRORLEVEL% NEQ 0 goto :error

rem build the reports
%PYTHON% %UTILS_DIR%\merge-reports.py MM %TEMP_DIR%\commit-log.xml %TEMP_DIR%\commit-tag-cloud.xml %TEMP_DIR%\files-with-most-revisions.xml %TEMP_DIR%\repository-tags.xml --out %REPORT_DIR%\history.xml --xslt %XSLT_DIR%\history.xsl

rem prepare the graphs
set GP_SCRIPTS_DIR=..\reports\statHg\gp
set GNUPLOT_LIB=%GP_SCRIPTS_DIR:\=/%
set PNG_OUTPUT_DIR=%REPORT_DIR%\png
md %PNG_OUTPUT_DIR%

call :plot lines-of-code
call :plot activity-by-day-of-week
call :plot activity-by-hour-of-day
call :plot activity-punchcard
call :plot activity

call :plot_ex loc-and-churn author-activity
call :plot_ex file-size file-count-and-size

set LOC_AND_CHURN="datafile_churn='%TEMP_DIR%/loc-and-churn.csv'"
set LOC_AND_CHURN=%LOC_AND_CHURN%";datafile_loc='%TEMP_DIR%/lines-of-code.csv'"
call :gnuplot %LOC_AND_CHURN% loc-and-churn

rem copy css and xslt files
xcopy /s /y %HOME_DIR%\sheets\* %REPORT_DIR% >nul 2>&1

rem clean up
del /q %DB_FILE%
rd /q /s %TEMP_DIR%
goto :eof

:plot
call :_plot %1 %1
goto :eof

:plot_ex
call :_plot %1 %2
goto :eof

:_plot
call :gnuplot "datafile='%TEMP_DIR:\=/%/%1.csv'" %2
goto :eof

:gnuplot
%GNUPLOT% -e %1 %GP_SCRIPTS_DIR%\%2.gp >%PNG_OUTPUT_DIR%\%2.png
goto :eof

:usage
echo Usage: %~nx0 ^<report-folder^> 
goto :eof

:error
exit /b 1
