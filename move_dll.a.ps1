Copy-Item -Path ".\*" -Destination ".\test\test_with_dll\lib\" -Include *.a
Move-Item -Path ".\*" -Destination ".\lib\" -Include *.a