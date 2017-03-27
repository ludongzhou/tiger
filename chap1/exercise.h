//
// Created by 周鲁东 on 2017/3/27.
//

#ifndef TIGER_EXERCISE_H
#define TIGER_EXERCISE_H

#include "util.h"

typedef struct tree *T_tree;
struct tree {
    T_tree left;
    String key;
    void *ptr;
    T_tree right;
};

T_tree Tree(T_tree l, string k, void *ptr, T_tree r);
//T_tree insert(string key, T_tree t);
bool member(T_tree t, string k);

// b
T_tree insert(string key, void *binding, T_tree t);
void * lookup(string key, T_tree t);


#endif //TIGER_EXERCISE_H
