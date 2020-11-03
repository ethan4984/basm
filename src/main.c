#include <preprocessor.h>
#include <parse.h>
#include <inst.h>

int main(int argc, char *argv[]) {
    pp_t *pp = parse_file(argv[1]);
    parse(pp);
}
