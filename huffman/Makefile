obj = huffman_main.o huffman.o
CC = gcc
target = huffman_main

$(target):$(obj)
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -o $@
clean:
	rm *.o $(target)

#huffman_main:huffman_main.o huffman.o
#	gcc huffman_main.cpp huffman.cpp -o huffman_main

#huffman_main.o:huffman_main.cpp
#	gcc -c huffman_main.cpp

#huffman.o:huffman.cpp
#	gcc -c huffman.cpp


