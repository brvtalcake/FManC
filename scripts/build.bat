: Windows build script

@echo off
setlocal

set job_num=%1
set target=%2

if "%job_num%" == "" (
    echo "Usage: build.bat JOB_NUM TARGET"
    echo "Example: build.bat 1 static"
    exit /b 1
)

make -j %job_num% %target%