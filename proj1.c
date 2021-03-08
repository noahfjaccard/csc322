#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

// strings.h is an extension of string.h with some less standardized functions

/*
 * arrange.c
 * author:
 * date:
 * last update:
 *
 */

#define USAGE_MESSAGE "usage: arrange [-v] [-r _to_remove_] _to_add_ "
#define DELIMIT ":"

int verbose_g = 0 ;

struct Node {
        char * word ;
        struct Node * next ;
} ;

struct Node * new_ll( void ) {
        // return a new node to be the list anchor
        struct Node * node = (struct Node *) malloc(sizeof(struct Node)) ;
        memset(node, 0, sizeof(struct Node)) ;
        return node ;
}

void add_ll( struct Node * anchor, char * word ) {
        // given a pointer ot the anchor of the list, and a word, add the word
        // to the list, does not matter where (except don't replace the anchor)

        // ...

        return ;
}

struct Node * find_ll(struct Node * anchor, char * word) {
        // given a pointer to the anchor of the list, and a word, search
        // the list for the word. return the pointer to the with the word, if found,
        // or NULL if not found

        // ...

        return NULL ;
}

void remove_ll( struct Node * anchor, struct Node * node_to_remove ) {
        // given a list anchor, and a pointer to a node in the list (but not the anchor)
        // do pointer surgery to remove the node, and free it.

        // sanity checks
        assert(node_to_remove) ;
        assert(node_to_remove!=anchor) ;

        // ...

        return ;
}

void print_ll( struct Node *anchor ) {
        struct Node * node ;
        node = anchor->next ;
        printf("list-> ") ;
        if (!node) printf("-- list is empty --") ;
        while (node) {
                printf("|%s| ",node->word) ;
                node = node->next ;
        }
        printf("\n") ;
        return ;
}

int main(int argc, char * argv[]) {
        int ch ;
        char * word ;
        struct Node * list_anchor ;
        char * remove_these = "" ;
        char * add_these ;

        while ((ch = getopt(argc, argv, "vr:")) != -1) {
                switch(ch) {
                case 'v':
                        verbose_g++ ;
                        break ;
                case 'r':
                        remove_these = strdup(optarg) ;
                        break ;
                default:
                        printf("%s\n", USAGE_MESSAGE) ;
                        return 0 ;
                }
        }
        argc -= optind; // these are globals defined in the getopt code
        argv += optind;

        if (argc!=1) {
                printf("%s\n", USAGE_MESSAGE) ;
                return 0 ;
        }
        add_these = strdup(argv[0]) ;

        if (verbose_g>1) {
                printf("verbose: %d\nto remove: |%s|\nto add: |%s|\n", verbose_g, remove_these, add_these) ;
        }

        list_anchor = new_ll() ;

        // insertions to process
        word = strtok(add_these,DELIMIT) ;
        while (word) {
                add_ll(list_anchor,word) ;
                if (verbose_g>0) print_ll(list_anchor) ;
                word = strtok(NULL,DELIMIT) ;
        }
        print_ll(list_anchor) ;

        // deletions to process
        if (strlen(remove_these)>0) {
                struct Node * n ;
                word = strtok(remove_these,DELIMIT) ;
                while (word) {
                        n = find_ll(list_anchor,word) ;
                        if (n) remove_ll(list_anchor,n) ;
                        if (verbose_g>0) print_ll(list_anchor) ;
                        word = strtok(NULL,DELIMIT) ;
                }
                print_ll(list_anchor) ;
        }


        return 0 ;
}
