#include<DynArray.h>
#include<iostream>
#define DEFAUT_CAPACITY 8
DynArray::DynArray(int capacity){
    /*
        初始化动态数组
        capacity:内存空间大小
    */
    this->data = new void*[capacity];
    this->len=0;
    this->capacity=capacity;
}

DynArray::~DynArray(){
    /*
        释放动态数组
    */
   
   for(int i=0;i<this->len;i++){
       if(this->data[i]!=nullptr){
           //delete this->data[i];
           this->data[i]=nullptr;
       }
   }
   delete this->data;
   this->data=nullptr;
   this->len=0;
   this->capacity=0;

}

void DynArray::realloc(int new_size){
    /*
        重新分配字符串容量
    */
    if(this->capacity>new_size){
        std::cout<<"DynArrayrealloc error:new size too small\n";
        return;
    }
    int new_capacity=this->capacity;
    while(new_capacity<new_size)
        new_capacity*=2;

    void**new_data=new void*[new_capacity];
    

    for(int i=0;i<this->len;i++){
       if(this->data[i]){
           new_data[i]=this->data[i];
           //delete this->data[i];
           this->data[i]=nullptr;
       }
       else{
           std::cout<<"DynArray realloc error: null point\n";
           break;
       }
   }
   delete this->data;
   this->data=new_data;
   this->capacity=new_capacity;
}

void DynArray::append(void* data){
    /*
        追加指针数组一个元素
        data:要追加的元素
    */
    int count=this->len+1;
    if(count>this->capacity)
        this->realloc(count);
    this->data[count-1]=data;
    this->len=count;
}

int DynArray::search(int key){
    /*
        查找数组元素，找到就返回下标，找不到返回-1
    */
   int**p=(int**)this->data;
   for(int i=0;i<this->len;i++){
       if(key==**p)
        return i;
   }
   return -1;
}

DynArray::DynArray(){
    this->data = new void*[DEFAUT_CAPACITY];
    this->len=0;
    this->capacity=DEFAUT_CAPACITY;
}