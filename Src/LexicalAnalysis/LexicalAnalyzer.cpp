#include<LexicalAnalyzer.h>
#include<Error.h>
#include<TokenCode.h>
#include<ColorPrint.h>
#include<string.h>
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
    /*
        取得单词v代表的源码字符串
    */
    if(v>this->tkTable.tktable.len){
        return nullptr;
    }
    else if(v>=TK_CINT&&v<=TK_CSTR){
        /*是常量返回源码字符串*/
        return this->sourceStr.data;
    }
    else
        return ((TkWord*)this->tkTable.tktable.data[v])->spelling;
}

void LexicalAnalyzer::getToken(){
    /*
        取单词
    */

    this->preprocess();

    switch(this->ch){
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':

        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
        case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
        case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':

        case '_':{
            TkWord* tp;
            this->parseIdentifier();          
            tp=this->tkTable.tkwordInsert(this->tkStr.data);     
            this->token=tp->tkcode;      
            break;
        }

        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
        case '8': case '9':{
            this->parseNum();
            token=TK_CINT;
            break;
        }

        case '+':{
            this->getch();
            this->token=TK_PLUS;
            break;
        }

        case '-':{
            this->getch();
            if(this->ch=='>'){
                this->token=TK_POINTSTO;
                this->getch();
            }
            else
                this->token=TK_MINUS;

            break;
        }

        case '/':{
            this->getch();
            this->token=TK_DIVIDE;
            break;
        }

        case '%':{
            this->getch();
            this->token=TK_MOD;
            break;
        }

        case '=':{
            this->getch();
            if(this->ch=='='){
                this->getch();
                this->token=TK_EQ;
            }
            else
                this->token=TK_ASSIGN;
            break;
        }

        case '!':{
            this->getch();
            if(this->ch=='='){
                this->getch();
                this->token=TK_NEQ;
            }
            else
                error("非法操作符!");
            break;
        }

        case '<':{
            this->getch();
            if(this->ch=='='){
                this->getch();
                this->token=TK_LEQ;
            }
            else
                this->token=TK_LT;
            break;
        }

        case '>':{
            this->getch();
            if(this->ch=='='){
                this->getch();
                this->token=TK_GEQ;
            }
            else
                this->token=TK_GT;
                break;
        }

        case '.':{
            this->getch();
            if(this->ch=='.'){
                this->getch();
                if(this->ch=='.'){
                    this->getch();
                    this->token=TK_ELLIPSIS;
                }
                else{
                    error("非法省略号!");
                }
            }
            else
                this->token=TK_DOT;
            break;
        }
        
        case '&':{
            this->getch();
            this->token=TK_AND;
            break;
        }

        case ';':{
            this->getch();
            this->token=TK_SEMICOLON;;
            break;
        }

        case ']':{
            this->getch();
            this->token=TK_CLOSEBR;
            break;
        }

        case '}':{
            this->getch();
            this->token=TK_END;
            break;
        }

        case ')':{
            this->getch();
            this->token=TK_CLOSEPA;
            break;
        }

        case '[':{
            this->getch();
            this->token=TK_OPENBR;
            break;
        }

        case '{':{
            this->getch();
            this->token=TK_BEGIN;
            break;
        }

        case '(':{
            this->getch();
            this->token=TK_OPENPA;
            break;
        }

        case ',':{
            this->getch();
            this->token=TK_COMMA;
            break;
        }

        case '*':{
            this->getch();
            this->token=TK_STAR;
            break;
        }

        case '\'':{
            this->parseString(this->ch);
            this->token=TK_CCHAR;
            this->tkvalue=*(char*)this->tkStr.data;
            break;
        }

        case '\"':{
            this->parseString(this->ch);
            this->token=TK_CSTR;
            break;
        }

        case EOF:{
            token=TK_EOF;
            break;
        }
        default:{
            error("未知字符:\\x%02x",this->ch);
            this->getch();
            break;
        }
    }

}

void LexicalAnalyzer::getch(){
    /*
        从源文件中读一个字符
    */
   
    this->ch=this->fin.get();
}


void LexicalAnalyzer::preprocess(){
    /*
        预处理，忽略空白字符以及注释
    */
    while(true){
        if(this->ch==' '||this->ch=='\t'||this->ch=='\n'){
            //printf("p666");
            this->skipWhiteSpace();
        }
        else if(this->ch=='/'){
            //printf("p666");
            //看看是不是注释
            this->getch();
            if(this->ch=='*'){
                this->parseComment();
            }
            else{
                //不是就放回去
                this->fin.unget();
                this->ch='/';
                break;
            }
        }
        else{
            break;
        }
    }
}

void LexicalAnalyzer::parseComment(){
    /*
        解析注释
    */
    while(true){
        while(true){
            if(this->ch=='\n'||this->ch=='*'||this->ch==EOF){
                break;
            }
            else{
                this->getch();
            }
        }
        if(this->ch=='\n'){
            this->lineNum++;
            this->getch();
        }
        else if(this->ch=='*'){
            this->getch();
            if(this->ch=='/'){
                this->getch();
                return;
            }
        }
        else{
            error("非法注释");
            return;
        }
    }
    return;
}

bool LexicalAnalyzer::isNoDigit(char c){
    /*
        判断是否为a-z或A-Z或_
    */
    return ((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_');
}

bool LexicalAnalyzer::isDigit(char c){
    /*
        判断是否为数字
    */
    return (c>='0'&&c<='9');
}

void LexicalAnalyzer::parseIdentifier(){
    /*
        解析标识符
    */
    this->tkStr.reset();

    this->tkStr.appendChar(this->ch);
    this->getch();
    while(isNoDigit(this->ch)||isDigit(this->ch)){

        this->tkStr.appendChar(this->ch);
        this->getch();
    }

    this->tkStr.appendChar('\0');

}

void LexicalAnalyzer::parseNum(){
    /*
        解析数字
    */
    this->tkStr.reset();
    this->sourceStr.reset();
    while(isDigit(this->ch)){
        this->tkStr.appendChar(this->ch);
        this->sourceStr.appendChar(this->ch);
        this->getch();
    }
    if(this->ch=='.'){
        while(isDigit(this->ch)){
            this->tkStr.appendChar(this->ch);
            this->sourceStr.appendChar(this->ch);
            this->getch();
        }
    }
    this->tkStr.appendChar('\0');
    this->sourceStr.appendChar('\0');
    this->tkvalue=atoi(this->tkStr.data);
}

void LexicalAnalyzer::parseString(char sep){
    /**/
    this->tkStr.reset();
    this->sourceStr.reset();
    this->sourceStr.appendChar(sep);
    this->getch();

    while(true){
        if(this->ch==sep)break;
        else if(ch=='\\'){
            this->sourceStr.appendChar(this->ch);
            this->getch();
            char c;
            switch(this->ch){
                case '0':c='0';break;
                case 'a':c='a';break;
                case 'b':c='b';break;
                case 't':c='t';break;
                case 'n':c='n';break;
                case 'v':c='v';break;
                case 'f':c='f';break;
                case 'r':c='r';break;
                case '\'':c='\'';break;
                case '\"':c='\"';break;
                case '\\':c='\\';break;
                default:{
                    c=this->ch;
                    if(c>='!'&&c<='~')
                        warning("非法转义字符:\'\\%c\'",c);
                    else
                        warning("非法转义字符:\'\\0x%x\'",c);
                    break;
                }
            }
            this->tkStr.appendChar(c);
            this->sourceStr.appendChar(this->ch);
            this->getch();
        }
        else{
            this->tkStr.appendChar(this->ch);
            this->sourceStr.appendChar(this->ch);
            this->getch();
        }
    }

    this->sourceStr.appendChar(sep);
    this->tkStr.appendChar('\0');
    this->sourceStr.appendChar('\0');
    this->getch();
}

void LexicalAnalyzer::skipWhiteSpace(){
    /*
        忽略空白字符
    */
    while(this->ch==' '||this->ch=='\t'||this->ch=='\n'){
        if(this->ch=='\n'){
            this->lineNum++;
        }
        printf("%c",this->ch);
        this->getch();
    }
    
}

LexicalAnalyzer::LexicalAnalyzer(char* path):tkStr(24),sourceStr(24){
    /**/
    this->fin.open(path,std::ios::in);
    if(!this->fin.is_open()){
        error("文件不存在!");
    }
    this->lineNum=1;
    this->getch();
    while(this->token!=TK_EOF){
        //printf("666");
        this->getToken();
        this->printColorToken();
    }
    
}

void LexicalAnalyzer::printColorToken(){
    if(this->token>=TK_IDEENT){
        //标识符为紫色
        colorPrint(this->get_tkstr(this->token),Color::PURPLE);
    }
    else if(this->token>=KW_CHAR){
        //关键字为绿色
        colorPrint(this->get_tkstr(this->token),Color::GREEN);
    }
    else if(this->token>=TK_CINT){
        //常量为棕色
        colorPrint(this->get_tkstr(this->token),Color::BROWN);
    }
    else{
        //运算符及分隔符为红色
        colorPrint(this->get_tkstr(this->token),Color::RED);
    }
}