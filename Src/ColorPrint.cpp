#include<ColorPrint.h>
#include<stdio.h>
static char* color[]={
    "\e[0m",
    "\e[0;30m",
    "\e[1;30m",
    "\e[0;31m",
    "\e[0;32m",
    "\e[1;32m",
    "\e[0;33m",
    "\e[1;33m",
    "\e[0;34m",
    "\e[1;34m",
    "\e[0;35m",
    "\e[1;35m",
    "\e[0;36m",
    "\e[1;36m",
    "\e[0;37m",
    "\e[1;37m"
};



void colorPrint(char* str,Color c){
    /**/
    printf("%s",color[c]);
    printf("%s",str);
    printf("%s",color[Color::NONE]);
}