#ifndef __SOCKS_H__

#include <stdint.h>
#include <sys/ioctl.h>

#define __SOCKS_H__

struct sock_name_param {
	char name[64];
};

struct sock_buffer_param {
	uint64_t size;
	void *buffer;
};

#define IOCTL_SOCKS_INIT		_IOWR('s', 1, uint64_t)
#define IOCTL_SOCKS_LISTEN		_IOWR('s', 2, struct sock_name_param)
#define IOCTL_SOCKS_CONNECT		_IOWR('s', 3, struct sock_name_param)
#define IOCTL_SOCKS_SEND		_IOWR('s', 4, struct sock_buffer_param)
#define IOCTL_SOCKS_RECV		_IOWR('s', 5, struct sock_buffer_param)
#define IOCTL_SOCKS_RESIZE		_IOWR('s', 6, uint64_t)

int sock_init(int fd, size_t size) {
    return ioctl(fd, IOCTL_SOCKS_INIT, size);
}

int sock_listen(int fd, char *name) {
    struct sock_name_param param;
    memset(&param, 0, sizeof(param));
    strncpy(param.name, name, sizeof(param.name) -1);
    int err = ioctl(fd, IOCTL_SOCKS_LISTEN, &param);
    if(err < 0){
        perror("ioctl sock_listen");
        fail();
    }
    return err;
}

int sock_connect(int fd, char *name) {
    struct sock_name_param param;
    memset(&param, 0, sizeof(param));
    strncpy(param.name, name, sizeof(param.name) -1);
    int err =  ioctl(fd, IOCTL_SOCKS_CONNECT, &param);
    if(err < 0){
        perror("ioctl sock_connect");
        fail();
    }
    return err;
}

int sock_send(int fd, void *buffer, size_t size) {
    struct sock_buffer_param param = { .size = size, .buffer = buffer};
    int err =  ioctl(fd, IOCTL_SOCKS_SEND, &param);
    if(err < 0){
        perror("ioctl sock_send");
        fail();
    }
    return err;
}

int sock_recv(int fd, void *buffer, size_t size) {
    struct sock_buffer_param param = { .size = size, .buffer = buffer};
    int err = ioctl(fd, IOCTL_SOCKS_RECV, &param);
    if(err < 0){
        perror("ioctl sock_recv");
        fail();
    }
    return err;
}

int sock_resize(int fd, size_t size) {
    int err =  ioctl(fd, IOCTL_SOCKS_RESIZE, size);
    if(err < 0){
        perror("ioctl sock_resize");
        fail();
    }
    return err;
}

#endif
