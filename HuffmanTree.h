/*Defined both classes in the same file :|*/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <memory>
#include <vector>
#include <bitset>
using namespace std;
namespace MLPBON002{
    class HuffmanNode;
    struct comp{
        bool operator()(const HuffmanNode& a, const HuffmanNode& b);
    };
    
    //Huffman [from/to binary, decimal]
    int binToDec(int bin);
    string decToBin(int dec);
class HuffmanTree {
public:
    /*HuffmanTree variables*/
    unordered_map<char, string> codeTable; //characters and frequency map
    unordered_map<string, char> reverseCodeTable;
    shared_ptr<HuffmanNode> root;
    unordered_map<char, int> freq;
    
    /*Special member functions*/
    HuffmanTree(); //default constructor
    HuffmanTree(const HuffmanTree& orig); //copy constructor
    HuffmanTree& operator = (const HuffmanTree& orig);//assignment op
    virtual ~HuffmanTree(); //destructor
    HuffmanTree(HuffmanTree&& orig); // move constructor
    HuffmanTree& operator = (HuffmanTree&& orig);// assignment op
    
    /*HuffmanTree functions*/
    void buildMap(string input);
    void buildTree(void);
    void buildCodeTable(void);
    void encode(string input, string output);
    string read(void);
    void traverse(string code, shared_ptr<HuffmanNode>& node);
    void convertToByteArray(string input);
    string readAndUnpack(void);
    
private:

};

class HuffmanNode {
    friend class HuffmanTree;
public:
    shared_ptr<HuffmanNode> left;
    shared_ptr<HuffmanNode> right;
    int freq; //frequency
    char ch; //characters
    
    /*Special member functions*/
    HuffmanNode();// default constructor
    HuffmanNode(char ch, int freq); //Parameterized constructor
    HuffmanNode(int freq); //Another parameterized constructor
    virtual ~HuffmanNode(void); //destructor
    HuffmanNode(const HuffmanNode& orig); // copy constructor
    HuffmanNode& operator = (const HuffmanNode& orig); //assignment op
    HuffmanNode(HuffmanNode&& orig); //move constructor
    HuffmanNode& operator = (HuffmanNode&& orig); //Assignment op
    
    /*HuffmanNode functions*/
    /*getter and setter methods(In case the code does not run:D)*/
};

}
#endif /* HUFFMANTREE_H */

