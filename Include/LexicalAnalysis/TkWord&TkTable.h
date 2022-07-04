/*单词存储结构与单词表*/
#include<DynArray.h>
int elf_hash(char* key);//哈希函数

class TkWord{
    /*
        单词，用来组成单词表
    */
public:
    int tkcode;//单词编码
    TkWord* next;//指向哈希冲突的同义词
    char* spelling;//单词字符串
    struct Symbol* sym_struct;//指向单词所表示的结构定义
    struct Symbol* sym_identifier;//指向单词所表示的标识符
};

#define MAXKEY 1024 //哈希表容量

class TkTable{
    /*
        单词表
    */
public:
    TkWord* tk_hashtable[MAXKEY]; //单词哈希表
    DynArray tktable; // 单词表

    TkTable();
    TkWord* tkwordDirectInsert(TkWord*tp);//运算符、关键字、常量直接放入单词表
    TkWord* tkwordFind(char* p,int keyno);//在单词表中查找单词
    TkWord* tkwordInsert(char*p);//标识符插入单词表

};