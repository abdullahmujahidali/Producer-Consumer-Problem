#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h> 
int mutex=1,full=0,empty=1,x=0;
FILE *fp;
char str[60];
char * line = NULL;
size_t len = 0;
size_t read;
// FUNCTION NO !
FILE reader(){
 fp = fopen("file.txt" , "r");
 return *fp;
} 
int main()
{
  int n;
  void producer();
  void consumer();
  int wait(int);
  int signal(int);
  printf("Reader process called sucessfully \n");
  reader();
  printf("\n1.Producer\n2.Consumer\n3.Exit");
  while(1)
  {
    printf("\nEnter your choice:");
    scanf("%d",&n);
    switch(n)
    {
      case 1: if((mutex==1)&&(empty!=0))
            producer();
          else
            printf("Buffer is full!!");
          break;
      case 2: if((mutex==1)&&(full!=0))
            consumer();
          else
            printf("Buffer is empty!!");
          break;
      case 3:
          exit(0);
          break;
    }
  }

    fclose(fp);
  return 0;
}

int wait(int s)
{
  return (--s);
}
 
int signal(int s)
{
  return(++s);
}
// FUNCTION NO 2 --> PROCESS 1
void process1(){
  for(int i=0;i<read;i++){
        if(line[i]==' '){
            line[i]='*';
        }

    }
  
}
// FUNCTION NO 3 --> PROCESS 2
void process2(){
int i=0;
 while(line[i]!='\0') 
     {
        if(line[i]>='a' && line[i]<='z')
        {
           line[i] -= 32; 
        }
        i++;
     }
 
fclose(fp);
}

// FUNCTION NO 4 --> WRITER FUNCTION 
void WRITER(){
FILE *fp;
int i=0;
fp  = fopen ("output.txt", "w");
 while(line[i]!='\0') {
        fputc(line[i], fp);
        i++;
}
}
void producer()
{
  mutex=wait(mutex);
  full=signal(full);
  empty=wait(empty);
    if((read = getline(&line, &len, fp)) != -1){
        printf("\nProducer produces the item %s",line);
    }
  x++;
  
  mutex=signal(mutex);
}
void consumer()
{
  mutex=wait(mutex);
  full=wait(full);
  empty=signal(empty);  
  printf("\nConsumer consumes item %s",line);
    process1();
    printf("\n Proces 1 sucessfully executed line passed to Process 2 \n");
    process2();
    printf("\n Proces 2 sucessfully executed line passed to WRITER\n");
    WRITER();
   x--;
  mutex=signal(mutex);
}
