CPPFLAGS += -O2  -s  -Wall
CPP       =  g++


# list of tests for build
TESTS  = logger_test




.PHONY: all
all: clean  $(TESTS)



.PHONY: clean
clean:
	-@rm  *.o
	-@rm  *.*~
	-@rm  $(TESTS)



.PHONY: $(TESTS)
$(TESTS):
	$(CPP)  $@.cpp logger.cpp -o $@  $(CPPFLAGS)
	@echo "  ---- Compiled $@ ----"
	@echo ""



.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   help    -  This help"

