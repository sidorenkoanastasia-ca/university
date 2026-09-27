#ifndef AVLTREE_H
#define AVLTREE_H

template <typename Key, typename Value>
class AVLtree
{
public:
    AVLtree() : root_(nullptr), countNodes_(0)
    {}
    ~AVLtree()
    {
        destroySubTree(root_);
    }
    AVLtree(const AVLtree& other) : root_(nullptr), countNodes_(0)
    {
        root_ = copySubTree(other.root_);
        countNodes_ = other.countNodes_;
    }

    AVLtree& operator=(const AVLtree& other)
    {
        if (this != &other)
        {
            AVLtree temp(other);
            swap(temp);
        }
        return *this;
    }

    AVLtree(AVLtree&& other) noexcept : root_(other.root_), countNodes_(other.countNodes_)
    {
        other.root_ = nullptr;
        other.countNodes_ = 0;
    }

    AVLtree& operator=(AVLtree&& other) noexcept
    {
        if (this != &other)
        {
            AVLtree temp(std::move(other));
            swap(temp);
        }
        return *this;
    }

    void swap(AVLtree& other) noexcept
    {
        std::swap(root_, other.root_);
        std::swap(countNodes_, other.countNodes_);
    }

    bool insert(const Key& key, const Value& value)
    {
        bool inserted = false;
        root_ = insertNode(root_, key, value, inserted);
        return inserted;
    }

    bool search(const Key& key, Value& outValue) const
    {
        Node* node = searchNode(root_, key);
        if (node)
        {
            outValue = node->value_;
            return true;
        }
        return false;
    }

    bool search(const Key& key) const
    {
        return searchNode(root_, key) != nullptr;
    }

    bool remove(const Key& key)
    {
        bool deleted = false;
        root_ = removeNode(root_, key, deleted);
        if (deleted)
        {
            countNodes_--;
        }
        return deleted;
    }

    void preOrderWalk(std::ostream& out) const
    {
        preOrderWalk(root_, out);
    }

    void inOrderWalk(std::ostream& out) const
    {
        inOrderWalk(root_, out);
    }

    void postOrderWalk(std::ostream& out) const
    {
        postOrderWalk(root_, out);
    }

    int size() const
    {
        return countNodes_;
    }
    bool empty() const
    {
        return countNodes_ == 0;
    }

    bool isAVL() const
    {
        int height = 0;
        return isAVL(root_, height);
    }

    int getHeight() const
    {
        return getHeight(root_);
    }

    void print(std::ostream& out) const
    {
        printNode(root_, out);
    }

private:
    struct Node
    {
        Key key_;
        Value value_;
        unsigned char height_;
        Node* left_;
        Node* right_;

        Node(const Key& k, const Value& v) : key_(k), value_(v), 
            height_(1), left_(nullptr), right_(nullptr)
        {
        }
    };
    Node* root_;
    int countNodes_;
    void destroySubTree(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        destroySubTree(node->left_);
        destroySubTree(node->right_);
        delete node;
    }

    void printNode(Node* node, std::ostream& out, int indent = 0) const
    {
        if (node == nullptr)
        {
            return;
        }
        for (int i = 0; i < indent; ++i)
        {
            out << "  ";
        }
        out << node->key_ << " : " << node->value_ << '\n';
        printNode(node->left_, out, indent + 1);
        printNode(node->right_, out, indent + 1);
    }
    unsigned char getHeight(Node* node) const
    {
        return node ? node->height_ : 0;
    }

    void updateHeight(Node* node)
    {
        if (node)
        {
            unsigned char left = getHeight(node->left_);
            unsigned char right = getHeight(node->right_);
            node->height_ = 1 + (left > right ? left : right);
        }
    }

    int balanceFactor(Node* node) const
    {
        return static_cast<int>(getHeight(node->right_)) - static_cast<int>(getHeight(node->left_));
    }

    Node* rotateRight(Node* node)
    {
        Node* leftChild = node->left_;
        node->left_ = leftChild->right_;
        leftChild->right_ = node;
        updateHeight(node);
        updateHeight(leftChild);
        return leftChild;
    }

    Node* rotateLeft(Node* node)
    {
        Node* rightChild = node->right_;
        node->right_ = rightChild->left_;
        rightChild->left_ = node;
        updateHeight(node);
        updateHeight(rightChild);
        return rightChild;
    }

    Node* balanceTree(Node* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf == 2)
        {
            if (balanceFactor(node->right_) < 0)
            {
                node->right_ = rotateRight(node->right_);
            }
            return rotateLeft(node);
        }
        else if (bf == -2)
        {
            if (balanceFactor(node->left_) > 0)
            {
                node->left_ = rotateLeft(node->left_);
            }
            return rotateRight(node);
        }

        return node;
    }

    Node* insertNode(Node* node, const Key& key, const Value& value, bool& inserted)
    {
        if (node == nullptr)
        {
            countNodes_++;
            inserted = true;
            return new Node(key, value);
        }

        if (key < node->key_)
        {
            node->left_ = insertNode(node->left_, key, value, inserted);
        }
        else if (key > node->key_)
        {
            node->right_ = insertNode(node->right_, key, value, inserted);
        }
        else
        {
            node->value_ = value;
            return node;
        }
        updateHeight(node);
        return balanceTree(node);
    }

    Node* searchNode(Node* node, const Key& key) const
    {
        Node* current = node;
        while (current != nullptr && current->key_ != key)
        {
            if (key < current->key_)
            {
                current = current->left_;
            }
            else
            {
                current = current->right_;
            }
        }
        return current;
    }

    Node* extractMinNode(Node*& node)
    {
        if (node->left_ == nullptr)
        {
            Node* minNode = node;
            node = node->right_;
            return minNode;
        }
        Node* minNode = extractMinNode(node->left_);
        updateHeight(node);
        node = balanceTree(node);
        return minNode;
    }

    Node* removeNode(Node* node, const Key& key, bool& deleted)
    {
        if (node == nullptr)
        {
            deleted = false;
            return nullptr;
        }

        if (key < node->key_)
        {
            node->left_ = removeNode(node->left_, key, deleted);
        }
        else if (key > node->key_)
        {
            node->right_ = removeNode(node->right_, key, deleted);
        }
        else
        {
            deleted = true;
            if (node->left_ == nullptr || node->right_ == nullptr)
            {
                Node* child = (node->left_ != nullptr) ? node->left_ : node->right_;
                delete node;
                return child;
            }
            Node* successor = extractMinNode(node->right_);
            successor->left_ = node->left_;
            successor->right_ = node->right_;
            delete node;
            node = successor;
        }
        updateHeight(node);
        return balanceTree(node);
    }

    void preOrderWalk(Node* node, std::ostream& out) const
    {
        if (node == nullptr)
        {
            return;
        }
        out << node->key_ << " : " << node->value_ << "\n";
        preOrderWalk(node->left_, out);
        preOrderWalk(node->right_, out);
    }

    void inOrderWalk(Node* node, std::ostream& out) const
    {
        if (node == nullptr)
        {
            return;
        }
        inOrderWalk(node->left_, out);
        out << node->key_ << " : " << node->value_ << "\n";
        inOrderWalk(node->right_, out);
    }

    void postOrderWalk(Node* node, std::ostream& out) const
    {
        if (node == nullptr)
        {
            return;
        }
        postOrderWalk(node->left_, out);
        postOrderWalk(node->right_, out);
        out << node->key_ << " : " << node->value_ << "\n";
    }
    bool isAVL(Node* node, int& height) const
    {
        if (node == nullptr)
        {
            height = 0;
            return true;
        }

        int left = 0;
        int right = 0;
        bool isAvlLeft = isAVL(node->left_, left);
        bool isAvlRight = isAVL(node->right_, right);

        height = 1 + (left > right ? left : right);

        int balanceFactor = right - left;

        if (balanceFactor < -1 || balanceFactor > 1)
        {
            return false;
        }
        if (node->height_ != static_cast<unsigned char>(height))
        {
            return false;
        }

        return isAvlLeft && isAvlRight;
    }
    Node* copySubTree(Node* otherNode)
    {
        if (otherNode == nullptr)
        {
            return nullptr;
        }
        Node* newNode = new Node(otherNode->key_, otherNode->value_);
        newNode->height_ = otherNode->height_;

        try 
        {
            newNode->left_ = copySubTree(otherNode->left_);
            newNode->right_ = copySubTree(otherNode->right_);
        }
        catch (...)
        {
            destroySubTree(newNode);
            throw;
        }
        return newNode;
    }

};

#endif