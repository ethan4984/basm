#include <preprocessor.h>

char *append_str(char *dest, char *str) {
    dest = realloc(dest, strlen(dest) + strlen(str) + 4);
    strcat(dest, str);
    return dest;
}

char *append_char(char *dest, char c) {
    dest = realloc(dest, strlen(dest) + sizeof(char) + 1);
    strncat(dest, &c, 1);
    return dest;
}

int find_char(char *src, char character) {
    int cnt = 0;
    for(char *ptr = src; *ptr != '\0'; ptr++, cnt++) {
        if(*ptr == character) { 
            return cnt; 
        }
    }
    return -1;
}

char *get_scope(FILE *fp, char *line) {
    int start = find_char(line, '{');
    if(start == -1) {
        find_char_file(fp, line, '{');
        start = find_char(line, '{');
    }

    int brase_cnt = 0;
    char *ret = calloc(1, 1);

    do {
        for(int i = start; i < (int)strlen(line); i++) {
            switch(line[i]) {
                case '{':
                    brase_cnt++;
                    break;
                case '}':
                    brase_cnt--;
                    break;
                default: 
                    if(!brase_cnt)
                        goto ret;
                    ret = append_char(ret, line[i]);
            }
        }
        start = 0;
    } while(fgets(line, 1000, fp)); // assumes line has >= 1000 bytes to its name
ret:
    return ret;
}

int find_char_file(FILE *fp, char *ret, char c) {
    while(fgets(ret, 1000, fp)) {
        if(find_char(ret, c) != -1) {
            return 1;
        }
    }
    return 0;
}

void replace_char(char *src, char c, char replace) {
    char *save = strchr(src, c);
    while(save) {
        *save = replace;
        save = strchr(save, c);
    }
}

void remove_char(char *src, char c) {
    char *str = src, *save = src;
    while(*str) {
        *str = *save++;
        str += (*str != c);
    }
}
