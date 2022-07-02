/*动态字符串*/
class DynString{

public:
    int len; //长度
    int capacity; //包含该字符串的缓冲区长度
    char* data; //字符串

    DynString(int capacity);
    ~DynString();
    void reset(); //重置，先释放再重新初始化
    void realloc(int new_size); //重新分配字符串容量
    void appendChar(char ch); //追加单个字符
};