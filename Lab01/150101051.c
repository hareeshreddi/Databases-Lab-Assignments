/* Name of the Student::Hareesh Reddi Roll Number:: 150101051  */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxstringlen 1000
struct Node
{
	 char* RollNumber;
	 char *dob;
	 char *attend;
	struct Node* next;
};
struct Student *arr;

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
// I am using Linked List Data Structure for storing the Data 
//Inserting at the end of linked list
void push(struct Node** head_ref,const char* temp1,const char* temp2,const char* temp3)
{
    // 1. allocate node 
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  
  	struct Node *last = *head_ref;
    //allocate memory
    new_node->RollNumber=(char*)malloc(sizeof(temp1));
    new_node->dob=(char*)malloc(sizeof(temp2));
    new_node->attend=(char*)malloc(sizeof(temp3));
    //2. put in the data
    strcpy(new_node->RollNumber,temp1);
    strcpy(new_node->dob,temp2);
    strcpy(new_node->attend,temp3);
    
    //printf("field1:%s field2:%s field3:%s\n",new_node->RollNumber,new_node->dob,new_node->attend);
  	new_node->next=NULL;
  	if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }  
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;     
}

void processlinkedlist(struct Node* head,FILE** f1,FILE** f2)
{
	int no_classes_present,rollno,no_classes_absent,total_classes;
	float precentage;
	while (head != NULL)
    {
    	struct Node* prev = (struct Node*) malloc(sizeof(struct Node));
    	rollno=atoi(head->RollNumber);
    	//printf("rollcalllcalllllllllllll%d\n",rollno);
    	no_classes_present=0;
    	no_classes_absent=0;
    	total_classes=0;
    	precentage=1.0;
    	while(head!=NULL&&head->next!=NULL&&atoi(head->RollNumber)==rollno)
    	{
    		//printf("ffffffffffffffffffffffffffffffffffff\n");
    		if(strcmp(head->attend," Present")==0)
    			no_classes_present++;
    		else
    			no_classes_absent++;
    		total_classes++;
    		prev=head;
    		head=head->next;
    	}
    	if(total_classes!=0)
    	{
	    	precentage=1.0*(float)(no_classes_present*100/total_classes);
	    	printf("%d %d %d and %f\n",no_classes_present,no_classes_absent,total_classes,precentage);
	    	if(precentage<75)
	        	fprintf((*f1), "%s,%d,%f\n",prev->RollNumber,no_classes_present,precentage);
	    	else
	    		fprintf((*f2), "%s,%d,%f\n",prev->RollNumber,no_classes_present,precentage);
    	}
    	else
    		return;
    }
}

void printList(struct Node *head)
{
	printf("......................Start of Printing the Linked List...............\n");
    while (head!= NULL)
    {
        printf("%s %s %s\n",head->RollNumber,head->dob,head->attend);
        head = head->next;
    }
    printf(".....................End of Printing the Linked List.............\n");
}

int main()
{
	FILE *fp;
	fp =fopen("database_12jan2017.csv","r");
	if(fp==NULL)
	{
		printf("The file might not exist or is write protected\n");
		exit(1);
	}
	int i=0,x,y,z;
	char *buf=(char*)malloc(maxstringlen);
	struct Node* head = NULL;
	head = (struct Node*)malloc(sizeof(struct Node)); 


	//Now the Linked List head contains entire Data 
	while( fgets(buf,maxstringlen,fp)!=NULL )//copying each line into buf
	{
		char* temp1=strdup(buf);
		char* temp2=strdup(buf);
		char* temp3=strdup(buf);
		const char* s1=getfield(temp1,1);
		const char* s2=getfield(temp2,2);
		const char* s3=getfield(temp3,3);
		//printf("field1:%s field2:%s field3:%s\n",getfield(temp1,1),getfield(temp2,2),getfield(temp3,3));
		//printf("field1:%s field2:%s field3:%s\n",s1,s2,s3);
		x=strlen(s1);
		y=strlen(s2);
		z=strlen(s3);
		push(&head,s1,s2,s3);
		free(temp1);
		free(temp2);
		free(temp3);
	}
	head=head->next;
	/*..................................Printing the List........................ */
	printList(head);
	FILE *f1,*f2;
	f1=fopen("L75.csv","a");
	f2=fopen("G75.CSV","a");
	processlinkedlist(head,&f1,&f2);
	return 0;
}