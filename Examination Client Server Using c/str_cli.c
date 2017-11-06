#include	"cc352.h"
#include <stdlib.h>
#include <string.h>

void
str_cli(FILE *fp, int sockfd)
{


	char	sendline[MAXLINE],*pch, recvline[MAXLINE];
	int     maxfdp1;
	fd_set		rset;
	FD_ZERO(&rset);
	
for ( ; ; ) {		
		
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		printf("Press q to Continue :");
		fflush(stdout);
		Select(maxfdp1, &rset, NULL, NULL, NULL);
		if (FD_ISSET(fileno(fp), &rset)) {
			if (Fgets(sendline, MAXLINE, fp) == NULL)
				return;	
		}else{
			printf("str_cli: server terminated prematurely");
			return;
		}		
		if(sendline[0] == 'q' || sendline[0] == 'Q'){
			Writen(sockfd, sendline, strlen(sendline));
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			    int     i = 0;
			    pch = strtok (recvline,"|");
			    while( pch != NULL ) {

				if(i < 4){
				      printf("%s\n",pch);	
				}
				pch = strtok(NULL, "|");
				i = i+1;
			   }
			FD_SET(sockfd, &rset);
			printf("Enter the correct answer number : ");
			fflush(stdout);
			Select(maxfdp1, &rset, NULL, NULL, NULL);
			if (FD_ISSET(fileno(fp), &rset)) {
				if (Fgets(sendline, MAXLINE, fp) == NULL)
				return;	
			}else{
				printf("str_cli: server terminated prematurely");
				return;
			}
			Writen(sockfd, sendline, strlen(sendline));
		
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			printf("Your answer is %s\n",recvline);

		}else{
			printf("User terminate the process !!!");
			return;
		}
	}
	
}
