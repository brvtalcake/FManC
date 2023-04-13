@echo off

rm -rf ./include/*
xcopy ".\src\" ".\include\" /T /E /Y /I /Q