#include "lock_file.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int open_lock_file(char *path)
{
	int ret = -1;
	int lock_ret = -1;

	int fd = open(path, O_RDWR | O_CREAT | O_EXCL);
	if (fd == -1) {
		if (errno == EEXIST) {
			fd = open(path, O_RDWR | O_TRUNC);
			if (fd == -1) {
				perror(path);
				goto err;
			}
		} else {
			perror(path);
			goto err;
		}
	}

	lock_ret = flock(fd, LOCK_EX | LOCK_NB);
	if (lock_ret == 0) {
		pid_t pid = getpid();
		char buf[32] = {0};
		snprintf(buf, sizeof(buf), "%d", pid);
		write(fd, buf, strlen(buf));
	} else if (errno == EWOULDBLOCK) {
		//printf("process is running now, exit ...\n");
		ret = -2; //file have been locked
		goto err;
	} else {
		goto err;;
	}

	return fd;
err:
	if (fd >= 0) {
		close(fd);
	}
	return ret;
}

int close_unlock_file(int fd)
{
	if (fd) {
		flock(fd, LOCK_UN);
		close(fd);
	}

	return 0;
}

