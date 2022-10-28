#include "HuffmanTree.h"
#include <cstdlib>


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    /*if(argc!= 3){
        cout <<"Invalid arguments."<<endl;
        cout <<"the correct arguments are: " <<
                "huffencode <inputFile><output file>"<<endl;
        return 0;
    }*/
    string input = argv[1];
    string output = argv[2];
    
    MLPBON002::HuffmanTree huffmanTree;
    huffmanTree.buildMap(input);
    huffmanTree.buildTree();
    huffmanTree.buildCodeTable();
    huffmanTree.encode(input, output);
    huffmanTree.convertToByteArray(input);
    huffmanTree.readAndUnpack();
    return 0;
}

