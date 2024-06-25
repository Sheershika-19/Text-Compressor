#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <string>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    char data;
    unsigned freq;
    string code;
    Node *left,*right;
    Node(){
       left=right=NULL;
     }
    };

class huffman {
    private:
       vector<Node*> arr;
       fstream inFile,outFile;
       string inFileName,outFileName;
       Node* root;
       class compare {
          public:
            bool operator()(Node* l,Node* r){
               return l->freq > r->freq;
            }
        };

       priority_queue<Node*,vector<Node*>,compare> minHeap;

       void createArr();

       void traverse(Node*,string);

       int binarytoDecimal(string);

       string decimaltoBinary(int);

       void buildHuffmanTree(char,string&);

       void createMinHeap();

       void createTree();

       void generateCodes();

       void EncodedFile();      

       void DecodedFile();     

       void getHuffmanTree();

       public:
          huffman(string inFileName,string outFileName){
              this->inFileName=inFileName;
              this->outFileName=outFileName;
              createArr();
          }
          void compress();
          void decompress();
    };
  #endif

          

              

                           