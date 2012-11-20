#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    void *label;
    struct node *left;
    struct node *right;
}           node_t;

node_t *    node_t_new(void *);
void        node_t_delete(node_t *);
node_t *    node_t_insert(node_t *, void *, int (*)(void *, void *));
void        node_t_preorder(node_t *, void (*)(void *));
void        node_t_inorder(node_t *, void (*)(void *));
void        node_t_postorder(node_t *, void (*)(void *));
int         node_t_height(node_t *);
node_t *    node_t_remove(node_t *, void *, int (*)(void *, void *));
node_t *    node_t_rotleft(node_t *);
node_t *    node_t_rotright(node_t *);
node_t *    node_t_drotleft(node_t *);
node_t *    node_t_drotright(node_t *);
node_t *    node_t_balance(node_t *);

typedef struct tree {
    struct node *root;
    size_t length;
}           tree_t;

tree_t *    tree_t_new();
void        tree_t_delete(tree_t *);

void        tree_t_insert(tree_t *, void *, int (*)(void *, void *));
void        tree_t_preorder(tree_t *, void (*)(void *));
void        tree_t_inorder(tree_t *, void (*)(void *));
void        tree_t_postorder(tree_t *, void (*)(void *));
int         tree_t_height(tree_t *);
void        tree_t_remove(tree_t *, void *, int (*)(void *, void *));
void        tree_t_balance(tree_t *);

void
action(void *label)
{
    printf("%d\n", *(int *)label);
}

int
compare(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

int
main()
{
    int *i;
    tree_t *tree = tree_t_new();

    i = (int *)malloc(sizeof(int));
    *i = 15;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 3;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 17;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 8;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 7;
    tree_t_insert(tree, i, compare);

/*
    i = (int *)malloc(sizeof(int));
    *i = 40;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 20;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 44;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 10;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 38;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 42;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 46;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 2;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 15;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 35;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 39;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 41;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 43;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 45;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 47;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 33;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 36;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 32;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 34;
    tree_t_insert(tree, i, compare);

    i = (int *)malloc(sizeof(int));
    *i = 37;
    tree_t_insert(tree, i, compare);
    */

    puts("preorder()");
    tree_t_preorder(tree, action);
    puts("inorder()");
    tree_t_inorder(tree, action);
    puts("postorder()");
    tree_t_postorder(tree, action);

    printf("Altura: %d\n", tree_t_height(tree));

    puts("inorder()");
    tree_t_inorder(tree, action);

    puts("remove(20)");
    i = (int *)malloc(sizeof(int));
    *i = 20;
    tree_t_remove(tree, i, compare);

    puts("inorder()");
    tree_t_inorder(tree, action);

    puts("preorder()");
    tree_t_preorder(tree, action);
    puts("balance()");
    tree_t_balance(tree);
    puts("preorder()");
    tree_t_preorder(tree, action);

    return 0;
}

node_t *
node_t_new(void *label)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if(NULL != node) {
        node->label = label;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void
node_t_delete(node_t *node)
{
}

node_t *
node_t_insert(node_t *node, void *label, int (*compare)(void *, void *))
{
    if(NULL == node) {
        node = node_t_new(label);
    } else {
        if(0 < compare(node->label, label)) {
            node->left = node_t_insert(node->left, label, compare);
        } else {
            node->right = node_t_insert(node->right, label, compare);
        }
    }
    return node;
}

void
node_t_preorder(node_t *node, void (*action)(void *))
{
    if(NULL != node) {
        action(node->label);
        node_t_preorder(node->left, action);
        node_t_preorder(node->right, action);
    }
}

void
node_t_inorder(node_t *node, void (*action)(void *))
{
    if(NULL != node) {
        node_t_inorder(node->left, action);
        action(node->label);
        node_t_inorder(node->right, action);
    }
}

void
node_t_postorder(node_t *node, void (*action)(void *))
{
    if(NULL != node) {
        node_t_postorder(node->left, action);
        node_t_postorder(node->right, action);
        action(node->label);
    }
}

int
node_t_height(node_t *node)
{
    if(NULL != node) {
        int a = node_t_height(node->left);
        int b = node_t_height(node->right);
        if(a > b) {
            return a + 1;
        } else {
            return b + 1;
        }
    } else {
        return -1;
    }
}

node_t *
node_t_search(node_t *node, void *label, int (*compare)(void *, void *))
{
    if(NULL != node) {
        if(0 == compare(node->left->label, label) 
            || 0 == compare(node->right->label, label)) {
            return node;
        } else {
            if(0 < compare(node->label, label)) {
                return node_t_search(node->left, label, compare);
            } else {
                return node_t_search(node->right, label, compare);
            }
        }
    }
    return node;
}

node_t *
node_t_leftmost(node_t *node)
{
    if(NULL != node && NULL != node->left) {
        if(NULL == node->left->left) {
            return node;
        } else {
            return node_t_leftmost(node->left);
        }
    } else {
        return node;
    }
}

node_t *
node_t_rightmost(node_t *node)
{
    if(NULL != node && NULL != node->right) {
        if(NULL == node->right->right) {
            return node;
        } else {
            return node_t_rightmost(node->right);
        }
    } else {
        return node;
    }
}

node_t *
node_t_remove(node_t *node, void *label, int (*compare)(void *, void *))
{
    if(NULL != node) {
        if(NULL != node->left && 0 == compare(node->left->label, label)) {
            node_t *b, *c, *d;
            b = node->left;
            c = node_t_leftmost(b->right);
            d = c->left;
            if(NULL == d) {
                c->left = b->left;
                node->left = c;
            } else {
                c->left = d->right;
                d->left = b->left;
                d->right = b->right;
                node->left = d;
            }
        } else if(NULL != node->right && 0 == compare(node->right->label, label)) {
            node_t *b, *c, *d;
            b = node->right;
            c = node_t_rightmost(b->left);
            d = c->right;
            if(NULL == d) {
                c->right = b->right;
                node->right = c;
            } else {
                c->right = d->left;
                d->left = b->right;
                d->right = b->right;
                node->right = d;
            }
        } else {
            if(0 < compare(node->label, label)) {
                node->left = node_t_remove(node->left, label, compare);
            } else {
                node->right = node_t_remove(node->right, label, compare);
            }
        }
    }
    return node;
}

node_t *
node_t_rotleft(node_t *node)
{
    node_t *b, *c;
    b = node->right;
    if(NULL != b) {
        c = b->left;
        b->left= node;
    }
    node->right = c;
    return b;
}

node_t *
node_t_rotright(node_t *node)
{
    node_t *b, *c;
    b = node->left;
    if(NULL != b) {
        c = b->right;
        b->right= node;
    }
    node->left = c;
    return b;
}

node_t *
node_t_drotleft(node_t *node)
{
    node->left = node_t_rotleft(node->left);
    return node_t_rotright(node);
}

node_t *
node_t_drotright(node_t *node)
{
    node->right = node_t_rotright(node->right);
    return node_t_rotleft(node);
}

node_t *
node_t_balance(node_t *node)
{
    if(NULL != node) {
        node->left = node_t_balance(node->left);
        node->right = node_t_balance(node->right);
        int a, b;
        a = node_t_height(node->left);
        b = node_t_height(node->right);
        if(1 < (a - b) && NULL != node->left) {
            int c, d;
            c = node_t_height(node->left->left);
            d = node_t_height(node->left->right);
            if(c < d) {
                node = node_t_rotright(node);
            } else {
                node = node_t_drotleft(node);
            }
        } else if (1 < (b - a) && NULL != node->right) {
            int c, d;
            c = node_t_height(node->right->left);
            d = node_t_height(node->right->right);
            if(c < d) {
                node = node_t_rotleft(node);
            } else {
                node = node_t_drotright(node);
            }
        } 
        /*node->left = node_t_balance(node->left);
        node->right = node_t_balance(node->right);*/
    }
    return node;
}

tree_t *
tree_t_new()
{
    tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
    if(NULL != tree) {
        tree->root = NULL;
        tree->length = 0;
    }
    return tree;
}

void
tree_t_delete(tree_t *tree)
{
}

void
tree_t_insert(tree_t *tree, void *label, int (*compare)(void *, void *))
{
    tree->root = node_t_insert(tree->root, label, compare);
}

void
tree_t_preorder(tree_t *tree, void (*action)(void *))
{
    node_t_preorder(tree->root, action);
}

void
tree_t_inorder(tree_t *tree, void (*action)(void *))
{
    node_t_inorder(tree->root, action);
}

void
tree_t_postorder(tree_t *tree, void (*action)(void *))
{
    node_t_postorder(tree->root, action);
}

int
tree_t_height(tree_t *tree)
{
    return node_t_height(tree->root);
}

void
tree_t_remove(tree_t *tree, void *label, int (*compare)(void *, void *))
{
    tree->root = node_t_remove(tree->root, label, compare);
}

void
tree_t_balance(tree_t *tree)
{
    tree->root = node_t_balance(tree->root);
}
