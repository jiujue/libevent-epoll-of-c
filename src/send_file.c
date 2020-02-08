
#include "../include/head.h"


int send_file(struct bufferevent *bufev,char* file){
    int ffd = open(file,O_RDONLY);
    if(-1 == ffd)
    {
        printf("sourceFilePath : %s\n",file);
        perror("open sourceFile error");
    }

//    char file_read_buf[1024];
    char *file_read_buf = (char*)malloc(40960);
    int read_len = 0;

    char * type = get_file_type(file);

    send_html_head(bufev,200, "OK", type);


    while((read_len=read(ffd, file_read_buf,40960)) > 0)
    {
        if(0 == read_len)
        {
            break;
        }
        bufferevent_write(bufev,file_read_buf,read_len);;
//        file_read_buf[strlen(file_read_buf)+1] = '\n';
        printf("send message :%s\n",file_read_buf);
        memset(file_read_buf,0,sizeof(file_read_buf));
    }
    bufferevent_write(bufev,"\r\n",2);;
    close(ffd);
    printf("close ...\n");
    free(file_read_buf);

    return 0;
}
