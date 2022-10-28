#include <cstring>

#include "HuffmanTree.h"
using namespace std;

namespace MLPBON002{
    /*HuffmanTree serialization*/
    /*Special member functions*/
    
    HuffmanTree::HuffmanTree() //default constructor
    {}
    
    HuffmanTree::~HuffmanTree(void){ //Destructor
        root = nullptr;
    }
    
    /*Copy constructor & assignment operator*/
    HuffmanTree::HuffmanTree(const HuffmanTree& orig):
    codeTable(orig.codeTable),
    reverseCodeTable(orig.reverseCodeTable),
    freq(orig.freq),
    root(orig.root){
    }
    
    HuffmanTree& HuffmanTree::operator = (const HuffmanTree& orig){
        if(this != &orig){
            codeTable = orig.codeTable;
            reverseCodeTable = orig.reverseCodeTable;
            freq = orig.freq;
            root = orig.root;
        }
        return *this;
    }
    /*Move constructor & assignment operator*/
    HuffmanTree::HuffmanTree(HuffmanTree&& orig){
        codeTable = move(orig.codeTable);
        reverseCodeTable = move(orig.reverseCodeTable);
        freq = move(orig.freq);
        root = move(orig.root);
    }
    
    /*Assignment operator*/
    HuffmanTree& HuffmanTree::operator = (HuffmanTree&& orig){
        if(this != &orig){
            codeTable = move(orig.codeTable);
            reverseCodeTable = move(orig.reverseCodeTable);
            freq = move(orig.freq);
            root = move(orig.root);
        }
        return *this;
    }
    
    /*independent functions*/
    //comparison operator
    bool comp::operator()(const HuffmanNode& a,
            const HuffmanNode& b){
        return a.freq > b.freq;
    }
    
    //Converting binary to dec, hopes it works :|
    int binToDec(int bin){
        long dec = 0, rem, base = 1;
        
        while(bin > 0){
            rem = bin % 10;
            dec = dec + rem * base;
            base = base * 2;
            bin = bin / 10;
        }
        return (int)dec;
    }
    //converting dec to binary
    string decToBin(int dec){
        string st = std::bitset<8>(dec).to_string();
        return st;
    }
    
    /*HuffmanTree functions*/
    
    void HuffmanTree::buildMap(string input){
        
        //try opening file:
        ifstream file(input);
        if(!file){
            cerr << "Couldn't open file :(";
        }
        
        string data = "";
        string line;
        
        while(getline(file, line)){
            data.append(line);
        }
        file.close();
        
        for(char& ch: data){
            freq[ch]++;
        }
    }
    
    void HuffmanTree::buildTree(){
        
        //priority queue
        priority_queue<HuffmanNode, vector<HuffmanNode>, comp> pq;
        
        for(auto& node: freq){
            HuffmanNode newNode(node.first, node.second);
            pq.push(newNode);
        }
        
        while(pq.size()>1){
            HuffmanNode left = pq.top();
            pq.pop();
            HuffmanNode right = pq.top();
            pq.pop();
            
            int Freq = left.freq + right.freq;
            
            HuffmanNode newNode(Freq);
            
            newNode.left = make_shared<HuffmanNode>(left);
            newNode.right = make_shared<HuffmanNode>(right);
            pq.push(newNode);
        }
        
        root = make_shared<HuffmanNode>(pq.top());
    }
    
    void HuffmanTree::traverse(string code, 
            shared_ptr<HuffmanNode>& node){
        
        if(node->left == NULL){
            char ch = node->ch;
            codeTable[ch] = code;
            reverseCodeTable[code] = ch;
        }
        
        else{
            string l = code;
            l.append("0");
            string r = code;
            r.append("1");
            
            traverse(l, node->left);
            traverse(r, node->right);
        }
    }
    
    void HuffmanTree::buildCodeTable(void){
        //building code table
        
        string code = "0";
        traverse(code, root);
        
        //printing the table
    }
    
    void HuffmanTree::encode(string input, string output){
        //encoding and writing output to output.textFile
        string buffer = "";
        string data;
        
        ifstream file(input);
        if(!file){
            cout << "Couldn't open file" << endl;
        }
        
        string line;
        while(getline(file, line)){
            data.append(line);
        }
        file.close();
        
        for(char& ch: data){
            buffer.append(codeTable[ch]);
        }
        
        char* ch = new char[buffer.length()+1];
        std::strcpy(ch, buffer.c_str());
        
        string bufferFile = "buffer.dat";
        ofstream outputFile;
        outputFile.open(bufferFile);
        outputFile.write(ch, buffer.length());
        outputFile.close();
        
        output.append(".hdr");
        ofstream File;
        File.open(output);
        
        for(const auto& Data : codeTable){
            File << "Character: " << Data.first
                    << " Code:" << Data.second
                    <<"\n" <<endl;
        }
        
        cout << "The compressed text is:\n" << ch <<"\n" << endl;
        
        double bytes = (buffer.length()/8) + (buffer.length() % 8 ? 1:0);
        File << "The actual packed file size is:" << bytes << "\n" << endl;
        
        double compRatio = bytes/(buffer.length()*8);
        File << "The compression ratio is: " << compRatio
                <<" [(bit string size in bytes)/(input chars in bytes)]\n"<<endl;
        
        cout << "Size of input: " <<buffer.length()*8 << " bytes" <<endl;
        cout << "Size of output: "<< bytes<< " bytes"<<endl;
        
        File.close();
    }
    
    void HuffmanTree::convertToByteArray(string input){
        stringstream bFile;
        stringstream hFile;
        
        bFile << "binary_out.raw";
        hFile << "header.dat";
        string binaryFile = bFile.str();
        string headerFile = hFile.str();
        
        string buffer = "";
        
        //try open file
        ifstream file(input);
        if(!file){
            cout << "Couldn't open file" << endl;
        }
        string Data;
        string line;
        while(getline(file, line)){
            Data.append(line);
        }
        file.close();
        
        for(char& ch: input){
            buffer.append(codeTable[ch]);
        }
        
        int lenOrigString = buffer.length();
        
        while(!((buffer.length())%8==0)){
            buffer.append("0");
        }
        
        char* byte = new char[(int)(buffer.length()/8)];
        
        for(int i=0; i<(int)(buffer.length()/8); i++){
            stringstream stream(buffer.substr((i*8),8));
            int num = 0, bin = 0;
            stream >> bin;
            num = binToDec(bin);
            byte[i] = num;
        }
        
        ofstream Bin;
        Bin.open(binaryFile, ios::out | ios::binary);
        Bin.write(byte, (int)buffer.length());
        Bin.close();
        
        ofstream HeaderFile;
        HeaderFile.open(headerFile);
        HeaderFile << lenOrigString;
        HeaderFile.close();
    }
    
    string HuffmanTree::readAndUnpack(void){
        int bits;
        int numBytes;
        
        stringstream bFile;
        stringstream hFile;
        bFile << "binary_out.raw";
        hFile << "header.dat";
        string binaryFile = bFile.str();
        string headerFile = hFile.str();
        
        ifstream headerInput;
        headerInput.open(headerFile);
        //check if file exist:
        if(!headerInput){
            cerr<< "Couldn't open header file.";
        }
        
        headerInput >> numBytes;
        headerInput.close();
        
        int len = bits+(8-bits%8); //come back simplify this
        numBytes = len/8;
        
        char* bytes = new char[len];
        ifstream binaryIn;
        
        binaryIn.open(binaryFile, ios::in | ios::binary);
        if(!binaryIn){
            cout << binaryFile << "not found"<<endl;
        }
        else{
            binaryIn.read(bytes, len);
        }
        binaryIn.close();
        
        string buff = "";
        for(int i = 0; i<numBytes; i++){
            buff.append(decToBin((int)(unsigned char)bytes[i]));
        }
        buff = buff.substr(0, bits);
        
        string msg = "";
        string tempCode = "";
        
        for(char& ch: buff){
            tempCode.push_back(ch);
            if(reverseCodeTable[tempCode]){
                msg.push_back(reverseCodeTable[tempCode]);
                tempCode = "";
            }
        }
        cout << "The unpacked text is: "<<msg<<endl;
        return msg;
    }
}
