#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Node
{
    char data;
    struct Node * next;
}node;

node * create_node (char data)
{
    node * newNode = (node *)malloc(sizeof(node));

    if(newNode == NULL)
    {
        printf("Error : Memory allocation Failed");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

node * push (node *top,char data)
{
    node * newNode = create_node(data);

    newNode->next = top;
    top = newNode;
    return top;
}

bool isEmpty(node * top)
{
    bool Empty = 1;
    bool NotEmpty = 0;
    if(top == NULL)
    {
        return Empty;
    }

    else 
    {
        return NotEmpty;
    }
}

node * pop (node ** top)
{
    if(isEmpty(*top) == 1)
    {
        printf("Error : Trying to pop Empty stack");
        exit(1);
    } 
    else
    {
        node * temp = *top;
        *top = (*top)->next;
        free(temp);

        return *top;
    }
}


void printStack(node * top)
{
    node * current_node = top;
    while(current_node != NULL)
    {
        printf("%c ",current_node->data);
        current_node = current_node->next;
    }
}

void stack(char * regex)
{
    node * top = NULL;
    int i = 0;
    while(regex[i] != '\0')
    {
        if((regex[i]=='(')||(regex[i]==')'))
        {
            top = push(top,regex[i]);
            printStack(top);
            if((top->next != NULL)&&(top->data == ')')&&(top->next->data == '('))
            {
                top = pop(&top);
                top = pop(&top);
            }
            printf("\n");
        }
         
         i++;
    }
    if(isEmpty(top)==1)
    {
        printf("valid regex");
    }
    else
    {
        printf("invalid regex");
    }
    
}


int main()
{
    char regex[] = "(a|b)*(";
    stack(regex); 

    return 0;
}
