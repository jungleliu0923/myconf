/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file myconf.cpp
 * @author liujun05(com@baidu.com)
 * @date 2013/12/16 13:38:50
 * @brief 
 *  
 **/

#include "myconf.h"
#include <sys/types.h>
#include <unistd.h>

/*
 * @author liujun05(com@baidu.com)
 * @brief 根据配置文件名初始化
 */

MY_CONF_INS* my_conf_init(const char* file_path, const char* file_name)
{
    char file_full_name[MAX_FILE_NAME_LEN];
    snprintf(file_full_name, sizeof(file_full_name), "%s/%s", file_path, file_name );
    if( access(file_full_name, F_OK) != 0)
    {
        MY_LOG_FATAL("conf_path[%s]  is not exist", file_full_name);
        return NULL;
    }

    ifstream in(file_full_name);
    string str;
    MY_CONF_INS* confs = new MY_CONF_INS();
    
    my_conf tmp_conf;
    while( getline( in , str ) )
    {
        str = trim(str);
        //如果是空行或者是注释
        if( str.size() == 0 || str[0] == '#')
        {
            continue;
        }
        //获得一行的key-value数据
        tmp_conf = my_conf_get_conf_key_value_by_str(str);
        if( tmp_conf != NULL)
        {
            confs->push_back(tmp_conf);
        }
        else
        {
            my_conf_close(confs);
            return NULL;
        }
    }
    return confs;
}


/*
 * @author liujun05(com@baidu.com)
 * @brief 根据一行内容解析出key-value
 */
my_conf my_conf_get_conf_key_value_by_str(string str)
{
    int pos = str.find( SYMBOL_SEP );
    bool value_read = false;
    int i = 0;
    int j = 0;
    int k = 0;

    //如果不是合法配置直接返回, pos是:位置
    if( str.find( SYMBOL_SEP ) == string::npos || str[0] == SYMBOL_SEP )
    {
        MY_LOG_WARNNING("conf string [%s] is not vaild, errno[%d]", str.c_str() , ERROR_NOT_VALID);
        return NULL;
    }

    my_conf read_conf = new my_conf_t();

    //读取key
    for(i=0; i< pos; i++)
    {
        //如果需要读取
        if(str[i] != SYMBOL_SPACE && str[i] != SYMBOL_TAB && str[i] != SYMBOL_SEP)
        {
            read_conf->key[j++] = str[i];
        }

        //如果是空格，并且已经有数据了，那么就不读了
        if(str[i] == SYMBOL_SPACE || str[i] == SYMBOL_TAB)
        {
            if( strlen(read_conf->key) > 0 )
            {
                read_conf->key[j] = '\0';
                break;
            }
        }

        //如果是分隔符
        if(  str[i] == SYMBOL_SEP)
        {
            //如果key为空，那么就错误
            if(  strlen(read_conf->key) == 0)
            {
                MY_LOG_WARNNING("conf string [%s] is not vaild, errno[%d]", str.c_str() , ERROR_NO_KEY);
                return NULL;
            }
        }
    }
    read_conf->key[j] = '\0';

    //如果没有value值
    if( pos == (int)str.size() )
    {
        read_conf -> value[0]  = '\0';
        return read_conf;
    }

    //读取value
    for(int i=pos+1; i< (int)str.size(); i++)
    {
        if(str[i] == SYMBOL_SPACE || str[i] == SYMBOL_TAB)
        {
            //如果value有值了，说明已经over了
            if(value_read == true)
            {
                if( read_conf -> value[0] == SYMBOL_QUOTO)
                {
                    read_conf -> value[k++] =  str[i];
                }
                else
                {
                    read_conf -> value[k] = '\0';
                    break;
                }
            }
            //这个还没开始读
            else
            {
                continue;
            }
        }
        value_read = true;
        read_conf -> value[k++] = str[i];
    }

    //如果第一个字符是 "
    if(read_conf -> value[0] == SYMBOL_QUOTO)
    {
        //如果不是以"结尾，报错
        if( read_conf -> value[k-1] != SYMBOL_QUOTO )
        {
            MY_LOG_WARNNING("conf string [%s] is not vaild, errno[%d]", str.c_str() , ERROR_QUOTO_NOT_CLOSE);
            return NULL;
        }
        else
        {
            //去掉""
            for(i=0; i<k-2;i++)
            {
                read_conf -> value[i] = read_conf -> value[i+1];
            }
        }
        read_conf -> value[k-2] = '\0';
    } 
    else
    {
        read_conf -> value[k] = '\0';
    }
    return read_conf;
}

/*
 * @author liujun05(com@baidu.com)
 * @brief 根据key获得value
 */
char* my_conf_get_conf_by_key(char* key,MY_CONF_INS* conf)
{
    if(conf->size() == 0)
    {
        return NULL;
    }
    MY_CONF_INS::iterator iter;
    for(iter = conf->begin(); iter != conf->end(); iter++)
    {
        //如果找到这个key
        if( strcmp(key, (*iter)->key) == 0 )
        {
            MY_LOG_DEBUG("key is [%s], value is [%s]", key, (*iter)->value);
            return (*iter)->value;
        }
    }
    return NULL;
}

/*
 * @author liujun05(com@baidu.com)
 * @brief 据key获得int信息
 */
bool my_conf_get_int32(char* key, MY_CONF_INS* conf, int& input_value, bool user_int,  const int default_value)
{
    uint32 i;
    int flag = 1;
    input_value = 0;
    bool read_digit = false;

    char* res_str = my_conf_get_conf_by_key(key, conf);

    if(res_str == NULL)
    {
        if( user_int == true)
        {
            MY_LOG_WARNNING("conf key[%s] is empty , return default value %d", key, default_value);
            input_value = default_value;
            return true;
        }
        else
        {
            MY_LOG_WARNNING("conf key[%s] is empty ", key);
            return false;
        }
    }


    for(i=0; i< strlen(res_str); i++)
    {
        //如果是负数
        if( read_digit == false && res_str[i] == SYMBOL_POS)
        {
            flag = -1 * flag;
            continue;
        }else if(res_str[i] <= '9' && res_str[i] >= '0')
        {
            input_value = input_value * 10 +  res_str[i] - '0';
            read_digit = true;
        }else {
            MY_LOG_WARNNING("get int fail, str is[%s], errno", ERROR_NOT_INT);
            return false;
        }
    }
    input_value = flag * input_value;
    return true;
}


/*
 * @author liujun05(com@baidu.com)
 * @brief 据key获得int信息
 */
bool my_conf_get_uint32(char* key, MY_CONF_INS* conf, uint32& input_value, bool user_int,  const uint32 default_value)
{
    uint32 i;
    input_value = 0;
    bool read_digit = false;

    char* res_str = my_conf_get_conf_by_key(key, conf);
    
    if(res_str == NULL)
    {
        if( user_int == true)
        {
            MY_LOG_WARNNING("conf key[%s] is empty , return default value %u", key, default_value);
            input_value = default_value;
            return true;
        }
        else
        {
            MY_LOG_WARNNING("conf key[%s] is empty ", key);
            return false;
        }
    }

    for(i=0; i< strlen(res_str); i++)
    {
        //如果是数字
        if(res_str[i] <= '9' && res_str[i] >= '0')
        {
            input_value = input_value * 10 +  res_str[i] - '0';
            read_digit = true;
        }else {
            MY_LOG_WARNNING("get int fail, str is[%s], errno", ERROR_NOT_INT);
            return false;
        }
    }
    return true;
}


/*
 * @author liujun05(com@baidu.com)
 * @breif 根据key获得str信息
 */
bool my_conf_get_string(char* key, MY_CONF_INS* conf, char* input_str, bool use_default,  const char* default_str=NULL)
{
    //根据key获得数据
    char* res_str = my_conf_get_conf_by_key(key, conf);
    
    if(res_str == NULL)
    {
        if( use_default == true && default_str != NULL )
        {
            MY_LOG_WARNNING("conf key[%s] is empty , return default value %s", key, default_str);
            strcpy(input_str, default_str);
            return true;
        }
        else
        {
            MY_LOG_WARNNING("conf key[%s] is empty ", key);
            return false;
        }
    }

    try
    {
        strcpy(input_str, res_str);
    }
    catch(...)
    {
        MY_LOG_WARNNING("my_conf_get_string fail, str is [%s]", res_str );
        return false;
    }
    return true;
}

/*
 * @author liujun05(com@baidu.com)
 * @breif 关闭配置
 */
bool my_conf_close(MY_CONF_INS* confs)
{
    uint32 i=0;
    for(i=0; i<confs->size(); i++)
    {
        //释放每一行数据
        if( confs->at(i) != NULL)
        {
            free(confs->at(i));
        }
    }

    confs->clear();

    //释放confs
    if( confs != NULL)
    {
        free(confs);
    }
    return true;
}


/*
 * @author liujun05(com@baidu.com)
 * @breif trim string
 */
string trim(string str)
{
    //左边trim
    if (str.find_first_not_of(" \n\r\t")!=string::npos)
    {
        str = str.substr(str.find_first_not_of(" \n\r\t"));
    }
    //右边trim
    if (str.find_first_not_of(" \n\r\t")!=string::npos)
    {
        str = str.substr(0,str.find_last_not_of(" \n\r\t")+1);
    }
    return str;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
