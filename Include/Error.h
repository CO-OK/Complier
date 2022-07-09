typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
/*错误枚举*/
enum e_ErrorLevel{
    /*错误级别*/
    LEVEL_WARNING,
    LEVEL_ERROR,
};

enum e_WorkStage{
    /*工作阶段*/
    STAGE_COMPILE,
    STAGE_LINK,
};

void handleException(int stage,int level,char*fmt,va_list ap);//异常处理
void warning(char*fmt, ...);//编译警告处理
void error(char*fmt, ...);//编译致命错误处理
void except(char*msg);//提示错误
void linkError(char* fmt, ...);//链接错误