/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file myconf.h
 * @author liujun05(com@baidu.com)
 * @date 2013/12/16 10:55:07
 * @brief 
 *  
 **/




#ifndef  __MYCONF_H_
#define  __MYCONF_H_

#include "myconf_define.h"

/*
 * @author liujun05(com@baidu.com)
 * @brief 根据配置文件名初始化
 *
 */
MY_CONF_INS* my_conf_init(const char* file_path, const char* file_name);

/*
 * @author liujun05(com@baidu.com)
 * @brief 根据一行内容解析出key-value
 */
my_conf my_conf_get_conf_key_value_by_str(string str);

/*
 * @author liujun05(com@baidu.com)
 * @brief 根据key获得value
 */
char* my_conf_get_conf_by_key(char* key, MY_CONF_INS* confs);

/*
 * @author liujun05(com@baidu.com)
 * @brief 据key获得int信息
 */
bool my_conf_get_int32(char* key, MY_CONF_INS* conf, int& input_value, bool user_int,  const int default_value);

/*
 * @author liujun05(com@baidu.com)
 * @brief 据key获得int信息
 */
bool my_conf_get_uint32(char* key, MY_CONF_INS* conf, uint32& input_value, bool user_int,  const uint32 default_value);

/*
 * @author liujun05(com@baidu.com)
 * @breif 根据key获得str信息
 *
 */
bool my_conf_get_string(char* key, MY_CONF_INS* conf, char* input_str, bool use_default,  const char* default_str);

/*
 * @author liujun05(com@baidu.com)
 * @breif 关闭配置
 */
bool my_conf_close(MY_CONF_INS* confs);

/*
 * @author liujun05(com@baidu.com)
 * @breif trim string
 */
string trim(string str);

#define MY_CONF_GET_INT32(key, confs, input_value) \
        my_conf_get_int32(key, confs, input_value, false, 0)

#define MY_CONF_GET_INT32_DEFAULT(key, confs, input_value, default_value) \
        my_conf_get_int32(key, confs, input_value, true, default_value)

#define MY_CONF_GET_UINT32(key, confs, input_value) \
        my_conf_get_uint32(key, confs, input_value, false, 0)

#define MY_CONF_GET_UINT32_DEFAULT(key, confs, input_value, default_value) \
        my_conf_get_uint32(key, confs, input_value, true, default_value)

#define MY_CONF_GET_STR(key, confs, input_str) \
        my_conf_get_string(key, confs, input_str, false, NULL)

#define MY_CONF_GET_STR_DEFAULT(key, confs, input_str, default_str) \
        my_conf_get_string(key, confs, input_str, true, default_str);

#endif  //__CONF_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
