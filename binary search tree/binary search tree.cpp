#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <vector>
#include <string>

class BinarySearchTree
{
private:
    int data{};
    BinarySearchTree* left{ nullptr };
    BinarySearchTree* right{ nullptr };
    BinarySearchTree* parent{ nullptr };

    void print_in()
    {
        if (left)
        {
            left->print_in();
        }
        std::cout << data << "  ";
        if (right)
        {
            right->print_in();
        }
    }

    void print_pre()
    {
        std::cout << data << "  ";
        if (left)
        {
            left->print_pre();
        }
        if (right)
        {
            right->print_pre();
        }
    }

    void print_post()
    {
        if (left)
        {
            left->print_post();
        }
        if (right)
        {
            right->print_post();
        }
        std::cout << data << "  ";
    }

    void print_pre_complete()
    {
        std::cout << data << "  ";

        if (left)
        {
            left->print_pre_complete();
        }
        else
        {
            std::cout << "-1  ";
        }

        if (right)
        {
            right->print_pre_complete();
        }
        else
        {
            std::cout << "-1  ";
        }
    }

public:
    BinarySearchTree(int value, BinarySearchTree* parent = nullptr) : data(value), parent(parent) {}

    BinarySearchTree(int value, BinarySearchTree* left_tree, BinarySearchTree* right_tree, BinarySearchTree* parent = nullptr)
        : data(value), parent(parent), left(left_tree), right(right_tree) {}

    ~BinarySearchTree()
    {
        clear();
    }
    
    void clear()
    {
        if (left)
        {
            delete left;
            left = nullptr;
        }
        if (right)
        {
            delete right;
            right = nullptr;
        }
    }

    void print_inOrder()
    {
        print_in();
        std::cout << "\n";
    }

    void print_preOrder()
    {
        print_pre();
        std::cout << "\n";
    }

    void print_postOrder()
    {
        print_post();
        std::cout << "\n";
    }

    void print_preOrder_complete()
    {
        print_pre_complete();
        std::cout << "\n";
    }

    //------------------------------

    void add(std::vector<int> values, std::vector<char> direction)
    {
        assert(values.size() == direction.size());
        BinarySearchTree* current = this;

        for (int i = 0; i < int(values.size()); i++)
        {
            if (direction[i] == 'L')
            {
                if (!current->left)
                {
                    current->left = new BinarySearchTree(values[i], this);
                }
                else
                {
                    assert(current->left->data == values[i]);
                }
                current = current->left;
            }
            else
            {
                assert(direction[i] == 'R');
                if (!current->right)
                {
                    current->right = new BinarySearchTree(values[i], this);
                }
                else
                {
                    assert(current->right->data == values[i]);
                }
                current = current->right;
            }
        }
    }

    int tree_height()
    {
        int height = 0;
        if (left)
        {
            height = 1 + left->tree_height();
        }
        if (right)
        {
            height = std::max(height, 1 + right->tree_height());
        }return height;
    }

    int total_nodes()
    {
        int nodes = 1;
        if (left)
        {
            nodes += left->total_nodes();
        }
        if (right)
        {
            nodes += right->total_nodes();
        }
        return nodes;
    }

    int leaf_count()
    {
        int count = !left && !right;
        if (left)
        {
            count += left->leaf_count();
        }
        if (right)
        {
            count += right->leaf_count();
        }
        return count;
    }

    void level_order_traversal2()
    {
        std::queue<BinarySearchTree*> nodes_queue;
        nodes_queue.push(this);

        int level = 0;
        while (!nodes_queue.empty())
        {
            int size = nodes_queue.size();

            std::cout << "Level " << level << ": ";
            while (size--)
            {
                BinarySearchTree* cur = nodes_queue.front();
                nodes_queue.pop();

                std::cout << cur->data << "  ";
                if (cur->left)
                {
                    nodes_queue.push(cur->left);
                }
                if (cur->right)
                {
                    nodes_queue.push(cur->right);
                }
            }
            level++;
            std::cout << "\n";
        }


        std::cout << "\n";
    }

    //------------------------------

    void insert(int value)
    {
        if (value < data)
        {
            if (!left)
            {
                left = new BinarySearchTree(value, this);
            }
            else
            {
                left->insert(value);
            }
        }
        else if (value > data)
        {
            if (!right)
            {
                right = new BinarySearchTree(value, this);
            }
            else
            {
                right->insert(value);
            }
        }
    }

    void get_inOrder(std::vector<int> &values)
    {
        if (left)
        {
            left->get_inOrder(values);
        }
        values.push_back(data);
        if (right)
        {
            right->get_inOrder(values);
        }
    }

    bool search_iterative(int value)
    {
        BinarySearchTree* current = this;

        while (current)
        {
            if (current->data == value)
            {
                return true;
            }
            else if (value < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return false;
    }

    bool is_binary_search_tree1(int min = INT_MIN, int max = INT_MAX)
    {
        bool status = min < data && data < max;
        if (!status)
        {
            return false;
        }

        bool left_bst = !left || left->is_binary_search_tree1(min, data);
        if (!left_bst)
        {
            return false;
        }

        bool right_bst = !right || right->is_binary_search_tree1(data, max);
        return right_bst;
    }

    bool is_binary_search_tree2()
    {
        std::vector<int> values;
        get_inOrder(values);

        for (int i = 1; i < values.size(); i++)
        {
            if (values[i] <= values[i - 1])
            {
                return false;
            }
        }
        return true;
    }

    int kth_smallest(int& k)
    {
        if (k == 0)
        {
            return -1234;
        }

        if (left)
        {
            int temp = kth_smallest(k);
            if (k == 0)
            {
                return temp;
            }
        }

        k--;

        if (k == 0)
        {
            return data;
        }

        if (right)
        {
            return kth_smallest(k);
        }

        return -1234;
    }

    int lowest_common_ancestor(int x, int y)
    {
        if (x < data && y < data)
        {
            return left->lowest_common_ancestor(x, y);
        }

        if (x > data && y > data)
        {
            return right->lowest_common_ancestor(x, y);
        }

        return data;
    }

    int min_recursive()
    {
        if (!left)
        {
            return data;
        }
        else
        {
            left->min_recursive();
        }
    }

    int max_recursive()
    {
        if ( !right )
        {
            return data;
        }
        else
        {
            right->max_recursive();
        }
    }

    int min_iterative()
    {
        BinarySearchTree* current = this;
        while (current && current->left)
        {
            current = current->left;
        }
        return current->data;
    }

    int max_iterative()
    {
        BinarySearchTree* current = this;
        while (current && current->right)
        {
            current = current->right;
        }
        return current->data;
    }

    //stack could also be used to store ancester nodes
    bool find_chain(std::vector< BinarySearchTree* > &ancestors, int value)
    {
        ancestors.push_back(this);

        if (value == data)
        {
            return true;
        }

        if (value < data)
        {
            return left && left->find_chain(ancestors, value);
        }

        return right && right->find_chain(ancestors, value);
    }

    BinarySearchTree* get_next(std::vector< BinarySearchTree* > &ancestors)
    {
        if (ancestors.size() == 0)
        {
            return nullptr;
        }

        BinarySearchTree* node = ancestors.back();
        ancestors.pop_back();
        return node;
    }

    //successor and predecessor without parent
    std::pair<bool, int> successor(int value)
    {
        std::vector< BinarySearchTree* > ancestors;

        if (!find_chain(ancestors, value))
        {
            return std::make_pair ( false, -1 );
        }

        BinarySearchTree* child = get_next(ancestors);

        if (child->right)
        {
            return std::make_pair(true, child->right->min_iterative());
        }

        BinarySearchTree* parent = get_next(ancestors);

        while (parent && parent->right == child)
        {
            child = parent;
            parent = get_next(ancestors);
        }

        if (parent)
        {
            return std::make_pair(true, parent->data);
        }

        return std::make_pair(false, -1);
    }

    std::pair<bool, int> predecessor(int value)
    {
        std::vector< BinarySearchTree* > ancestors;

        if (!find_chain(ancestors, value))
        {
            return std::make_pair(false, -1);
        }

        BinarySearchTree* child = get_next(ancestors);

        if (child->left)
        {
            return std::make_pair(true, child->left->max_iterative());
        }

        BinarySearchTree* parent = get_next(ancestors);

        while (parent && parent->left == child)
        {
            child = parent;
            parent = get_next(ancestors);
        }

        if (parent)
        {
            return std::make_pair(true, parent->data);
        }

        return std::make_pair(false, -1);
    }

    BinarySearchTree* find(int value)
    {
        if (value == data)
        {
            return this;
        }

        if (value < data)
        {
            return left->find(value);
        }

        if (value > data)
        {
            return right->find(value);
        }

        return nullptr;
    }

    //successor and predecessor with parent
    std::pair<bool, int> successor_parent(int value)
    {
        BinarySearchTree* child = find(value);

        if (!child)
        {
            return std::make_pair(false, -1);
        }

        if (child->right)
        {
            return std::make_pair(true, child->right->min_iterative());
        }

        BinarySearchTree* parent = child->parent;

        while (parent && parent->right == child)
        {
            child = parent;
            parent = parent->parent;
        }

        if (parent)
        {
            return std::make_pair(true, parent->data);
        }

        return std::make_pair(false, -1);
    }

    std::pair<bool, int> predecessor_parent(int value)
    {
        BinarySearchTree* child = find(value);

        if (!child)
        {
            return std::make_pair(false, -1);
        }

        if (child->left)
        {
            return std::make_pair(true, child->left->max_iterative());
        }

        BinarySearchTree* parent = child->parent;

        while (parent && parent->left == child)
        {
            child = parent;
            parent = parent->parent;
        }

        if (parent)
        {
            return std::make_pair(true, parent->data);
        }

        return std::make_pair(false, -1);
    }

    void successor_queries(std::deque<int>& queries, std::vector<int> &answer, std::vector<int> &traversal)
    {
        if (queries.empty())
        {
            return;
        }

        if (left && queries.front() < data)
        {
            left->successor_queries(queries, answer, traversal);

            if (queries.empty())
            {
                return;
            }
        }

        if (!traversal.empty() && traversal.back() == queries.front())
        {
            answer.push_back(data);
            queries.pop_front();

            if (queries.empty())
            {
                return;
            }
        }
        traversal.push_back(data);

        if (right && queries.front() >= data)
        {
            right->successor_queries(queries, answer, traversal);
        }
    }

    void predecessor_queries(std::deque<int>& queries, std::vector<int>& answer, std::vector<int>& traversal)
    {
        if (queries.empty())
        {
            return;
        }

        if (left && queries.front() <= data)
        {
            left->predecessor_queries(queries, answer, traversal);

            if (queries.empty())
            {
                return;
            }
        }

        traversal.push_back(data);
        if (!traversal.empty() && traversal.back() == queries.front())
        {
            answer.push_back(traversal[traversal.size() - 2]); //changed here and <= for left and > for right instead of the opposite
            queries.pop_front();

            if (queries.empty())
            {
                return;
            }
        }

        if (right && queries.front() > data)
        {
            right->predecessor_queries(queries, answer, traversal);
        }
    }

    bool is_degenerate()
    {
        if (left && right)
        {
            return false;
        }

        if (!left && !right)
        {
            return true;
        }

        if (left)
        {
            return left->is_degenerate();
        }

        if (right)
        {
            return right->is_degenerate();
        }
    }

    bool next_between(std::deque<int>& preorder, int min, int max)
    {
        if (preorder.empty())
        {
            return false;
        }
        return min < preorder[0] && max > preorder[0];
    }

    BinarySearchTree(std::deque<int>& preorder, int min = INT_MIN, int max = INT_MAX)
    {
        data = preorder[0];
        preorder.pop_front();

        if (next_between(preorder, min, data))
        {
            left = new BinarySearchTree(preorder, min, data);
        }

        if (next_between(preorder, data, max))
        {
            right = new BinarySearchTree(preorder, data, max);
        }
    }

    void special_delete(BinarySearchTree* child)
    {
        data = child->data;
        left = child->left;
        right = child->right;
        child->left = nullptr;
        child->right = nullptr;
        child->parent = nullptr;
        delete child;
    }

    BinarySearchTree* min_node()
    {
        BinarySearchTree* cur = this;
        while (cur && cur->left)
        {
            cur = cur->left;
        }
        return cur;
    }

    BinarySearchTree* delete_node(int value, BinarySearchTree* node)
    {
        if (!node)
        {
            return nullptr;
        }

        if (value < node->data)
        {
            node->left = delete_node(value, node->left);
        }
        else if (value > node->data)
        {
            node->right = delete_node(value, node->right);
        }
        else
        {
            BinarySearchTree* temp = node;

            if (!node->left && !node->right)
            {
                node = nullptr;
            }
            else if (!node->right)
            {
                node->special_delete(node->left);
                temp = nullptr;
            }
            else if (!node->left)
            {
                node->special_delete(node->right);
                temp = nullptr;
            }
            else
            {
                BinarySearchTree* min = node->right->min_node();
                node->data = min->data;
                node->right = delete_node(node->data, node->right);
                temp = nullptr;
            }

            if (temp)
            {
                delete temp;
            }
        }

        return node;
    }

    void delete_value(int value)
    {
        if (value == data && !left && !right)
        {
            return;
        }
        delete_node(value, this);
    }

    BinarySearchTree* max_node()
    {
        BinarySearchTree* cur = this;
        while (cur && cur->right)
        {
            cur = cur->right;
        }
        return cur;
    }

    BinarySearchTree* delete_node2(int value, BinarySearchTree* node)
    {
        if (!node)
        {
            return nullptr;
        }

        if (value < node->data)
        {
            node->left = delete_node2(value, node->left);
        }
        else if (value > node->data)
        {
            node->right = delete_node2(value, node->right);
        }
        else
        {
            BinarySearchTree* temp = node;

            if (!node->left && !node->right)
            {
                node = nullptr;
            }
            else if (!node->right)
            {
                node->special_delete(node->left);
                temp = nullptr;
            }
            else if (!node->left)
            {
                node->special_delete(node->right);
                temp = nullptr;
            }
            else
            {
                BinarySearchTree* max = node->left->max_node();
                node->data = max->data;
                node->left = delete_node(node->data, node->left);
                temp = nullptr;
            }

            if (temp)
            {
                delete temp;
            }
        }

        return node;
    }

    void delete_value2(int value)
    {
        if (value == data && !left && !right)
        {
            return;
        }
        delete_node2(value, this);
    }

    BinarySearchTree* delete_node_iterative(int value, BinarySearchTree* node)
    {
        if (!node)
        {
            return nullptr;
        }

        if (value < node->data)
        {
            node->left = delete_node_iterative(value, node->left);
        }
        else if (value > node->data)
        {
            node->right = delete_node_iterative(value, node->right);
        }
        else
        {
            BinarySearchTree* temp = node;

            if (!node->left && !node->right)
            {
                node = nullptr;
            }
            else if (!node->right)
            {
                node->special_delete(node->left);
                temp = nullptr;
            }
            else if (!node->left)
            {
                node->special_delete(node->right);
                temp = nullptr;
            }
            else
            {
                BinarySearchTree* parent = node;
                BinarySearchTree* child = parent->right;
                while (child->left)
                {
                    parent = child;
                    child = child->left;
                }

                node->data = child->data;

                if (parent->right == child)
                {
                    parent->right = child->right;
                }
                else
                {
                    parent->left = child->right;
                }

                child->right = nullptr;
                child->left = nullptr;
                child->parent = nullptr;
                temp = child;
            }

            if (temp)
            {
                delete temp;
            }
        }

        return node;
    }

    void delete_value_iterative(int value)
    {
        if (value == data && !left && !right)
        {
            return;
        }
        delete_node_iterative(value, this);
    }

    BinarySearchTree* delete_node_iterative2(int value, BinarySearchTree* node)
    {
        if (!node)
        {
            return nullptr;
        }

        if (value < node->data)
        {
            node->left = delete_node_iterative(value, node->left);
        }
        else if (value > node->data)
        {
            node->right = delete_node_iterative(value, node->right);
        }
        else
        {
            BinarySearchTree* temp = node;

            if (!node->left && !node->right)
            {
                node = nullptr;
            }
            else if (!node->right)
            {
                node->special_delete(node->left);
                temp = nullptr;
            }
            else if (!node->left)
            {
                node->special_delete(node->right);
                temp = nullptr;
            }
            else
            {
                BinarySearchTree* parent = node;
                BinarySearchTree* child = parent->left;
                while (child->right)
                {
                    parent = child;
                    child = child->right;
                }

                node->data = child->data;

                if (parent->right == child)
                {
                    parent->right = child->left;
                }
                else
                {
                    parent->left = child->left;
                }

                child->right = nullptr;
                child->left = nullptr;
                child->parent = nullptr;
                temp = child;
            }

            if (temp)
            {
                delete temp;
            }
        }

        return node;
    }

    void delete_value_iterative2(int value)
    {
        if (value == data && !left && !right)
        {
            return;
        }
        delete_node_iterative2(value, this);
    }
    
};


BinarySearchTree* build_balanced_binary_search_tree(std::vector<int>& values, int start = 0, int end = -10)
{
    if (end == -10)
    {
        end = values.size() - 1;
    }

    if (start > end)
    {
        return nullptr;
    }

    int mid = (start + end) / 2;
    BinarySearchTree* left_tree = build_balanced_binary_search_tree(values, start, mid - 1);
    BinarySearchTree* right_tree = build_balanced_binary_search_tree(values, mid + 1, end);
    BinarySearchTree* root = new BinarySearchTree(values[mid], left_tree, right_tree);

    return root;
}

bool is_degenerate_preorder(std::vector<int> &preorder)
{
    if (preorder.size() <= 2)
    {
        return true;
    }

    int min = INT_MIN;
    int max = INT_MAX;

    for (int i = 1; i < preorder.size(); i++)
    {
        if (preorder[i] < min || preorder[i] > max)
        {
            return false;
        }

        if (preorder[i] > preorder[i - 1])
        {
            min = preorder[i - 1] + 1;
        }
        else
        {
            max = preorder[i - 1] - 1;
        }
    }

    return true;
}



int main()
{
    //std::vector<int> values = { 0,1,2,3,4,5,6,7,8,9, 10, 11, 12, 13};
    //BinarySearchTree* tree = build_balanced_binary_search_tree(values);
    //tree->print_inOrder();
    //tree->level_order_traversal2();
    //std::cout << tree->min_recursive() << "\n";
    //std::cout << tree->max_recursive() << "\n";
    //std::cout << tree->min_iterative() << "\n";
    //std::cout << tree->max_iterative() << "\n";
    //std::cout << tree->predecessor_parent(10).second << "\n";

    //std::deque<int> queries = { 1, 4, 8, 12, 13 };
    //std::vector<int> answer;
    //std::vector<int> traversal;
    //tree->predecessor_queries(queries, answer, traversal);
    //for (int i = 0; i < answer.size(); i++)
    //{
    //    std::cout << answer[i] << "\n";
    //}
    

    //BinarySearchTree tree2(0);
    //tree2.add({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }, { 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L' });
    //tree2.add({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14 }, { 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R' });
    //tree2.level_order_traversal2();
    //std::cout << "Is degenerate: " << tree2.is_degenerate() << "\n";

    //std::vector<int> preorder = {500, 400, 300, 200, 250, 275, 260};
    //std::cout << "Is degenerate: " << is_degenerate_preorder(preorder) << "\n";

    std::deque<int> preorder = { 50, 20, 15, 45, 35, 60, 70, 73 };
    BinarySearchTree tree3(preorder);
    tree3.level_order_traversal2();
    tree3.delete_value_iterative2(73);
    tree3.level_order_traversal2();
}

