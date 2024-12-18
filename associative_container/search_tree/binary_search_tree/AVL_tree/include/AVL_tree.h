#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_AVL_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_AVL_TREE_H

#include <binary_search_tree.h>

template<
    typename tkey,
    typename tvalue>
class AVL_tree final:
    public binary_search_tree<tkey, tvalue>
{

private:
    
    struct node final:
        binary_search_tree<tkey, tvalue>::node
    {
        explicit node(tkey const &, tvalue &&, size_t const &);

        size_t _height;

        int getBalanceFactor() const;

        static int getHeight(node *);

        void updateHeight();
    };

public:
    
    struct iterator_data final:
        public binary_search_tree<tkey, tvalue>::iterator_data
    {
    
    public:
        
        size_t subtree_height;
    
    public:
        
        explicit iterator_data(
            unsigned int depth,
            tkey const &key,
            tvalue const &value,
            size_t subtree_height);

        explicit iterator_data(node *node, size_t d);
        
    };

    struct iterator_const_data final:
        public binary_search_tree<tkey, tvalue>::iterator_const_data
    {

    public:

        size_t subtree_height;

    public:

        explicit iterator_const_data(
            unsigned int depth,
            tkey const &key,
            tvalue const &value,
            size_t subtree_height);

        explicit iterator_const_data(node *node, size_t d);

    };

public:

    class prefix_iterator final
    {
        std::stack<std::pair<std::pair<bool, bool>, std::pair<node *, iterator_data>>> pathToNode;
    public:

        explicit prefix_iterator(
            typename AVL_tree<tkey, tvalue>::node *subtree_root);

    public:

        bool operator==(
            prefix_iterator const &other) const noexcept;

        bool operator!=(
            prefix_iterator const &other) const noexcept;

        prefix_iterator &operator++();

        prefix_iterator const operator++(
            int not_used);
        iterator_data const *operator*() const;

    };

    class prefix_const_iterator final
    {
        std::stack<std::pair<std::pair<bool, bool>, std::pair<node *, iterator_const_data>>> pathToNode;
    public:

        explicit prefix_const_iterator(
            typename AVL_tree<tkey, tvalue>::node *subtree_root);

    public:

        bool operator==(
            prefix_const_iterator const &other) const noexcept;

        bool operator!=(
            prefix_const_iterator const &other) const noexcept;

        prefix_const_iterator &operator++();

        prefix_const_iterator const operator++(
            int not_used);
        iterator_const_data const *operator*() const;

    };

    class prefix_reverse_iterator final
    {
        std::stack<std::pair<std::pair<bool, bool>, std::pair<node *, iterator_data>>> pathToNode;
    public:

        explicit prefix_reverse_iterator(
            node *subtree_root);

    public:

        bool operator==(
            prefix_reverse_iterator const &other) const noexcept;

        bool operator!=(
            prefix_reverse_iterator const &other) const noexcept;

        prefix_reverse_iterator &operator++();

        prefix_reverse_iterator const operator++(
            int not_used);

        iterator_data const *operator*() const;

    };

    class prefix_const_reverse_iterator final
    {
        std::stack<std::pair<std::pair<bool, bool>, std::pair<node *, iterator_const_data>>> pathToNode;
    public:

        explicit prefix_const_reverse_iterator(
            node *subtree_root);

    public:

        bool operator==(
            prefix_const_reverse_iterator const &other) const noexcept;

        bool operator!=(
            prefix_const_reverse_iterator const &other) const noexcept;

        prefix_const_reverse_iterator &operator++();

        prefix_const_reverse_iterator const operator++(
            int not_used);

        iterator_const_data const *operator*() const;

    };

    class infix_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_data>>> pathToNode;
    public:

        explicit infix_iterator(
            node *subtree_root);

    public:

        bool operator==(
            infix_iterator const &other) const noexcept;

        bool operator!=(
            infix_iterator const &other) const noexcept;

        infix_iterator &operator++();

        infix_iterator const operator++(
            int not_used);

        iterator_data const *operator*() const;

    };

    class infix_const_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_const_data>>> pathToNode;
    public:

        explicit infix_const_iterator(
            node *subtree_root);

    public:

        bool operator==(
            infix_const_iterator const &other) const noexcept;

        bool operator!=(
            infix_const_iterator const &other) const noexcept;

        infix_const_iterator &operator++();

        infix_const_iterator const operator++(
            int not_used);

        iterator_const_data const *operator*() const;

    };

    class infix_reverse_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_data>>> pathToNode;
    public:

        explicit infix_reverse_iterator(
            node *subtree_root);

    public:

        bool operator==(
            infix_reverse_iterator const &other) const noexcept;

        bool operator!=(
            infix_reverse_iterator const &other) const noexcept;

        infix_reverse_iterator &operator++();

        infix_reverse_iterator const operator++(
            int not_used);

        iterator_data *operator*() const;

    };

    class infix_const_reverse_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_const_data>>> pathToNode;
    public:

        explicit infix_const_reverse_iterator(
            node *subtree_root);

    public:

        bool operator==(
            infix_const_reverse_iterator const &other) const noexcept;

        bool operator!=(
            infix_const_reverse_iterator const &other) const noexcept;

        infix_const_reverse_iterator &operator++();

        infix_const_reverse_iterator const operator++(
            int not_used);

        iterator_const_data const *operator*() const;

    };

    class postfix_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_data>>> pathToNode;
    public:

        explicit postfix_iterator(
            node *subtree_root);

    public:

        bool operator==(
            postfix_iterator const &other) const noexcept;

        bool operator!=(
            postfix_iterator const &other) const noexcept;

        postfix_iterator &operator++();

        postfix_iterator const operator++(
            int not_used);

        iterator_data const *operator*() const;

    };

    class postfix_const_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_const_data>>> pathToNode;
    public:

        explicit postfix_const_iterator(
            node *subtree_root);

    public:

        bool operator==(
            postfix_const_iterator const &other) const noexcept;

        bool operator!=(
            postfix_const_iterator const &other) const noexcept;

        postfix_const_iterator &operator++();

        postfix_const_iterator const operator++(
            int not_used);

        iterator_const_data const *operator*() const;

    };

    class postfix_reverse_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_data>>> pathToNode;
    public:

        explicit postfix_reverse_iterator(
            node *subtree_root);

    public:

        bool operator==(
            postfix_reverse_iterator const &other) const noexcept;

        bool operator!=(
            postfix_reverse_iterator const &other) const noexcept;

        postfix_reverse_iterator &operator++();

        postfix_reverse_iterator const operator++(
            int not_used);

        iterator_data const *operator*() const;

    };

    class postfix_const_reverse_iterator final
    {
        std::stack<std::pair<unsigned char, std::pair<node *, iterator_const_data>>> pathToNode;
    public:

        explicit postfix_const_reverse_iterator(
            node *subtree_root);

    public:

        bool operator==(
            postfix_const_reverse_iterator const &other) const noexcept;

        bool operator!=(
            postfix_const_reverse_iterator const &other) const noexcept;

        postfix_const_reverse_iterator &operator++();

        postfix_const_reverse_iterator const operator++(
            int not_used);

        iterator_const_data const *operator*() const;

    };

private:
    
    class insertion_template_method final:
        public binary_search_tree<tkey, tvalue>::insertion_template_method
    {
    
    public:
        
        explicit insertion_template_method(
            AVL_tree<tkey, tvalue> *tree,
            typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy);
    
    private:
        
        inline size_t getSizeOfNode() const override;

        void balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &) override;

        void construct_node(typename binary_search_tree<tkey, tvalue>::node *at, tkey const &key, tvalue &&value) const noexcept override;
        
    };
    
    class obtaining_template_method final:
        public binary_search_tree<tkey, tvalue>::obtaining_template_method
    {
    
    public:
        
        explicit obtaining_template_method(
            AVL_tree<tkey, tvalue> *tree);
        
        // TODO: think about it!
        
    };
    
    class disposal_template_method final:
        public binary_search_tree<tkey, tvalue>::disposal_template_method
    {
    
    public:
        
        explicit disposal_template_method(
            AVL_tree<tkey, tvalue> *tree,
            typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy);
        
        // TODO: think about it!
    private:
        void balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &) override;
        
    };

public:
    
    explicit AVL_tree(
        allocator *allocator = nullptr,
        logger *logger = nullptr,
        typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy = binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy::throw_an_exception,
        typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy = binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy::throw_an_exception,
        std::function<int(tkey const &, tkey const &)> const &comparer = [](tkey const &a, tkey const &b) {
        if(a < b) return -1;
        if(a == b) return 0;
        return 1;
    });

public:
    
    ~AVL_tree() noexcept final;
    
    AVL_tree(
        AVL_tree<tkey, tvalue> const &other);
    
    AVL_tree<tkey, tvalue> &operator=(
        AVL_tree<tkey, tvalue> const &other);
    
    AVL_tree(
        AVL_tree<tkey, tvalue> &&other) noexcept;
    
    AVL_tree<tkey, tvalue> &operator=(
        AVL_tree<tkey, tvalue> &&other) noexcept;

#pragma region iterators requests definition

    prefix_iterator begin_prefix() const noexcept;

    prefix_iterator end_prefix() const noexcept;

    prefix_const_iterator cbegin_prefix() const noexcept;

    prefix_const_iterator cend_prefix() const noexcept;

    prefix_reverse_iterator rbegin_prefix() const noexcept;

    prefix_reverse_iterator rend_prefix() const noexcept;

    prefix_const_reverse_iterator crbegin_prefix() const noexcept;

    prefix_const_reverse_iterator crend_prefix() const noexcept;

    infix_iterator begin_infix() const noexcept;

    infix_iterator end_infix() const noexcept;

    infix_const_iterator cbegin_infix() const noexcept;

    infix_const_iterator cend_infix() const noexcept;

    infix_reverse_iterator rbegin_infix() const noexcept;

    infix_reverse_iterator rend_infix() const noexcept;

    infix_const_reverse_iterator crbegin_infix() const noexcept;

    infix_const_reverse_iterator crend_infix() const noexcept;

    postfix_iterator begin_postfix() const noexcept;

    postfix_iterator end_postfix() const noexcept;

    postfix_const_iterator cbegin_postfix() const noexcept;

    postfix_const_iterator cend_postfix() const noexcept;

    postfix_reverse_iterator rbegin_postfix() const noexcept;

    postfix_reverse_iterator rend_postfix() const noexcept;

    postfix_const_reverse_iterator crbegin_postfix() const noexcept;

    postfix_const_reverse_iterator crend_postfix() const noexcept;

    void copyNode(node *other, node *&dest);

#pragma endregion iterators requests definition
    
};
template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::insertion_template_method::insertion_template_method(
    AVL_tree<tkey, tvalue> *tree,
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy):
    binary_search_tree<tkey, tvalue>::insertion_template_method(tree, insertion_strategy)
{
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue>::insertion_template_method::insertion_template_method(AVL_tree<tkey, tvalue> *, typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::obtaining_template_method::obtaining_template_method(
    AVL_tree<tkey, tvalue> *tree) :
    binary_search_tree<tkey, tvalue>::obtaining_template_method(tree)
{
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue>::obtaining_template_method::obtaining_template_method(AVL_tree<tkey, tvalue> *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::disposal_template_method::disposal_template_method(
    AVL_tree<tkey, tvalue> *tree,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) :
    binary_search_tree<tkey, tvalue>::disposal_template_method(tree, disposal_strategy)
{
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue>::disposal_template_method::disposal_template_method(AVL_tree<tkey, tvalue> *, typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::AVL_tree(
    allocator *allocator,
    logger *logger,
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy,
    std::function<int(tkey const &, tkey const &)> const &comparator) :
    binary_search_tree<tkey, tvalue>(
        new AVL_tree<tkey, tvalue>::insertion_template_method(this, insertion_strategy),
        new AVL_tree<tkey, tvalue>::obtaining_template_method(this),
        new AVL_tree<tkey, tvalue>::disposal_template_method(this, disposal_strategy),
        comparator,
        allocator,
        logger
    )
{
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue>::AVL_tree(allocator *, logger *, typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy, typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::~AVL_tree() noexcept
{
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue>::~AVL_tree() noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::AVL_tree(
    AVL_tree<tkey, tvalue> const &other) :
binary_search_tree<tkey, tvalue>(
        new insertion_template_method(this, other._insertion_template->_strategy),
        new obtaining_template_method(this),
        new disposal_template_method(this, other._disposal_template->_strategy),
        other._keys_comparer,
        other.get_allocator(),
        other.get_logger()
    )
{
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue>::AVL_tree(AVL_tree<tkey, tvalue> const &)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue> &AVL_tree<tkey, tvalue>::operator=(
    AVL_tree<tkey, tvalue> const &other)
{
    if(this != &other) {
        this->destroyNodes();
        this->_keys_comparer = other._keys_comparer;
        this->_logger = other._logger;
        this->_allocator = other._allocator;
        this->_insertion_template->_strategy = other._insertion_template->_strategy;
        this->_disposal_template->_strategy = other._disposal_template->_strategy;
        copyNode(other._root, this->_root);
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue> &AVL_tree<tkey, tvalue>::operator=(AVL_tree<tkey, tvalue> const &)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::AVL_tree(
    AVL_tree<tkey, tvalue> &&other) noexcept :
binary_search_tree<tkey, tvalue>(
        new insertion_template_method(this, other._insertion_template->_strategy),
        new obtaining_template_method(this),
        new disposal_template_method(this, other._disposal_template->_strategy),
        other._keys_comparer,
        other.get_allocator(),
        other.get_logger()
    )
{
    this->_root = other._root;
    other._root = nullptr;
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue>::AVL_tree(AVL_tree<tkey, tvalue> &&) noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue> &AVL_tree<tkey, tvalue>::operator=(
    AVL_tree<tkey, tvalue> &&other) noexcept
{
    if(this != &other) {
        this->destroyNodes();
        this->_keys_comparer = other._keys_comparer;
        this->_logger = other._logger;
        this->_allocator = other._allocator;
        this->_insertion_template->_strategy = other._insertion_template->_strategy;
        this->_disposal_template->_strategy = other._disposal_template->_strategy;
        this->_root = other._root;
        other._root = nullptr;
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> AVL_tree<tkey, tvalue> &AVL_tree<tkey, tvalue>::operator=(AVL_tree<tkey, tvalue> &&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue>
void AVL_tree<tkey, tvalue>::copyNode(node *other, node *&dest) {
    if(other == nullptr) return;
    dest = reinterpret_cast<typename AVL_tree<tkey, tvalue>::node *>(allocator_guardant::allocate_with_guard(sizeof(typename AVL_tree<tkey, tvalue>::node)));
    new (dest) typename AVL_tree<tkey, tvalue>::node(other->_key, other->_value, other->_height);
    copyNode(other->left_subtree, dest->left_subtree);
    copyNode(other->right_subtree, dest->right_subtree);
}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::node::node(tkey const &key, tvalue &&value, size_t const &height) :
    binary_search_tree<tkey, tvalue>::node(key, std::forward<tvalue>(value)),
    _height(height)
{}

template<
    typename tkey,
    typename tvalue>
inline size_t AVL_tree<tkey, tvalue>::insertion_template_method::getSizeOfNode() const {
    return sizeof(AVL_tree<tkey, tvalue>::node);
}

template<
    typename tkey,
    typename tvalue>
void AVL_tree<tkey, tvalue>::insertion_template_method::balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &path) {
    if(path.empty()) return;
    path.pop();
    while(!path.empty()) {
        auto pNow = path.top();
        auto balanceFactor = dynamic_cast<node *>(*pNow)->getBalanceFactor();
        if(abs(balanceFactor) > 1) {
            if(balanceFactor < -1) {
                auto leftChildBalanceFactor = dynamic_cast<node *>((*pNow)->left_subtree)->getBalanceFactor();
                if(leftChildBalanceFactor <= 0) {
                    this->_tree->small_right_rotation(*pNow);
                } else {
                    this->_tree->big_right_rotation(*pNow);
                }
            } else {
                auto rightChildBalanceFactor = dynamic_cast<node *>((*pNow)->right_subtree)->getBalanceFactor();
                if(rightChildBalanceFactor >= 0) {
                    this->_tree->small_left_rotation(*pNow);
                } else {
                    this->_tree->big_left_rotation(*pNow);
                }
            }
        }
        dynamic_cast<node *>(*pNow)->updateHeight();
        path.pop();
    }
}

template<
    typename tkey,
    typename tvalue>
void AVL_tree<tkey, tvalue>::insertion_template_method::construct_node(typename binary_search_tree<tkey, tvalue>::node *at, tkey const &key, tvalue &&value) const noexcept {
    allocator::construct(reinterpret_cast<AVL_tree<tkey, tvalue>::node *>(at), key, std::forward<tvalue>(value), 1);
}

template<typename tkey, typename tvalue>
int AVL_tree<tkey, tvalue>::node::getHeight(node *node) {
    return (node == nullptr) ? 0 : node->_height;
}


template<typename tkey, typename tvalue>
int AVL_tree<tkey, tvalue>::node::getBalanceFactor() const {
    return getHeight(dynamic_cast<node *>(this->right_subtree)) - getHeight(dynamic_cast<node *>(this->left_subtree));
}

template<typename tkey, typename tvalue>
void AVL_tree<tkey, tvalue>::node::updateHeight() {
    if(this->left_subtree != nullptr) dynamic_cast<node *>(this->left_subtree)->_height = std::max(getHeight(dynamic_cast<node *>(this->left_subtree->left_subtree)), getHeight(dynamic_cast<node *>(this->left_subtree->right_subtree))) + 1;
    if(this->right_subtree != nullptr) dynamic_cast<node *>(this->right_subtree)->_height = std::max(getHeight(dynamic_cast<node *>(this->right_subtree->left_subtree)), getHeight(dynamic_cast<node *>(this->right_subtree->right_subtree))) + 1;
    this->_height = std::max(getHeight(dynamic_cast<node *>(this->left_subtree)), getHeight(dynamic_cast<node *>(this->right_subtree))) + 1;
}

template<
    typename tkey,
    typename tvalue>
void AVL_tree<tkey, tvalue>::disposal_template_method::balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &path) {
    if(path.empty()) return;
    path.pop();
    while(!path.empty()) {
        auto pNow = path.top();
        auto balanceFactor = dynamic_cast<node *>(*pNow)->getBalanceFactor();
        if(abs(balanceFactor) > 1) {
            if(balanceFactor < -1) {
                auto leftChildBalanceFactor = dynamic_cast<node *>((*pNow)->left_subtree)->getBalanceFactor();
                if(leftChildBalanceFactor <= 0) {
                    this->_tree->small_right_rotation(*pNow);
                } else {
                    this->_tree->big_right_rotation(*pNow);
                }
            } else {
                auto rightChildBalanceFactor = dynamic_cast<node *>((*pNow)->right_subtree)->getBalanceFactor();
                if(rightChildBalanceFactor >= 0) {
                    this->_tree->small_left_rotation(*pNow);
                } else {
                    this->_tree->big_left_rotation(*pNow);
                }
            }
        }
        dynamic_cast<node *>(*pNow)->updateHeight();
        path.pop();
    }
}

#pragma region iterators implementation

#pragma region iterator data implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::iterator_data::iterator_data(
    unsigned int depth,
    tkey const &key,
    tvalue const &value,
    size_t height
    ):
    binary_search_tree<tkey, tvalue>::iterator_data(depth, key, value),
    subtree_height(height)
{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::iterator_data::iterator_data(unsigned int, tkey const &, tvalue const &)", "your code should be here...");
}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue>::iterator_data::iterator_data(node *node, size_t d) :
iterator_data(d, node->_key, node->_value, node == nullptr ? 0 : node->_height)
{}

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::iterator_const_data::iterator_const_data(
unsigned int depth,
tkey const &key,
tvalue const &value,
size_t height
):
binary_search_tree<tkey, tvalue>::iterator_const_data(depth, key, value),
subtree_height(height)
{}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue>::iterator_const_data::iterator_const_data(node *node, size_t d) :
iterator_const_data(d, node->_key, node->_value, node->_height)
{}

#pragma endregion iterator data implementation

#pragma region prefix_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root) :
    pathToNode()
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(subtree_root, iterator_data(subtree_root, 0)));
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::prefix_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::prefix_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_iterator &AVL_tree<tkey, tvalue>::prefix_iterator::operator++()
{
    //if(pathToNode.empty()) return *this;
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        /*Мы были везде*/
        pathToNode.pop();
    }

    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_iterator &binary_search_tree<tkey, tvalue>::prefix_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_iterator const AVL_tree<tkey, tvalue>::prefix_iterator::operator++(
    int not_used)
{
    prefix_iterator copy(*this);
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_iterator const binary_search_tree<tkey, tvalue>::prefix_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_data const *AVL_tree<tkey, tvalue>::prefix_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data *binary_search_tree<tkey, tvalue>::prefix_iterator::operator*() const", "your code should be here...");
}

#pragma endregion prefix_iterator implementation

#pragma region prefix_const_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::prefix_const_iterator::prefix_const_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root):
    pathToNode()
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(subtree_root, iterator_const_data(subtree_root, 0)));
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_const_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::prefix_const_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_const_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::prefix_const_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_iterator &AVL_tree<tkey, tvalue>::prefix_const_iterator::operator++()
{
    //if(pathToNode.empty()) return *this;
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        /*Мы были везде*/
        pathToNode.pop();
    }

    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_const_iterator &binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_iterator const AVL_tree<tkey, tvalue>::prefix_const_iterator::operator++(
    int not_used)
{
    prefix_const_iterator copy(*this);
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_const_data const *AVL_tree<tkey, tvalue>::prefix_const_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator*() const", "your code should be here...");
}

#pragma endregion prefix_const_iterator implementation

#pragma region prefix_reverse_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::prefix_reverse_iterator::prefix_reverse_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(subtree_root, iterator_data(subtree_root, 0)));
    // not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::prefix_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_reverse_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_reverse_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator &AVL_tree<tkey, tvalue>::prefix_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        /*Мы были везде*/
        pathToNode.pop();
    }

    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator &binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator const AVL_tree<tkey, tvalue>::prefix_reverse_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_data const *AVL_tree<tkey, tvalue>::prefix_reverse_iterator::operator*() const
{
    if(pathToNode.empty()) throw;
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data *binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator*() const", "your code should be here...");
}

#pragma endregion prefix_reverse_iterator implementation

#pragma region prefix_const_reverse_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(subtree_root, iterator_const_data(subtree_root, 0)));
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator &AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        /*Мы были везде*/
        pathToNode.pop();
    }

    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator &binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator const AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_const_data const *AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator*() const
{
    if(pathToNode.empty()) throw;
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator*() const", "your code should be here...");
}

#pragma endregion prefix_const_reverse_iterator implementation

#pragma region infix_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::infix_iterator::infix_iterator(
    AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    node *pNow = subtree_root;
    size_t death = 0;
    while(pNow != nullptr){
        pathToNode.emplace(1, std::pair<node *, iterator_data>(pNow, iterator_data(pNow, death++)));
        pNow = pNow->left_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::infix_iterator::infix_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::infix_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::infix_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_iterator &AVL_tree<tkey, tvalue>::infix_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(top.second.first->left_subtree, iterator_data(top.second.first->left_subtree, top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            break;
        }
        if(top.first == 2) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(top.second.first->right_subtree, iterator_data(top.second.first->right_subtree, top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_iterator &binary_search_tree<tkey, tvalue>::infix_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_iterator const AVL_tree<tkey, tvalue>::infix_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_iterator const binary_search_tree<tkey, tvalue>::infix_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_data const *AVL_tree<tkey, tvalue>::infix_iterator::operator*() const
{
    if(pathToNode.empty()) throw;
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data *binary_search_tree<tkey, tvalue>::infix_iterator::operator*() const", "your code should be here...");
}

#pragma endregion infix_iterator implementation

#pragma region infix_const_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::infix_const_iterator::infix_const_iterator(
    AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    node *pNow = subtree_root;
    size_t death = 0;
    while(pNow != nullptr){
        pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
        pNow = dynamic_cast<node *>(pNow->left_subtree);
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::infix_const_iterator::infix_const_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_const_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::infix_const_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_const_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::infix_const_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_iterator &AVL_tree<tkey, tvalue>::infix_const_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            break;
        }
        if(top.first == 2) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_const_iterator &binary_search_tree<tkey, tvalue>::infix_const_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_iterator const AVL_tree<tkey, tvalue>::infix_const_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_const_iterator const binary_search_tree<tkey, tvalue>::infix_const_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_const_data const *AVL_tree<tkey, tvalue>::infix_const_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::infix_const_iterator::operator*() const", "your code should be here...");
}

#pragma endregion infix_const_iterator implementation

#pragma region infix_reverse_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::infix_reverse_iterator::infix_reverse_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(pNow != nullptr) {
        pathToNode.emplace(1, std::pair<node *, iterator_data>(pNow, iterator_data(pNow, death++)));
        pNow = dynamic_cast<node *>(pNow->right_subtree);
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::infix_reverse_iterator::infix_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_reverse_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::infix_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_reverse_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::infix_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_reverse_iterator &AVL_tree<tkey, tvalue>::infix_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            break;
        }
        if(top.first == 2) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator &binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_reverse_iterator const AVL_tree<tkey, tvalue>::infix_reverse_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_data *AVL_tree<tkey, tvalue>::infix_reverse_iterator::operator*() const
{
    if(pathToNode.empty()) throw;
    return const_cast<iterator_data *>(&(pathToNode.top().second.second));
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data *binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator*() const", "your code should be here...");
}

#pragma endregion infix_reverse_iterator implementation

#pragma region infix_const_reverse_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::infix_const_reverse_iterator::infix_const_reverse_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(pNow != nullptr) {
        pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
        pNow = dynamic_cast<node *>(pNow->right_subtree);
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::infix_const_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_const_reverse_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::infix_const_reverse_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator &AVL_tree<tkey, tvalue>::infix_const_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            break;
        }
        if(top.first == 2) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator &binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator const AVL_tree<tkey, tvalue>::infix_const_reverse_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_const_data const *AVL_tree<tkey, tvalue>::infix_const_reverse_iterator::operator*() const
{
    if(pathToNode.empty()) throw;
    return const_cast<iterator_const_data *>(&(pathToNode.top().second.second));
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator*() const", "your code should be here...");
}

#pragma endregion infix_const_reverse_iterator implementation

#pragma region postfix_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::postfix_iterator::postfix_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_data>(pNow, iterator_data(pNow, death++)));
            if(pNow->left_subtree == nullptr) break;
            pNow = dynamic_cast<node *>(pNow->left_subtree);
        }
        ++pathToNode.top().first;
        if(pNow->right_subtree == nullptr) break;
        pNow = dynamic_cast<node *>(pNow->right_subtree);
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_iterator::postfix_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::postfix_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::postfix_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_iterator &AVL_tree<tkey, tvalue>::postfix_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 2) {
            ++top.first;
            break;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_iterator &binary_search_tree<tkey, tvalue>::postfix_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_iterator const AVL_tree<tkey, tvalue>::postfix_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_iterator const binary_search_tree<tkey, tvalue>::postfix_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_data const *AVL_tree<tkey, tvalue>::postfix_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data *binary_search_tree<tkey, tvalue>::postfix_iterator::operator*() const", "your code should be here...");
}

#pragma endregion postfix_iterator implementation

#pragma region postfix_const_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::postfix_const_iterator::postfix_const_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
            if(pNow->left_subtree == nullptr) break;
            pNow = dynamic_cast<node *>(pNow->left_subtree);
        }
        ++pathToNode.top().first;
        if(pNow->right_subtree == nullptr) break;
        pNow = dynamic_cast<node *>(pNow->right_subtree);
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_const_iterator::postfix_const_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_const_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::postfix_const_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_const_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::postfix_const_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_iterator &AVL_tree<tkey, tvalue>::postfix_const_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 2) {
            ++top.first;
            break;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_const_iterator &binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_iterator const AVL_tree<tkey, tvalue>::postfix_const_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_const_data const *AVL_tree<tkey, tvalue>::postfix_const_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator*() const", "your code should be here...");
}

#pragma endregion postfix_const_iterator implementation

#pragma region postfix_reverse_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::postfix_reverse_iterator::postfix_reverse_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_data>(pNow, iterator_data(pNow, death++)));
            if(pNow->right_subtree == nullptr) break;
            pNow = dynamic_cast<node *>(pNow->right_subtree);
        }
        ++pathToNode.top().first;
        if(pNow->left_subtree == nullptr) break;
        pNow = dynamic_cast<node *>(pNow->left_subtree);
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::postfix_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_reverse_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_reverse_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator &AVL_tree<tkey, tvalue>::postfix_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 2) {
            ++top.first;
            break;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator &binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator const AVL_tree<tkey, tvalue>::postfix_reverse_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_data const *AVL_tree<tkey, tvalue>::postfix_reverse_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data *binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator*() const", "your code should be here...");
}

#pragma endregion postfix_reverse_iterator implementation

#pragma region postfix_const_reverse_iterator implementation

template<
    typename tkey,
    typename tvalue>
AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(
    typename AVL_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
            if(pNow->right_subtree == nullptr) break;
            pNow = dynamic_cast<node *>(pNow->right_subtree);
        }
        ++pathToNode.top().first;
        if(pNow->left_subtree == nullptr) break;
        pNow = dynamic_cast<node *>(pNow->left_subtree);
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator==(
    typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator!=(
    typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator &AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->right_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->right_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(dynamic_cast<node *>(top.second.first->left_subtree), iterator_const_data(dynamic_cast<node *>(top.second.first->left_subtree), top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 2) {
            ++top.first;
            break;
        }
        if(top.first == 3) {
            pathToNode.pop();
        }
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator &binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator++()", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator const AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator++(
    int not_used)
{
    auto copy = *this;
    ++*this;
    return copy;
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator++(int)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::iterator_const_data const *AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator*() const", "your code should be here...");
}

#pragma endregion postfix_const_reverse_iterator implementation

#pragma endregion iterators implementation

#pragma region iterators requesting implementation

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_iterator AVL_tree<tkey, tvalue>::begin_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_iterator AVL_tree<tkey, tvalue>::end_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_iterator AVL_tree<tkey, tvalue>::cbegin_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_const_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_iterator AVL_tree<tkey, tvalue>::cend_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_const_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator AVL_tree<tkey, tvalue>::rbegin_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_reverse_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator AVL_tree<tkey, tvalue>::rend_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator AVL_tree<tkey, tvalue>::crbegin_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator AVL_tree<tkey, tvalue>::crend_prefix() const noexcept
{
    return AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_iterator AVL_tree<tkey, tvalue>::begin_infix() const noexcept
{
    return AVL_tree<tkey, tvalue>::infix_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_iterator AVL_tree<tkey, tvalue>::end_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_iterator AVL_tree<tkey, tvalue>::cbegin_infix() const noexcept
{
    return AVL_tree<tkey, tvalue>::infix_const_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_iterator AVL_tree<tkey, tvalue>::cend_infix() const noexcept
{
    return AVL_tree<tkey, tvalue>::infix_const_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_reverse_iterator AVL_tree<tkey, tvalue>::rbegin_infix() const noexcept
{
    return AVL_tree<tkey, tvalue>::infix_reverse_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_reverse_iterator AVL_tree<tkey, tvalue>::rend_infix() const noexcept
{
    return AVL_tree<tkey, tvalue>::infix_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator AVL_tree<tkey, tvalue>::crbegin_infix() const noexcept
{
    return AVL_tree<tkey, tvalue>::infix_const_reverse_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator AVL_tree<tkey, tvalue>::crend_infix() const noexcept
{
    return AVL_tree<tkey, tvalue>::infix_const_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_iterator AVL_tree<tkey, tvalue>::begin_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_iterator AVL_tree<tkey, tvalue>::end_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_iterator AVL_tree<tkey, tvalue>::cbegin_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_const_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_iterator AVL_tree<tkey, tvalue>::cend_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_const_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator AVL_tree<tkey, tvalue>::rbegin_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_reverse_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator AVL_tree<tkey, tvalue>::rend_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator AVL_tree<tkey, tvalue>::crbegin_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator(dynamic_cast<typename AVL_tree<tkey, tvalue>::node *>(this->_root));
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator AVL_tree<tkey, tvalue>::crend_postfix() const noexcept
{
    return AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator(nullptr);
}


#pragma endregion iterators request implementation

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_AVL_TREE_H