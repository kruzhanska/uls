#include "uls.h"

static void add_to_Parser(char *argv, t_list **Parser, int k);
// static void print_Parser(t_list **Parser);
static void distributor(char *argv, t_list **Parser);

t_list **mx_parsing(int i, int argc, char **argv) {
    t_list **Parser = malloc(5 * sizeof(t_list *));
    
    for (int h = 0; h < 5; h++)
        Parser[h] = NULL;
    if (i == 0)
        Parser[4] = mx_create_node(".");
    else {
        for (; i < argc; i++) {
            distributor(argv[i], Parser);
        }
    }
    // print_Parser(Parser);
    return Parser;
}

static void add_to_Parser(char *argv, t_list **Parser, int k) {
    if (Parser[k] == NULL)
        Parser[k] = mx_create_node(argv);
    else
        mx_push_back(&Parser[k], argv);
}

static void distributor(char *argv, t_list **Parser) {
    DIR *dir = NULL;
    int fd = 0;

    fd = open(argv, O_RDONLY);
    dir = opendir(argv);
    if (!dir) {
        if (errno == ENOENT)
            add_to_Parser(argv, Parser, 1);
        if (fd > 0)
            add_to_Parser(argv, Parser, 2);
        if (errno == EACCES)
            add_to_Parser(argv, Parser, 3);
    }
    else
        add_to_Parser(argv, Parser, 4);
}

// static void print_Parser(t_list **Parser) {
//     for (int i = 0; i < 5; i++) {
//         mx_printstr("Potok ");
//         mx_printint(i);
//         mx_printchar('\n');
//         while (Parser[i] != NULL) {
//             mx_printstr(Parser[i]->data);
//             mx_printchar(' ');
//             Parser[i] = Parser[i]->next;
//         }
//         mx_printchar('\n');
//     }
// }
