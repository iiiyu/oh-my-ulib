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


    if(!strcmp(node_x->word, node_y->word))
    {
        node_y->count += 1;
    }
  
    return strcmp(node_x->word, node_y->word);
}


struct tree_root * word2tree(struct tree_root *root, const char *file)
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
    
        while(1)
        {
            if(line[0] == 9){
                line += 1;
            }
            else
            {
                break;
            }
        }
        p = (struct tree_node *) malloc(sizeof(struct tree_node));
        if (p == NULL) {
            ULIB_FATAL("cannot new entry");
            exit(EXIT_FAILURE);
        } 
        //tmpstr = strtok(line, tok);
        //p->word = (char *)malloc(sizeof(char) * strlen(tmpstr));
       // strcpy(p->word, tmpstr);
        p->word = strtok(line, tok);
        p->count = 1;
        if(&p->link != tree_map(&p->link, comp_tree_node, &root))
        {

            //free(p->word);
            free(p);
        }

        while((line = strtok(NULL, tok)))
        {
            p = (struct tree_node *) malloc(sizeof(struct tree_node));
            if (p == NULL) 
            {
                ULIB_FATAL("cannot new entry");
                exit(EXIT_FAILURE);
            } 
            /*
            p->word = (char *)malloc(sizeof(char) * strlen(tmpstr));
            strcpy(p->word, tmpstr);
            */
            p->word = strtok(line, tok);
            p->count = 1;

            if(&p->link != tree_map(&p->link, comp_tree_node, &root))
            {
                //free(p->word);
                free(p);
            }
        }
    }
/*
    tree_for_each_entry(p, root, link) {
        printf("data for current node is %s\n", p->word);
    }
    */
    return root;
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

    root = word2tree(root, argv[1]);


    tree_for_each_entry(node, root, link) {
        printf("data for current node is %s %d\n", node->word, node->count);
    }
    
    
    printf("passed\n");

    return 0;
}