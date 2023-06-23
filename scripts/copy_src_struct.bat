@echo off

set where_to_copy=%1

rm -rf %where_to_copy%
xcopy ".\src\" "%where_to_copy%" /T /E /Y /I /Q