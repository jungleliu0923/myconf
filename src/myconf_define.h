/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file myconf_define.h
 * @author liujun05(com@baidu.com)
 * @date 2013/12/16 10:58:44
 * @brief 
 *  
 **/




#ifndef  __MYCONF_DEFINE_H_
#define  __MYCONF_DEFINE_H_


#include <string>
#include <vector>
#include <fstream>
#include "mylog.h"
using namespace std;

#define MAX_FILE_NAME_LEN 1024
#define MAX_KEY_LEN 128
#define MAX_VALUE_LEN 10240

#define ERROR_NOT_VALID 1
#define ERROR_NO_KEY 2
#define ERROR_QUOTO_NOT_CLOSE 3
#define ERROR_NOT_INT 4

#define SYMBOL_SEP ':'
#define SYMBOL_TAB '\t'
#define SYMBOL_SPACE ' '
#define SYMBOL_EOF '\0'
#define SYMBOL_QUOTO '"'
#define SYMBOL_POS '-'

#define FIND_NONE string::npos
#define MY_CONF_INS vector<my_conf>

#ifndef UNSIGNED_LONG
#define uint32 unsigned int
#endif

#ifndef UNSIGNED_LONG_LONG
#define uint64 unsigned long long
#endif

typedef struct _my_conf_t
{
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} my_conf_t, *my_conf;


#endif  //__MYCONF_DEFINE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
