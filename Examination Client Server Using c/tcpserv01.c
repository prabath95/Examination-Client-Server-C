#include	"cc352.h"
#include	<sys/wait.h>
#include        "signal.c"

void
sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}
int main(int argc, char **argv)
{
	int			listenfd, connfd;
	pid_t			childpid;
	socklen_t		clilen;
	struct sockaddr_in	cliaddr, servaddr;
	char  			buff[MAXLINE];
	const char		*ptr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_TCP_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	Signal(SIGCHLD,sig_chld);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if( (ptr = inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff))) == NULL) {
			fprintf(stderr, "inet_ntop error \n");
			exit (1);
		}
		printf("connection from %s, port %d\n", ptr, ntohs(cliaddr.sin_port));


		if ( (childpid = Fork()) == 0) {
			printf("child %d Created\n", getpid());	/* child process */
			Close(listenfd);				/* close listening socket */
			str_echo(connfd);				/* process the request */
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
