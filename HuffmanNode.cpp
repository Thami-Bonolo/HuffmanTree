#include "HuffmanTree.h"
using namespace std;

namespace MLPBON002{
    /*Serialization :)*/
    /*Special member functions*/
    HuffmanNode::HuffmanNode(): //default constructor
    left(nullptr), right(nullptr){
    }
    
    HuffmanNode::HuffmanNode(char ch, int freq): //parameterized constructor
    ch(ch), freq(freq){ 
    }
    
    HuffmanNode::HuffmanNode(int freq): //the other one :)
    freq(freq){
    }
    
    HuffmanNode::~HuffmanNode(){
        //We shouldn't delete any node so i guess we leave it as it is
    }
    
    /*copy const & assignment operator*/
    HuffmanNode::HuffmanNode(const HuffmanNode& orig):
    freq(orig.freq), ch(orig.ch),
    left(orig.left), right(orig.right){   
    }
    
    HuffmanNode& HuffmanNode::operator = (
    const HuffmanNode& orig){
        if(this != &orig){
            ch = orig.ch;
            freq = orig.freq;
            left = orig.left;
            right = orig.right;
        }
        return *this;
    }
    
    /*move constructor & assignment operator*/
    HuffmanNode::HuffmanNode(HuffmanNode&& orig):
    freq(std::move(orig.freq)), ch(std::move(orig.ch)){
        left = std::move(orig.left);
        right = std::move(orig.right);
    }
    
    HuffmanNode & HuffmanNode::operator = (HuffmanNode && orig){
        if(this != &orig){
            ch = std::move(orig.ch);
            freq = std::move(orig.freq);
            left = std::move(orig.left);
            right = std::move(orig.right);
        }
        return *this;
    }
}