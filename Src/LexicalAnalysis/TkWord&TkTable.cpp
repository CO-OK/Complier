#include<TkWord&TkTable.h>
#include<string.h>
TkWord* TkTable::tkwordDirectInsert(TkWord*tp){
    /*
        运算符、关键字、常量直接放入单词表
    */
    int keyno;
    this->tktable.append(tp);
    keyno=elf_hash(tp->spelling);
    tp->next=this->tk_hashtable[keyno];
    this->tk_hashtable[keyno]->next=tp;
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