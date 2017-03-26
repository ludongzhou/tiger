#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "slp.h"
#include "prog1.h"

int maxargs(A_stm);

int max(int a, int b);

int count_exp_list(A_expList);

int max_exp_list(A_expList);

int max_exp(A_exp);

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

void print_table(Table_ t);

Table_ Table(string id, int value, struct table *tail) {
    Table_ t = malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;

    print_table(t);

    return t;
}

void interp(A_stm);

Table_ interpStm(A_stm s, Table_ t);

struct IntAndTable interpExp(A_exp e, Table_ t);

Table_ interpExpList(A_expList, Table_);

Table_ update(Table_ t, string key, int value);

int lookup(Table_ t, string key);


int main() {
    A_stm statement = prog();
//    printf("the maximum number of arguments of any print statement is: %d\n", maxargs(statement));
    interp(statement);
}

void print_table(Table_ t) {
    Table_ i = t;
    while (i) {
        printf("%s = %d\n", i->id, i->value);
        i = i->tail;
    }
    printf("--------\n");
}

void interp(A_stm stm) {
    Table_ t = interpStm(stm, NULL);
    print_table(t);
}

Table_ interpStm(A_stm s, Table_ t) {
    if (s->kind == A_compoundStm) {
        t = interpStm(s->u.compound.stm1, t);
        t = interpStm(s->u.compound.stm2, t);
        return t;
    } else if (s->kind == A_assignStm) {
        struct IntAndTable int_and_table = interpExp(s->u.assign.exp, t);
        return update(int_and_table.t, s->u.assign.id, int_and_table.i);
    } else {
        return interpExpList(s->u.print.exps, t);
    }
}

Table_ interpExpList(A_expList exps, Table_ t) {
    if (exps->kind == A_lastExpList) {
        return interpExp(exps->u.last, t).t;
    } else {
        return interpExpList(exps->u.pair.tail, interpExp(exps->u.pair.head, t).t);
    }
}

struct IntAndTable interpExp(A_exp exp, Table_ t) {
    struct IntAndTable int_and_table;

    if (exp->kind == A_idExp) {
        int_and_table.i = lookup(t, exp->u.id);
        int_and_table.t = t;
    } else if (exp->kind == A_numExp) {
        int_and_table.i = exp->u.num;
        int_and_table.t = t;
    } else if (exp->kind == A_opExp) {
        struct IntAndTable int_and_table0 = interpExp(exp->u.op.left, t);
        struct IntAndTable int_and_table1 = interpExp(exp->u.op.right, int_and_table0.t);

        switch (exp->u.op.oper) {
            case A_plus:
                int_and_table.i = int_and_table0.i + int_and_table1.i;
                break;
            case A_minus:
                int_and_table.i = int_and_table0.i - int_and_table1.i;
                break;
            case A_times:
                int_and_table.i = int_and_table0.i * int_and_table1.i;
                break;
            case A_div:
                int_and_table.i = int_and_table0.i / int_and_table1.i;
                break;
        }
        int_and_table.t = int_and_table1.t;
    } else {
        return interpExp(exp->u.eseq.exp, interpStm(exp->u.eseq.stm, t));
    }

    return int_and_table;
}

Table_ update(Table_ t, string key, int value) {
    return Table(key, value, t);
}

int lookup(Table_ t, string key) {
    if (!t) {
        return NULL;
    } else {
        if (strcmp(key, t->id) == 0) {
            return t->value;
        } else {
            return lookup(t->tail, key);
        }
    }
}

int maxargs(A_stm statement) {
    if (statement->kind == A_printStm) {
        A_expList exp_list = statement->u.print.exps;
        return max(count_exp_list(exp_list), max_exp_list(exp_list));
    } else if (statement->kind == A_assignStm) {
        return max_exp(statement->u.assign.exp);
    } else if (statement->kind == A_compoundStm) {
        return max(maxargs(statement->u.compound.stm1), maxargs(statement->u.compound.stm2));
    } else {
        return 0;
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

int count_exp_list(A_expList exp_list) {
    if (exp_list->kind == A_lastExpList) {
        return 1;
    } else {
        return 1 + count_exp_list(exp_list->u.pair.tail);
    }
}

int max_exp_list(A_expList exp_list) {
    if (exp_list->kind == A_lastExpList) {
        return max_exp(exp_list->u.last);
    } else {
        return max(max_exp(exp_list->u.pair.head), max_exp_list(exp_list->u.pair.tail));
    }
}

int max_exp(A_exp exp) {
    if (exp->kind == A_idExp || exp->kind == A_numExp) {
        return 0;
    } else if (exp->kind == A_opExp) {
        return max(max_exp(exp->u.op.left), max_exp(exp->u.op.right));
    } else {
        return max(maxargs(exp->u.eseq.stm), max_exp(exp->u.eseq.exp));
    }
}
