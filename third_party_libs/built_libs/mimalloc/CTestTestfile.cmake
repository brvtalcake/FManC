# CMake generated Testfile for 
# Source directory: /home/axel/Documents/programmation/c/FManC/third_party_libs/mimalloc
# Build directory: /home/axel/Documents/programmation/c/FManC/third_party_libs/built_libs/mimalloc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test-api "/home/axel/Documents/programmation/c/FManC/third_party_libs/built_libs/mimalloc/mimalloc-test-api")
set_tests_properties(test-api PROPERTIES  _BACKTRACE_TRIPLES "/home/axel/Documents/programmation/c/FManC/third_party_libs/mimalloc/CMakeLists.txt;506;add_test;/home/axel/Documents/programmation/c/FManC/third_party_libs/mimalloc/CMakeLists.txt;0;")
add_test(test-api-fill "/home/axel/Documents/programmation/c/FManC/third_party_libs/built_libs/mimalloc/mimalloc-test-api-fill")
set_tests_properties(test-api-fill PROPERTIES  _BACKTRACE_TRIPLES "/home/axel/Documents/programmation/c/FManC/third_party_libs/mimalloc/CMakeLists.txt;506;add_test;/home/axel/Documents/programmation/c/FManC/third_party_libs/mimalloc/CMakeLists.txt;0;")
add_test(test-stress "/home/axel/Documents/programmation/c/FManC/third_party_libs/built_libs/mimalloc/mimalloc-test-stress")
set_tests_properties(test-stress PROPERTIES  _BACKTRACE_TRIPLES "/home/axel/Documents/programmation/c/FManC/third_party_libs/mimalloc/CMakeLists.txt;506;add_test;/home/axel/Documents/programmation/c/FManC/third_party_libs/mimalloc/CMakeLists.txt;0;")
