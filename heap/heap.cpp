#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <vector>
#include <string>



class MinHeap
{
    int* array{};
    int size{};
    int capacity{ 1000 };

//get children or parent node
int left(int node)
{
    int p = 2 * node + 1;
    if (p >= size)
    {
        return -1;
    }
    return p;
}
int right(int node)
{
    int p = 2 * node + 2;
    if (p >= size)
    {
        return -1;
    }
    return p;
}
int parent(int node)
{
    return node == 0 ? -1 : (node - 1) / 2;
}

public:
    MinHeap()
    {
        array = new int[capacity];
        size = 0;
    }

    ~MinHeap()
    {
        delete array;
        array = nullptr;
    }

    bool isEmpty()
    {
        if (size > 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    int top()
    {
        assert(!isEmpty());
        return array[0];
    }

    void heapify_up(int child_pos)
    {
        int parent_pos = parent(child_pos);
        if (child_pos == 0 || array[parent_pos] <= array[child_pos])
        {
            return;
        }

        std::swap(array[child_pos], array[parent_pos]);
        heapify_up(parent_pos);
    }

    void push(int value)
    {
        assert(size + 1 <= capacity);
        array[size++] = value;
    }

    void heapify_down(int parent_pos)
    {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if (child_pos == -1)
        {
            return;
        }

        if (right_child != -1 && array[right_child] < array[child_pos])
        {
            child_pos = right_child;
        }

        if (array[parent_pos] > array[child_pos])
        {
            std::swap(array[parent_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    void pop()
    {
        assert(!isEmpty());
        array[0] = array[--size];
        heapify_down(0);
    }

    void heapify()
    {
        for (int i = size - 1; i >= 0; i--)
        {
            heapify_down(i);
        }
    }

    MinHeap(const std::vector<int>& v)
    {
        assert(v.size() <= capacity);
        array = new int[capacity];
        size = v.size();

        for (int i = 0; i < v.size(); i++)
        {
            array[i] = v[i];
        }

        heapify();
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << array[i] << "  ";
        }
        std::cout << "\n";
    }

    void print_less_than(int val, int pos = 0)
    {
        if (isEmpty())
        {
            return;
        }

        if (pos == -1 || array[pos] >= val)
        {
            return;
        }

    std::cout << array[pos] << "  ";

    print_less_than(val, left(pos));
    print_less_than(val, right(pos));
    }

    bool is_heap(int pos)
    {
        if (isEmpty())
        {
            return false;
        }

        if (pos == -1)
        {
            return true;
        }

        int left_child = left(pos);
        int right_child = right(pos);

        if (left_child == -1 || array[pos] > array[left_child])
        {
            return false;
        }

        if (right_child == -1 || array[pos] > array[right_child])
        {
            return false;
        }

        return is_heap(left_child) && is_heap(left_child);
    }

    bool is_heap_array(int* p, int n)
    {
        int* old_array = array;
        int old_size = size;

        array = p;
        size = n;

        bool result = is_heap(0);

        array = old_array;
        size = old_size;

        return result;
    }

    void heap_sort(int* p, int n)
    {
        if (n <= 1)
        {
            return;
        }

        int* old_array = array;
        int old_size = size;

        array = p;
        size = n;

        heapify();

        while (size--)
        {
            std::swap(array[0], array[size]);
            heapify_down(0);
        }

        for (int i = 0; i < n / 2; i++)
        {
            std::swap(array[i], array[n - i - 1]);
        }

        array = old_array;
        size = old_size;
    }

};

class MaxHeap2
{
private:
    MinHeap heap;

    std::vector<int> mutiply_neg1(const std::vector<int>& v)
    {
        std::vector<int> res = v;
        for (int i = 0; i < res.size(); i++)
        {
            res[i] *= -1;
        }
        return res;
    }

public:
    MaxHeap2() {}

    MaxHeap2(const std::vector<int>& v) : heap(mutiply_neg1(v)) {}

    int top()
    {
        return -heap.top();
    }

    void push(int value)
    {
        heap.push(-value);
    }

    void pop()
    {
        heap.pop();
    }

    bool isEmpty()
    {
        return heap.isEmpty();
    }

    void print()
    {
        heap.print();
    }
};

//-------------------------------------------------------------------------------------------------------------

class MaxHeap {
private:
    int capacity{ 1000 };
    int* array{};
    int size{};

    int left(int node) {
        int p = 2 * node + 1;
        if (p >= size)
            return -1;
        return p;
    }
    int right(int node) {
        int p = 2 * node + 2;
        return p >= size ? -1 : p;
    }
    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    void heapify_up(int child_pos) {
        // stop when parent is smaller (or no parent)
        int par_pos = parent(child_pos);
        if (child_pos == 0 || array[par_pos] > array[child_pos])
            return;

        std::swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int parent_pos) {	// O(logn)
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if (child_pos == -1) // no children
            return;
        // is right bigger than left?
        if (right_child != -1 && array[right_child] > array[child_pos])
            child_pos = right_child;

        if (array[parent_pos] < array[child_pos]) {
            std::swap(array[parent_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    void heapify() {	// O(n)
        for (int i = size / 2 - 1; i >= 0; --i)
            heapify_down(i);
    }
public:

    MaxHeap() {
        array = new int[capacity] {};
        size = 0;
    }

    MaxHeap(const std::vector<int>& v) {
        assert((int)v.size() <= capacity);
        array = new int[capacity] {};
        size = v.size();

        for (int i = 0; i < (int)v.size(); ++i)
            array[i] = v[i];

        heapify();
    }

    ~MaxHeap() {
        delete[] array;
        array = nullptr;
    }

    int top() {
        assert(!isempty());
        return array[0];
    }

    void push(int key) {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    void pop() {
        assert(!isempty());
        array[0] = array[--size];
        heapify_down(0);
    }

    bool isempty() {
        return size == 0;
    }

    int sz() {
        return size;
    }
};

class KthNumberProcessor {
private:
    int k;
    MaxHeap q;

public:
    KthNumberProcessor(int k) : k(k) {
    }

    int next(int new_num) {

        if (q.sz() < k)
            q.push(new_num);
        else if (new_num < q.top()) {
            q.pop();
            q.push(new_num);
        }
        return q.top();
    }
};

//-------------------------------------------------------------------------------------------------------------

class BinaryTree {
private:
    int data{ };
    BinaryTree* left{ };
    BinaryTree* right{ };

public:

    BinaryTree(int data) :
        data(data) {
    }

    void add(std::vector<int> values, std::vector<char> direction) {
        assert(values.size() == direction.size());
        BinaryTree* current = this;
        // iterate on the path, create all necessary nodes
        for (int i = 0; i < (int)values.size(); ++i) {
            if (direction[i] == 'L') {
                if (!current->left)
                    current->left = new BinaryTree(values[i]);
                else
                    assert(current->left->data == values[i]);
                current = current->left;
            }
            else {
                if (!current->right)
                    current->right = new BinaryTree(values[i]);
                else
                    assert(current->right->data == values[i]);
                current = current->right;
            }
        }
    }
    ////////////////////////////////////////////

    void level_order_traversal() {
        std::queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);

        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            while (sz--) {
                BinaryTree* cur = nodes_queue.front();
                nodes_queue.pop();

                std::cout << cur->data << " ";
                if (cur->left)
                    nodes_queue.push(cur->left);
                if (cur->right)
                    nodes_queue.push(cur->right);
            }
            std::cout << "\n";
        }
    }

    void level_order_traversal_sorted() {
        std::priority_queue<std::pair<int, BinaryTree*>> heaps[2];

        int flag = 0;
        heaps[flag].push(std::make_pair(data, this));

        while (!heaps[flag].empty()) {
            int sz = heaps[flag].size();

            while (sz--) {
                std::pair<int, BinaryTree*> cur_pair = heaps[flag].top();
                heaps[flag].pop();
                BinaryTree* cur = cur_pair.second;
                std::cout << cur_pair.first << " ";

                if (cur->left)
                    heaps[!flag].push(std::make_pair(cur->left->data, cur->left));

                if (cur->right)
                    heaps[!flag].push(std::make_pair(cur->right->data, cur->right));
            }
            std::cout << "\n";
            flag = !flag;
        }
    }
};

void test() {
    BinaryTree tree(1);

    tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
    tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
    tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
    tree.add({ 3, 6, 15 }, { 'R', 'R', 'L' });

    tree.add({ 2, 5, 13 }, { 'L', 'R', 'L' });
    tree.add({ 3, 6, 12 }, { 'R', 'R', 'R' });
    tree.add({ 3, 14, 15 }, { 'R', 'L', 'L' });
    tree.add({ 3, 14, 16 }, { 'R', 'L', 'R' });

    tree.level_order_traversal();
    tree.level_order_traversal_sorted();
}

//-------------------------------------------------------------------------------------------------------------

int main()
{
    //std::vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    //MinHeap heap(v);
    //heap.print_less_than(10);
    //std::cout << "\n";

    //int a[] = { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    //MinHeap heap2;
    //heap2.heap_sort(a, 14);
    //
    //for (int i = 0; i < 14; i++)
    //{
    //    std::cout << a[i] << "  ";
    //}
    //std::cout << "\n";

    test();

}

