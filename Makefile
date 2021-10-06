CLANG_FORMAT_OPTIONS=--verbose -i --style=file
CLANG_FORMAT_FILES=$(wildcard ./include/**/**.h ./include/**.h ./src/**/**.cpp ./src/**.cpp)
CPP_CHECK_FLAGS=--enable=all --quiet --suppress=unusedFunction

format:
	clang-format $(CLANG_FORMAT_OPTIONS) $(CLANG_FORMAT_FILES)
