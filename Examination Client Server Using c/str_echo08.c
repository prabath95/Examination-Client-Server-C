#include	"cc352.h"
#include        <stdbool.h>

void
str_echo(int sockfd)
{

	long		arg1, arg2;
	ssize_t		n;
	char		line[MAXLINE],* sanswer;
	int 		i = 0,Qanswer,Qnumber,randomnumber;
  	char 		ln[16][100] , *pch ;


void getQuestion ()
{
    FILE *myfile;
    myfile = fopen("file.txt","r");
    if (myfile == NULL)
    {
        printf("can not open file \n");
	return;
    }
    while(!feof(myfile))
    {
      fgets(ln[i], sizeof ln[i], myfile);
      i++;
    }
    fclose(myfile);
    srand(time(NULL));
    randomnumber = rand() % (i-2)+0;
    Qnumber = ln[randomnumber][0];
    Qnumber = Qnumber-'0';
   
}
bool findAnswer(int Question,int ans)
{
    i = 0;
    FILE *myfile;
    myfile = fopen("file.txt","r");
    if (myfile == NULL)
    {
        printf("can not open file \n");
    }
    while(!feof(myfile))
    {
      fgets(ln[i], sizeof ln[i], myfile);
      i++;
    }
    fclose(myfile);
    pch = strtok (ln[Question],"|");
    i = 0;
    while (pch != NULL)
    {
        if(i == 4)
        {
           if(atoi(pch) == ans)
           {
               return true;
           }
           else
            {
                return false;
            }
        }
        pch = strtok(NULL,"|");
        i++;
    }
}

	
	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		strtok(line,"\n");
		strtok(line,"\n");
			getQuestion();
			n = strlen(ln[randomnumber]);
			Writen(sockfd, ln[randomnumber], n);
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;
		strtok(line,"\n");
		strtok(line,"\n");
		Qanswer = line[0]-'0';
			
		bool answer = findAnswer(Qnumber,Qanswer);
		//printf("%s", answer ? "true" : "false");
		if(answer){
			sanswer = "Correct\n";
		}else{
			sanswer = "Incorrect\n";
		}
			
		n = strlen(sanswer);
		Writen(sockfd,sanswer,n);
	
	}	
	
}
