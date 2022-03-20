#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

/*
 * ~ 構造体 ~
 * Vector, Type, Token, Var, Node, Function
 *
 */

/* ベクターの定義 */
typedef struct Vector Vector;
struct Vector
{
    void **body;
    int len;
    int capacity;
};

/* 型の定義 */
typedef enum
{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_PTR,
    TYPE_ARRAY,
} TypeKind;

typedef struct Type Type;
struct Type
{
    TypeKind kind;
    Type *ptr_to;
    int size;
    int array_size;
};

/* トークンの定義 */
typedef enum
{
    TK_NUM = 256, // number
    TK_IDENT,     // ident
    TK_EQ,        // ==
    TK_NE,        // !=
    TK_LE,        // <= 260
    TK_GE,        // >=
    TK_ADD_EQ,    // +=
    TK_SUB_EQ,    // -=
    TK_MUL_EQ,    // *=
    TK_INC,       // ++
    TK_DEC,       // --
    TK_DIV_EQ,    // /= 265
    TK_MOD_EQ,    // %= 
    TK_RETURN,    // return
    TK_IF,        // if
    TK_ELSE,      // else
    TK_FOR,       // for
    TK_WHILE,     // while 
    TK_EOF,       // eof
    TK_TYPE,      // int
    TK_SIZEOF,    // sizeof
    TK_STRING,    // string
    TK_CONTINUE,  // continue
    TK_BREAK,     // break
} TokenKind;

typedef struct Token Token;
struct Token
{
    TokenKind kind; //
    Type *type;     //
    Token *next;    //
    int val;        //
    char *str;      //
    int str_literal_index; //
    int len;        //
};

/* 変数の定義 */
typedef struct Var Var;
struct Var
{
    Var *next;  // 次の変数かNULL
    char *name; // 変数の名前
    int len;    // 名前の長さ
    int offset; // RBPからのオフセット
    Type *type; // 型情報

    bool is_global;
};

/* ノードの定義 */
typedef enum
{
    ND_ADD,      // +
    ND_SUB,      // -
    ND_MUL,      // *
    ND_DIV,      // /
    ND_MOD,      // %
    ND_ASSIGN,   // =
    ND_EQ,       // ==
    ND_NE,       // !=
    ND_LT,       // <
    ND_LE,       // <=
    ND_VAR,      // local var
    ND_NUM,      // num
    ND_RETURN,   // return
    ND_IF,       // if
    ND_ELSE,     // else
    ND_FOR,      // for
    ND_WHILE,    // while
    ND_BLOCK,    // block {}
    ND_CALL,     // call
    ND_ADDR,     // & アドレス
    ND_DEREF,    // * ポインタ
    ND_STRING,   // string literal
    ND_CONTINUE, // continue
    ND_BREAK,    //break
    ND_LOGICALNOT,   // !
} NodeKind;

typedef struct Node Node;
struct Node
{
    NodeKind kind;
    Node *lhs;     // 左辺
    Node *rhs;     // 右辺
    int val;       // ND_NUM ND_STRINGの時に使う
    Var *var;     // kindがND_VARの場合のみ使う
    char *fn_name; //
    char *str_literal; // ND_STRINGのときに使う
    Vector *args;  //
    Vector *stmts; //
    Type *type;    // 型

    // if (cond) then els
    // while (cond) body
    // for (init;cond;inc) body
    Node *cond;
    Node *then;
    Node *els;
    Node *body;
    Node *init;
    Node *inc;
};

/* 関数型の定義 */
typedef struct Function Function;
struct Function
{
    char *name;
    Node *body;
    Var *params;
    Var *locals;
    int stack_size;
};

typedef struct Initializer Initializer;
struct Initializer
{
    int val;
    Vector *el;
    Type *type;
};


// parse.c
void program();

// util.c
int is_alpha(char c);
int is_alnum(char c);
void str_advanve(char **p);
void next_token();
Token *get_nafter_token(int n);
bool startsWith(char *p, char *q);
void error_at(char *loc, char *msg);
void error(char *fmt, ...);
char *my_strndup(const char *s, size_t n);
void swap(void **p, void **q);
void *memory_alloc(size_t size);

// debug.c
void print_node_kind(NodeKind kind);
void print_token_kind(TokenKind kind);
void print_type_kind(TypeKind kind);
void debug_var(Var *var);
void debug_type(Type *ty);
void debug_node(Node *node, char *pos);
void debug_token(Token *t);

// vector.c
Vector *new_vec();
void vec_push(Vector *v, void *elem);
void vec_pushi(Vector *v, int val);
void *vec_pop(Vector *v);
void *vec_last(Vector *v);
bool vec_contains(Vector *v, void *elem);
bool vec_union1(Vector *v, void *elem);

// codegen.c
void codegen();

// token.c
Token *tokenize(char *p);

// type.c
Type *new_type(TypeKind tykind);
Type *new_ptr_type(Type *ptr_to);
Type *new_array_type(Type *ptr_to, int size);
void add_type(Node *node);
int sizeOfType(Type *ty);
int is_numtype(TypeKind kind);
TypeKind large_numtype(Type *t1, Type *t2);

// グローバル変数
Vector *string_literal;
Var *globals;
Token *token;         // tokenは単方向の連結リスト
char *user_input;     // 入力プログラム
char *file_name;
Function *funcs[1000]; // TODO: Vectorに対応する
int label_if_count;   // ifのラベル
int label_loop_count; // forとwhileのラベル