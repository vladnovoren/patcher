#ifndef PATCH_HPP
#define PATCH_HPP

#include "../include/ONEGIN_files.hpp"
#include "../include/barmaley.hpp"
#include <ctype.h>


static const size_t JMP_POS = 3;
static const char JMP_CODE  = 0xeb;

static const size_t OFFSET_POS = 4;
static const char OFFSET       = 21;

static const size_t NOP_POS = 5;
static const char NOP_VAL   = 0x90;

static const size_t RIGHT_HASH = 14590549568906848455u;

static const char *WRONG_FILE_MSG = "You tried to patch wrong file. Aborted.";
static const char *LOSE_MSG       = "You must kill Barmaley and keep cat safe to patch!";
static const char *PATCHED 		  = "Patched successfully!";

static const size_t HASH_P = 257;

size_t CountHash(const Str buf);

bool CheckHash(const Str *file_buf);

int Hack(Str *file_buf);



#endif /* patch.hpp */