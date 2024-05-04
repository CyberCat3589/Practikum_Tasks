#include <cassert>
#include <iostream>
#include <memory>

template <typename T> 
struct TreeNode;

template <typename T> 
using TreeNodePtr = std::unique_ptr<TreeNode<T>>;

template <typename T> 
struct TreeNode
{
    // Используйте TreeNodePtr<T> вместо сырых указателей.
    // Примите умные указатели по rvalue-ссылке.
    TreeNode(T val, TreeNodePtr<T>&& left, TreeNodePtr<T>&& right) : value(std::move(val)), left(std::move(left)), right(std::move(right)) {}

    T value;
    TreeNodePtr<T> left;   // Замените TreeNode* на TreeNodePtr<T>
    TreeNodePtr<T> right;  // Замените TreeNode* на TreeNodePtr<T>

    // parent оставьте обычным указателем, иначе возникнет
    // кольцевая зависимость.
    TreeNode* parent = nullptr;
};

template <typename T> 
bool CheckTreeProperty(const TreeNode<T>* node, const T* min, const T* max) noexcept
{
    if (!node)
    {
        return true;
    }
    if ((min && node->value <= *min) || (max && node->value >= *max))
    {
        return false;
    }
    return CheckTreeProperty(node->left.get(), min, &node->value) && CheckTreeProperty(node->right.get(), &node->value, max);
}

template <class T> 
bool CheckTreeProperty(const TreeNode<T>* node) noexcept
{
    return CheckTreeProperty<T>(node, nullptr, nullptr);
}

template <typename T> 
TreeNode<T>* begin(TreeNode<T>* node) noexcept
{
    while (node->left)
    {
        node = node->left.get();
    }

    return node;
}

template <typename T> 
TreeNode<T>* next(TreeNode<T>* node) noexcept
{
    if (node->right)
    {
        return begin(node->right.get());
    }
    while (node->parent)
    {
        bool is_right = (node == node->parent->right.get());
        if (!is_right)
        {
            return node->parent;
        }
        node = node->parent;
    }

    return nullptr;
}

// Замените указатели на умные. Сигнатура функции должна стать такой:
// TreeNodePtr<int> N(int val, TreeNodePtr<int>&& left = {}, TreeNodePtr<int>&& right = {})
TreeNodePtr<int> N(int val, TreeNodePtr<int>&& left = {}, TreeNodePtr<int>&& right = {})
{
    auto node = std::make_unique<TreeNode<int>>(val, std::move(left), std::move(right));
    if (node->left)
    {
        node->left->parent = node.get();
    }
    if (node->right)
    {
        node->right->parent = node.get();
    }

    return node;
}

int main()
{
    using namespace std;
    using T = TreeNode<int>;
    auto root1 = N(6, N(4, N(3), N(5)), N(7));
    assert(CheckTreeProperty(root1.get()));

    T* iter = begin(root1.get());
    while (iter)
    {
        cout << iter->value << " "s;
        iter = next(iter);
    }
    cout << endl;

    auto root2 = N(6, N(4, N(3), N(5)), N(7, N(8)));
    assert(!CheckTreeProperty(root2.get()));
}