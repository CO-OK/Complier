#include<DynString.h>
#include<iostream>
#include <string.h>
DynString::DynString(int capacity){
    /*
        初始化动态字符串
        capacity:动态字符串初始化内存空间
    */
    
    this->data = new char[capacity];
    this->len=0;
    this->capacity=capacity;
}

DynString::~DynString(){
    /*
        释放动态字符串
    */
   if(this->data){
       delete[] this->data;
   }
   this->data=nullptr;
   this->len=0;
   this->capacity=0;
}

void DynString::reset(){
    /*
        重置动态字符串
        先删除再初始化，分配八个字节
    */
    if(this->data){
        delete this->data;
    }
    this->len=0;
    this->data = new char[24];
    this->capacity=24;
}

void DynString::realloc(int new_size){
    /*
        重新分配字符串容量
    */
    if(this->capacity>new_size){
        std::cout<<"DynString: realloc error\n";
        return;
    }
    int new_capacity=this->capacity;
    while(new_capacity<new_size)
        new_capacity*=2;

    char*new_data=new char[new_capacity];
    memcpy(new_data,this->data,this->len);

    delete this->data;
    this->data=new_data;
    this->capacity=new_capacity;
}

void DynString::appendChar(char ch){
    int count=this->len+1;
    if(count>this->capacity)
        this->realloc(count);
    this->data[count-1]=ch;
    this->len=count;
}