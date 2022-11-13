CPP = g++ -std=c++17 -Wall -Werror -Wextra
GCOV = --coverage
CHECK= -lgtest
BD = build
SRC = src/

all: clean test

test: clean
	$(CPP) $(SRC)model/model.cpp $(SRC)model/model_test.cpp $(CHECK) -o test
	./test

build: clean 
	mkdir $(SRC)build
	cp $(SRC)model/* $(SRC)controller/* $(SRC)view/* $(SRC)$(BD)
	cp Makefile $(SRC)$(BD)/
	cd $(SRC)$(BD); qmake calc.pro
	make -C $(SRC)$(BD)
	cd $(SRC)$(BD); rm -rf *.c *.h *.hpp *.cpp *.ui *.o *.pro* Makefile 
	open $(SRC)$(BD)

install: build
	mkdir $(HOME)/Desktop/SmartCalc/
	cp -rf $(SRC)$(BD) $(HOME)/Desktop/SmartCalc/

uninstall:
	rm -rf $(HOME)/Desktop/SmartCalc/
	rm -rf $(SRC)build

dvi:
	open description.html

dist:
	rm -rf backup_Smart_Calc
	mkdir backup_Smart_Calc
	cp Makefile $(SRC)model/* $(SRC)controller/* $(SRC)view/* backup_Smart_Calc/
	tar -cvzf $(HOME)/Desktop/backup_Smart_Calc.tgz backup_Smart_Calc/
	rm -rf backup_Smart_Calc/

clean: uninstall
	rm -rf test $(SRC)build* $(SRC)view/*.user

# leaks: test
# 	leaks -atExit -- ./test 