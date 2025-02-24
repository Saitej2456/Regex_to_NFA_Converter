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

void paranthesis_check(char * regex)
{
    node * top = NULL;
    int i = 0;
    while(regex[i] != '\0')
    {
        if((regex[i]=='(')||(regex[i]==')'))
        {
            top = push(top,regex[i]);

            //tester 
            //used to understand how the stack is after pushing a value into it
            if(0)
            {
                printStack(top);
                printf("\n");
            }

            if((top->next != NULL)&&(top->data == ')')&&(top->next->data == '('))
            {
                top = pop(&top);
                top = pop(&top);
                //tester 
                //used to understand how the stack is after poping values from it
                if(0)
                {
                    printStack(top);
                    printf("\n");
                }
            }
        }
         
         i++;
    }
    if(isEmpty(top)==1)
    {
        printf("Valid Regex check1 : Passed");
    }
    else
    {
        printf("Invalid Regex Error: Check the Parenthesis\n");
        exit(1);
    }
    
}

void symbol_check(char * regex)
{
    bool flag = false;
    char valid_symbols[] = {'a','b','+','.','*','E'};
    int i = 0 ;
    while(regex[i] != '\0')
    {
        if((regex[i] == '(')||(regex[i] == ')'))
        {
            i++;
            continue;
        }
        else
        {
            for(int j = 0 ;j < 6 ; j++)
            {
                if(regex[i] == valid_symbols[j])
                {
                    flag = true;
                    break;
                }
            }

            if(flag == true)
            {   
                i++;
                flag = false;
                continue;
            }
            printf("\nInvalid Regex Error: invalid Symbol Found in Regex");
            printf("\nInvalid Regex symbol found : %c\n", regex[i]);
            exit(1);
        }
    }
    printf("\nValid Regex check2 : Passed\n");
}

void validation_of_regex(char * regex)
{
    paranthesis_check(regex); 
    symbol_check(regex);

}
int main()
{
    char regex[] = "(a+++b)*(E)*";
    validation_of_regex(regex);
    return 0;
}
