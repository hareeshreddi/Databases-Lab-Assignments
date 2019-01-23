/* Name of the Student::Hareesh Reddi Roll Number:: 150101051  */
//Databases include exam-time-table.csv course-credits.csv course-wise-student-list
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/types.h>
#define maxstringlen 10000000//maximum length of any string
const char* getfield(char*,int);
struct Node1//exam-time-table//fp1
{
	char* course_id;
	char* exam_date;
	char* start_time;
	char* end_time;
	struct Node1* next;
};
struct Node2//course-credits//fp2
{
	char* course_id;
	char* no_of_credits;
	struct Node2* next;
};
struct Node3//course-wise-students//fp3
{
	char* serial_number;
	char* roll_number;
	char* name;
	char* email;
	struct Node3* next;
};

//taking maximum no of courses a student can have is 20
struct Node//final list//fp
{
	int i;//no_of_courses
	char* roll_number;
	char* name;
	int   credits;
	char subject[20][50];
	struct Node* next;
};
void printList1(struct Node1*);
void printList2(struct Node2*);
void printList(struct Node*);
void push1(struct Node1**,const char*,const char*,const char*,const char*);
void push2(struct Node2**,const char*,const char*);

int get_no_of_credits(char* temp,struct Node2* head2)
{
	struct Node2* current = head2;
	while(current != NULL)
	{
		if(strcmp(current->course_id,temp)==0)
		{
			//printf(" hey man:::::::%s and %d\n",current->course_id,atoi(current->no_of_credits));
			return atoi(current->no_of_credits);
		}
		current=current->next;
	}
	return 0;
}

int search(struct Node** head_ref,const char* temp2,char* temp,struct Node2* head2)
{
	struct Node* current = *head_ref;  // Initialize current
    while (current != NULL)
    {
        if (strcmp(current->roll_number,temp2)==0)
        {	
        	current->credits+=get_no_of_credits(temp,head2);		//add credits of temp(course_id)
        	//printf("orey::::%d\n", current->credits);
        	//printf("\nHareesh..................................%s and %s and %s and %d\n",current->roll_number,temp2,temp,current->credits);
        	current->i++;
        	strcpy(((*current).subject[current->i]),temp);
			//printf("orrrrrrrrrrrrrrrrrrrrrr:::%d and %s \n",current->i,(*current).subject[current->i]);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void push(struct Node** head_ref,const char* temp1,const char* temp2,const char* temp3,const char* temp4,char* temp,struct Node2* head2)
{
	if(search(head_ref,temp2,temp,head2)==0)
	{
		//printf("ppppppppp\n");
		struct Node* n = (struct Node*) malloc(sizeof(struct Node));
	  	struct Node* last = *head_ref;
	  	n->roll_number=(char*)malloc(sizeof(temp2)+100);
	  	n->name=(char*)malloc(sizeof(temp3)+100);
	  	//n->subjects=(char*)malloc(sizeof(temp)+1000);
	  	strcpy(n->roll_number,temp2);
	  	strcpy(n->name,temp3);
	  	n->credits=get_no_of_credits(temp,head2);
	  	n->i=1;
	  	strcpy(((*n).subject[0]),temp);
	  	//printf("you ::roll_number::%s and name::%s and credits::%d and subject:%s\n",n->roll_number,n->name,n->credits,((*n).subject[0]));
	  	n->next=NULL;
	  	if (*head_ref == NULL)
	    {
	       *head_ref = n;
	       return;
	    }  
	    while (last->next != NULL)
	        last = last->next;
	    last->next = n;
	}
    return;  
}
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
		push1(&head1,s1,s2,s3,s4);
		free(temp1);
		free(temp2);
		free(temp3);
		free(temp4);
	}
	printf("...............................HELLO1...............................\n");
	//head1=head1->next;
	printList1(head1);
	while( fgets(buf2,maxstringlen,fp2)!=NULL )//copying each line into buf
	{
		char* temp1=strdup(buf2);
		char* temp2=strdup(buf2);
		const char* s1=getfield(temp1,1);
		const char* s2=getfield(temp2,2);
		push2(&head2,s1,s2);
		free(temp1);
		free(temp2);
	} 
	//head2=head2->next;
	printf("\n...............................HELLO2...............................\n");
	printList2(head2);
	printf("\n...............................HELLO3...............................\n");
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
							//printf("%s and %s and %s and %s and %s\n",s1,s2,s3,s4,de1->d_name);
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
	//printf("serial_number::%s and roll_number::%s and name::%s and email::%s and course_name::%s and credits::%d\n",s1,s2,s3,s4,tt,get_no_of_credits(tt,head2));
							push(&head,s1,s2,s3,s4,tt,head2);
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
    printf("\n.......................................STARTING THE FINAL ANSWER..................................\n");
    printList(head);
    //printf("\n......................................Printing the students who are having clashes in exams....................\n");
    //printListFinal(head,head1);
	return 0;
}


void printListFinal(struct Node* head ,struct Node1* head1)
{
	while(head!=NULL)//looping all students
	{
		int ii=head->i;
		while(ii>0)//looping all subjects
		{

		}
		head=head->next;
	}
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
void push1(struct Node1** head_ref,const char* temp1,const char* temp2,const char* temp3,const char* temp4)
{
	struct Node1* n = (struct Node1*) malloc(sizeof(struct Node1)); 
  	struct Node1* last = *head_ref;
  	n->course_id=(char*)malloc(sizeof(temp1));
  	n->exam_date=(char*)malloc(sizeof(temp2));
  	n->start_time=(char*)malloc(sizeof(temp3));
  	n->end_time=(char*)malloc(sizeof(temp4));
  	strcpy(n->course_id,temp1);
  	strcpy(n->exam_date,temp2);
  	strcpy(n->start_time,temp3);
  	strcpy(n->end_time,temp4);
  	n->next=NULL;
  	if (*head_ref == NULL)
    {
       *head_ref = n;
       return;
    }  
    while (last->next != NULL)
        last = last->next;
    last->next = n;
    return;  
}
void push2(struct Node2** head_ref,const char* temp1,const char* temp2)
{
	struct Node2* n = (struct Node2*) malloc(sizeof(struct Node2)); 
  	struct Node2* last = *head_ref;
  	n->course_id=(char*)malloc(sizeof(temp1));
  	n->no_of_credits=(char*)malloc(sizeof(temp2));
  	strcpy(n->course_id,temp1);
  	strcpy(n->no_of_credits,temp2);
  	n->next=NULL;
  	if (*head_ref == NULL)
    {
       *head_ref = n;
       return;
    }  
    while (last->next != NULL)
        last = last->next;
    last->next = n;
    return;  
}
void printList1(struct Node1 *head)
{
	printf("......................Start of Printing the exam-time-table Linked List1...............\n");
    while (head!= NULL)
    {
        printf("%s %s %s %s\n",head->course_id,head->exam_date,head->start_time,head->end_time);
        head = head->next;
    }
    printf(".....................End of Printing the exam-time-table Linked List1.............\n");
}
void printList2(struct Node2 *head)
{
	printf("......................Start of Printing the course-credits Linked List2...............\n");
    while (head!= NULL)
    {
        printf("%s %s\n",head->course_id,head->no_of_credits);
  		head = head->next;
    }
    printf(".....................End of Printing the course-credits Linked List2.............\n");
}
void printList(struct Node *head)//only printing if credits are greater than 40
{
	printf("......................Printing people who are violating condition of more than 40 credits...............\n");
	int students_greaterthan_40=0;
    while (head!= NULL)
    {
    	if(head->credits>40)
        {
        	printf("%s %s %d     -->no of courses::%d\n",head->roll_number,head->name,head->credits,head->i);
        	students_greaterthan_40++;
        }
  		head = head->next;
    }
    printf("\nThere are totally %d students having their credits more than 40\n\n",students_greaterthan_40 );
    printf(".....................End of Printing the List.............\n");
}