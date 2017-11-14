#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef CharStream_hpp
#define CharStream_hpp

using namespace std;

class CharStream
{
public:
    CharStream(char* filename);
    void readFile(void);
    char getCurrent(void);
    bool next(void);
    char lookAhead(void);
    int getBufferRow(int i);
    int getBufferCol(int i);
    int getFilesize(void);
    
    
private:
    int filesize, index, row, col;
    vector<char> buffer;
    vector<char> rowBuffer;
    vector<char> colBuffer;
    const char* filename;
    ifstream file;
    char current, look;
};

#endif /* CharStream_hpp */
