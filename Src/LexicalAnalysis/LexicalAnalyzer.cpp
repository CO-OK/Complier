#include<LexicalAnalyzer.h>
#include<Error.h>
#include<TokenCode.h>
void LexicalAnalyzer:: skip(int c){
    /*
        跳过单词c,如果不是当前单词不是c，提示错误
        c:要跳过的单词
    */
    if(this->token!=c)
        error("缺少'%s'",get_tkstr(c));
    this->getToken();
}

char* LexicalAnalyzer:: get_tkstr(int v){
    /**/
    if(v>this->tkTable.tktable.len){
        return nullptr;
    }
    else if(v>=TK_CINT<=TK_CSTR){
        /*是常量返回源码字符串*/
        return this->sourceStr.data;
    }
    else
        return ((TkWord*)this->tkTable.tktable.data[v])->spelling;
}

void LexicalAnalyzer::getToken(){
    
}