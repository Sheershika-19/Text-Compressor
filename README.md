# Text-Compressor
<br>
This project is based on greedy algorithm called Huffman's coding. It can compress and decompress any text files.  <br>
# How to run this project ?
<br>
To compress inputFile.txt(which is 1.1MB) file . Use the commands given below<br>
      g++ huffmanencode.cpp huffman.cpp -o main <br>
      ./main inputFile.txt compressedFile.huf <br>
After running above commands, we get compressedFile.huf ( binary file ) which is 1.1 MB in size.<br>
To decompress compressedFile.huf file .Use the commands given below<br>
     g++ huffmandecode.cpp huffman.cpp -o main <br>
     ./main compressedFile.huf outputFile.txt  <br>
size of output file is 2.2MB<br>
This implementation is not as efficient as currently used compression algorithms.

      
