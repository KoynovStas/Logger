CPPFLAGS += -std=c++11 -O2 -s -lpthread -Wall
CPPFLAGS += -I..
CPP       =  g++


# list of tests for build
TESTS  = logger_test logger_r_test




.PHONY: all
all: clean  $(TESTS)



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(TESTS)



.PHONY: $(TESTS)
$(TESTS):
	$(CPP)  $@.cpp ../logger.cpp -o $@  $(CPPFLAGS)
	@echo "  ---- Compiled $@ ----"
	@echo ""



.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   help    -  This help"

