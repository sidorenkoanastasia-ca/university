#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <stack>
#include <queue>

template <class T>
class BinarySearchTree
{
public:
    BinarySearchTree() : root_(nullptr)
    {
    }

    BinarySearchTree(const BinarySearchTree& other) = delete;

    BinarySearchTree(BinarySearchTree&& other) noexcept : root_(other.root_)
    {
        other.root_ = nullptr;
    }

    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;

    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept
    {
        if (this != &other)
        {
            BinarySearchTree temp(std::move(other));
            swap(temp);
        }
        return *this;
    }
    virtual ~BinarySearchTree()
    {
        destroySubTreeIterative(root_);
    }

    bool searchIterative(const T& key) const
    {
        return searchNode(key) != nullptr;
    }

    bool insert(const T& key)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(key);
            return true;
        }
        Node* current = root_;
        while (current != nullptr)
        {
            if (current->key_ == key)
            {
                return false;
            }
            else if (current->key_ < key)
            {
                if (current->right_ == nullptr)
                {
                    current->right_ = new Node(key);
                    current->right_->p_ = current;
                    return true;
                }
                else
                {
                    current = current->right_;
                }
            }
            else
            {
                if (current->left_ == nullptr)
                {
                    current->left_ = new Node(key);
                    current->left_->p_ = current;
                    return true;
                }
                else
                {
                    current = current->left_;
                }
            }
        }
        return false;
    }

    bool remove(const T& key)
    {
        Node* current = searchNode(key);
        if (current == nullptr)
        {
            return false;
        }
        removeNode(current);
        return true;
    }

    void output(std::ostream& out) const
    {
        output(out, root_);
    }

    int getNumberOfNodes() const
    {
        return getNumberOfNodes(root_);
    }

    int getHeight() const
    {
        return getHeight(root_);
    }

    void inorderWalkIterative(void (*visit)(const T& key)) const
    {
        if (root_ == nullptr)
        {
            return;
        }
        std::stack<Node*> stack;
        Node* current = root_;
        while (current != nullptr || !stack.empty())
        {
            while (current != nullptr)
            {
                stack.push(current);
                current = current->left_;
            }
            current = stack.top();
            stack.pop();
            visit(current->key_);
            current = current->right_;
        }
    }

    void inorderWalk(void (*visit)(const T& key)) const
    {
        inorderWalk(root_, visit);
    }

    void walkByLevels(void (*visit)(const T& key)) const
    {
        if (root_ == nullptr)
        {
            return;
        }
        std::queue<Node*> queue;
        queue.push(root_);
        while (!queue.empty())
        {
            Node* current = queue.front();
            queue.pop();
            visit(current->key_);
            if (current->left_ != nullptr)
            {
                queue.push(current->left_);
            }
            if (current->right_ != nullptr)
            {
                queue.push(current->right_);
            }
        }
    }
    int countNodeInRange(const T& low, const T& high) const
    {
        return countNodeInRange(root_, low, high);
    }
private:
    struct Node
    {
        T key_;
        Node* left_;
        Node* right_;
        Node* p_;
        Node(const T& key) : key_(key), left_(nullptr),
            right_(nullptr), p_(nullptr)
        {
        }
        Node(T&& key) : key_(std::move(key)), left_(nullptr),
            right_(nullptr), p_(nullptr)
        {
        }
    };
    Node* root_;


    void swap(BinarySearchTree& other) noexcept
    {
        std::swap(root_, other.root_);
    }
    Node* searchNode(const T& key) const
    {
        Node* current = root_;
        while (current != nullptr && current->key_ != key)
        {
            if (key > current->key_)
            {
                current = current->right_;
            }
            else
            {
                current = current->left_;
            }
        }
        return current;
    }

    void removeNode(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->left_ != nullptr && node->right_ != nullptr)
        {
            Node* successor = node->right_;
            while (successor->left_ != nullptr)
            {
                successor = successor->left_;
            }
            node->key_ = successor->key_;
            node = successor;
        }

        Node* child = (node->left_ != nullptr) ? node->left_ : node->right_;
        Node* parent = node->p_;
        if (parent == nullptr)
        {
            root_ = child;
        }
        else if (parent->left_ == node)
        {
            parent->left_ = child;
        }
        else
        {
            parent->right_ = child;
        }
        if (child != nullptr)
        {
            child->p_ = parent;
        }
        delete node;
    }

    void destroySubTreeIterative(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        Node* current = root;
        Node* last = nullptr;

        while (current != nullptr)
        {
            if (current->left_ != nullptr && current->left_ != last)
            {
                current = current->left_;
                continue;
            }
            if (current->right_ != nullptr && current->right_ != last)
            {
                current = current->right_;
                continue;
            }
            Node* parent = current->p_;

            if (parent != nullptr)
            {
                if (parent->left_ == current)
                {
                    parent->left_ = nullptr;
                }
                else
                {
                    parent->right_ = nullptr;
                }
            }
            Node* toDelete = current;
            current = parent;
            last = toDelete;
            delete toDelete;
        }
    }

    void output(std::ostream& out, Node* root) const
    {
        if (root == nullptr)
        {
            return;
        }
        out << root->key_;
        if (root->left_ == nullptr && root->right_ == nullptr)
        {
            return;
        }
        out << "(";
        if (root->left_ != nullptr)
        {
            output(out, root->left_);
        }
        out << ")";
        out << "(";
        if (root->right_ != nullptr)
        {
            output(out, root->right_);
        }
        out << ")";
    }

    int getNumberOfNodes(const Node* node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return (1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_));
    }

    int getHeight(const Node* node) const
    {
        if (node == nullptr)
        {
            return -1;
        }
        return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
    }

    void inorderWalk(Node* node, void (*visit)(const T& key)) const
    {
        if (node == nullptr)
        {
            return;
        }
        inorderWalk(node->left_, visit);
        visit(node->key_);
        inorderWalk(node->right_, visit);
    }

    int countNodeInRange(Node* node, const T& low, const T& high) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->key_ < low)
        {
            return countNodeInRange(node->right_, low, high);
        }
        if (node->key_ > high)
        {
            return countNodeInRange(node->left_, low, high);
        }
        return 1 + countNodeInRange(node->right_, low, high) +
            countNodeInRange(node->left_, low, high);
    }
};
#endif