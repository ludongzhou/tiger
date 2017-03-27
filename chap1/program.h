//
// Created by 周鲁东 on 2017/3/27.
//

#ifndef TIGER_PROGRAM_H
#define TIGER_PROGRAM_H

// max print arguments
int maxargs(A_stm);
int max(int a, int b);
int max_exp_list(A_expList);
int max_exp(A_exp);
int count_exp_list(A_expList);

// interpret
typedef struct table *Table_;
struct table {
    string id;
    int value;
    Table_ tail;
};

struct IntAndTable {
    int i;
    Table_ t;
};

Table_ Table(string id, int value, struct table *tail);
void interp(A_stm);
Table_ interpStm(A_stm s, Table_ t);
struct IntAndTable interpExp(A_exp e, Table_ t);
Table_ interpExpList(A_expList, Table_);

Table_ update(Table_ t, string key, int value);
int lookup(Table_ t, string key);
void print_table(Table_ t);

#endif //TIGER_PROGRAM_H
