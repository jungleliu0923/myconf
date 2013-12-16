/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file sample.cpp
 * @author liujun05(com@baidu.com)
 * @date 2013/12/16 17:40:06
 * @brief 
 *  
 **/

#include "mylog.h"
#include "myconf.h"
#include <iostream>
using namespace std;


int main()
{
    my_log_init("./log", "sample.log", "sample.log.wf", 16);
    MY_LOG_DEBUG("main begin");

    MY_CONF_INS* my_ins = my_conf_init("./conf", "sample.conf");
    if( my_ins == NULL)
    {
        MY_LOG_FATAL("file is not exist or not vaild");
        return -1;
    }

    bool ret;
    //get int
    int int_a1;
    ret = MY_CONF_GET_INT32("int_a", my_ins, int_a1);
    if(ret == true)
    {
        cout << "int_a1 is " << int_a1 << endl;
    }
    else
    {
        cout << "get int_a1 fail";
    }

    //get uint32
    uint32 uint32_b1;
    ret = MY_CONF_GET_UINT32("int_b", my_ins, uint32_b1);
    cout << "uint32_b1 is " << uint32_b1 << endl;

    //get int 缺省值
    uint32 int_a2;
    ret = MY_CONF_GET_UINT32_DEFAULT("int_a_default", my_ins, int_a2, 100);
    cout << "int_a_default " << int_a2 << endl;

    char string_noraml[1024];
    ret = MY_CONF_GET_STR("string_noraml", my_ins, string_noraml);
    cout << "string_noraml is " <<  string_noraml << endl;

    char string_quoto[1024];
    ret = MY_CONF_GET_STR("string_quoto", my_ins, string_quoto);
    cout << "string_quoto is " <<  string_quoto << endl;

    my_conf_close(my_ins);
    MY_LOG_DEBUG("main end");

}



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
