/*词法分析器*/
#include<DynString.h>
#include<TkWord&TkTable.h>
#include<fstream>
class LexicalAnalyzer{
public:
    //成员变量
    TkTable tkTable;//单词表
    DynString tkStr;//单词字符串 存入时用
    DynString sourceStr;//单词源码字符串 取出时用
    int tkvalue;//单词值 存储字符的ascii码或者是数字字符串的实际值
    char ch;//当前取到的源码字符
    int token;//单词编码，在单词表中的下标值
    int lineNum;//行号

    std::ifstream fin; //源文件读

    
    //词法分析过程
    void getch();//从源文件中读取一个字符
    void getToken();//取单词
    void preprocess();//预处理，忽略空白字符以及注释
    void parseComment();//处理注释
    void skipWhiteSpace();//忽略空格 tab 回车
    bool isNoDigit(char c);//判断是否是字母或者下划线
    bool isDigit(char c);//判断是否为数字
    void parseIdentifier();//解析标识符
    void parseNum();//解析整形常量
    void parseString(char sep);//解析字符串

    //错误处理
    void skip(int c);//跳过单词
    char* get_tkstr(int v);//取得单词v所代表的源码字符串

    //输出彩色
    void printColorToken();

    //构造函数
    LexicalAnalyzer(char* path);
};