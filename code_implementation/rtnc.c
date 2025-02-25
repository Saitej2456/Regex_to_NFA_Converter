#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Node
{
    char data;
    struct Node * next;
}node;

//function which will create new node to place as an element in the stack [one of the stack functions]
node * create_node (char data)
{
    node * newNode = (node *)malloc(sizeof(node));

    if(newNode == NULL)
    {
        printf("Stack Error : Memory allocation Failed");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//function used to add elements into the stack [one of the stack functions]
node * push (node *top,char data)
{
    node * newNode = create_node(data);

    newNode->next = top;
    top = newNode;
    return top;
}

// function used to check if the stack is empty [one of the stack functions]
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

//function used to remove the top element in the stack [one of the stack functions]
node * pop (node ** top)
{
    if(isEmpty(*top) == 1)
    {
        printf("Stack Error : Trying to pop Empty stack");
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

//function used to print all the elements in the stack [one of the stack functions]
void printStack(node * top)
{
    node * current_node = top;
    while(current_node != NULL)
    {
        printf("%c ",current_node->data);
        current_node = current_node->next;
    }
}

void empty_paranthesis_check(char * regex)
{
    //string charecter index currently used from regex charecter string
    int i = 0 ;
    //Charecter variable used to keep track of charecter at string charecter index previously used from regex charecter string.
    //By default it has a value '\n' which represents that it still didn`t store any previous charecter values 
    char prev_val = '\n';
    while(regex[i] != '\0')
    {
        if(i == 0)
        {
            prev_val = regex[0];
            i++;
            continue;
        }
        //charecter variable used to keep track of charecter at string charecter index currently used from regex charecter string
        char current_val = regex[i];

        //tester
        //check what is the current and the previous values 
        if(0)
        {
            printf("\nThe prev val is %c and the current val is %c",prev_val,current_val);
        }
        if((prev_val == '(')&&(current_val == ')'))
        {
            printf("\nInvalid Regex Error : Empty Parenthesis Encountered\n");
            exit(1);
        }
        prev_val = regex[i];
        i++;
    }
    printf("\nValid Regex check1.2 : Passed\n");
}

//function used to check if the parenthesis used for regex are valid or invalid
void paranthesis_check(char * regex)
{
    //pointer used to keep track of the top element in the stack
    node * top = NULL;
    //string charecter index currently used from regex charecter string 
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
        printf("Valid Regex check1.1 : Passed");
        empty_paranthesis_check(regex);
    }
    else
    {
        printf("Invalid Regex Error: Check the Parenthesis\n");
        exit(1);
    }
    
}

//fucntion used to check if all the used symbols and operators are valid or invalid 
void symbol_check(char * regex)
{
    //flag tells if the pointed symbol in regex is one of the valid symbols or not 
    bool flag = false;

    //string of all valid symbols
    char valid_symbols[] = {'a','b','+','.','*','E'};

    //string charecter index currently used from regex charecter string
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
            printf("Invalid Regex Error: invalid Symbol Found in Regex");
            printf("\nInvalid Regex symbol found : %c\n", regex[i]);
            exit(1);
        }
    }
    printf("Valid Regex check2 : Passed");
}

//function used to check if there are any operators in regex which are side by side example : (a++b) or (a+*b)
void multi_operator_check(char * regex)
{
    //string charecter index currently used from regex charecter string
    int i = 0 ;
    //Charecter variable used to keep track of charecter at string charecter index previously used from regex charecter string.
    //By default it has a value '\n' which represents that it still didn`t store any previous charecter values 
    char prev_val = '\n';
    while(regex[i] != '\0')
    {
        if(i == 0)
        {
            prev_val = regex[0];
            i++;
            continue;
        }
        //charecter variable used to keep track of charecter at string charecter index currently used from regex charecter string
        char current_val = regex[i];

        //tester
        //check what is the current and the previous values 
        if(0)
        {
            printf("\nThe prev val is %c and the current val is %c",prev_val,current_val);
        }
        if(((prev_val == '+')||(prev_val == '.')||(prev_val == '*'))&&((current_val == '+')||(current_val == '.')||(current_val == '*')))
        {
            printf("\nInvalid Regex Error : Operators encountered side by side");
            printf("\nThe op1 is %c and the op2 is %c\n",prev_val,current_val);
            exit(1);
        }
        prev_val = regex[i];
        i++;
    }
    printf("\nValid Regex check3 : Passed\n");
}

//function which will check the validity of the regex
void validation_of_regex(char * regex)
{
    paranthesis_check(regex); 
    symbol_check(regex);
    multi_operator_check(regex);
}
int main()
{
    char regex[] = "(a)";
    validation_of_regex(regex);
    return 0;
}
