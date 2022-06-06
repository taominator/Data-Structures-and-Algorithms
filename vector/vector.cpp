#include <iostream>
#include <assert.h>

class Vector
{
public:
    int* m_arr;
    int m_size;
    int m_capacity;

public:
    Vector(int size) : m_size(size), m_capacity(size * 5)
    {
        if (m_size < 1)
        {
            m_size = 1;
        }
        m_arr = new int[m_capacity];
    }

    ~Vector()
    {
        delete[] m_arr;
        m_arr = nullptr;
    }

    int get(int index)
    {
        assert(index >= 0 && index < m_size);
        return m_arr[index];
    }

    void set(int index, int value)
    {
        assert(index >= 0 && index < m_size);
        m_arr[index] = value;
    }

    void print()
    {
        for (int i = 0; i < m_size; i++)
        {
            std::cout << m_arr[i] << "  ";
            std::cout << "\n";
        }
    }

    int find(int value)
    {
        for (int i = 0; i < m_size; i++)
        {
            if (m_arr[i] == value) return i;
        }
        return -1; //-1 for not found
    }

    int get_front()
    {
        return m_arr[0];
    }

    int get_back()
    {
        return m_arr[m_size - 1];
    }

    void push_back(int value)
    {
        if (m_size == m_capacity)
        {
            expand_capacity();
        }
        m_arr[m_size] = value;
        m_size++;
    }

    void expand_capacity()
    {
        m_capacity *= 5;
        std::cout << "Expanded capacity to " << m_capacity << "\n";

        int* arr2 = new int[m_capacity];
        for (int i = 0; i < m_size; i++)
        {
            arr2[i] = m_arr[i];
        }
        std::swap(m_arr, arr2);
        delete[] arr2;
    }

    void insert(int index, int value)
    {
        assert(index >= 0 && index < m_size);

        if (m_size == m_capacity)
        {
            expand_capacity();
        }
        for (int p = m_size - 1; p >= index; p--)
        {
            m_arr[p + 1] = m_arr[p];
        }
        m_arr[index] = value;
        m_size++;
    }

    void rightRotate()
    {
        int last_element = m_arr[m_size - 1];

        for (int p = m_size; p > 0; p--)
        {
            m_arr[p] = m_arr[p - 1];
        }
        m_arr[0] = last_element;
    }

    void leftRotate()
    {
        int first_element = m_arr[0];

        for (int i = 0; i < m_size; i++)
        {
            m_arr[i] = m_arr[i + 1];
        }
        m_arr[m_size - 1] = first_element;
    }

    void rightRotate(int times)
    {
        times %= m_size;
        while (times--)
        {
            rightRotate();
        }
    }

    void leftRotate(int times)
    {
        times %= m_size;
        while (times--)
        {
            leftRotate();
        }
    }

    //less efficient pop()
    /*int pop(int index)
    {
        int return_value = m_arr[index];
        int* arr2 = new int[m_size-1];
        for (int i = 0; i < m_size; i++)
        {
            if (i < index)
            {
                arr2[i] = m_arr[i];
            }
            else if (i == index)
            {
                continue;
            }
            else if(i > index)
            {
                arr2[i - 1] = m_arr[i];
            }
        }
        std::swap(m_arr, arr2);
        m_size--;

        delete[] arr2;
        return return_value;
    }*/

    int pop(int index)
    {
        assert(index >= 0 && index < m_size);

        int val = m_arr[index];
        for (int i = index + 1; i < m_size; i++)
        {
            m_arr[i - 1] = m_arr[i];
        }
        m_size--;
        return val;
    }

    //my find_transposition()
    /*int find_transposition(int value)
    {
        int index = find(value);
        int temp_value = m_arr[index];

        if (index != 0)
        {
            m_arr[index] = m_arr[index - 1];
            m_arr[index-1] = temp_value;
            index -= 1;
        }
        return index;
    }*/

    int find_transposition(int value)
    {
        for (int i = 0; i < m_size; i++)
        {
            if (m_arr[i] == value)
            {
                if (i == 0)
                {
                    return 0;
                }

                std::swap(m_arr[i], m_arr[i - 1]);
                return i - 1;
            }
        }
        return -1; //not found
    }
};

int main()
{
    Vector v(5);
    for (int i = 0; i < 5; i++)
    {
        v.set(i, i);
    }
    v.push_back(345);
    v.push_back(34);
    v.push_back(56);

    v.insert(3, 69);

    v.print();
    std::cout << "----------------------------\n";

    v.find_transposition(69);
    std::cout << v.find_transposition(69) << "**\n";

    v.print();
}
