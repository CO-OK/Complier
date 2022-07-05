#include<Error.h>
#include<stdio.h>
#include<stdlib.h>
int filename;//文件名
int line_num;//文件所在行
void handleException(int stage,int level,char*fmt,va_list ap){
    /*
        异常处理
        stage:出现异常时所处的阶段
        level:错误级别
        fmt:参数输出格式
        ap:可变参数列表
    */
    char buf[1024];
    vsprintf(buf,fmt,ap);
    if(stage==STAGE_COMPILE){
        if(level=LEVEL_WARNING){
            printf("%s(第%d行):编译警告:%s!\n",filename,line_num,buf);
        }
        else{
            printf("%s(第%d行):编译错误:%s!\n",filename,line_num,buf);
            exit(-1);
        }
    }
    else{
        printf("链接错误:%s!\n",buf);
        exit(-1);
    }
}

void warning(char*fmt, ...){
    /*
        编译警告处理
        fmt:参数输出格式
        ap:可变参数列表
    */
    va_list ap;
    va_start(ap,fmt);
    handleException(STAGE_COMPILE,LEVEL_WARNING,fmt,ap);
    va_end(ap);
}

void error(char*fmt, ...){
    /*
        编译警告处理
        fmt:参数输出格式
        ap:可变参数列表
    */
    va_list ap;
    va_start(ap,fmt);
    handleException(STAGE_COMPILE,LEVEL_ERROR,fmt,ap);
    va_end(ap);
}

void except(char* msg){
    /*
        提示缺少某个语法成分
        msg:缺少的内容
    */
    error("缺少%s",msg);
}

void linkError(char* fmt, ...){
    /*
        编译警告处理
        fmt:参数输出格式
        ap:可变参数列表
    */
    va_list ap;
    va_start(ap,fmt);
    handleException(STAGE_LINK,LEVEL_ERROR,fmt,ap);
    va_end(ap);
}
