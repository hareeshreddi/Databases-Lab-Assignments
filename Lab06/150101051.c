/* Name of the Student::Hareesh Reddi Roll Number:: 150101051  */
//Databases include exam-time-table.csv course-credits.csv course-wise-student-list
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/types.h>
const char* getfield(char*,int);
#define maxstringlen 10000000//maximum length of any string
int main()
{
	
	FILE *fp1,*fp2,*fp3,*fp;
	fp1=fopen("database-19-jan-2018/database-19-jan-2018/exam-time-table.csv","r");
	fp2=fopen("database-19-jan-2018/database-19-jan-2018/course-credits.csv","r");	
	if(fp1==NULL||fp2==NULL)
	{
		printf("The file might not exist or is write protected\n");
		exit(1);
	}
	char *buf1=(char*)malloc(maxstringlen);
	char *buf2=(char*)malloc(maxstringlen);
	struct Node1* head1 = NULL;
	struct Node2* head2 = NULL;
	struct Node*  head  = NULL;
	int s5=0;
	FILE *ff1;
	ff1=fopen("150101051_ett.sql","w");
	while( fgets(buf1,maxstringlen,fp1)!=NULL )//copying each line into buf
	{
		char* temp1=strdup(buf1);
		char* temp2=strdup(buf1);
		char* temp3=strdup(buf1);
		char* temp4=strdup(buf1);
		const char* s1=getfield(temp1,1);
		const char* s2=getfield(temp2,2);
		const char* s3=getfield(temp3,3);
		const char* s4=getfield(temp4,4);
    	printf("INSERTING::%s %s %s %s\n",s1,s2,s3,s4);
    	s5++;
        fprintf(ff1,"insert into ett values ('%d','%s','%s','%s','%s');\n",s5,s1,s2,s3,s4);
		free(temp1);
		free(temp2);
		free(temp3);
		free(temp4);
	}
	printf("...............................HELLO1...............................\n");
	FILE *ff2;
	ff2=fopen("150101051_cc.sql","w");
	while( fgets(buf2,maxstringlen,fp2)!=NULL )//copying each line into buf
	{
		char* temp1=strdup(buf2);
		char* temp2=strdup(buf2);
		const char* s1=getfield(temp1,1);
		const char* s2=getfield(temp2,2);
		printf("hellllll\n");
        fprintf(ff2,"insert into cc values ('%s','%s');\n",s1,s2);
		free(temp1);
		free(temp2);
	} 
	printf("\n...............................HELLO2...............................\n");
	struct dirent *de;  // Pointer for directory entry
 
    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir("database-19-jan-2018/database-19-jan-2018/course-wise-students-list/");
 
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
    char* path=(char*)malloc(sizeof(char)*100);
    path="database-19-jan-2018/database-19-jan-2018/course-wise-students-list/";
    FILE *ff3;
	ff3=fopen("150101051_cwsl.sql","w");
    while ((de = readdir(dr)) != NULL)
     	{
            char* fullpath=NULL;
            fullpath=(char*)malloc(strlen(de->d_name)+20+strlen(path));
            fullpath[0]='\0';
            //printf("fullpath::%s path::%s\n",fullpath,path);
            strcat(fullpath,path);
            strcat(fullpath,de->d_name);
            DIR *dr1=opendir(fullpath);
            struct dirent *de1;
            if (dr1 == NULL || strcmp(".",de->d_name)==0 || strcmp("..",de->d_name)==0)  // opendir returns NULL if couldn't open directory
    		{
        		//printf("Could not open current directory " );
        		continue;
    		}
    		else
    		{
    			while ((de1 = readdir(dr1)) != NULL)
	            {
	            	if(strcmp(".",de1->d_name)!=0 && strcmp("..",de1->d_name)!=0)
	            	{
		            	//printf("here is the name:::::%s\n",de1->d_name);
		            	char* ff=NULL;
		            	ff=(char*)malloc(strlen(fullpath)+20+strlen(de1->d_name));
		            	ff[0]='\0';
		            	strcat(ff,fullpath);
		            	strcat(ff,"/");
		            	strcat(ff,de1->d_name);
		            	///////////////printf("here is the path:::::%s\n",ff);
		            	fp3=fopen(ff,"r");
		            	if(fp3==NULL)
						{
							printf("The file might not exist or is write protected\n");
							exit(1);
						}
						char *buf3=(char*)malloc(maxstringlen);
						
						while(fgets(buf3,maxstringlen,fp3)!=NULL)//copying each line into buf
						{
							char* temp1=strdup(buf3);
							char* temp2=strdup(buf3);
							char* temp3=strdup(buf3);
							char* temp4=strdup(buf3);
							const char* s1=getfield(temp1,1);
							const char* s2=getfield(temp2,2);
							const char* s3=getfield(temp3,3);
							const char* s4=getfield(temp4,4);
							printf("%s and %s and %s and %s and %s\n",s1,s2,s3,s4,de1->d_name);
							char* tt=NULL;
							tt=(char*)malloc(sizeof(de1->d_name));
							tt[0]='\0';
							strcat(tt,de1->d_name);
							int i=0;
							while(tt[i])
							{
								if(tt[i]=='.')
									{
										tt[i]='\0';
										break;
									}
								i++;
							}
    printf("INSERTING::%s %s %s %s %s\n",s1,s2,s3,s4,tt);
    fprintf(ff3,"insert into cwsl values ('%s','%s','%s','%s','%s');\n",s1,s2,s3,s4,tt);
							free(temp1);
							free(temp2);
							free(temp3);
							free(temp4);
						}
		            	free(ff);
		            }
	            }
    		}
    		free(fullpath);
    		closedir(dr1);
        }
    closedir(dr); 
}
const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}