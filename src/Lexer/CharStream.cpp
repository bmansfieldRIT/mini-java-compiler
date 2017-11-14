#include "CharStream.hpp"

CharStream::CharStream(char* f)
{
    filename = f;
    readFile();
    index = 0;
}

void CharStream::readFile()
{
    char temp;
    
    //std::cout << "Opening file...\n";
    file.open(filename);
    if (file.fail()){
        string errorMsg =  "Failed to read input file\n";
        throw errorMsg;
    }
    
    //std::cout << "Reading file into memory...\n";
    // read the file into memory
    
    row = 1;
    col = 0;
    filesize = 0;
    
    while (file.is_open() && !file.eof() && file.good()){
        
        temp = file.get();
        if (temp == '\n'){
            row++;
            buffer.push_back('\n');
            filesize++;
            //std::cout << temp;
            col = 0;
            
        } else if (temp == '\t'){
            col += 4;
            
        } else if (isspace(temp)){
            buffer.push_back(temp);
            filesize++;
            col++;
            //std::cout << temp;
            
        } else {
            buffer.push_back(temp);
            filesize++;
            col++;
            //std::cout << temp;
            
        }
        rowBuffer.push_back(row);
        colBuffer.push_back(col);
    }
    //std::cout << filesize;
    //std::cout << "Finished reading file into memory...\n";
}

char CharStream::getCurrent()
{
    return (current);
}

int CharStream::getFilesize()
{
    return (filesize);
}

bool CharStream::next()
{
    if (index < filesize){
        current = buffer[index];
        index++;
        return true;
    }
    
    return false;
}

char CharStream::lookAhead()
{
    
    if (index < filesize){
        look = buffer[index];
        return look;
    }
    
    return ' ';
}

int CharStream::getBufferRow(int i)
{
    if (rowBuffer[i] == 0){
        return row;
    }
    return rowBuffer[i];
}

int CharStream::getBufferCol(int i)
{
    if (rowBuffer[i] == 0){
        return col;
    }
    return colBuffer[i];
}

