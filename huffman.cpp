#include "huffman.hpp"

void huffman::createArr(){
  for(int i=0;i<128;++i){
    arr.push_back(new Node());
    arr[i]->data=i;
    arr[i]->freq=0;
    }
  }


int huffman::binarytoDecimal(string s){
   int num=0;
   for(int i=0;i<s.length();++i){
     num=num*2+s[i]-'0';
    }
    return num;
  }

string huffman::decimaltoBinary(int num){
   string temp="",ans="";
   while(num > 0){
      temp+=(num%2+'0');
      num/=2;}
   ans.append(8-temp.length(),'0');
   for(int i=temp.length()-1;i>=0;--i)
      ans+=temp[i];
   return ans;
   }

void huffman::traverse(Node* t,string s){
   if(t->left==NULL && t->right==NULL){
      t->code=s;
      return ; }
   traverse(t->left,s+'0');
   traverse(t->right,s+'1');
  }

void huffman::buildHuffmanTree(char code, string& path){
   Node*curr=root;
   for(int i=0;i<path.length();++i){
       if(path[i]=='0'){
          if(curr->left==NULL)
            curr->left=new Node();
          curr=curr->left;
       }
      else if(path[i]=='1'){
          if(curr->right==NULL)
            curr->right=new Node();
          curr=curr->right;
       }   
   }    
   curr->data=code;
   }

void huffman::createMinHeap(){
  char id;
  inFile.open(inFileName,ios::in);
  inFile.get(id);
  while(!inFile.eof()){
     arr[id]->freq++;
     inFile.get(id);
  }
  inFile.close();
  for(int i=0;i<128;++i){
      if(arr[i]->freq > 0){
         minHeap.push(arr[i]);
         }
     }
 }

void huffman::createTree(){
  Node *left,*right;
  priority_queue<Node*, vector<Node*>, compare> temp(minHeap);
  while(temp.size()!=1){
       left=temp.top();
       temp.pop();
       right=temp.top();
       temp.pop();
       root=new Node();
       root->freq=left->freq+right->freq;
       root->left=left;
       root->right=right;
       temp.push(root);
    }
 }

 
 void huffman::generateCodes(){
     traverse(root,"");
   }

void huffman::EncodedFile(){
  inFile.open(inFileName, ios::in);
  outFile.open(outFileName, ios::out | ios::binary);
  string in="";
  string temp="";
  char id;

  in+=(char)minHeap.size();
  priority_queue <Node*,vector<Node*>,compare> temppq(minHeap);
  while(!temppq.empty()){
       Node* curr=temppq.top();
       in+=curr->data;
       temp.assign(127-curr->code.length(),'0');
       temp+='1';
       temp+=curr->code;
       in+= (char)binarytoDecimal(temp.substr(0,8));
       for(int i=0;i<15;++i){
          temp=temp.substr(8);
          in+=(char)binarytoDecimal(temp.substr(0,8));
         }
       temppq.pop();
      }

  temp.clear();
  inFile.get(id);

  while(!inFile.eof()){
      temp+=arr[id]->code;
      while(temp.length()>8){
         in+=(char)binarytoDecimal(temp.substr(0,8));
         temp=temp.substr(8);
       }
      inFile.get(id);
     }   

  int count=8-temp.length();
  if(temp.length()<8){
     temp.append(count, '0');
    }
    in+=(char)binarytoDecimal(temp);
    in+=(char)count;
    outFile.write(in.c_str(),in.size());
    inFile.close();
    outFile.close();
   }         

           

void huffman::DecodedFile() {
   inFile.open(inFileName, ios::in | ios::binary);
   outFile.open(outFileName, ios::out);
   unsigned char size;
   inFile.read(reinterpret_cast<char*>(&size),1);
   inFile.seekg(-1, ios::end);
   char count0;
   inFile.read(&count0,1);
   inFile.seekg(1+17*size,ios::beg);
   vector<unsigned char> text;
   unsigned char textseg;
   inFile.read(reinterpret_cast<char*>(&textseg),1);
   while(!inFile.eof()){
      text.push_back(textseg);
      inFile.read(reinterpret_cast<char*>(&textseg),1);
     }

   Node* curr=root;
   string path;
   for(int i=0;i<text.size()-1;++i){
      path=decimaltoBinary(text[i]);
       if(i==text.size()-2){
         path=path.substr(0,8-count0);
      }

      for(int j=0;j<path.size();++j){
          if(path[j]=='0'){
            curr=curr->left;
          }
          else{
            curr=curr->right;
         }     

         if(curr->left==NULL && curr->right==NULL){
            outFile.put(curr->data);
            curr=root;
            }
          }
       }
    inFile.close();
    outFile.close();
    }                   

void huffman::getHuffmanTree(){
    inFile.open(inFileName, ios::in | ios::binary);
    unsigned char size;
    inFile.read(reinterpret_cast<char*>(&size),1);
    root=new Node();
    for(int i=0;i<size;++i){
        char ac;
        unsigned char hcode[16];
        inFile.read(&ac,1);
        inFile.read(reinterpret_cast<char*>(hcode),16);
        string hcstr="";
        for(int i=0;i<16;++i){
           hcstr+=decimaltoBinary(hcode[i]);
           }                    

        int j=0;
        while(hcstr[j]=='0')
           ++j; 

        hcstr=hcstr.substr(j+1);
        buildHuffmanTree(ac,hcstr);
       }
     inFile.close();
     }

void huffman::compress(){
     createMinHeap();
     createTree();
     generateCodes();
     EncodedFile();
     }    

void huffman::decompress(){
   getHuffmanTree();
   DecodedFile();
  }                                             