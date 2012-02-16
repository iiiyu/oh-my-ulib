#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ulib/tree.h>
#include <ulib/log.h>
#include <ulib/common.h> // generic_compare()



struct tree_node {
    struct tree_root link;
    char *word;
    int count;
};



int comp_tree_node(const void *x, const void *y)
{

    struct tree_node *node_x = tree_entry(x, struct tree_node, link);
    struct tree_node *node_y = tree_entry(y, struct tree_node, link);
  
    return strcmp(node_x->word, node_y->word);
}


void word2tree(struct tree_root *root, const char *file)
{
    FILE *fp;
    struct tree_node *p;
    struct tree_root *q;
    char *line = NULL;
    const char *tok = " ~!@#$\\%%^&*()-=_+;:\'\",.<>/?{}[]";
    char *tmpstr = NULL;
    size_t n;
    int nl = 0;

    fp = fopen(file, "r");
    if (fp == NULL) {
        ULIB_FATAL("cannot open %s", file);
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &n, fp) > 0)
    {
        p = (struct tree_node *) malloc(sizeof(struct tree_node));
        if (p == NULL) {
            ULIB_FATAL("cannot new entry");
            exit(EXIT_FAILURE);
        } 
        tmpstr = strtok(line, tok);
        p->word = (char *)malloc(sizeof(char) * strlen(tmpstr));
        strcpy(p->word, tmpstr);
        p->count = 0;
        if(&p->link != tree_map(&p->link, comp_tree_node, &root))
        {
            
        }

        while((tmpstr = strtok(NULL, tok)))
        {
            p = (struct tree_node *) malloc(sizeof(struct tree_node));
            if (p == NULL) 
            {
                ULIB_FATAL("cannot new entry");
                exit(EXIT_FAILURE);
            } 
            p->word = (char *)malloc(sizeof(char) * strlen(tmpstr));
            strcpy(p->word, tmpstr);
            p->count = 0;
            if(&p->link != tree_map(&p->link, comp_tree_node, &root))
            {
            
            }
        }
    }
/*
    tree_for_each_entry(p, root, link) {
        printf("data for current node is %s\n", p->word);
    }
    */
}


int main(int argc, char const *argv[])
{
    struct tree_root *root = 0; 
    struct tree_node *node;
    struct tree_node *tmp;

    if (argc != 2) {
        ULIB_FATAL("usage: %s file", argv[0]);
        return -1;
    }

    word2tree(root, argv[1]);
/*
    node = (struct tree_node *)malloc(sizeof(struct tree_node));
    //node->word = (char *)malloc(sizeof(char)*1024);
    node->count = 1;
    node->word = "1";

    tree_map(&node->link, comp_tree_node, &root);

    node = (struct tree_node *)malloc(sizeof(struct tree_node));
    //node->word = (char *)malloc(sizeof(char)*1024);
    node->count = 1;
    node->word = "2";

    tree_map(&node->link, comp_tree_node, &root);
    

    node = (struct tree_node *)malloc(sizeof(struct tree_node));
    //node->word = (char *)malloc(sizeof(char)*1024);
    node->count = 1;
    node->word = "3";

    tree_map(&node->link, comp_tree_node, &root);
    

    node = (struct tree_node *)malloc(sizeof(struct tree_node));
    //node->word = (char *)malloc(sizeof(char)*1024);
    node->count = 1;
    node->word = "4";

    tree_map(&node->link, comp_tree_node, &root);
    

    node = (struct tree_node *)malloc(sizeof(struct tree_node));
    //node->word = (char *)malloc(sizeof(char)*1024);
    node->count = 1;
    node->word = "5";

    tree_map(&node->link, comp_tree_node, &root);
    
*/



    tree_for_each_entry(node, root, link) {
        printf("data for current node is %s\n", node->word);
    }
    
    
    printf("passed\n");

    return 0;
}