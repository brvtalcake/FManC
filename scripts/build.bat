@echo off
: Windows build script

setlocal
setlocal ENABLEDELAYEDEXPANSION

set job_num=%1
set target=%2

if "%job_num%" == "" (
    echo "Usage: build.bat JOB_NUM TARGET [PYTHON_EXECUTABLE]"
    echo "Example: build.bat 1 static"
    exit /b 1
)

: Search for the installed python (if python or python3)
set PYTHON=
for /f "delims=" %%i in ('where python') do set PYTHON=%%i
if "%PYTHON%" == "" (
    for /f "delims=" %%i in ('where python3') do set PYTHON=%%i
)

if "%PYTHON%" == "" (
    if "%3" == "" (
        echo "Python executable not found. Please specify it as the third argument."
        exit /b 1
    ) 
    else (
        set PYTHON=%3
    )
)

echo "Using python executable: %PYTHON%"
%PYTHON% -OO scripts/build.py %job_num% %target%

: set COG_OUT_DIR=obj/cog_processed/
: 
: set COG_FILES=
: set SRC_FILES=
: for /r src %%f in (*.c *.h *.hpp *.cpp) do (
:     set COG_FILES=!COG_FILES! %%f
:     set SRC_FILES=!SRC_FILES! %%f
: )
: 
: set COG_FILES=%COG_FILES:src/=%
: set COG_FILES=%COG_FILES:src\=%
: set TMP_COG_FILES=
: for %%f in (%COG_FILES%) do (
:     set TMP_COG_FILES=!TMP_COG_FILES! %COG_OUT_DIR%%%f
: )
: set COG_FILES=%TMP_COG_FILES%
: set COG_FILES=%COG_FILES:/=\%
: 
: echo %COG_FILES%
: 
: set COG_FILES_COUNT=0
: for %%f in (%SRC_FILES%) do (
:     echo Processing %%f
:     call :get_file_n %COG_FILES% %COG_FILES_COUNT% PROCESSED_FILE
:     echo "%%f --> !PROCESSED_FILE!""
: 
:     set /a COG_FILES_COUNT+=1
: )
: echo %COG_FILES_COUNT% files processed

: set PROCESSED_FILE=
: set COG_FILES_COUNT=0
: for /r src %%f in (*.c *.h *.hpp *.cpp) do (
:     set PROCESSED_FILE=%%f
:     echo Processing !PROCESSED_FILE!
:     set PROCESSED_FILE=%PROCESSED_FILE:src/=%
:     set PROCESSED_FILE=%PROCESSED_FILE:src\=%
:     set TMP_PROCESSED_FILE=
:     set TMP_PROCESSED_FILE=%COG_OUT_DIR%%PROCESSED_FILE%
:     set TMP_PROCESSED_FILE=%TMP_PROCESSED_FILE:/=\%
:     set PROCESSED_FILE=%TMP_PROCESSED_FILE%
:     cog -o !PROCESSED_FILE! %%f
:     set /a COG_FILES_COUNT+=1
: )
: 
: echo %COG_FILES_COUNT% files processed

: make -j %job_num% %target%

: End of file label
:EOF
exit /b 0
: for instance get_file_n("file1 file2 file3", 1, file) will set file to file2
:get_file_n
set nth_file=%~2
set counter=0
set files_list=%~1
set returned_file=
set loop=1
for %%f in (%files_list%) do (
    if !loop! == 1 (
        if !counter! == %nth_file% (
            set returned_file=%%f
            set loop=0
        )
    )
)
set %~3=%returned_file%