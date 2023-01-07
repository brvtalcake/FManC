.PHONY : static

static : 
	gcc -O3 -D STATIC -Wall -Werror -std=c11 src/*.c src/notByMe/*.c -c 
	ar -rsc lib/libFManC.a *.o
	ar -rsc test/test_with_static/lib/libFManC.a *.o
	pwsh .\include\notByMe\remove.ps1
	pwsh .\include\remove.ps1
	pwsh .\test\test_with_dll\include\remove.ps1
	pwsh .\test\test_with_dll\include\notByMe\remove.ps1
	pwsh .\test\test_with_static\include\remove.ps1
	pwsh .\test\test_with_static\include\notByMe\remove.ps1
	pwsh .\remove.ps1
	pwsh .\copyHeaders.ps1

.PHONY : dyn

dyn :
	gcc -O3 -Wall -Werror -std=c11 -c -D BUILD_DLL src/*.c src/notByMe/*.c
	gcc -O3 -Wall -Werror -std=c11 -shared *.o -o bin/FManC.dll "-Wl,--out-implib,libFManC.dll.a,--export-all-symbols"
	gcc -O3 -Wall -Werror -std=c11 -shared *.o -o test/test_with_dll/bin/FManC.dll "-Wl,--out-implib,libFManC.dll.a,--export-all-symbols"
	pwsh .\include\notByMe\remove.ps1
	pwsh .\include\remove.ps1
	pwsh .\test\test_with_dll\include\remove.ps1
	pwsh .\test\test_with_dll\include\notByMe\remove.ps1
	pwsh .\test\test_with_static\include\remove.ps1
	pwsh .\test\test_with_static\include\notByMe\remove.ps1
	pwsh .\test\test_with_dll\lib\remove.ps1
	pwsh .\lib\remove.ps1
	pwsh .\test\test_with_dll\lib\remove.ps1
	pwsh .\move_dll.a.ps1
	pwsh .\remove.ps1
	pwsh .\copyHeaders.ps1
