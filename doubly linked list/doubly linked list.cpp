#include <iostream>

struct Node
{
    int data;
    Node* next;
    Node* prev;
    Node(int data) : data(data), next(nullptr), prev(nullptr) {};

    void set(Node* next, Node* previous)
    {
        this->next = next;
        this->prev = previous;
    }

};

class LinkedList
{
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;

    void delete_node(Node* node)
    {
        delete node;
        length--;
    }

    //link existing node after first
    void link(Node* first, Node* second)
    {
        if (first)
        {
            first->next = second;
        }
        if (second)
        {
            second->prev = first;
        }
    }

    void add_new(Node* first, Node* second)
    {
         first->next = second;
         second->prev = first;
         length++;
    }

    //link new node between previous and next
    void link_between(Node* item, Node* previous, Node* next)
    {
        if (item && previous && next)
        {
            previous->next = item;
            item->prev = previous;
            item->next = next;
            next->prev = item;
            length++;
        }
    }

    //link cur prev to cur next
    Node* delete_and_link(Node* cur)
    {
        Node* previous = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);
        if (!previous->next)
        {
            tail = previous;
        }
        return previous;
    }

public:
    void print_head()
    {
        std::cout << "Head data: " << head->data << "\n";
    }

    void print_tail()
    {
        std::cout << "Tail data: " << tail->data << "\n";
    }    

    void print()
    {
        for (Node* cur = head; cur; cur = cur->next)
        {
            std::cout << cur->data << "  ";
        }
        std::cout << "    Length: " << length << "\n";
    }

    void print_reversed()
    {
        for (Node* cur = tail; cur; cur = cur->prev)
        {
            std::cout << cur->data << "  ";
        }
        std::cout << "    Length: " << length << "\n";
    }

    void insert_end(int value)
    {
        Node* item = new Node(value);

        if (!head)
        {
            head = tail = item;
            length++;
        }
        else
        {
            add_new(tail, item);
            tail = item;
        }
    }

    void insert_front(int value)
    {
        Node* item = new Node(value);

        if (!head)
        {
            head = tail = item;
            length++;
        }
        else
        {
            add_new(item, head);
            head = item;
        }
    }

    //ascending
    void insert_sorted(int value)
    {
        Node* item = new Node(value);

        if (!head)
        {
            insert_front(value);
        }
        else if (tail->data <= value)
        {
            insert_end(value);
        }
        else
        {
            for (Node* cur = head; cur; cur = cur->next)
            {
                if (item->data < cur->data)
                {
                    if (cur == head)
                    {
                        insert_front(value);
                        return;
                    }
                    else {
                        link_between(item, cur->prev, cur);
                        return;
                    }
                }
            } 
        }
    }

    void delete_front()
    {
        if (!head)
        {
            return;
        }

        Node* cur = head->next;
        delete_node(head);
        head = cur;
        if (head)
        {
            head->prev = nullptr;
        }
        else if (!length)
        {
            tail = nullptr;
        }
    }

    void delete_end()
    {
        if (!head)
        {
            return;
        }

        Node* cur = tail->prev;
        delete_node(tail);
        tail = cur;
        if (tail)
        {
            tail->next = nullptr;
        }
        else if (!length)
        {
            head = nullptr;
        }
    }

    void delete_key(int value)
    {
        if (!length)
        {
            return;
        }
        if (head->data == value)
        {
            delete_front();
        }
        else
        {
            for (Node* cur = head; cur; cur = cur->next)
            {
                if (cur->data == value)
                {
                    cur = delete_and_link(cur);
                    return;
                }
            }
        }
    }

    void delete_all_key(int value)
    {
        if (!length)
        {
            return;
        }
        else
        {
            insert_front(-1); //Dummy head
            for (Node* cur = head->next; cur; cur = cur->next)
            {
                if (cur->data == value)
                {
                    cur = delete_and_link(cur);
                }
            }
            delete_front();
        }
    }

    void delete_even_index()
    {
        if (!length)
        {
            return;
        }
        else
        {
            insert_front(-1); //Dummy head
            int i = 0;
            for (Node* cur = head->next; cur; cur = cur->next)
            {
                if (i % 2 == 0)
                {
                    cur = delete_and_link(cur);
                }
                i++;
            }
            delete_front();
        }
    }

    void delete_odd_index()
    {
        if (!length)
        {
            return;
        }
        else
        {
            insert_front(-1); //Dummy head
            int i = 0;
            for (Node* cur = head->next; cur; cur = cur->next)
            {
                if (i % 2 == 1)
                {
                    cur = delete_and_link(cur);
                }
                i++;
            }
            delete_front();
        }
    }

    bool is_palindrome()
    {
        Node* start = head;
        Node* end = tail;
        int times = length / 2;

        for (int i = 0; i < times; i++)
        {
            if (start->data != end->data)
            {
                return false;
            }
        }
        return true;
    }

    void print_middle()
    {
        if (!length)
        {
            std::cout << "No values in the list\n";
            return;
        }

        Node* start = head;
        Node* end = tail;

        while (start || end)
        {
            if (start == end)
            {
                std::cout << "Middle value: " << start->data << "\n";
                return;
            }
            else if (start->next == end)
            {
                std::cout << "Middle values: " << start->data << ", " << end->data << "\n";
                return;
            }
            start = start->next;
            end = end->prev;
        }       
    }

    //nth node from start on a 1 based index
    Node* get_nth_front(int n)
    {
        if (n > length)
        {
            n = length;
        }

        Node* cur = head;
        for (int i = 0; i < n; i++)
        {
            if (i == n-1)
            {
                return cur;
            }
            cur = cur->next;
        }
    }

    //nth node from end on a 1 based index
    Node* get_nth_back(int n)
    {
        if (n > length)
        {
            n = length;
        }

        Node* cur = tail;
        for (int i = 0; i < n; i++)
        {
            if (i == n - 1)
            {
                return cur;
            }
            cur = cur->prev;
        }
    }

    void reverse()
    {
        if (length < 2)
        {
            return;
        }

        Node* cur = head;
        tail = head;
        Node* previous = nullptr;
        Node* next = nullptr;
        while (cur)
        {
            previous = cur->prev;
            next = cur->next;

            cur->next = previous;
            cur->prev = next;

            cur = next;
        }
        head = previous->prev;
    }

    void merge_sorted_list(LinkedList& other)
    {
        if (!other.head)
        {
            return;
        }

        if (head)
        {
            Node* cur1 = head;
            Node* cur2 = other.head;
            Node* last{};
            head = nullptr;

            while (cur1 && cur2)
            {
                Node* next{};
                
                if (cur1->data <= cur2->data)
                {
                    next = cur1;
                    cur1 = cur1->next;
                }
                else
                {
                    next = cur2;
                    cur2 = cur2->next;
                }
                link(last, next);
                last = next;
                if (!head)
                {
                    head = last;
                }
            }
            if (cur2)
            {
                tail = other.tail;
                link(last, cur2);
            }
            else if (cur1)
            {
                link(last, cur1);
            }
        }
        else
        {
            head = other.head;
            tail = other.tail;
        }

        length += other.length;
        other.head = other.tail = nullptr;
        other.length = 0;
    }
};

int main()
{
    LinkedList list1;
    list1.insert_end(5);
    list1.insert_end(23);
    list1.insert_end(34);
    list1.insert_end(53);
    list1.insert_end(63);

    LinkedList list2;
    list2.insert_end(6);
    list2.insert_end(7);
    list2.insert_end(34);
    list2.insert_end(64);
    list2.insert_end(436);
    list2.print();
    list2.merge_sorted_list(list1);
    list2.print();
    //std::cout << "Data: " << list1.get_nth_back(7)->data << "\n";



    std::cout << "No Runtime Error\n";
}

