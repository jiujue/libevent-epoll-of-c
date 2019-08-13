// File Name: _send_dir.c
// Author: jiujue
// Created Time: 2019年04月05日 星期五 19时27分18秒

#include "head.h"
#define MAXFORGTML_ 4096


int send_dir_asheml(struct bufferevent *bufev, char *dirname, void* arg)
{
    printf("******************send_dir name is %s\n",dirname);

    char* buf_dir_html = (char *)malloc(MAXFORGTML_); 
    struct dirent **ptr;
    int dir_total_num = scandir(dirname,&ptr,NULL,alphasort);
    
    //html head
    sprintf(buf_dir_html,"<!doctype HTML>\
                                <html>\
                                    <head>\
                                        <title>Curent dir:%s</title>\
                                    </head>\
                                    <body>\
                                        <h1>Curretn Dir Content:%s </h1>\
                                        <table>\
                                            <tr>\
                                                <td>Name</td><td>Size</td><td>Type</td>\
                                            </tr>",dirname,dirname);
    bufferevent_write(bufev,buf_dir_html,strlen(buf_dir_html));

    for(int i=0;i<dir_total_num;++i)
    {
        char buf_current_name[1024] = {0};
        if( 0 == strcmp(dirname,"./"))
        {
            sprintf(buf_current_name,"%s%s",dirname,ptr[i]->d_name);
        }
        else
        {
            sprintf(buf_current_name,"%s/%s",dirname,ptr[i]->d_name);
        }
        printf("++++++++++++++++++++send cur dir <name>>%s\n",buf_current_name);
        struct stat st;
        memset(&st,0,sizeof(st));
        stat(buf_current_name,&st);
    
        sprintf(buf_dir_html,
                                        "<tr>\
                                            <td><a href=\"%s\">%s</a></td>\
                                            <td>%ld</td>\
                                            <td>%s</td>\
                                        </tr>",
                buf_current_name,
                ptr[i]->d_name,st.st_size,
                judge_type_dir_or_nondir(buf_current_name)!= 0?"dir":"plain file");
        bufferevent_write(bufev,buf_dir_html,strlen(buf_dir_html));
        memset((char*)buf_dir_html,0,sizeof(buf_dir_html));
    }

    //html end
    sprintf(buf_dir_html,
                                        "</table>\
                                    </body>\
                                </html>");
    bufferevent_write(bufev,buf_dir_html,strlen(buf_dir_html));
    bufferevent_write(bufev,"\r\n",2);

    free(buf_dir_html);
    return 0;
}
