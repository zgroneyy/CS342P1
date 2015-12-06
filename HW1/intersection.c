#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//A node definition that can carry on a string as well as shows it's next
typedef struct node{
	char data[255];
	struct node *next;
}node;

node* readFile(FILE* fp)
{
	node* head; //Will be the first node of our linked list 
	node* curr=NULL; //Will be floating node through linked list
	//Head of the desired linked list should be defined first
	head=(node*)malloc(sizeof(struct node));
	char word[255]; //
	fscanf(fp,"%s",word);
	strcpy(head->data,word);
	head->next=NULL;
	curr=head;
	
	while(1)
	{
		//When filereader sees end of the document, it will be stopped 
		if(feof(fp))
		   break;
		fscanf(fp,"%s",word);
		node* newnode=(node*)malloc(sizeof(struct node));
		strcpy(newnode->data,word);
		curr->next=newnode;
		newnode->next=NULL;
		curr=curr->next;
	}
	
	return head;
}
void writeFile(FILE* fp, node* outputlist)
{
	//A simple loop to print out our Intersection linked list to .txt file
	while(outputlist!=NULL)
	{
		fprintf(fp,"%s\n",outputlist->data);
		outputlist=outputlist->next;
	}
	fclose(fp);
}


/*	
Purify method that removes same and sequential entries in the linked list.	-designed for simplicity
Method ONLY works for sequential entries, does not work on elements spreaded over the list.
Thereby method provided should be used just after sorting
*/
node* purify(node* p)
{
    node* cur=p;
    while(cur->next!=NULL)
    {
        node* preventor=cur->next;
        if(strcmp(cur->data,cur->next->data)==0)//As long as u have same entry next to a particular node
        {
            cur->next=cur->next->next;
            free(preventor);
        }
        else
            cur=cur->next;
    }
    return p;
}
/*	
findIntersection method that find intersection of two linked lists (as can be understood from name :D)
*/
node* findIntersection(node* list1, node* list2)
{
	node* result=NULL;
	//Silly control statement
	if(list1==NULL || list2==NULL)
	   return NULL;
	else
	{
		//As long as we have elements in our lists, it goes on
		while(list1!=NULL && list2!=NULL)
		{
		//Shift left side of comparison
			if(strcmp(list1->data,list2->data)<0)
				list1=list1->next;
			else if(strcmp(list1->data,list2->data)>0)
				list2=list2->next;
			//We have found an intersection! A new node is created for output list and necessary data copied to this node. 
			else{
				node* newnode=(node*)malloc(sizeof(struct node));
				strcpy(newnode->data, list1->data);
				newnode->next=result;
				result=newnode;
				list1 = list1->next;
				list2 = list2->next;
		  }
		}
	}
	return result;
}

void bubblesort(struct node **head) 
{
    int done = 0; // True if no swaps were made in a pass

    // Silly control statement
    if (*head == NULL || (*head)->next == NULL) return;

    while (!done) {
        struct node **pv = head; // "source" of the pointer to the current node in the list struct
                                            
        struct node *nd = *head;// local iterator pointer
        struct node *nx = (*head)->next;// local next pointer

        done = 1;
	   //As long as we have elements to sort, this should be continued.
        while (nx) {
        	  //Compare strings
            int cmp = strcmp(nd->data, nx->data);
		  //If first is bigger than second, swap.
            if (cmp > 0) {
                nd->next = nx->next;
                nx->next = nd;
                *pv = nx;

                done = 0;
            }
            pv = &nd->next;
            nd = nx;
            nx = nx->next;
        }
    }
}
int main(int argc, char* argv[])
{
	FILE* input1=NULL; 
	FILE* input2=NULL; 
	FILE* output=NULL;
	
	//assigning input and output files in necessary file modes
	input1=fopen(argv[1], "r");//read mode
	input2=fopen(argv[2], "r");//read mode	
	output=fopen(argv[3], "w+");//write mode
	node* list1=readFile(input1);
	node* list2=readFile(input2);
	bubblesort(&list1);
	bubblesort(&list2);
	list1=purify(list1);
	list2=purify(list2);
	node* listout=findIntersection(list1,list2);
	bubblesort(&listout);
	writeFile(output,listout);	
}
