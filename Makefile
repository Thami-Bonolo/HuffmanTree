CC=g++

Huffencode: HuffmanNode.o HuffmanTree.o huffencode.o
	$(CC) HuffmanNode.o HuffmanTree.o huffencode.o -o huffencode

HuffmanNode.o: HuffmanNode.cpp HuffmanTree.h
	$(CC) HuffmanNode.cpp -c

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h
	$(CC) HuffmanTree.cpp -c

huffencode.o: huffencode.cpp HuffmanTree.h
	$(CC) huffencode.cpp -c

clean:
	@rm -f *.o huffencode
