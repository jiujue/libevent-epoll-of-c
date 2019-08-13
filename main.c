// File Name: main.c
// Author: jiujue
// Created Time: 2019年04月05日 星期五 19时54分48秒

#include "head.h"

int main(int argc, const char* argv[])
{
    if(argc < 4)
    {
        printf("argument not enough\neg:./app Ip Port sourceDir\n");
        exit(1);
    }


    int ret = chdir(argv[3]);
    if(-1 == ret)
    {
        perror("chdir error");
        exit(1);
    }
    else
    {
        printf("chdir successful,to -> %s\n",argv[3]);
    }

    struct event_base* base = event_base_new();

    struct evconnlistener* listen = libev_start(base,argv[1],atoi(argv[2]));

    event_base_dispatch(base);

    evconnlistener_free(listen);
    event_base_free(base);

    return 0 ;
}
