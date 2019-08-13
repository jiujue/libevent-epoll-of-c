#ifndef _HEAD_H_
#define _HEAD_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <fcntl.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>

int judge_type_dir_or_nondir(const char* name);
int send_dir_asheml(struct bufferevent *bufev, char *dirname, void *arg);
struct evconnlistener* libev_start(struct event_base*base, const char* Ip,int Port);
int send_html_head(struct bufferevent* bufev, int stat_no, const char* stat_desc, char* type);
const char *get_file_type(const char *name);
int send_file(struct bufferevent *bufev,char* file);

#endif
