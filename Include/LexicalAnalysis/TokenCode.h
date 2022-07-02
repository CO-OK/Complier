enum e_TokenCode{
    /*运算符及分隔符*/
    TK_PLUS, //+
    TK_MINUS, //-
    TK_STAR, //*
    TK_DIVIDE, ///
    TK_MOD, //%
    TK_EQ, //==
    TK_NEQ, //!=
    TK_LT, //<
    TK_LEQ, //<=
    TK_GT, //>
    TK_GEQ, //>=
    TK_ASSIGN, //=
    TK_POINTSTO, //->
    TK_DOT, //.
    TK_AND, //&
    TK_OPENPA, //(
    TK_CLOSEPA, //)
    TK_OPENBR, //[
    TK_CLOSEBR, //]
    TK_BEGIN, // {
    TK_END, // }
    TK_SEMICOLON, // ;
    TK_COMMA, // ,
    TK_ELLIPSIS, // ...
    TK_EOF, 

    /*常量*/
    TK_CINT, //int
    TK_CCHAR, //char
    TK_CSTR, //string

    /*关键字*/
    KW_CHAR,
    KW_SHORT,
    KW_INT,
    KW_VOID,
    KW_STRUCT,
    KW_IF,
    KW_ELSE,
    KW_FOR,
    KW_CONTINUE,
    KW_BREAK,
    KW_RETURN,
    KW_SIZEOF,

    KW_ALIGN, // __align
    KW_CDECL, // __cdecl
    KW_STDCALL, // __stdcall

    /*标识符*/
    TK_IDEENT
};