#include <stdio.h>
#include "slp.h"
#include "prog1.h"

int maxargs(A_stm);
int max ( int a, int b);
int count_exp_list(A_expList);
int max_exp_list(A_expList);
int max_exp(A_exp);

int main() {
    A_stm statement = prog();
    printf("the maximum number of arguments of any print statement is: %d\n", maxargs(statement));
}

int maxargs(A_stm statement) {
    if (statement->kind == A_printStm) {
        A_expList exp_list = statement->u.print.exps;
        return max(count_exp_list(exp_list), max_exp_list(exp_list));
    }
    else if (statement->kind == A_assignStm) {
        return max_exp(statement->u.assign.exp);
    }
    else if (statement->kind == A_compoundStm){
        return max(maxargs(statement->u.compound.stm1), maxargs(statement->u.compound.stm2));
    }
    else {
        return 0;
    }
}

int max ( int a, int b )
{
    return a > b ? a : b;
}

int count_exp_list(A_expList exp_list) {
    if (exp_list->kind == A_lastExpList) {
        return 1;
    }
    else {
        return 1 + count_exp_list(exp_list->u.pair.tail);
    }
}

int max_exp_list(A_expList exp_list) {
    if (exp_list->kind == A_lastExpList) {
        return max_exp(exp_list->u.last);
    }
    else {
        return max(max_exp(exp_list->u.pair.head), max_exp_list(exp_list->u.pair.tail));
    }
}

int max_exp(A_exp exp) {
    if (exp->kind == A_idExp || exp->kind == A_numExp) {
        return 0;
    }
    else if (exp->kind == A_opExp) {
        return max(max_exp(exp->u.op.left), max_exp(exp->u.op.right));
    }
    else {
        return max(maxargs(exp->u.eseq.stm), max_exp(exp->u.eseq.exp));
    }
}
