//
// Created by 周鲁东 on 2017/3/27.
//
#include "exercise.h"

T_tree Tree(T_tree l, string k, void *ptr, T_tree r) {
    T_tree t = checked_malloc(sizeof(*t));
    t->left = l;
    t->key = k;
    t->ptr = ptr;
    t->right = r;
    return t;
}

//T_tree insert(string key, T_tree t) {
//    if (t == NULL)
//        return Tree(NULL, key, NULL);
//    else if (strcmp(key, t->key) < 0)
//        return Tree(insert(key, t->left), t->key, t->right);
//    else if (strcmp(key, t->key) > 0)
//        return Tree(t->left, t->key, insert(key, t->right));
//    else
//        return Tree(t->left, key, t->right);
//}

bool member(T_tree t, string k) {
    if (t == NULL) {
        return FALSE;
    } else if (strcmp(k, t->key) < 0) {
        return member(t->left, k);
    } else if (strcmp(k, t->key) > 0) {
        return member(t->right, k);
    } else {
        return TRUE;
    }
}

// b
T_tree insert(string key, void *binding, T_tree t) {
    if (t == NULL) {
        return Tree(NULL, key, binding, NULL);
    } else if (strcmp(key, t->key) < 0) {
        return Tree(insert(key, binding, t->left), t->key, t->right);
    } else if (strcmp(key, t->key) > 0) {
        return Tree(t->left, t->key, insert(key, binding, t->right));
    } else {
        return Tree(t->left, key, binding, t->right);
    }
}

void *lookup(string key, T_tree t) {
    if (t == NULL) {
        return NULL;
    } else if (strcmp(key, t->key) < 0) {
        return lookup(key, t->left);
    } else if (strcmp(key, t->key) > 0) {
        return lookup(t->right, key);
    } else {
        return t->ptr;
    }
}