#include "9cc.h"

void recursion_line_printf(int depth, char *fmt, ...) {
    va_list ap;
    int space_width = 4;
    va_start(ap, fmt);
    fprintf(stderr, "%*s", depth * space_width, "");
    vfprintf(stderr, fmt, ap);
}

void print_node_kind(NodeKind kind)
{
    fprintf(stderr, "nodekind -> ");
    if (kind == ND_ADD)
        fprintf(stderr, "ND_ADD"); // +
    else if (kind == ND_SUB)
        fprintf(stderr, "ND_SUB"); // -
    else if (kind == ND_MUL)
        fprintf(stderr, "ND_MUL"); // *
    else if (kind == ND_DIV)
        fprintf(stderr, "ND_DIV"); // /
    else if (kind == ND_MOD)
        fprintf(stderr, "ND_MOD"); // %
    else if (kind == ND_ASSIGN)
        fprintf(stderr, "ND_ASSIGN"); // =
    else if (kind == ND_EQ)
        fprintf(stderr, "ND_EQ"); // ==
    else if (kind == ND_NE)
        fprintf(stderr, "ND_NE"); // !=
    else if (kind == ND_LT)
        fprintf(stderr, "ND_LT"); // <
    else if (kind == ND_LE)
        fprintf(stderr, "ND_LE"); // <=
    else if (kind == ND_VAR)
        fprintf(stderr, "ND_VAR"); // local var
    else if (kind == ND_NUM)
        fprintf(stderr, "ND_NUM"); // num
    else if (kind == ND_RETURN)
        fprintf(stderr, "ND_RETURN"); // return
    else if (kind == ND_IF)
        fprintf(stderr, "ND_IF"); // if
    else if (kind == ND_ELSE)
        fprintf(stderr, "ND_ELSE"); // else
    else if (kind == ND_FOR)
        fprintf(stderr, "ND_FOR"); // for
    else if (kind == ND_WHILE)
        fprintf(stderr, "ND_WHILE"); // while
    else if (kind == ND_BLOCK)
        fprintf(stderr, "ND_BLOCK"); // block {}
    else if (kind == ND_CALL)
        fprintf(stderr, "ND_CALL"); // call
    else if (kind == ND_ADDR)
        fprintf(stderr, "ND_ADDR"); // & アドレス
    else if (kind == ND_DEREF)
        fprintf(stderr, "ND_DEREF"); // * ポインタ
    else if (kind == ND_STRING)
        fprintf(stderr, "ND_STRING"); // string literal
    else if (kind == ND_CONTINUE)
        fprintf(stderr, "ND_CONTINUE"); // continue
    else if (kind == ND_BREAK)
        fprintf(stderr, "ND_BREAK"); // break
    else
        error("print_node_kind() failure");
    
    fprintf(stderr, "\n");
}

void print_token_kind(TokenKind kind) {
    fprintf(stderr, "tokenkind -> ");
    if (kind == TK_NUM)
        fprintf(stderr, "TK_NUM");
    else if (kind == TK_IDENT)
        fprintf(stderr, "TK_IDENT");
    else if (kind == TK_EQ)
        fprintf(stderr, "TK_EQ");
    else if (kind == TK_NE)
        fprintf(stderr, "TK_NE");
    else if (kind == TK_LE)
        fprintf(stderr, "TK_LE");
    else if (kind == TK_GE)
        fprintf(stderr, "TK_GE");
    else if (kind == TK_ADD_EQ)
        fprintf(stderr, "TK_ADD_EQ");
    else if (kind == TK_SUB_EQ)
        fprintf(stderr, "TK_SUB_EQ");
    else if (kind == TK_MUL_EQ)
        fprintf(stderr, "TK_MUL_EQ");
    else if (kind == TK_INC)
        fprintf(stderr, "TK_INC");
    else if (kind == TK_DEC)
        fprintf(stderr, "TK_DEC");
    else if (kind == TK_DIV_EQ)
        fprintf(stderr, "TK_DIV_EQ");
    else if (kind == TK_MOD_EQ)
        fprintf(stderr, "TK_MOD_EQ");
    else if (kind == TK_RETURN)
        fprintf(stderr, "TK_RETURN");
    else if (kind == TK_IF)
        fprintf(stderr, "TK_IF");
    else if (kind == TK_ELSE)
        fprintf(stderr, "TK_ELSE");
    else if (kind == TK_FOR)
        fprintf(stderr, "TK_FOR");
    else if (kind == TK_WHILE)
        fprintf(stderr, "TK_WHILE");
    else if (kind == TK_EOF)
        fprintf(stderr, "TK_EOF");
    else if (kind == TK_TYPE)
        fprintf(stderr, "TK_TYPE");
    else if (kind == TK_SIZEOF)
        fprintf(stderr, "TK_SIZEOF");
    else if (kind == TK_STRING)
        fprintf(stderr, "TK_STRING");
    else if (kind == TK_CONTINUE)
        fprintf(stderr, "TK_CONTINUE");
    else if (kind == TK_BREAK)
        fprintf(stderr, "TK_BREAK");
    else
        error("print_token_kind() failure");
    
    fprintf(stderr, "\n");
}

void print_type_kind(TypeKind kind) {
    fprintf(stderr, "tokenkind -> ");
    if (kind == TYPE_CHAR)
        fprintf(stderr, "TYPE_CHAR");
    else if (kind == TYPE_INT)
        fprintf(stderr, "TYPE_INT");
    else if (kind == TYPE_PTR)
        fprintf(stderr, "TYPE_PTR");
    else if (kind == TYPE_ARRAY)
        fprintf(stderr, "TYPE_ARRAY");
    else if (kind == TYPE_VOID) {
        fprintf(stderr, "TYPE_VOID");
    }
    else
        error("print_type_kind() failure: unexpected type %d", kind);
    
    fprintf(stderr, "\n");
}

void debug_node(Node *node, char *pos, int depth)
{
    
    recursion_line_printf(depth, "[%s]\n", pos);

    if (node == NULL)
    {  
        recursion_line_printf(depth, "node -> NULL\n");
        return;
    }

    recursion_line_printf(depth, "");
    print_node_kind(node->kind);
    puts("");

    debug_node(node->lhs, "lhs", depth+1);
    debug_node(node->rhs, "rhs", depth+1);
}

void debug_var(Var *var)
{
    if (var == NULL)
    {
        fprintf(stderr, "var -> NULL\n");
        return;
    }

    fprintf(stderr, "name -> %s\n", var->name);
    fprintf(stderr, "len -> %d\n", var->len);
    fprintf(stderr, "offset -> %d\n", var->offset);

    debug_type(var->type, 0);
}

void debug_type(Type *ty, int depth)
{
    if (ty == NULL)
    {
        recursion_line_printf(depth, "type -> NULL\n");
        return;
    }

    recursion_line_printf(depth, "");
    print_type_kind(ty->kind);
    puts("");
    recursion_line_printf(depth, "size -> %d\n", ty->size);
    recursion_line_printf(depth, "array_size -> %d\n", ty->array_size);

    debug_type(ty->ptr_to, depth+1);
}

void debug_token(Token *t) {
    if (t == NULL)
    {
        fprintf(stderr, "token -> NULL\n");
        return;
    }

    print_token_kind(t->kind);
    debug_type(t->type, 0);
    fprintf(stderr, "val -> %d\n", t->val);
    fprintf(stderr, "str -> %s\n", t->str);
    fprintf(stderr, "str_literal_index -> %d\n", t->str_literal_index);
    fprintf(stderr, "len; -> %d\n", t->len);
}