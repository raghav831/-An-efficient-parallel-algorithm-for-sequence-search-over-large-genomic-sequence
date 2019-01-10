#include<stdio.h>
#include<omp.h>
#include<string.h>
#define MAXTHREADS 10
int main(void)
{
int i,j,k,a,n,found=0,flag=0;
FILE * file;
char str[32],str1[4];
char strlist[4];

file=fopen("genome.txt","r");

if(file)

{

while(fscanf(file,"%s",str)!=EOF)

{

printf("Genome sequence in which searching is performed: %s",str);

}

fclose(file);

}

printf("\nEnter the sequence to be searched: "); scanf("%s",str1);
int STRINGSIZE=strlen(str);

double start_time,run_time;

for(j=4;j<=4;j++)

{

omp_set_num_threads(j);

found=0;

start_time = omp_get_wtime();

#pragma omp parallel private(i)

{
int start,noofsteps;

#pragma omp single

printf("\n num of threads in action: %d\n",j);

if(found==0)

{

start=(omp_get_thread_num())*(STRINGSIZE/omp_get_num_threads()); 
noofsteps=start+(STRINGSIZE/omp_get_num_threads());
if(STRINGSIZE%j!=0)

noofsteps+=(STRINGSIZE%j);


 
for(i=start;i<noofsteps;i++)

{

a=i;

for(k=0;k<strlen(str1);k++)

{





if(str1[k]==str[a])
{
flag++;
a++;
}
else
{
flag=0;
}
if(flag==4)
{
printf("Value has been found in %d thread\n",omp_get_thread_num()+1);
found=1;
break;
}
}
}
}
}
run_time = omp_get_wtime() - start_time; printf(" %f seconds %d threads \n ",run_time,j);
}
return 0;
}

