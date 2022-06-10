#include <iostream>
#include <cassert>
#include <vector>

struct Node
{
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {};

    void print1(Node* head)
    {
        while (head != nullptr)
        {
            std::cout << head->data << "  ";
            head = head->next;
        }
        std::cout << "\n";
    }

    //recursive
    void print2(Node* head)
    {
        if (head == nullptr)
        {
            std::cout << "\n";
            return;
        }
        std::cout << head->data << "  ";
        print2(head->next);
    }

    //reversed recursive
    void print3_reversed(Node* head)
    {
        if (head == nullptr)
        {
            return;
        }
        print3_reversed(head->next);
        std::cout << head->data << "  ";
    }

};

class LinkedList
{
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;

    void embed_after(Node* previous, int n)
    {
        Node* item = new Node(n);
        item->next = previous->next;
        previous->next = item;
        length++;
    }

    //Given node src, link target after it with my list before/after
    void insert_after(Node* src, Node* target)
    {
        target->next = src->next;
        src->next = target;
        length++;
    }

    //delete given node and return next node
    Node* move_and_delete(Node* node)
    {
        Node* temp = node->next;
        delete node;
        return temp;
    }

public:
    //Delete copy
    LinkedList(){}
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator= (const LinkedList& another) = delete;

    ~LinkedList()
    {
        Node* next_head = nullptr;
        while (head)
        {
            next_head = head->next;
            delete head;
            //std::cout << "deleted\n";
            head = next_head;
        }
    }

    void print()
    {
        //DON"T CORRUPT HEAD to prevent PERMANENT LOSS
        Node* temp_head = head;
        while (temp_head != nullptr)
        {
            std::cout << temp_head->data << "  ";
            temp_head = temp_head->next;
        }
        std::cout << "   Length: " << length << "\n";
    }

    void print2()
    {
        for (Node* cur = head; cur; cur = cur->next)
        {
            std::cout << cur->data << "  ";
        }
        std::cout << "\n";
    }

    void insert_end(int value)
    {
        Node* item = new Node(value);

        if (!head)
        {
            head = item;
            length++;
        }
        else if (!tail)
        {
            head->next = item;
            tail = item;
            length++;
        }
        else
        {
            tail->next = item;
            tail = item;
            length++;
        }
    }

    // 1 based index
    Node* get_nth(int n)
    {
        Node* item = head;
        for (int i = 0; i < n; i++)
        {
            if (i == n - 1)
            {
                return item;
            }
            item = item->next;
        }
        return nullptr;
    }

    // 0 based index
    Node* get_item(int n)
    {
        Node* item = head;
        for (int i = 0; i <= n; i++)
        {
            if (i == n)
            {
                return item;
            }
            item = item->next;
        }
        return nullptr;
    }

    //returns index of first node with value
    int search(int value)
    {
        int index = 0;
        for (Node* item = head; item; item = item->next, index++)
        {
            if (item->data == value)
            {
                return index;
            }
        }
        return -1;
    }

    //shift searched value one node left
    int search_shift_left(int value)
    {
        int index = 0;
        Node* previous = nullptr;
        for (Node* current = head; current; current = current->next)
        {
            if (current->data == value)
            {
                if (!previous)
                {
                    return index;
                }
                std::swap(previous->data, current->data);
                return index - 1;
            }
            previous = current;
            index++;
        }
    }

    void insert_front(int value)
    {
        Node* item = new Node(value);
        item->next = head;
        if (length == 1)
        {
            tail = head;
        }
        head = item;
        length++;
    }

    Node* get_nth_back(int n)
    {
        int index = length - n;
        Node* item = head;
        for (int i = 0; i <= index; i++)
        {
            if (i == index)
            {
                return item;
            }
            item = item->next;
        }
        return nullptr;
    }

    bool is_same1(const LinkedList& other)
    {
        Node* h1 = head, *h2 = other.head;
        while (h1 && h2)
        {
            if (h1->data != h2->data)
            {
                return false;
            }
            h1 = h1->next;
            h2 = h2->next;
        }
        return !(h1 && h2); //making sure both end together
    }

    bool is_same2(const LinkedList& other)
    {
        if (length != other.length)
        {
            return false;
        }

        Node* other_h = other.head;
        for (Node* current = head; current; current = current->next)
        {
            if (current->data != other_h->data)
            {
                return false;
            }
            other_h = other_h->next;
        }
        return true;
    }

    void delete_front()
    {
        Node* next = head->next;
        delete head;
        head = next;
        if (length != 0)
        {
        length--;
        }
    }

    void delete_last()
    {
        if (length == 0) 
        {
            return;
        }
        else if (length == 1)
        {
            delete_front();
            return;
        }
        Node* current = head;
        Node* previous = nullptr;
        for (int i = 0; i < length; i++)
        {
            if (i == length - 1)
            {
                delete tail;
                if (length == 2)
                {
                    tail = nullptr;
                    head->next = tail;
                }
                else
                {
                tail = previous;
                tail->next = nullptr;
                }
            }
            previous = current;
            current = current->next;
        }
        length--;
    }

    //0 based index delete
    void delete_index(int index)
    {
        assert(index < length);

        if (length < 1)
        {
            return;
        }
        else if (length == 1)
        {
            delete_front();
            return;
        }
        else if (index == 0)
        {
            delete_front();
            return;
        }
        else if (index == length-1)
        {
            delete_last();
            return;
        }

        Node* current = head;
        Node* previous = nullptr;
        for (int i = 0; i <= index; i++)
        {
            if (i == index)
            {
                previous->next = current->next;
                delete current;
                length--;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    void delete_value(int value)
    {
        int index = search(value);
        delete_index(index);
    }

    void swap_pair()
    {
        Node* current = head;
        Node* previous = nullptr;
        for (int i = 0; i < length; i++)
        {
            if (i % 2 == 1)
            {
                int temp = previous->data;
                previous->data = current->data;
                current->data = temp;
            }
            previous = current;
            current = current->next;
        }
    }

    void reverse_list()
    {
        Node* current = head;
        Node* previous = nullptr;
        Node* next = nullptr;
        head = tail;
        tail = current;
        for (int i = 0; i < length; i++)
        {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
    }

    void delete_even()
    {
        Node* current = head;
        Node* previous = nullptr;
        Node* next = nullptr;
        for (int i = 0; i < length; i++)
        {
            next = current->next;
            if (i % 2 == 1)
            {
                previous->next = next;
                previous = current;
                delete current;
                length--;
                current = next;
                continue;
            }
            previous = current;
            current = next;
        }
    }

    void insert_sorted(int n)
    {
        if (length == 0)
        {
            insert_front(n);
            return;
        }

        Node* current = head;
        Node* previous = nullptr;
        for (int i = 0; i < length; i++)
        {
            if (n < current->data)
            {
                if (i == 0)
                {
                    insert_front(n);
                    return;
                }
                embed_after(previous, n);
                return;
            }
            previous = current;
            current = current->next;
        }
        insert_end(n);
    }

    //swap head and tail nodes
    void swap_ends()
    {
        get_item(length - 2)->next = head;
        tail->next = head->next;
        head->next = nullptr;
        std::swap(head, tail);
    }

    void left_rotate(int times)
    {
        times = times % length;
        for (int i = 0; i < times; i++)
        {
            tail->next = head;
            tail = head;
            head = head->next;
            tail->next = nullptr;
        }
    }

    void remove_deplicates()
    {
        std::vector<int> values;
        Node* current = head;
        Node* previous = nullptr;
        Node* temp = nullptr;

        //save length in new int variable as length could be reduced through deletion;
        int l = length;
        for (int i = 0; i < l; i++)
        {
            if (std::count(values.begin(), values.end(), current->data))
            {
                previous->next = current->next;
                temp = current;
                current = current->next;
                delete temp;
                length--;
                continue;

            }
            values.push_back(current->data);
            previous = current;
            current = current->next;
        }
    }

    void remove_last_occurence(int n)
    {
        Node* current = head;
        int latest_index = -1;
        for (int i = 0; i < length; i++)
        {
            if (current->data == n)
            {
                latest_index = i;
            }
            current = current->next;
        }
        if (latest_index + 1)
        {
            delete_index(latest_index);
        }
    }

    //move all nodes with key to back
    void move_to_back(int n)
    {
        int times_deleted = 0;
        Node* current = head;
        for (int i = 0; i < length; i++)
        {
            if (current->data == n)
            {
                current = current->next;
                delete_index(i);
                i--;
                times_deleted++;
                continue;
            }
            current = current->next;
        }
        for (int i = 0; i < times_deleted; i++)
        {
            insert_end(n);
        }
    }

    int max_recursive(Node* head = nullptr, bool is_first_call = true)
    {
        if (is_first_call)
        {
            return this->max_recursive(this->head, false);
        }

        if (head == nullptr)
        {
            return -999999999;
        }

        return std::max(head->data, this->max_recursive(head->next, false));
    }

    //rearranges odd index nodes to come first
    void even_first()
    {
        if (length < 2)
        {
            return;
        }
        
        Node* first_odd = head->next;
        Node* current_even = head;
        Node* next_odd = nullptr;

        while (current_even->next && current_even->next->next)
        {
            next_odd = current_even->next;
            current_even->next = current_even->next->next;
            next_odd->next = next_odd->next->next;
            current_even = current_even->next;  
            if (length % 2 == 1)
            {
                tail = next_odd;
            }
        }
            current_even->next = first_odd;
    }

    void insert_alternate(LinkedList& another)
    {
        if (another.length == 0)
        {
            return;
        }

        if (length == 0)
        {
            //copy data
            head = another.head;
            tail = another.tail;
            length = another.length;
            return;
        }

        Node* cur2 = another.head;
        for (Node* cur1 = head; cur1 && cur2;)
        {
            Node* cur2_next = cur2->next;
            insert_after(cur1, cur2);
            another.length--;
            cur2 = cur2_next;
            if (cur1 == tail)
            {
                tail = another.tail;
                cur1->next->next = cur2;
                length += another.length;
                break;
            }
            cur1 = cur1->next->next;
        }
        another.head = another.tail = nullptr;
    }

    void addition(LinkedList& other)
    {
        Node* my_cur = head;
        Node* other_cur = other.head;
        int my_value, other_value, carry = 0;

        while (my_cur || other_cur)
        {
            my_value = other_value = 0;
            if (my_cur)
            {
                my_value = my_cur->data;
            }
            if (other_cur)
            {
                other_value = other_cur->data;
                other_cur = other_cur->next;
            }

            my_value += other_value + carry;
            carry = my_value / 10;
            my_value %= 10;

            if (my_cur)
            {
                my_cur->data = my_value;
                my_cur = my_cur->next;
            }
            else
            {
                insert_end(my_value);
            }
        }
        if (carry)
        {
            insert_end(carry);
        }
    }

    //remove all nodes whose values are repeated
    void remove_repeated()
    {
        insert_front(-1); //dummy head to not lose track of head
        Node* previous = head;
        Node* cur = head->next; //Actual head

        while (cur)
        {
            //keep removing blocks of same value
            bool any_removed = false;
            while (cur && cur->next && cur->data == cur->next->data)
            {
                int block_value = cur->data;
                any_removed = true;
                while (cur && cur->data == cur->next->data)
                {
                    cur = move_and_delete(cur);
                }
            }
            if (any_removed)
            {
                cur = move_and_delete(cur);
                if (!cur)
                {
                    tail = previous;
                }
                previous->next = cur; //linked after removed nodes
                previous = cur;
            }
            else
            {
                //no duplicates. connect and use tail for now
                tail = cur;
                previous = cur;
                cur = cur->next;
            }
        }
        previous = head->next; //actual head
        delete_front(); //remove dummy head
        head = previous;
        if (!head)
        {
            tail = head;
        }
    }

    void reverse_chain(int n)
    {
        if (n > length)
        {
            n = length;
        }

        Node* current = head;
        Node* previous = nullptr;
        Node* next = nullptr;
        Node* original_head = this->head;
        Node* original_head_next = get_item(n);

        for (int i = 0; i < n; i++)
        {
            next = current->next;
            current->next = previous;

            if (i == n - 1)
            {
                head = current;
            }

            previous = current;
            current = next;
        }
        original_head->next = original_head_next;
    }

    void reverse_chain_recursive(int n, Node* head = nullptr,  bool is_first_call = true)
    {
        if (is_first_call)
        {
            if (!this->head)
            {
                return;
            }

            if (n > length)
            {
                n = length;
            }

            Node* original_head = this->head;
            Node* original_head_next = get_item(n);
            reverse_chain_recursive(n - 2, this->head->next, false);
            original_head->next->next = original_head;
            original_head->next = original_head_next;
            return;
        }

        if (n == 0)
        {
            this->head = head;
            return;
        }
        else if (!head->next)
        {
            this->tail = this->head;
            this->head = head;
            return;
        }

        reverse_chain_recursive(n - 1, head->next, false);
        head->next->next = head;

    }
};

int main()
{
    /*Node* node1 = new Node(6);
    Node* node2 = new Node(10);
    Node* node3 = new Node(8);
    Node* node4 = new Node(15);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = nullptr;

    node1->print1(node1);
    node1->print2(node1);
    node1->print3_reversed(node1);
    std::cout << "\n";

    delete node1;
    delete node2;
    delete node3;
    delete node4;

    LinkedList linkedlist;
    linkedlist.insert_end(55);
    linkedlist.insert_end(85);
    linkedlist.insert_end(98);
    linkedlist.insert_end(4);
    linkedlist.insert_end(97);
    linkedlist.print();
    linkedlist.print2();

    std::cout << "-------------------------\n";

    std::cout << linkedlist.get_nth(2)->data << "\n";
    std::cout << linkedlist.get_nth(5)->data << "\n";

    std::cout << linkedlist.get_item(1)->data << "\n";
    std::cout << linkedlist.get_item(4)->data << "\n";

    std::cout << "-------------------------\n";

    std::cout << linkedlist.search(55) << "\n";
    std::cout << linkedlist.search(97) << "\n";
    std::cout << linkedlist.search(9999) << "\n";

    std::cout << "-------------------------\n";

    std::cout << linkedlist.search_shift_left(97) << "\n";
    std::cout << linkedlist.search_shift_left(97) << "\n";
    linkedlist.print();

    std::cout << "-------------------------\n";

    linkedlist.insert_front(22);
    linkedlist.insert_front(39);
    linkedlist.print();

    std::cout << "-------------------------\n";

    std::cout << linkedlist.get_nth_back(3)->data << "\n";

    std::cout << "-------------------------\n";

    LinkedList list2;
    list2.insert_front(5);
    list2.insert_front(8);
    list2.insert_front(11);
    list2.print();

    std::cout << "-------------------------\n";

    LinkedList list3;
    list3.insert_front(5);
    list3.insert_front(8);
    list3.insert_front(11);

    std::cout << list2.is_same1(list3) << "\n";
    std::cout << list2.is_same2(list3) << "\n";

    std::cout << "-------------------------\n";

    list3.delete_last();
    list3.delete_last();
    list3.print();

    std::cout << "-------------------------\n";

    LinkedList list4;
    for (int i = 0; i < 10; i++)
    {
        list4.insert_end(i);
    }
    list4.print();
    list4.delete_index(1);
    list4.delete_value(9);
    list4.print();*/

    /*LinkedList list5;
    for (int i = 0; i < 12; i++)
    {
        list5.insert_end(i);
    }
    list5.print();
    list5.swap_pair();
    list5.print();
    std::cout << "------------------\n";
    list5.reverse_list();
    list5.print();
    std::cout << "------------------\n";
    list5.delete_even();
    list5.print();
    std::cout << "------------------\n";

    LinkedList list6;
    list6.insert_sorted(10);
    list6.insert_sorted(2);
    list6.insert_sorted(30);
    list6.insert_sorted(4);
    list6.insert_sorted(1);
    list6.insert_sorted(300);
    list6.print();
    std::cout << "------------------\n";
    list6.swap_ends();
    list6.print();
    std::cout << "------------------\n";
    list6.left_rotate(3);
    list6.print();
    std::cout << "------------------\n";

    LinkedList list7;
    list7.insert_end(1);
    list7.insert_end(2);
    list7.insert_end(1);
    list7.insert_end(3);
    list7.insert_end(2);
    list7.insert_end(4);
    list7.insert_end(3);
    list7.insert_end(5);
    list7.insert_end(2);
    list7.insert_end(4);
    //std::cout << "Max Recursive: " << list7.max_recursive(list7.head, true) << "\n";
    list7.print();
    list7.addition(list6);
    list7.print();*/

    LinkedList list8;
    list8.insert_end(1);
    list8.insert_end(1);
    list8.insert_end(5);
    list8.insert_end(2);
    list8.insert_end(2);
    list8.insert_end(2);
    list8.insert_end(3);
    list8.print();
    list8.reverse_chain_recursive(20);
    list8.print();
    list8.reverse_chain(5);
    list8.print();


    std::cout << "No Runtime Error\n";
}

