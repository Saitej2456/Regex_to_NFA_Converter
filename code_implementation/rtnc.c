#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<ctype.h>

//Macros defined to use colors in output [syntax example : printf(YELLOW "text" RESET);]
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /*Macro defined to use the color Black */
#define RED     "\033[31m"      /*Macro defined to use the color Red */
#define GREEN   "\033[32m"      /*Macro defined to use the color Green */
#define YELLOW  "\033[33m"      /*Macro defined to use the color Yellow */
#define BLUE    "\033[34m"      /*Macro defined to use the color Blue */
#define MAGENTA "\033[35m"      /*Macro defined to use the color Magenta */
#define CYAN    "\033[36m"      /*Macro defined to use the color Cyan */
#define WHITE   "\033[37m"      /*Macro defined to use the color White */
#define BOLDBLACK   "\033[1m\033[30m"      /*Macro defined to use the color "Bold" Black */
#define BOLDRED     "\033[1m\033[31m"      /*Macro defined to use the color "Bold" Red */
#define BOLDGREEN   "\033[1m\033[32m"      /*Macro defined to use the color "Bold" Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /*Macro defined to use the color "Bold" Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /*Macro defined to use the color "Bold" Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /*Macro defined to use the color "Bold" Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /*Macro defined to use the color "Bold" Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /*Macro defined to use the color "Bold" White */

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
        printf(BOLDRED "Stack Error : Memory allocation Failed" RESET);
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
        printf(BOLDRED "Stack Error : Trying to pop Empty stack" RESET);
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


// Returns the data of top 
char peek(node *top) {
    if (!isEmpty(top))
    {
        return top->data;
    }
    return '\0';
}

// Returns the precedence of a charcter
int precedence(char op) {
    if (op == '+') return 1;
    if (op == '.') return 2;
    if (op == '*') return 3;
    return 0;
}
// Check if a character is a operator or not.
bool isOperator(char ch)
{
    return ch == '+' || ch == '.' || ch == '*';
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
            printf("\nValid Regex check1.2 : "BOLDRED"Failed\n" RESET);
            printf(BOLDRED "\nInvalid Regex Error : Empty Parenthesis Encountered\n" RESET);
            exit(1);
        }
        prev_val = regex[i];
        i++;
    }
    printf("\nValid Regex check1.2 : "BOLDGREEN"Passed\n" RESET);
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
        printf("Valid Regex check1.1 : "BOLDGREEN"Passed" RESET);
        empty_paranthesis_check(regex);
    }
    else
    {
        printf("Valid Regex check1.1 : "BOLDRED"Failed\n" RESET);
        printf(BOLDRED "\nInvalid Regex Error: Parenthesis are not properly placed\n" RESET);
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
            printf("Valid Regex check2 : "BOLDRED"Failed\n" RESET);
            printf(BOLDRED "\nInvalid Regex Error: invalid Symbol Found in Regex" RESET);
            printf( BOLDRED "\nInvalid Regex symbol found \"%c\"\n" RESET, regex[i]);
            exit(1);
        }
    }
    printf("Valid Regex check2 : "BOLDGREEN"Passed" RESET);
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
            printf("\nValid Regex check3 : "BOLDRED"Failed\n" RESET);
            printf(BOLDRED "\nInvalid Regex Error : Operators encountered side by side" RESET);
            printf( BOLDRED "\nThe op1 is \"%c\" and the op2 is \"%c\"\n" RESET ,prev_val,current_val);
            exit(1);
        }
        prev_val = regex[i];
        i++;
    }
    printf( "\nValid Regex check3 : "BOLDGREEN"Passed\n" RESET);
}

//function which will check the validity of the regex
void validation_of_regex(char * regex)
{
    paranthesis_check(regex); 
    symbol_check(regex);
    multi_operator_check(regex);
}

// This is a function to convert the given Regex to postfix
void Infix_to_Postfix(char *regex)
{
    node *stack = NULL; // stack for operator stack
    node *Postfix_stack = NULL; // Postfix_stack for the output


    for(int i=0; regex[i] !='\0';i++)
    {
        char ch = regex[i];
        int prec = precedence(ch);

        if(isalnum(ch))
        {
            Postfix_stack = push(Postfix_stack,ch);
        }
        else if(ch == '(')
        {
            stack = push(stack,ch);
        }
        else if (ch == ')')
        {
            while(!isEmpty(stack) && peek(stack) != '(')
            {
                Postfix_stack = push(Postfix_stack, peek(stack));
                stack = pop(&stack);
            }
            if (!isEmpty(stack) && peek(stack) == '(') {
                stack = pop(&stack); // Pop '(' but do not store it
            }
        }
        else if(isOperator(ch))
        {
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(ch))
            {
                Postfix_stack = push(Postfix_stack,peek(stack)); 
                stack = pop(&stack);
            }
            stack = push(stack, ch);
        }
    }
    while (!isEmpty(stack)) {
        Postfix_stack = push(Postfix_stack, peek(stack));
        stack = pop(&stack);
    }
    printStack(Postfix_stack);
}

int main()
{
    char regex[] = "(a)";
    validation_of_regex(regex);
    Infix_to_Postfix(regex);
    return 0;
}
