// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef NOTE_FACTORY_H
#define NOTE_FACTORY_H



#define NOTE_DEFAULT_CODE 0
#define NOTE_WRITABLEARRAY_CODE 1
#define NOTE_WRITABLELOGINNOTE_CODE 11



#include "writable.h"
#include "writablearray.h"
#include "writableloginnote.h"



Writable* factory(uint16_t code);



#endif