// File Name: _libev.c
// Author: jiujue
// Created Time: 2019年04月05日 星期五 19时54分08秒
#include "head.h"
#define PATH_OF_404_ "404.html"

void read_cb(struct bufferevent* bufev, void* arg)
{
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<,,Happen read_cb\n");
    char buf[1024] = {0}, method[12] = {0}, path[1024] = {0}, protocol[12] = {0};
    bufferevent_read(bufev,buf,sizeof(buf));
    //printf("-----------------------recv http request :%s\n",buf);
    sscanf(buf,"%s %s %s",method,path,protocol);
    char *file = path+1;
    if(0 == (strcmp(path,"/") ) )
    {
        file = (char*)"./";
    }
    
    int isFile = judge_type_dir_or_nondir(file);
    printf("fffffffff          is %d \n",isFile);
    if(0 == isFile)
    {//is palin file
        printf("send file <name>>%s\n",file);
        send_file(bufev,file);
    }
    if(isFile == 1){//is dir
        printf("send dir <name>>%s\n",file);
        send_html_head(bufev,200,"OK",(char*)"text/html");
        send_dir_asheml(bufev,file,NULL);
    }
    else if(-1 == isFile)
    {//is not found file or directory
        printf("send 404 <name>>%s\n",file);
        send_file(bufev,PATH_OF_404_);
    }

}

void write_cb(struct bufferevent* bufev, void* arg)
{
    struct sockaddr_in *cli = (struct sockaddr_in*)arg;
    char buf[1024] = {0};
    printf("Sent respond to cli,Ip ->%s and Port ->%d\n",
            inet_ntop(AF_INET,&(cli->sin_addr.s_addr), buf,sizeof(buf)), 
            ntohs(cli->sin_port) );
}

void event_cb(struct bufferevent* bufev, short ev, void* arg)
{
    printf("event_cb successful\n");
    if(ev & BEV_EVENT_EOF)
    {
        struct sockaddr_in *cli = (struct sockaddr_in*)arg;
        char buf[1024] = {0};
        printf("Have client disconnect, Ip ->%s and Port ->%d\n",
                inet_ntop(AF_INET,&(cli->sin_addr.s_addr), buf,sizeof(buf)), 
                ntohs(cli->sin_port) );

    }
    if(ev & BEV_EVENT_ERROR )
    {
        printf("******************************** Happy Error******************************\n");
    }
    bufferevent_free(bufev);
}

void listener_cb(struct evconnlistener *listener, 
        evutil_socket_t fd, struct sockaddr* cli, 
        int cli_len, void* arg)
{

    printf("<<<<<<<<<<<<<<<<<<<<,,,,,,,,, listener_cb successful\n");
    struct event_base* base = (struct event_base*)arg;

    struct bufferevent* bufev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bufev, read_cb, write_cb, event_cb,cli);
    bufferevent_enable(bufev,EV_READ);

}


struct evconnlistener* libev_start(struct event_base*base, const char* Ip,int Port)
{

    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(Port);
    inet_pton(AF_INET,Ip,&(ser.sin_addr.s_addr));

    struct evconnlistener* ret =  evconnlistener_new_bind(base, listener_cb, base, 
            LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 128, 
            (struct sockaddr *)&ser, sizeof(ser));

    if(ret == NULL)
    {
        return NULL;
    }

    return ret;
}
