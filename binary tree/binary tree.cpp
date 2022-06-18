#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <vector>
#include <string>

struct Node
{
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int data) : data(data) {}
};

void print_preorder(Node* current)
{
    if (!current)
    {
        return;
    }

    std::cout << current->data << "  ";
    print_preorder(current->left);
    print_preorder(current->right);
}

void print_inorder(Node* current)
{
    if (!current)
    {
        return;
    }

    print_inorder(current->left);
    std::cout << current->data << "  \n";
    print_inorder(current->right);
}

void print_postorder(Node* current)
{
    if (!current)
    {
        return;
    }

    print_postorder(current->left);
    print_postorder(current->right);
    std::cout << current->data << "  \n";
}

//-----------------------------------------------------------------------------



class BinaryTree
{
private:
    int data{};
    BinaryTree* left{nullptr};
    BinaryTree* right{ nullptr };

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
    BinaryTree(int value) : data(value) {}


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

    //------------------------------

    void add(std::vector<int> values, std::vector<char> direction)
    {
        assert(values.size() == direction.size());
        BinaryTree* current = this;

        for (int i = 0; i < int(values.size()); i++)
        {
            if (direction[i] == 'L')
            {
                if (!current->left)
                {
                    current->left = new BinaryTree(values[i]);
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
                    current->right = new BinaryTree(values[i]);
                }
                else
                {
                    assert(current->right->data == values[i]);
                }
                current = current->right;
            }
        }
    }

    int tree_max()
    {
        int temp = data;
        if (left)
        {
            temp = std::max(temp, left->tree_max());
        }
        if (right)
        {
            temp = std::max(temp, right->tree_max());
        }
        return temp;
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

    bool is_exists(int value)
    {
        bool exists = value == data;
        if (!exists && left)
        {
            exists = left->is_exists(value);
        }
        if (!exists && right)
        {
            exists = right->is_exists(value);
        }
        return exists;
    }

    bool is_perfect(int h = -1)
    {
        if (h == -1)
        {
            h = tree_height();
        }

        if (!left and !right)
        {
            return h == 0;
        }

        if ((!left && right) || (left && !right))
        {
            return false;
        }

        return left->is_perfect() && right->is_perfect();
    }

    bool is_perfect_formula()
    {
        int height = tree_height();
        int nodes = total_nodes();
        return pow(2, height + 1) - 1 == nodes;
    }

    ~BinaryTree()
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

    void print_inorder_iterative()
    {
        std::stack < std::pair < BinaryTree*, bool > > nodes;

        nodes.push(std::make_pair(this, false));

        while (!nodes.empty())
        {
            BinaryTree* current = nodes.top().first;
            bool is_expanded = nodes.top().second;
            nodes.pop();

            if (is_expanded)
            {
                std::cout << current->data << "  ";
            }
            else
            {
                if (current->right)
                {
                nodes.push(std::make_pair(current->right, false));
                }

                nodes.push(std::make_pair(current, true));

                if (current->left)
                {
                    nodes.push(std::make_pair(current->left, false));
                }
            }
        }

        std::cout << "\n";

    }

    void print_preorder_iterative()
    {
        std::stack < std::pair < BinaryTree*, bool > > nodes;

        nodes.push(std::make_pair(this, false));

        while (!nodes.empty())
        {
            BinaryTree* current = nodes.top().first;
            bool is_expanded = nodes.top().second;
            nodes.pop();

            if (is_expanded)
            {
                std::cout << current->data << "  ";
            }
            else
            {
                if (current->right)
                {
                    nodes.push(std::make_pair(current->right, false));
                }

                if (current->left)
                {
                    nodes.push(std::make_pair(current->left, false));
                }

                nodes.push(std::make_pair(current, true));
            }
        }

        std::cout << "\n";

    }

    void print_postorder_iterative()
    {
        std::stack < std::pair < BinaryTree*, bool > > nodes;

        nodes.push(std::make_pair(this, false));

        while (!nodes.empty())
        {
            BinaryTree* current = nodes.top().first;
            bool is_expanded = nodes.top().second;
            nodes.pop();

            if (is_expanded)
            {
                std::cout << current->data << "  ";
            }
            else
            {
                nodes.push(std::make_pair(current, true));

                if (current->right)
                {
                    nodes.push(std::make_pair(current->right, false));
                }

                if (current->left)
                {
                    nodes.push(std::make_pair(current->left, false));
                }
            }
        }

        std::cout << "\n";

    }

    void traverse_left_boundary(bool first = true)
    {
        std::cout << data << "  ";

        if (left)
        {
            left->traverse_left_boundary(false);
        }
        else if (right)
        {
            right->traverse_left_boundary(false);
        }

        if (first)
        {
            std::cout << "\n";
        }
    }

    std::pair<int, int> tree_diameter() //return diameter and height
    {
        std::pair<int, int> info = std::make_pair(0, 0);
    
        if (!left and !right)
        {
            return info;
        }
    
        std::pair<int, int> left_info = std::make_pair(0, 0);
        std::pair<int, int> right_info = std::make_pair(0, 0);
    
        if (left)
        {
            left_info = left->tree_diameter();
            info.first += 1 + left_info.second;
        }
        if (right)
        {
            right_info = right->tree_diameter();
            info.first += 1 + right_info.second;
        }

        info.first = std::max(info.first, std::max(left_info.first, right_info.first));

        info.second = 1 + std::max(left_info.second, right_info.second);

        return info;
    }

    void level_order_traversal()
    {
        std::queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);

        while (!nodes_queue.empty())
        {
            BinaryTree* cur = nodes_queue.front();
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
        std::cout << "\n";
    }

    void level_order_traversal2()
    {
        std::queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);

        int level = 0;
        while (!nodes_queue.empty())
        {
            int size = nodes_queue.size();

            std::cout << "Level " << level << ": ";
            while (size--)
            {
                BinaryTree* cur = nodes_queue.front();
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

    void level_order_traversal_spiral()
    {
        std::deque<BinaryTree*> nodes_queue;
        nodes_queue.push_back(this);

        int level = 0;
        bool forward_level = true;

        while (!nodes_queue.empty())
        {
            int size = nodes_queue.size();

            std::cout << "Level " << level << ": ";
            while (size--)
            {
                BinaryTree* cur;

                if (forward_level)
                {
                    cur = nodes_queue.front();
                    nodes_queue.pop_front();

                    std::cout << cur->data << "  ";
                    if (cur->left)
                    {
                        nodes_queue.push_back(cur->left);
                    }
                    if (cur->right)
                    {
                        nodes_queue.push_back(cur->right);
                    }
                }
                else
                {
                    cur = nodes_queue.back();
                    nodes_queue.pop_back();

                    std::cout << cur->data << "  ";
                    if (cur->right)
                    {
                        nodes_queue.push_front(cur->right);
                    }
                    if (cur->left)
                    {
                        nodes_queue.push_front(cur->left);
                    }
                }
            }
            forward_level = !forward_level;
            level++;
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    bool is_complete()
    {
        std::queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);

        bool no_more_allowed = false;

        while (!nodes_queue.empty())
        {
            int size = nodes_queue.size();

            while (size--)
            {
                BinaryTree* cur = nodes_queue.front();
                nodes_queue.pop();

                if (cur->left)
                {
                    if (no_more_allowed)
                    {
                        return false;
                    }
                    nodes_queue.push(cur->left);
                }
                else
                {
                    no_more_allowed = true;
                }

                if (cur->right)
                {
                    if (no_more_allowed)
                    {
                        return false;
                    }
                    nodes_queue.push(cur->right);
                }
                else
                {
                    no_more_allowed = true;
                }
            }
        }
        return true;
    }

    BinaryTree(std::deque<int> &pre_order, std::deque<int> &in_order, int inorder_start = 0, int inorder_end = -1)
    {
        if (inorder_end == -1)
        {
            inorder_end = (int) in_order.size() - 1;
        }

        data = pre_order[0];
        pre_order.pop_front();

        for (int split = inorder_start; split <= inorder_end; split++)
        {
            if (in_order[split] == data)
            {
                if (inorder_start < split)
                {
                    left = new BinaryTree(pre_order, in_order, inorder_start, split - 1);
                }
                if (split < inorder_end)
                {
                    right = new BinaryTree(pre_order, in_order, split + 1, inorder_end);
                }
                break;
            }
        }
    }

    BinaryTree(std::deque<int> &pre_order, int level = -1)
    {
        if (level == -1)
        {
        int nodes = pre_order.size();
        int levels = std::log2(nodes + 1);
        level = levels;
        std::cout << "levels: " << level << "\n";
        }
        
        data = pre_order.front();
        pre_order.pop_front();

        if (level == -1 || level > 1)
        {
            left = new BinaryTree(pre_order, level - 1);
            right = new BinaryTree(pre_order, level - 1);
        }
    }

    void print_preOrder_complete()
    {
        print_pre_complete();
        std::cout << "\n";
    }

    bool is_mirror(BinaryTree* first, BinaryTree* second)
    {
        if (!first && !second)
        {
            return true;
        }

        if ((!first && second) || (first && !second) || (first->data != second->data))
        {
            return false;
        }

        return is_mirror(first->left, second->right) && is_mirror(first->right, second->left);
    }

    bool is_symmetric_recursive()
    {
        return is_mirror(left, right);
    }

    std::string paranthesize(bool left_first = true)
    {
        std::string repr = "(" + std::to_string(data);

        if (left_first)
        {
            if (left)
            {
                repr += left->paranthesize(left_first);
            }
            else
            {
                repr += "()";
            }

            if (right)
            {
                repr += right->paranthesize(left_first);
            }
            else
            {
                repr += "()";
            }
        }
        else
        {
            if (right)
            {
                repr += right->paranthesize(left_first);
            }
            else
            {
                repr += "()";
            }

            if (left)
            {
                repr += left->paranthesize(left_first);
            }
            else
            {
                repr += "()";
            }
        }
        repr += ")";
        return repr;
    }

    bool is_symmetric()
    {
        if (!left && !right)
        {
            return true;
        }

        if (!left && right || left && !right)
        {
            return false;
        }

        return left->paranthesize() == right->paranthesize(false);
    }

    std::string parenthesize_canonical()
    {
        std::string repr = "(" + std::to_string(data);

        std::vector < std::string> v;

        if (left)
        {
            v.push_back(left->parenthesize_canonical());
        }
        else
        {
            v.push_back("()");
        }

        if (right)
        {
            v.push_back(right->parenthesize_canonical());
        }
        else
        {
            v.push_back("()");
        }

        std::sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++)
        {
            repr += v[i];
        }
        repr += ")";
        return repr;
    }

    bool is_flip_equiv(BinaryTree* other)
    {
        return parenthesize_canonical() == other->parenthesize_canonical();
    }

    std::string paranthesize(std::vector<std::string> &all_repres)
    {
        std::string repr = "(" + std::to_string(data);

        if (left)
        {
            repr += left->paranthesize(all_repres);
        }
        else
        {
            repr += "()";
        }

        if (right)
        {
            repr += right->paranthesize(all_repres);
        }
        else
        {
            repr += "()";
        }

        repr += ")";

        if (left || right)
        {
            all_repres.push_back(repr);
        }
        return repr;
    }

    void print_duplicate_subtrees()
    {
        std::vector<std::string> all_repres;
        paranthesize(all_repres);

        std::sort(all_repres.begin(), all_repres.end());
        all_repres.push_back("#");

        for (int i = 0; i < all_repres.size();)
        {
            int j = i + 1;
            while (j < all_repres.size() && all_repres[i] == all_repres[j])
            {
                j++;
            }

            if (j > i + 1)
            {
                std::cout << all_repres[i] << "\n";
            }
            i = j;
        }
    }

};

int main()
{
    //BinaryTree tree(1);
    //tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
    //tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
    //tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
    //tree.add({ 2, 5, 29 }, { 'L', 'R', 'L' });
    //tree.add({ 3, 6, 10 }, { 'R', 'R', 'L' });
    //tree.add({ 3, 6, 20 }, { 'R', 'R', 'R' });
    //tree.add({ 3, 11, 12 }, { 'R', 'L', 'L' });
    //tree.add({ 3, 11, 13 }, { 'R', 'L', 'R' });
    //
    //std::cout << tree.is_symmetric() << "\n";
    

    //BinaryTree tree1(1);
    //tree1.add({ 1 , 1, 1 }, { 'L', 'L', 'L' });
    //tree1.add({ 1 , 1, 1 }, { 'L', 'L', 'R' });
    //tree1.add({ 1 , 1, 1 }, { 'L', 'R', 'R' });
    //tree1.add({ 1 , 1, 1 }, { 'L', 'R', 'L' });
    //tree1.add({ 1 , 1, 1 }, { 'R', 'R', 'L' });
    //tree1.add({ 1 , 1, 1 }, { 'R', 'R', 'R' });
    //tree1.add({ 1 , 1, 1 }, { 'R', 'L', 'L' });
    //tree1.add({ 1 , 1, 1 }, { 'R', 'L', 'R' });
    //tree1.print_duplicate_subtrees();
    //std::cout << tree1.is_symmetric() << "\n";

    //std::deque<int> pre_order;
    //pre_order.push_back(3);
    //pre_order.push_back(9);
    //pre_order.push_back(1);
    //pre_order.push_back(2);
    //pre_order.push_back(20);
    //pre_order.push_back(15);
    //pre_order.push_back(7);
    //
    //std::deque<int> in_order;
    //in_order.push_back(1);
    //in_order.push_back(9);
    //in_order.push_back(2);
    //in_order.push_back(3);
    //in_order.push_back(15);
    //in_order.push_back(20);
    //in_order.push_back(7);
    //
    //BinaryTree tree2(pre_order, in_order);
    //tree2.print_preOrder();
    //tree2.print_inOrder();
    //tree2.print_postOrder();

    //std::deque<int> full_preorder;
    //full_preorder.push_back(1);
    //full_preorder.push_back(2);
    //full_preorder.push_back(4);
    //full_preorder.push_back(8);
    //full_preorder.push_back(9);
    //full_preorder.push_back(5);
    //full_preorder.push_back(10);
    //full_preorder.push_back(11);
    //full_preorder.push_back(3);
    //full_preorder.push_back(6);
    //full_preorder.push_back(12);
    //full_preorder.push_back(13);
    //full_preorder.push_back(7);
    //full_preorder.push_back(14);
    //full_preorder.push_back(15);
    //
    //BinaryTree tree3(full_preorder);
    //tree3.print_preOrder();
    //tree3.print_inOrder();
    //tree3.print_postOrder();


}
