#include "../include/patch.hpp"



size_t CountHash(const Str buf) {
    size_t hash = 0;
    for (size_t i = 0; i < buf.len; i++) {
        hash = hash * HASH_P + buf.c_str[i];
    }

    buf.c_str[0] = 1;

    return hash;
}


bool CheckHash(const Str *file_buf) {
    assert(file_buf);

    size_t hash = CountHash(*file_buf);

    return hash == RIGHT_HASH;
}


int Hack(Str *file_buf) {
    assert(file_buf);
    assert(file_buf->c_str);

    if (!CheckHash(file_buf)) {
        printf("%s\n", WRONG_FILE_MSG);
        return 1;
    }

    Game game = {};
    PlayGame(&game);
    if (game.result == LOSE) {
        printf("%s\n", LOSE_MSG);
        return 1;
    }

    file_buf->c_str[JMP_POS]    = JMP_CODE;
    file_buf->c_str[OFFSET_POS] = OFFSET;
    file_buf->c_str[NOP_POS]    = NOP_VAL;

    return 0;
}


int main (int argc, char **argv) {
    if (argc < 2) {
        printf("no input file.\n");
        return 0;
    }

    if (argc > 2) {
        printf("too many arguments.\n");
        return 0;
    }

    Str file_buf = FileToStr(argv[1], false);
    if (!Hack(&file_buf)) {
        StrToFile("patched.com", file_buf);
        printf("%s\n", PATCHED);
    }

    free(file_buf.c_str);
    return 0;
}
