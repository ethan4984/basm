#include <preprocessor.h>

static pp_t *pp_parse(char *file_path);
static void pp_strip(char *src);

static int directive_search(char *src, FILE *fp, pp_t *output); 
static void include_handler(char *src, FILE *fp, pp_t *output);
static void macro_handler(char *src, FILE *fp);
static void add_macro(macro_t *new_mac);

static macro_t *macros;
static size_t macro_cnt = 0;

pp_t *parse_file(char *file_path) {
    macros = malloc(sizeof(macro_t) * 10); 

    pp_t *ret = pp_parse(file_path);

    pp_strip(ret->output);

    return ret;
}

static pp_t *pp_parse(char *file_path) {
    FILE *f = fopen(file_path, "r"); 
    if(!f) {
        printf("unable to open file %s\n", file_path);
        exit(0);
    }

    pp_t *pp = malloc(sizeof(pp_t));
    *pp = (pp_t) { calloc(1, 1), 0, malloc(sizeof(label_t)) };

    char line[1000];  
    while(fgets(line, 1000, f)) { // parse directives and also strip down each line
        if(directive_search(line, f, pp)) 
            continue;

        pp->output = append_str(pp->output, line); 
    }

    fclose(f);

    return pp;
}

static void pp_strip(char *src) {
    remove_char(src, '\n');
    replace_char(src, ',', ' ');
}

static int directive_search(char *src, FILE *fp, pp_t *output) {
    if(*src != '#') {
        return 0; 
    }

    if(strncmp(src + 1, "inc", 3) == 0) { // + 1 to skip '#'
        include_handler(src + 4, fp, output); // + 4 to skip over the declaration
    } else if(strncmp(src + 1, "mac", 3) == 0) {
        macro_handler(src + 4, fp);
    }

    return 1;
}

static void include_handler(char *src, FILE *fp, pp_t *out) {
    char *scope = get_scope(fp, src);

    remove_char(scope, ' ');
    remove_char(scope, '\n');

    char *word, *save = scope;
    while((word = strtok_r(save, ",", &save))) {
        pp_t *pp = pp_parse(word);
        out->output = append_str(out->output, pp->output);
    } 
    free(scope);
}

static void macro_handler(char *src, FILE *fp) {
    char *identifier;
    size_t arg_cnt;

    char *word, *save = malloc(strlen(src)); 
    strcpy(save, src);

    word = strtok_r(save, " ", &save);
    identifier = malloc(strlen(word));
    strcpy(identifier, word);

    word = strtok_r(save, " ", &save);
    arg_cnt = atoi(word);

    char *scope = get_scope(fp, src);

    add_macro(&(macro_t) { arg_cnt, scope, identifier } ); 

    free(scope);
}

static void add_macro(macro_t *new_macro) {
    if(macro_cnt + 1 % 10 == 0) {
        macros = realloc(new_macro, macro_cnt + 10);
    }

    macros[macro_cnt++] = *new_macro;
}
