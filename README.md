myconf是一个可以方便读取key-value配置的C/C++库。<br>
1 规则如下 <br>
1)、配置为 key : value 格式 <br>
2)、可以支持读取int(正负数), unsigend int, char *, 支持默认缺省值。<br>
3)、string如果有特殊字符（如空格等）需要加上""(如"你 好");<br>
4)、使用完必须调用关闭日志文件句柄，否则有内存泄漏。<br>
5)、需要使用[mylog](http://www.oschina.net/p/mylog)编译依赖, 编译主要修改Makefile置顶工作目录WORKROOT，然后通过makefile.env指定MYLOG、MYCONF的路径<br>

2 API<br>
1) 初始化日志句柄
```c
MY_CONF_INS* my_conf_init(const char* file_path, const char* file_name);
```
file_path: 配置目录<br>
file_name: 配置文件<br>

2) 获得int
```c
MY_CONF_GET_INT32(key, confs, input_value)
```
key ：获得key<br>
confs: 配置文件句柄<br>
input_value : 配置返回的结果引用<br>
注意：成功返回true,否则返回false<br>

3) 缺省获得int
```c
MY_CONF_GET_INT32_DEFAULT(key, confs, input_value, default_value)
```
key ：获得key<br>
confs: 配置文件句柄<br>
input_value : 配置返回的结果引用<br>
default_value :如果没有结果，返回default_value<br>
注意：成功返回true,否则返回false<br>

4) 获得unsigned int
```c
MY_CONF_GET_UINT32(key, confs, input_value)
```
key ：获得key<br>
confs: 配置文件句柄<br>
input_value : 配置返回的结果引用<br>
注意：成功返回true,否则返回false<br>

5) 缺省获得unsigned int 
```c
MY_CONF_GET_INT32_DEFAULT(key, confs, input_value, default_value)
```
key ：获得key<br>
confs: 配置文件句柄<br>
input_value : 配置返回的结果引用<br>
default_value :如果没有结果，返回default_value<br>
注意：成功返回true,否则返回false<br>

6) 获得string
```c
MY_CONF_GET_STR(key, confs, input_str)
```
key ：获得key<br>
confs: 配置文件句柄<br>
input_str : 配置返回的结果引用<br>
注意：成功返回true,否则返回false, input_str必须申请初始化大小<br>

7) 缺省获得string
```c
MY_CONF_GET_STR_DEFAULT(key, confs, input_str, default_str)
```
key ：获得key<br>
confs: 配置文件句柄<br>
input_str : 配置返回的结果引用<br>
default_str : 如果没有结果返回缺省值<br>
注意：成功返回true,否则返回false, input_str必须申请初始化大小<br>

3 示例
1) 代码
```c
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
    return 0;
}
```
b) 运行结果<br>
![终端结果](http://hiphotos.baidu.com/lvpics/pic/item/960a304e251f95ca40f782c1cb177f3e67095242.jpg)
![日志](http://hiphotos.baidu.com/lvpics/pic/item/5bafa40f4bfbfbed673b26087af0f736afc31f62.jpg)
