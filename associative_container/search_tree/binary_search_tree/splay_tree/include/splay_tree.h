#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_SPLAY_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_SPLAY_TREE_H

#include <binary_search_tree.h>

template<
    typename tkey,
    typename tvalue>
class splay_tree final:
    public binary_search_tree<tkey, tvalue>
{
private:

    class splayer {
        splay_tree<tkey, tvalue> *tree;
    protected:
        explicit splayer(splay_tree<tkey, tvalue> *);
        void splay(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &) const;

        virtual ~splayer() noexcept = default;
    };
    
    class insertion_template_method final:
        public binary_search_tree<tkey, tvalue>::insertion_template_method,
        public splayer
    {
    
    public:
        
        explicit insertion_template_method(
            splay_tree<tkey, tvalue> *tree,
            typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy);
    
    private:
        void balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &) override;
        // TODO: think about it!
        
    };
    
    class obtaining_template_method final:
        public binary_search_tree<tkey, tvalue>::obtaining_template_method,
        public splayer
    {
    
    public:
        
        explicit obtaining_template_method(
            splay_tree<tkey, tvalue> *tree);

        void balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &) override;
        // TODO: think about it!
        
    };
    
    class disposal_template_method final:
        public binary_search_tree<tkey, tvalue>::disposal_template_method,
        public splayer
    {
    
    public:
        
        explicit disposal_template_method(
            splay_tree<tkey, tvalue> *tree,
            typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy);
        
        // TODO: think about it!
        tvalue dispose(
            tkey const &key) override;

        std::pair<typename binary_search_tree<tkey, tvalue>::node **, typename binary_search_tree<tkey, tvalue>::node *>
            separate(typename binary_search_tree<tkey, tvalue>::node **) noexcept;

        void merge(std::pair<typename binary_search_tree<tkey, tvalue>::node **, typename binary_search_tree<tkey, tvalue>::node *> &);

        void balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &) override;
        
    };

public:
    
    explicit splay_tree(
    allocator *allocator = nullptr,
    logger *logger = nullptr,
    std::function<int(tkey const &, tkey const &)> comparer = [](tkey const &a, tkey const &b) {
        if(a < b) return -1;
        if(a == b) return 0;
        return 1;
    },
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy = binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy::throw_an_exception,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy = binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy::throw_an_exception);

public:
    
    ~splay_tree() noexcept final;
    
    splay_tree(
        splay_tree<tkey, tvalue> const &other);
    
    splay_tree<tkey, tvalue> &operator=(
        splay_tree<tkey, tvalue> const &other);
    
    splay_tree(
        splay_tree<tkey, tvalue> &&other) noexcept;
    
    splay_tree<tkey, tvalue> &operator=(
        splay_tree<tkey, tvalue> &&other) noexcept;

    void copyNode(typename binary_search_tree<tkey, tvalue>::node *, typename binary_search_tree<tkey, tvalue>::node *&) override;
};

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::insertion_template_method::insertion_template_method(
    splay_tree<tkey, tvalue> *tree,
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy strategy) :
    binary_search_tree<tkey, tvalue>::insertion_template_method(tree, strategy),
    splayer(tree)
{
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue>::insertion_template_method::insertion_template_method(splay_tree<tkey, tvalue> *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::obtaining_template_method::obtaining_template_method(
    splay_tree<tkey, tvalue> *tree) :
    binary_search_tree<tkey, tvalue>::obtaining_template_method(tree),
    splayer(tree)
{
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue>::obtaining_template_method::obtaining_template_method(splay_tree<tkey, tvalue> *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::disposal_template_method::disposal_template_method(
    splay_tree<tkey, tvalue> *tree,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) :
    binary_search_tree<tkey, tvalue>::disposal_template_method(tree, disposal_strategy),
    splayer(tree)
{
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue>::disposal_template_method::disposal_template_method(splay_tree<tkey, tvalue> *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::splay_tree(
    allocator *allocator,
    logger *logger,
    std::function<int(tkey const &, tkey const &)> comparer,
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) :
    binary_search_tree<tkey, tvalue>(
        new splay_tree<tkey, tvalue>::insertion_template_method(this, insertion_strategy),
        new splay_tree<tkey, tvalue>::obtaining_template_method(this),
        new splay_tree<tkey, tvalue>::disposal_template_method(this, disposal_strategy),
        comparer,
        allocator,
        logger
        )
{
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue>::splay_tree(allocator *, logger *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::~splay_tree() noexcept
{
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue>::~splay_tree() noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::splay_tree(
    splay_tree<tkey, tvalue> const &other) :
    binary_search_tree<tkey, tvalue>(
        new splay_tree<tkey, tvalue>::insertion_template_method(this, other._insertion_template->_strategy),
        new splay_tree<tkey, tvalue>::obtaining_template_method(this),
        new splay_tree<tkey, tvalue>::disposal_template_method(this, other._disposal_template->_strategy),
        other._keys_comparer,
        other.get_allocator(),
        other.get_logger()
    )
{
    copyNode(other._root, this->_root);
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue>::splay_tree(splay_tree<tkey, tvalue> const &)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue> &splay_tree<tkey, tvalue>::operator=(
    splay_tree<tkey, tvalue> const &other)
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
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue> &splay_tree<tkey, tvalue>::operator=(splay_tree<tkey, tvalue> const &)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::splay_tree(
    splay_tree<tkey, tvalue> &&other) noexcept :
    binary_search_tree<tkey, tvalue>(
        new splay_tree<tkey, tvalue>::insertion_template_method(this, other._insertion_template->_strategy),
        new splay_tree<tkey, tvalue>::obtaining_template_method(this),
        new splay_tree<tkey, tvalue>::disposal_template_method(this, other._disposal_template->_strategy),
        other._keys_comparer,
        other.get_allocator(),
        other.get_logger()
    )
{
    this->_root = other._root;
    other._root = nullptr;
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue>::splay_tree(splay_tree<tkey, tvalue> &&) noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue> &splay_tree<tkey, tvalue>::operator=(
    splay_tree<tkey, tvalue> &&other) noexcept
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
    //throw not_implemented("template<typename tkey, typename tvalue> splay_tree<tkey, tvalue> &splay_tree<tkey, tvalue>::operator=(splay_tree<tkey, tvalue> &&) noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void splay_tree<tkey, tvalue>::insertion_template_method::balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &path) {
    this->splay(path);
}

template<
    typename tkey,
    typename tvalue>
void splay_tree<tkey, tvalue>::obtaining_template_method::balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &path) {
    this->splay(path);
}

template<
    typename tkey,
    typename tvalue>
void splay_tree<tkey, tvalue>::disposal_template_method::balance(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &path) {
    this->splay(path);
}

template<
    typename tkey,
    typename tvalue>
tvalue splay_tree<tkey, tvalue>::disposal_template_method::dispose(tkey const &key) {
    auto pathToNode = this->searchPath(key);
    auto &top = pathToNode.top();
    if(*top == nullptr) throw typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_exception(key);
    auto value = std::move((*top)->_value);
    this->splay(pathToNode);
    auto trees = separate(this->searchPath(key).top());
    auto child = (*trees.first)->left_subtree;
    (*trees.first)->~node();
    allocator_guardant::deallocate_with_guard(*trees.first);
    (*trees.first) = child;
    merge(trees);
    return value;
}

template<
    typename tkey,
    typename tvalue>
std::pair<typename binary_search_tree<tkey, tvalue>::node **, typename binary_search_tree<tkey, tvalue>::node *>
            splay_tree<tkey, tvalue>::disposal_template_method::separate(typename binary_search_tree<tkey, tvalue>::node **sepNode) noexcept {
    std::pair<typename binary_search_tree<tkey, tvalue>::node **, typename binary_search_tree<tkey, tvalue>::node *>
        trees;
    trees.first = sepNode;
    trees.second = (*sepNode)->right_subtree;
    (*sepNode)->right_subtree = nullptr;
    return trees;
}

template<typename tkey, typename tvalue>
void splay_tree<tkey, tvalue>::disposal_template_method::merge(std::pair<typename binary_search_tree<tkey, tvalue>::node **, typename binary_search_tree<tkey, tvalue>::node *> &trees) {
    if(*trees.first == nullptr) {
        *trees.first  = trees.second;
        return;
    }
    std::stack<typename binary_search_tree<tkey, tvalue>::node **> pathToMinNode;
    auto **pNow = trees.first;
    while(*pNow != nullptr) {
        pathToMinNode.push(pNow);
        pNow = &((*pNow)->right_subtree);
    }
    this->splay(pathToMinNode);
    (*trees.first)->right_subtree = trees.second;
}


template<
    typename tkey,
    typename tvalue>
splay_tree<tkey, tvalue>::splayer::splayer(splay_tree<tkey, tvalue> *tree) :
    tree(tree)
{}

template<typename tkey, typename tvalue>
void splay_tree<tkey, tvalue>::splayer::splay(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &path) const {
    if(path.empty()) return;
    auto **toSplay = path.top();
    path.pop();
    while(!path.empty()) {
        auto **parrent = path.top();
        path.pop();
        if(path.empty()) {
            if((*parrent)->left_subtree == *toSplay) tree->small_right_rotation(*parrent);
            if((*parrent)->right_subtree == *toSplay) tree->small_left_rotation(*parrent);
            toSplay = parrent;
            break;
        }
        auto gParrent = path.top();
        path.pop();
        if((*gParrent)->left_subtree == *parrent) {
            if((*parrent)->left_subtree == *toSplay) {
                this->tree->double_right_rotation(*gParrent, true);
            }else if((*parrent)->right_subtree == *toSplay) {
                this->tree->big_right_rotation(*gParrent);
            }
        } else if((*gParrent)->right_subtree == *parrent) {
            if((*parrent)->left_subtree == *toSplay) {
                this->tree->big_left_rotation(*gParrent);
            }else if((*parrent)->right_subtree == *toSplay) {
                this->tree->double_left_rotation(*gParrent, true);
            }
        }
        toSplay = gParrent;
    }
}

template<typename tkey, typename tvalue>
void splay_tree<tkey, tvalue>::copyNode(typename binary_search_tree<tkey, tvalue>::node *other, typename binary_search_tree<tkey, tvalue>::node *&dest) {
    if(other == nullptr) return;
    dest = reinterpret_cast<typename binary_search_tree<tkey, tvalue>::node *>(allocator_guardant::allocate_with_guard(sizeof(typename binary_search_tree<tkey, tvalue>::node)));
    new (dest) typename binary_search_tree<tkey, tvalue>::node(other->_key, other->_value);
    copyNode(other->left_subtree, dest->left_subtree);
    copyNode(other->right_subtree, dest->right_subtree);
}

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_SPLAY_TREE_H