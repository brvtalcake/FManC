# Project informations
VERSION=0.1.0
MAJOR_VERSION=0

# OS-dependant variables
TEST_RES_FOLD=lin
ifneq (,$(findstring Windows,$(OS)))
	TEST_RES_FOLD=win
	SHELL=cmd
else ifneq (,$(findstring windows,$(OS)))
	SHELL=cmd
	TEST_RES_FOLD=win
endif

.PHONY : stat_win stat_lin dyn_win dyn_lin

stat_lin : 