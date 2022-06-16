#include <iostream>
#include <cassert>
#include <doublylinkedlist.h>

class CircularQueue //array based
{
    int size = 0;
    int front = 0;
    int rear = 0;
    int added_elements = 0;
    int* array;


    int next(int pos)
    {
        return (pos + 1) % size;
    }

    int isEmpty()
    {
        return added_elements == 0;
    }

    int isFull()
    {
        return added_elements == size;
    }

public:

    CircularQueue(int size) : size(size)
    {
        array = new int[size];
    }

    void enqueue(int value)
    {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }

    int dequeue()
    {
        assert(!isEmpty());
        int value = array[front];
        front = next(front);
        added_elements--;
        return value;
    }

    void display()
    {
        std::cout << "Front: " << front << " Rear: " << rear << "\n";

        for (int cur = front, step = 0; step < added_elements; cur = next(cur), step++)
        {
            std::cout << array[cur] << "  ";
        }
        std::cout << "\n";
    }
};

class LinkedQueue
{
    LinkedList list;

public:
    void enqueue(int value)
    {
        list.insert_end(value);
    }

    int dequeue()
    {
        return list.delete_front();
    }

    void display()
    {
        list.print();
    }

    bool isEmpty()
    {
        return list.isEmpty();
    }
};

class PriorityQueue //for priorities 1, 2 and 3
{
    int added_elements = 0;
    LinkedQueue q1, q2, q3;

public:
    void enqueue(int value, int priority)
    {
        if (priority == 3)
        {
            q3.enqueue(value);
        }
        else if (priority == 2)
        {
            q2.enqueue(value);
        }
        else if (priority == 1)
        {
            q1.enqueue(value);
        }
        else
        {
            assert(false);
        }
        added_elements++;
    }

    int dequeue()
    {
        if (!q3.isEmpty())
        {
            return q3.dequeue();
        }
        else if (!q2.isEmpty())
        {
            return q2.dequeue();
        }
        else if (!q1.isEmpty())
        {
            return q1.dequeue();
        }
        else
        {
            assert(false);
        }
    }

    void display()
    {
        if (!q3.isEmpty())
        {
            std::cout << "Priority #3 tasks: ";
            q3.display();
        }
        if (!q2.isEmpty())
        {
            std::cout << "Priority #2 tasks: ";
            q2.display();
        }
        if (!q1.isEmpty())
        {
            std::cout << "Priority #1 tasks: ";
            q1.display();
        }
        else
        {
            std::cout << "Queue is empty.\n";
        }
    }
};

int main()
{
    PriorityQueue q1;
    q1.enqueue(15, 3);
    q1.enqueue(25, 1);
    q1.enqueue(35, 3);
    q1.enqueue(45, 2);
    q1.enqueue(55, 2);
    q1.enqueue(65, 3);
    q1.display();
}
