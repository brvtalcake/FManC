Copy-Item -Path ".\src\*" -Destination ".\include\" -Include *.h  
Copy-Item -Path ".\src\notByMe\*" -Destination ".\include\notByMe\" -Include *.h

Copy-Item -Path ".\src\*" -Destination ".\test\test_with_dll\include\" -Include *.h  
Copy-Item -Path ".\src\notByMe\*" -Destination ".\test\test_with_dll\include\notByMe\" -Include *.h  

Copy-Item -Path ".\src\*" -Destination ".\test\test_with_static\include\" -Include *.h  
Copy-Item -Path ".\src\notByMe\*" -Destination ".\test\test_with_static\include\notByMe\" -Include *.h 