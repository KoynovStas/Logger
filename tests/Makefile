CXXFLAGS += -std=c++11 -O2 -Wall -lpthread
CXXFLAGS += -I..
CXX      ?=  g++


# list of tests for build
TESTS  = logger_test   \
         logger_r_test



UNAME := $(shell uname)

ifneq ($(UNAME), Linux)
BIN_TESTS       = $(addsuffix .exe, $(TESTS))
CXXFLAGS       += -lucrtbase
else
BIN_TESTS       = $(TESTS)
endif




.PHONY: all
all: $(BIN_TESTS)
	@for test in $(BIN_TESTS) ; do  \
    echo "  ---- Run $$test ----";  \
	./$$test ; \
    done



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(BIN_TESTS)



$(BIN_TESTS): ../logger.cpp ../logger.h
	$(CXX)  $(basename $@).cpp ../logger.cpp -o $@  $(CXXFLAGS)
	@echo "  ---- Compiled $@ ----"
	@echo ""




.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   help    -  This help"
