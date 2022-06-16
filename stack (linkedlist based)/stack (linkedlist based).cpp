#include <iostream>
#include <cassert>

class Stack
{
private:
    struct Node
    {
        int data;
        Node* next = nullptr;
        Node(int data) : data(data) {}
    };

    Node* head = nullptr;

public:
    void push(int value)
    {
        Node* item = new Node(value);
        item->next = head;
        head = item;
    }

    bool isEmpty()
    {
        return !head;
    }

    int pop()
    {
        assert(!isEmpty());
        int element = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return element;
    }

    int peek()
    {
        assert(!isEmpty());
        int element = head->data;
        return element;
    }
};

int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}

std::string infixToPostfix(std::string& infix)
{
    Stack operators;
    std::string postfix;

    for (int i = 0; i < infix.size(); i++)
    {
        if (std::isdigit(infix[i]))
        {
            postfix += infix[i];
        }
        else
        {
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(infix[i]))
            {
                postfix += operators.pop();
            }
            operators.push(infix[i]);
        }
    }

    while (!operators.isEmpty())
    {
        postfix += operators.pop(); 
    }

    return postfix;
}

int main()
{
    std::string infix = "2+5*3";
    std::cout << infixToPostfix(infix) << "\n";
}

