#ifndef ONEGIN_STRINGS_HPP
#define ONEGIN_STRINGS_HPP


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ONEGIN_structs.hpp"


size_t CntSymb(const char *c_str, const char symb);

size_t CntStrsWithSymb(StrArr strs, const char symb);


char   *SubStrChr(const char *str, const size_t sub_str_len, const char symb);

bool   IsSymbFromStr(const char *c_type_str, const char symb);

size_t SkipSymbols(const char **crg, const char symb);

size_t SkipSymbols(const char **crg, int (*cmp)(int));


#endif /* ONEGIN_strings.hpp */
