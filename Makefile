huffman_main:huffman_main.o huffman.o
	gcc huffman_main.cpp huffman.cpp -o huffman_main

huffman_main.o:huffman_main.cpp
	gcc -c huffman_main.cpp

huffman.o:huffman.cpp
	gcc -c huffman.cpp

