#include<TkWord&TkTable.h>
#include<string.h>
#include<TokenCode.h>
#include<iostream>
TkWord* TkTable::tkwordDirectInsert(TkWord*tp){
    /*
        运算符、关键字、常量直接放入单词表
    */
    int keyno;
    this->tktable.append(tp);
    keyno=elf_hash(tp->spelling);
    tp->next=this->tk_hashtable[keyno];
    this->tk_hashtable[keyno]=tp;
    return tp;
}
TkWord* TkTable::tkwordFind(char* p,int keyno){
    /*
        在单词表中查找单词
    */
    TkWord*tp=nullptr;
    TkWord*tp1=this->tk_hashtable[keyno];
    while(tp1!=nullptr){
        if(!strcmp(p,tp1->spelling)){
            tp=tp1;
            //token=tp1->tkcode
            return tp;
        }
        tp1=tp1->next;
    }
    return tp;
}
TkWord* TkTable::tkwordInsert(char*p){
    /*
        标识符插入单词表,查找不到再插入
    */
   
    int keyno=elf_hash(p);
    TkWord*tp=this->tkwordFind(p,keyno);
    if(tp==nullptr){
        int length=strlen(p);
        tp = new TkWord;
        tp->next=this->tk_hashtable[keyno];//头插法
        this->tk_hashtable[keyno]=tp;
        this->tktable.append(tp);
        tp->tkcode=this->tktable.len-1;
        tp->spelling=new char[length+1];
        for(int i=0;i<length;i++){
            tp->spelling[i]=p[i];
        }
        tp->spelling[length]='\0';
    }
    return tp;
}

TkTable::TkTable(){
    /*
        构造初始化的单词表
    */
    static TkWord keywords[]={//要插入的关键词的TkWord
        {TK_PLUS,nullptr,"+",nullptr,nullptr},
        {TK_MINUS,nullptr,"-",nullptr,nullptr},
        {TK_STAR,nullptr,"*",nullptr,nullptr},
        {TK_DIVIDE,nullptr,"/",nullptr,nullptr},
        {TK_MOD,nullptr,"%",nullptr,nullptr},
        {TK_EQ,nullptr,"==",nullptr,nullptr},
        {TK_NEQ,nullptr,"!=",nullptr,nullptr},
        {TK_LT,nullptr,"<",nullptr,nullptr},
        {TK_LEQ,nullptr,"<=",nullptr,nullptr},
        {TK_GT,nullptr,">",nullptr,nullptr},
        {TK_GEQ,nullptr,">=",nullptr,nullptr},
        {TK_ASSIGN,nullptr,"=",nullptr,nullptr},
        {TK_POINTSTO,nullptr,"->",nullptr,nullptr},
        {TK_DOT,nullptr,".",nullptr,nullptr},
        {TK_AND,nullptr,"&",nullptr,nullptr},
        {TK_OPENPA,nullptr,"(",nullptr,nullptr},
        {TK_CLOSEPA,nullptr,")",nullptr,nullptr},
        {TK_OPENBR,nullptr,"[",nullptr,nullptr},
        {TK_CLOSEBR,nullptr,"]",nullptr,nullptr},
        {TK_BEGIN,nullptr,"{",nullptr,nullptr},
        {TK_END,nullptr,"}",nullptr,nullptr},
        {TK_SEMICOLON,nullptr,";",nullptr,nullptr},
        {TK_COMMA,nullptr,",",nullptr,nullptr},
        {TK_ELLIPSIS,nullptr,"...",nullptr,nullptr},
        {TK_EOF,nullptr,"End_Of_File",nullptr,nullptr},

        {TK_CINT,nullptr,"整形常量",nullptr,nullptr},
        {TK_CCHAR,nullptr,"字符常量",nullptr,nullptr},
        {TK_CSTR,nullptr,"字符串常量",nullptr,nullptr},
        
        {KW_CHAR,nullptr,"char",nullptr,nullptr},
        {KW_SHORT,nullptr,"short",nullptr,nullptr},
        {KW_INT,nullptr,"int",nullptr,nullptr},
        {KW_VOID,nullptr,"void",nullptr,nullptr},
        {KW_STRUCT,nullptr,"struct",nullptr,nullptr},

        {KW_IF,nullptr,"if",nullptr,nullptr},
        {KW_ELSE,nullptr,"else",nullptr,nullptr},
        {KW_FOR,nullptr,"for",nullptr,nullptr},
        {KW_CONTINUE,nullptr,"continue",nullptr,nullptr},
        {KW_BREAK,nullptr,"break",nullptr,nullptr},
        {KW_RETURN,nullptr,"return",nullptr,nullptr},
        {KW_SIZEOF,nullptr,"sizeof",nullptr,nullptr},
        {KW_ALIGN,nullptr,"__align",nullptr,nullptr},
        {KW_CDECL,nullptr,"__cdecl",nullptr,nullptr},
        {KW_STDCALL,nullptr,"__stdcall",nullptr,nullptr},
        {0,nullptr,nullptr,nullptr,nullptr}

    };
    
    for(TkWord*tp=&keywords[0];tp->spelling!=nullptr;tp++){
        //std::cout<<tp->spelling<<std::endl;
        this->tkwordDirectInsert(tp);
    }
}

int elf_hash(char* key){
    int h=0,g;
    while(*key){
        h=(h<<4)+*key++;
        g=h&0xf0000000;
        if(g)
            h^=g>>24;
        h&=~g;
    }
    return h%MAXKEY;
}