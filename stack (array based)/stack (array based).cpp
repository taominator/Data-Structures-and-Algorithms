#include <iostream>
#include <cassert>

class Stack
{
private:
    int size;
    int top; //index of last element
    int* array;
public:
    Stack(int size) : size(size), top(-1) 
    {
        array = new int[size];
    }

    bool isFull()
    {
        return top == size - 1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    void display()
    {
        for (int i = 0; i <= top; i++)
        {
            std::cout << array[i] << "  ";
        }
        std::cout << "\n";
    }

    void display_reverse()
    {
        for (int i = top; i >= 0; i--)
        {
            std::cout << array[i] << "  ";
        }
        std::cout << "\n";
    }

    void push(int x)
    {
        assert(!isFull());
        array[++top] = x;
    }

    int pop()
    {
        assert(!isEmpty());
        return array[top--];
    }

    int peek()
    {
        assert(!isEmpty());
        return array[top];
    }
    
    void insert_bottom(int value)
    {
        int temp;

        if (!isEmpty())
        {
            temp = pop();
            insert_bottom(value);
        }
        else if (isEmpty())
        {
            push(value);
            return;
        }
        push(temp);
    }

    void reverse()
    {
        int temp;

        if (!isEmpty())
        {
            temp = pop();
            reverse();
        }
        else if (isEmpty())
        {
            return;
        }
        insert_bottom(temp);
    }
};

std::string reverse_subwords(std::string line)
{
    std::string result;

    line += " "; //dummy space to force formation of last subgroup
    Stack stack(line.size());
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ')
        {
            while (!stack.isEmpty())
            {
                result += stack.pop();
            }
            result += ' ';
        }
        else
        {
            stack.push(line[i]);
        }
    }
    return result;
}

int reverse_num(int num)
{
    if (!num) {
        return 0;
    }

    Stack stack(25);

    while (num)
    {
        stack.push(num % 10);
        num /= 10;
    }

    int times = 1;
    while (!stack.isEmpty())
    {
        num += stack.pop() * times;
        times *= 10;
    }
    return num;
}

char get_open_match(char ch)
{
    if (ch == ')')
    {
        return '(';
    }
    else if (ch == ']')
    {
        return '[';
    }
    else
    {
        return '{';
    }
}

bool isValid(std::string str)
{
    Stack parantheses(str.size());

    for (int i = 0; i < str.size(); i++)
    {
        char ch = str[i];

        if (ch == '(' || ch == '[' || ch == '{')
        {
            parantheses.push(ch);
        }
        else if (parantheses.isEmpty() || parantheses.pop() != get_open_match(ch))
        {
            return false;
        }
    }
    return parantheses.isEmpty();
}

std::string remove_duplicates(std::string str)
{
    Stack stack(str.length());

    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if (!stack.isEmpty() && ch == stack.peek())
        {
            stack.pop();
        }
        else
        {
            stack.push(ch);
        }
    }
    str = "";
    while (!stack.isEmpty())
    {
        str = char(stack.pop()) + str;
    }
    return str;
}

void asteroid_collision(int arr[], int len)
{
    Stack result(len);

    for (int i = 0; i < len; i++)
    {
        int asteroid = arr[i];
        bool is_exploded = false;
        while (!result.isEmpty() && asteroid < 0 && result.peek() > 0)
        {
            if (result.peek() < -asteroid)
            {
                result.pop();
                continue;
            }
            else if (result.peek() == asteroid)
            {
                result.pop();
                is_exploded = true;
                break;
            }
        }
        if (!is_exploded)
        {
            result.push(asteroid);
        }
        result.display_reverse();
    }
}

int scoreOfParentheses(std::string str)
{
    Stack stack(str.size());

    stack.push(0); //dummy value

    for (int i = 0; i < (int)str.size(); i++) 
    {
        char c = str[i];

        if (c == '(')
        {
            stack.push(0);
        }
        else
        {
            int last = stack.pop();

            if (last == 0)
            {
                last = 1;
            }
            else
            {
                last *= 2;
            }
            int parent_par = stack.pop() + last;
            stack.push(parent_par);
        }
    }
    return stack.pop();
}


int main()
{
    //std::cout << reverse_subwords("Hello World!") << "\n";
    //std::cout << reverse_num(9346278) << "\n";
    //std::cout << isValid("({}()[()])") << "\n";
    //std::cout << remove_duplicates("aabacaacd") << "\n";
    //int a[] = { 5, 10, -5 };
    //asteroid_collision(a, 3);

    std::cout << scoreOfParentheses("()((())())") << "\n";

    //Stack stack(10);
    //stack.push(7);
    //stack.push(3);
    //stack.push(9);
    //stack.push(5);
    //stack.display();
    //stack.insert_bottom(11);
    //stack.display();
    //stack.reverse();
    //stack.display();
}

