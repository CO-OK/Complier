/*动态数组*/
class DynArray{
public:
    int len; //元素个数
    int capacity; //缓冲区长度
    void** data; //指针数组

    DynArray(int capacity);
    ~DynArray();
    void realloc(int new_size); //重新分配容量
    void append(void *data); //追加数组元素
    int search(int key);//查找元素
};