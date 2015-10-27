all: int1

int1: int1.cpp
	g++ -g -o int1 int1.cpp -lX11
	gencat -o int1.msg int1.txt


clean:
	rm -v int{1,2,3,4,5,6,7,8,9} \
          int0{1,2,3,4,5,6,7,8,9} \
          *.msg
