#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

void daemon()
{
	int              i;
	int		fd0, fd1, fd2;
	pid_t            pid;

	umask(0);

#if 0
	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
		printf("%s: can't get file limit", cmd);
#endif
	if((pid = fork()) < 0) {
		perror("fork");
	} else if (pid != 0) {
		exit(0);
	}
	setsid();

	if(signal(SIGHUP, SIG_IGN) < 0) {
		perror("signal");
	}

	if((pid = fork()) < 0) {
		perror("fork");
	} else if(pid != 0) {
		exit(0);
	}

#if 0	
	if(chdir("/") < 0) {
		perror("chidir");
	}

	if(rl.rlim_max == RLIM_INFINITY) {
		rl.rlim_max = 1024;
	}

#endif

	for(i = 0; i < 3; i++) {
		close(i);
	}
	
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	//openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2){
		//syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		printf("unexpected file descriptors %d %d %d", fd0, fd1, fd2);
	}
}
