// File Name: _judge_type.c
// Author: jiujue
// Created Time: 2019年04月05日 星期五 20时54分34秒

#include "head.h"

int judge_type_dir_or_nondir(const char* name)
{
    struct stat st;
    int ret = stat(name,&st);
    if(-1 == ret)
    {
        return -1;
    }
    if(S_ISREG(st.st_mode))
    {
        return 0;
    }
    if(S_ISDIR(st.st_mode))
    {
        return 1;
    }
    else
    {
        return 2;
    }

}


#if 0
int main(int argc,char* argv[])
{
    int ret =  judge_type_dir_or_nondir(argv[1]);
    if(ret == 1)
    {
        printf("is dir ");
    }
    if(ret == 0)
    {
        printf("is  file");
    }
    return 0;
}
#endif

