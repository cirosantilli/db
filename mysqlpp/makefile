IN_DIR 		?= ./
IN_EXTS 	?= .cpp
OUT_DIR 	?= _out/
OUT_EXT 	?=
RUN			?= main
CXX			:= g++
FLAGS 	    := -Wall -std=c++11 -pedantic-errors -I"/usr/include/mysql/" -I"/usr/include/mysql++/"
LIBS		:= -lmysqlpp

INS			:= $(foreach IN_EXT, $(IN_EXTS), $(wildcard $(IN_DIR)*$(IN_EXT)) )
INS_NODIR 	:= $(notdir $(INS))
OUTS_NODIR	:= $(basename $(INS_NODIR))
OUTS_NODIR	:= $(addsuffix $(OUT_EXT), $(OUTS_NODIR))
OUTS		:= $(addprefix $(OUT_DIR), $(OUTS_NODIR))

.PHONY: all clean mkdir run install-deps-ubuntu setup

all: mkdir $(OUTS)

# rule to make the c files
$(OUT_DIR)%$(OUT_EXT): %.cpp
	$(CXX) $(FLAGS) -o "$@" "$<" $(LIBS)

clean:
	rm -rf $(OUT_DIR)

install-deps-ubuntu:
	sudo apt-get install -y mysql-server
	sudo apt-get install -y libmysql++-dev

mkdir:
	mkdir -p $(OUT_DIR)

run: all
	cd $(OUT_DIR) && ./$(RUN)$(OUT_EXT)

# setup before running the program for the first time
setup:
	mysql -u root -h localhost -p < setup.sql
