#ifndef ONEGIN_STRUCTS_HPP
#define ONEGIN_STRUCTS_HPP


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


struct Str {
  char   *c_str;
  size_t    len;
};

struct StrArr {
  Str      *arr;
  size_t n_strs;
  size_t   size;
};


const Str    EMPTY_STR     = {};

const StrArr EMPTY_STR_ARR = {};


Str    AllocStr(const size_t len);

void   DestructStr(Str *str_p);

StrArr AllocStrArr(const size_t n_strs);

void   DestructStrArr(StrArr *str_arr);


#endif /* ONEGIN_structs.hpp */
