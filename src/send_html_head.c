// File Name: _send_html_head.c
// Author: jiujue
// Created Time: 2019年04月05日 星期五 22时14分29秒

#include "../include/head.h"

int send_html_head(struct bufferevent* bufev, int stat_no, const char* stat_desc, char* type)
{
    char buf[1024] = {0};
    //send status row
    sprintf(buf,"HTTP/1.1 %d %s \r\n",stat_no,stat_desc);
    bufferevent_write(bufev,buf,strlen(buf));
//    printf("send htp head -> status line:%s \n",buf);

    //send message dgrame
    sprintf(buf,"Content-Type: %s; charset=utf-8\r\n",type);
    bufferevent_write(bufev,buf,strlen(buf));
//  printf("send htp head -> grame:%s",buf);

    //send blank row
    bufferevent_write(bufev,"\r\n",2);
//  printf("send htp head -> blank line\n");

        
    return 0;
}
