#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H

#include <list>
#include <stack>
#include <vector>
#include <logger.h>
#include <logger_guardant.h>
#include <allocator.h>
#include <allocator_guardant.h>
#include <not_implemented.h>
#include <search_tree.h>
template<
    typename tkey,
    typename tvalue>
class binary_search_tree:
    public search_tree<tkey, tvalue>
{
    friend class insertion_template_method;
    friend class obtaining_template_method;
    friend class disposal_template_method;

protected:
    
    struct node
    {
    
    public:
        
        tkey _key;
        
        tvalue _value;
        
        node *left_subtree;
        
        node *right_subtree;
    
    public:
        
        explicit node(
            tkey const &key,
            tvalue const &value);
        
        explicit node(
            tkey const &key,
            tvalue &&value);

        virtual ~node() noexcept = default;
        
    };

public:

    #pragma region iterators definition

    struct iterator_data
    {
    
    public:
        
        unsigned int depth;
        
        tkey const &key;
        
        tvalue &value;
    
    public:
    
        explicit iterator_data(
            unsigned int depth,
            tkey const &key,
            tvalue const &value);

        explicit iterator_data(node *, size_t);

        virtual ~iterator_data() noexcept = default;
        
    };

    struct iterator_const_data
    {

    public:

        unsigned int depth;

        tkey const &key;

        tvalue const &value;

    public:

        explicit iterator_const_data(
            unsigned int depth,
            tkey const &key,
            tvalue const &value);

        explicit iterator_const_data(node *, size_t);

        virtual ~iterator_const_data() noexcept = default;

    };
    
    class prefix_iterator final
    {
        std::stack<std::pair<std::pair<bool, bool>, std::pair<node *, iterator_data>>> pathToNode;
    public:
        
        explicit prefix_iterator(
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
            typename binary_search_tree<tkey, tvalue>::node *subtree_root);
    
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
    
    #pragma endregion iterators definition

protected:

    #pragma region target operations strategies definition
    
    enum class insertion_of_existent_key_attempt_strategy
    {
        update_value,
        throw_an_exception
    };
    
    enum class disposal_of_nonexistent_key_attempt_strategy
    {
        do_nothing,
        throw_an_exception
    };
    
    #pragma endregion target operations strategies definition
    
    #pragma region target operations associated exception types

    class insertion_of_existent_key_attempt_exception final:
        public std::logic_error
    {

    private:

        tkey _key;

    public:

        explicit insertion_of_existent_key_attempt_exception(
            tkey const &key);

    public:

        tkey const &get_key() const noexcept;

    };

    class obtaining_of_nonexistent_key_attempt_exception final:
        public std::logic_error
    {

    private:

        tkey _key;

    public:

        explicit obtaining_of_nonexistent_key_attempt_exception(
            tkey const &key);

    public:

        tkey const &get_key() const noexcept;

    };

    class disposal_of_nonexistent_key_attempt_exception final:
        public std::logic_error
    {

    private:

        tkey _key;

    public:

        explicit disposal_of_nonexistent_key_attempt_exception(
            tkey const &key);

    public:

        tkey const &get_key() const noexcept;

    };

    #pragma endregion target operations associated exception types

    #pragma region template methods definition

    class template_method_basics:
        public logger_guardant
    {

    public:

        binary_search_tree<tkey, tvalue> *_tree;

    public:

        explicit template_method_basics(
            binary_search_tree<tkey, tvalue> *tree);

    protected:

        std::stack<node **> searchPath(tkey const &) const;
        // TODO: think about it!

    protected:

        [[nodiscard]] logger *get_logger() const noexcept final;

    };

    class insertion_template_method:
        public template_method_basics,
        public allocator_guardant
    {

    public:

        binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy _strategy;

    public:

        explicit insertion_template_method(
            binary_search_tree<tkey, tvalue> *tree,
            typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy);

    public:

        void insert(
            tkey const &key,
            tvalue &&value);

        void set_insertion_strategy(
            typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy) noexcept;

    protected:
        virtual inline size_t getSizeOfNode() const;

        virtual void balance(std::stack<node **> &);

        virtual void construct_node(node *at, tkey const &key, tvalue &&value) const noexcept;
        // TODO: think about it!

    private:

        [[nodiscard]] allocator *get_allocator() const noexcept final;

    };

    class obtaining_template_method:
        public template_method_basics
    {

    public:

        explicit obtaining_template_method(
            binary_search_tree<tkey, tvalue> *tree);

    public:

        tvalue const &obtain(
            tkey const &key);

    protected:
        virtual void balance(std::stack<node **> &);
        // TODO: think about it!

    };

    class disposal_template_method:
        public template_method_basics,
        public allocator_guardant
    {

    public:

        binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy _strategy;

    public:

        explicit disposal_template_method(
            binary_search_tree<tkey, tvalue> *tree,
            typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy);

    public:

        virtual tvalue dispose(
            tkey const &key);

        void set_disposal_strategy(
            typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) noexcept;

    protected:
        static void swapNode(node *, node *) noexcept;
        virtual void balance(std::stack<node **> &);
        // TODO: think about it!

    private:

        [[nodiscard]] allocator *get_allocator() const noexcept final;

    };

    #pragma endregion template methods definition

protected:

    node *_root;

    insertion_template_method *_insertion_template;

    obtaining_template_method *_obtaining_template;

    disposal_template_method *_disposal_template;

protected:

    explicit binary_search_tree(
        typename binary_search_tree<tkey, tvalue>::insertion_template_method *insertion_template,
        typename binary_search_tree<tkey, tvalue>::obtaining_template_method *obtaining_template,
        typename binary_search_tree<tkey, tvalue>::disposal_template_method *disposal_template,
        std::function<int(tkey const &, tkey const &)>,
        allocator *allocator,
        logger *logger);

public:

    explicit binary_search_tree(
        std::function<int(tkey const &, tkey const &)> comparer  = [](tkey const &a, tkey const &b){return a - b;},
        allocator *allocator = nullptr,
        logger *logger = nullptr,
        typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy = binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy::throw_an_exception,
        typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy = binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy::throw_an_exception);

public:

    binary_search_tree(
        binary_search_tree<tkey, tvalue> const &other);

    binary_search_tree(
        binary_search_tree<tkey, tvalue> &&other) noexcept;

    binary_search_tree<tkey, tvalue> &operator=(
        binary_search_tree<tkey, tvalue> const &other);

    binary_search_tree<tkey, tvalue> &operator=(
        binary_search_tree<tkey, tvalue> &&other) noexcept;

    ~binary_search_tree() override;

public:

    void insert(
        tkey const &key,
        tvalue &value) final;

    void insert(
        tkey const &key,
        tvalue &&value) final;

    tvalue const &obtain(
        tkey const &key) final;

    std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
        tkey const &lower_bound,
        tkey const &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive) final;

    tvalue dispose(
        tkey const &key) final;

public:

    void set_insertion_strategy(
        typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy) noexcept;

    void set_removal_strategy(
        typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) noexcept;

public:

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

    #pragma endregion iterators requests definition

public:

    #pragma region subtree rotations definition

    void small_left_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root,
        bool validate = true) const;

    void small_right_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root,
        bool validate = true) const;

    void big_left_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root,
        bool validate = true) const;

    void big_right_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root,
        bool validate = true) const;

    void double_left_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root,
        bool at_grandparent_first,
        bool validate = true) const;

    void double_right_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root,
        bool at_grandparent_first,
        bool validate = true) const;

    #pragma endregion subtree rotations definition

    #pragma region myMethods definition!!!
    void destroyTree();

    void destroyNodes(node *);

    void privatePrint(std::ostream &, node *, size_t) const;

    void copyTree(binary_search_tree<tkey, tvalue> const &);

    virtual void copyNode(node *, node *&);
public:
    void printTree(std::ostream &) const;
    #pragma endregion myMethods definition!!!

};

#pragma region binary_search_tree<tkey, tvalue>::node methods implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::node::node(
    tkey const &key,
    tvalue const &value) :
    _key(key),
    _value(value),
    left_subtree(nullptr),
    right_subtree(nullptr)

{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::node::node(tkey const &, tvalue const &)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::node::node(
    tkey const &key,
    tvalue &&value) :
    _key(key),
    _value(std::forward<tvalue &&>(value)),
    left_subtree(nullptr),
    right_subtree(nullptr)
{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::node::node(tkey const &, tvalue &&)", "your code should be here...");
}

#pragma endregion binary_search_tree<tkey, tvalue>::node methods implementation

#pragma region iterators implementation

#pragma region iterator data implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::iterator_data::iterator_data(
    unsigned int depth,
    tkey const &key,
    tvalue const &value):
    depth(depth),
    key(const_cast<tkey &>(key)),
    value(const_cast<tvalue &>(value))
{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::iterator_data::iterator_data(unsigned int, tkey const &, tvalue const &)", "your code should be here...");
}

template<typename tkey, typename tvalue>
binary_search_tree<tkey, tvalue>::iterator_data::iterator_data(node *node, size_t d) :
iterator_data(d, node->_key, node->_value)
{}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::iterator_const_data::iterator_const_data(
unsigned int depth,
tkey const &key,
tvalue const &value):
depth(depth),
key(key),
value(value){}

template<typename tkey, typename tvalue>
binary_search_tree<tkey, tvalue>::iterator_const_data::iterator_const_data(node *node, size_t d) :
iterator_const_data(d, node->_key, node->_value)
{}

#pragma endregion iterator data implementation

#pragma region prefix_iterator implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root) :
    pathToNode()
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(subtree_root, iterator_data(subtree_root, 0)));
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator &binary_search_tree<tkey, tvalue>::prefix_iterator::operator++()
{
    //if(pathToNode.empty()) return *this;
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(top.second.first->left_subtree, iterator_data(top.second.first->left_subtree, top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(top.second.first->right_subtree, iterator_data(top.second.first->right_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::prefix_iterator const binary_search_tree<tkey, tvalue>::prefix_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::prefix_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::prefix_const_iterator::prefix_const_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root):
    pathToNode()
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(subtree_root, iterator_const_data(subtree_root, 0)));
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_const_iterator &binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator++()
{
    //if(pathToNode.empty()) return *this;
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(top.second.first->left_subtree, iterator_const_data(top.second.first->left_subtree, top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(top.second.first->right_subtree, iterator_const_data(top.second.first->right_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::prefix_const_iterator const binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_const_data const *binary_search_tree<tkey, tvalue>::prefix_const_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::prefix_reverse_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(subtree_root, iterator_data(subtree_root, 0)));
    // not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::prefix_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator &binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(top.second.first->right_subtree, iterator_data(top.second.first->right_subtree, top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_data>(top.second.first->left_subtree, iterator_data(top.second.first->left_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator const binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(subtree_root, iterator_const_data(subtree_root, 0)));
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator &binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first.second /*Мы не были справа*/) {
            top.first.second = true;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(top.second.first->right_subtree, iterator_const_data(top.second.first->right_subtree, top.second.second.depth + 1)));
                break;
                //return *this;
            }
        }
        if(!top.first.first /*Мы не были слева*/) {
            top.first.first = true;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(std::pair<bool, bool>(false, false), std::pair<node *, iterator_const_data>(top.second.first->left_subtree, iterator_const_data(top.second.first->left_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator const binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_const_data const *binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::infix_iterator::infix_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
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
bool binary_search_tree<tkey, tvalue>::infix_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::infix_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::infix_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::infix_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_iterator &binary_search_tree<tkey, tvalue>::infix_iterator::operator++()
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
typename binary_search_tree<tkey, tvalue>::infix_iterator const binary_search_tree<tkey, tvalue>::infix_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::infix_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::infix_const_iterator::infix_const_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    node *pNow = subtree_root;
    size_t death = 0;
    while(pNow != nullptr){
        pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
        pNow = pNow->left_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::infix_const_iterator::infix_const_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::infix_const_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::infix_const_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::infix_const_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::infix_const_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_const_iterator &binary_search_tree<tkey, tvalue>::infix_const_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->left_subtree, iterator_const_data(top.second.first->left_subtree, top.second.second.depth + 1)));
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
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->right_subtree, iterator_const_data(top.second.first->right_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::infix_const_iterator const binary_search_tree<tkey, tvalue>::infix_const_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_const_data const *binary_search_tree<tkey, tvalue>::infix_const_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::infix_reverse_iterator::infix_reverse_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(pNow != nullptr) {
        pathToNode.emplace(1, std::pair<node *, iterator_data>(pNow, iterator_data(pNow, death++)));
        pNow = pNow->right_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::infix_reverse_iterator::infix_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator &binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(top.second.first->right_subtree, iterator_data(top.second.first->right_subtree, top.second.second.depth + 1)));
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
                pathToNode.emplace(0, std::pair<node *, iterator_data>(top.second.first->left_subtree, iterator_data(top.second.first->left_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator const binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_data *binary_search_tree<tkey, tvalue>::infix_reverse_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::infix_const_reverse_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(pNow != nullptr) {
        pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
        pNow = pNow->right_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::infix_const_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator &binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->right_subtree, iterator_const_data(top.second.first->right_subtree, top.second.second.depth + 1)));
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
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->left_subtree, iterator_const_data(top.second.first->left_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator const binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_const_data const *binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::postfix_iterator::postfix_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_data>(pNow, iterator_data(pNow, death++)));
            if(pNow->left_subtree == nullptr) break;
            pNow = pNow->left_subtree;
        }
        ++pathToNode.top().first;
        if(pNow->right_subtree == nullptr) break;
        pNow = pNow->right_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_iterator::postfix_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::postfix_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::postfix_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_iterator &binary_search_tree<tkey, tvalue>::postfix_iterator::operator++()
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
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(top.second.first->right_subtree, iterator_data(top.second.first->right_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::postfix_iterator const binary_search_tree<tkey, tvalue>::postfix_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::postfix_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::postfix_const_iterator::postfix_const_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
            if(pNow->left_subtree == nullptr) break;
            pNow = pNow->left_subtree;
        }
        ++pathToNode.top().first;
        if(pNow->right_subtree == nullptr) break;
        pNow = pNow->right_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_const_iterator::postfix_const_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_const_iterator &binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->left_subtree, iterator_const_data(top.second.first->left_subtree, top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->right_subtree, iterator_const_data(top.second.first->right_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::postfix_const_iterator const binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_const_data const *binary_search_tree<tkey, tvalue>::postfix_const_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::postfix_reverse_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_data>(pNow, iterator_data(pNow, death++)));
            if(pNow->right_subtree == nullptr) break;
            pNow = pNow->right_subtree;
        }
        ++pathToNode.top().first;
        if(pNow->left_subtree == nullptr) break;
        pNow = pNow->left_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::postfix_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator &binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(top.second.first->right_subtree, iterator_data(top.second.first->right_subtree, top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_data>(top.second.first->left_subtree, iterator_data(top.second.first->left_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator const binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::operator*() const
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
binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(
    typename binary_search_tree<tkey, tvalue>::node *subtree_root)
{
    if(subtree_root == nullptr) return;
    auto pNow = subtree_root;
    size_t death = 0;
    while(true) {
        while(pNow != nullptr) {
            pathToNode.emplace(1, std::pair<node *, iterator_const_data>(pNow, iterator_const_data(pNow, death++)));
            if(pNow->right_subtree == nullptr) break;
            pNow = pNow->right_subtree;
        }
        ++pathToNode.top().first;
        if(pNow->left_subtree == nullptr) break;
        pNow = pNow->left_subtree;
    }
    ++pathToNode.top().first;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(typename binary_search_tree<tkey, tvalue>::node *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const &other) const noexcept
{
    if(pathToNode.empty() && other.pathToNode.empty()) return true;
    if(pathToNode.size() != other.pathToNode.size()) return false;
    return pathToNode.top().second.first == other.pathToNode.top().second.first;
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator==(typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const &other) const noexcept
{
    return !(*this == other);
    //throw not_implemented("template<typename tkey, typename tvalue> bool binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator!=(typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator &binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator++()
{
    while(!pathToNode.empty()) {
        auto &top = pathToNode.top();
        if(!top.first) {
            ++top.first;
            if(top.second.first->right_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->right_subtree, iterator_const_data(top.second.first->right_subtree, top.second.second.depth + 1)));
            }
            continue;
        }
        if(top.first == 1) {
            ++top.first;
            if(top.second.first->left_subtree != nullptr) {
                pathToNode.emplace(0, std::pair<node *, iterator_const_data>(top.second.first->left_subtree, iterator_const_data(top.second.first->left_subtree, top.second.second.depth + 1)));
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
typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator const binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator++(
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
typename binary_search_tree<tkey, tvalue>::iterator_const_data const *binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator*() const
{
    if(pathToNode.empty()) throw std::logic_error("Iterator is empty");
    return &(pathToNode.top().second.second);
    //throw not_implemented("template<typename tkey, typename tvalue> typename binary_search_tree<tkey, tvalue>::iterator_data const *binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::operator*() const", "your code should be here...");
}

#pragma endregion postfix_const_reverse_iterator implementation

#pragma endregion iterators implementation

#pragma region target operations associated exception types implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_exception::insertion_of_existent_key_attempt_exception(
    tkey const &key):
    std::logic_error("Attempt to insert already existing key inside the tree.")
{

}

template<
    typename tkey,
    typename tvalue>
tkey const &binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_exception::get_key() const noexcept
{
    return _key;
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::obtaining_of_nonexistent_key_attempt_exception::obtaining_of_nonexistent_key_attempt_exception(
    tkey const &key):
    std::logic_error("Attempt to obtain a value by non-existing key from the tree.")
{

}

template<
    typename tkey,
    typename tvalue>
tkey const &binary_search_tree<tkey, tvalue>::obtaining_of_nonexistent_key_attempt_exception::get_key() const noexcept
{
    return _key;
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_exception::disposal_of_nonexistent_key_attempt_exception(
    tkey const &key):
    std::logic_error("Attempt to dispose a value by non-existing key from the tree.")
{

}

template<
    typename tkey,
    typename tvalue>
tkey const &binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_exception::get_key() const noexcept
{
    return _key;
}

#pragma endregion target operations associated exception types implementation

#pragma region template methods implementation

#pragma region binary_search_tree<tkey, tvalue>::template_method_basics implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::template_method_basics::template_method_basics(
    binary_search_tree<tkey, tvalue> *tree) :
    _tree(tree)
{
    //throw not_implemented("template<typename tkey, typename tvalue>binary_search_tree<tkey, tvalue>::insertion_template_method::insertion_template_method(binary_search_tree<tkey, tvalue> *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
[[nodiscard]] inline logger *binary_search_tree<tkey, tvalue>::template_method_basics::get_logger() const noexcept
{
    return _tree->get_logger();
    //throw not_implemented("template<typename tkey, typename tvalue> [[nodiscard]] inline logger *binary_search_tree<tkey, tvalue>::template_method_basics::get_logger() const noexcept", "your code should be here...");
}

#pragma endregion binary_search_tree<tkey, tvalue>::template_method_basics implementation

#pragma region search_tree<tkey, tvalue>::insertion_template_method implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::insertion_template_method::insertion_template_method(
    binary_search_tree<tkey, tvalue> *tree,
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy):
    binary_search_tree<tkey, tvalue>::template_method_basics::template_method_basics(tree),
    _strategy(insertion_strategy)
{
    //throw not_implemented("template<typename tkey, typename tvalue>binary_search_tree<tkey, tvalue>::insertion_template_method::insertion_template_method(binary_search_tree<tkey, tvalue> *, typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::insertion_template_method::insert(
    tkey const &key,
    tvalue &&value)
{
    auto pathToNode = template_method_basics::searchPath(key);
    auto &targetNode = pathToNode.top();
    if(*targetNode != nullptr) {
        if(_strategy == insertion_of_existent_key_attempt_strategy::throw_an_exception) throw insertion_of_existent_key_attempt_exception(key);
        (*targetNode) ->_value = std::forward<tvalue>(value);
        return;
    }
    node *newNode = reinterpret_cast<node *>(allocate_with_guard(getSizeOfNode()));
    construct_node(newNode, key, std::forward<tvalue>(value));
    *targetNode = newNode;
    this->balance(pathToNode);
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::insertion_template_method::insert(tkey const &, tvalue &&)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::insertion_template_method::set_insertion_strategy(
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy) noexcept
{
    _strategy = insertion_strategy;
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::insertion_template_method::set_insertion_strategy(typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
allocator *binary_search_tree<tkey, tvalue>::insertion_template_method::get_allocator() const noexcept
{
    return binary_search_tree<tkey, tvalue>::template_method_basics::_tree->get_allocator();
    //throw not_implemented("template<typename tkey, typename tvalue> allocator *binary_search_tree<tkey, tvalue>::insertion_template_method::get_allocator() const noexcept", "your code should be here...");
}

#pragma endregion search_tree<tkey, tvalue>::insertion_template_method implementation

#pragma region search_tree<tkey, tvalue>::obtaining_template_method implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::obtaining_template_method::obtaining_template_method(
    binary_search_tree<tkey, tvalue> *tree):
    binary_search_tree<tkey, tvalue>::template_method_basics::template_method_basics(tree)
{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::obtaining_template_method::obtaining_template_method(binary_search_tree<tkey, tvalue> *tree)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
tvalue const &binary_search_tree<tkey, tvalue>::obtaining_template_method::obtain(
    tkey const &key)
{
    if(this->_tree->_root == nullptr) throw std::logic_error("Tree is empty");
    auto pathToNode = template_method_basics::searchPath(key);
    auto *node = *pathToNode.top();
    if(node == nullptr) throw std::logic_error("Obtain error");
    this->balance(pathToNode);
    return node->_value;
    //throw not_implemented("template<typename tkey, typename tvalue> tvalue const &binary_search_tree<tkey, tvalue>::obtaining_template_method::obtain(tkey const &)", "your code should be here...");
}

#pragma endregion search_tree<tkey, tvalue>::obtaining_template_method implementation

#pragma region search_tree<tkey, tvalue>::disposal_template_method implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::disposal_template_method::disposal_template_method(
    binary_search_tree<tkey, tvalue> *tree,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy):
    binary_search_tree<tkey, tvalue>::template_method_basics(tree),
    _strategy(disposal_strategy)
{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::disposal_template_method::disposal_template_method(binary_search_tree<tkey, tvalue> *, typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
tvalue binary_search_tree<tkey, tvalue>::disposal_template_method::dispose(
    tkey const &key)
{
    auto pathToNode = this->searchPath(key);
    auto targetNode = pathToNode.top();
    if(*targetNode == nullptr) throw disposal_of_nonexistent_key_attempt_exception(key);
    if((*targetNode)->left_subtree != nullptr && (*targetNode)->right_subtree != nullptr) {
        //Начинаем поиск максимума слева
        auto pNow = &((*targetNode)->left_subtree);
        while(*pNow != nullptr) {
            pathToNode.push(pNow);
            pNow = &((*pNow)->right_subtree);
        }
        swapNode(*targetNode, *pathToNode.top());
        targetNode = pathToNode.top();
    }
    tvalue result = std::move((*targetNode)->_value);
    if((*targetNode)->left_subtree == nullptr && (*targetNode)->right_subtree == nullptr) {
        (*targetNode)->~node();
        deallocate_with_guard(*targetNode);
        *targetNode = nullptr;
    }
    else if(
        ((*targetNode)->left_subtree == nullptr && (*targetNode)->right_subtree != nullptr) ^
        ((*targetNode)->left_subtree != nullptr && (*targetNode)->right_subtree == nullptr)
        ) {
        auto newNode = ((*targetNode)->left_subtree != nullptr ? (*targetNode)->left_subtree : (*targetNode)->right_subtree);
        (*targetNode)->~node();
        deallocate_with_guard(*targetNode);
        *targetNode = newNode;
    }
    this->balance(pathToNode);
    return result;
    //throw not_implemented("template<typename tkey, typename tvalue> tvalue binary_search_tree<tkey, tvalue>::disposal_template_method::dispose(tkey const &)", "your code should be here...");
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::disposal_template_method::swapNode(node *f, node *s) noexcept {
    std::swap(f->_key, s->_key);
    std::swap(f->_value, s->_value);
}


template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::disposal_template_method::set_disposal_strategy(
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) noexcept
{
    _strategy = disposal_strategy;
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::disposal_template_method::set_disposal_strategy(typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
[[nodiscard]] inline allocator *binary_search_tree<tkey, tvalue>::disposal_template_method::get_allocator() const noexcept
{
    return template_method_basics::_tree->get_allocator();
    //throw not_implemented("template<typename tkey, typename tvalue> [[nodiscard]] inline allocator *binary_search_tree<tkey, tvalue>::disposal_template_method::get_allocator() const noexcept", "your code should be here...");
}

#pragma endregion search_tree<tkey, tvalue>::disposal_template_method implementation

#pragma endregion template methods

#pragma region construction, assignment, destruction implementation

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::binary_search_tree(
    typename binary_search_tree<tkey, tvalue>::insertion_template_method *insertion_template,
    typename binary_search_tree<tkey, tvalue>::obtaining_template_method *obtaining_template,
    typename binary_search_tree<tkey, tvalue>::disposal_template_method *disposal_template,
    std::function<int(tkey const &, tkey const &)> comparer,
    allocator *allocator,
    logger *logger):
    search_tree<tkey, tvalue>(comparer, logger, allocator),
    _insertion_template(insertion_template),
    _obtaining_template(obtaining_template),
    _disposal_template(disposal_template),
    _root(nullptr)
{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::binary_search_tree(typename binary_search_tree<tkey, tvalue>::insertion_template_method *, typename binary_search_tree<tkey, tvalue>::obtaining_template_method *, typename binary_search_tree<tkey, tvalue>::disposal_template_method *, std::function<int(tkey const &, tkey const &)>, allocator *, logger *)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::binary_search_tree(
    std::function<int(tkey const &, tkey const &)> keys_comparer,
    allocator *allocator,
    logger *logger,
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy):
    binary_search_tree(
        new binary_search_tree<tkey, tvalue>::insertion_template_method(this, insertion_strategy),
        new binary_search_tree<tkey, tvalue>::obtaining_template_method(this),
        new binary_search_tree<tkey, tvalue>::disposal_template_method(this, disposal_strategy),
        keys_comparer,
        allocator,
        logger)
{
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::binary_search_tree(std::function<int(tkey const &, tkey const &)>, allocator *, logger *, typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy, typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::binary_search_tree (
    binary_search_tree<tkey, tvalue> const &other) :
    search_tree<tkey, tvalue>(other._keys_comparer, other.get_logger(), other.get_allocator()),
    _root(nullptr),
    _disposal_template(nullptr),
    _insertion_template(nullptr),
    _obtaining_template(nullptr)
{
    copyTree(other);
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::binary_search_tree(binary_search_tree<tkey, tvalue> const &)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::binary_search_tree(
    binary_search_tree<tkey, tvalue> &&other) noexcept :
    search_tree<tkey, tvalue>(other._keys_comparer, other.get_logger(), other.get_allocator()),
    _root(other._root),
    _obtaining_template(other._obtaining_template),
    _disposal_template(other._disposal_template),
    _insertion_template(other._insertion_template)
{
    other._root = nullptr;
    other._insertion_template = nullptr;
    other._obtaining_template = nullptr;
    other._disposal_template = nullptr;
    other._allocator = nullptr;
    other._logger = nullptr;
    _insertion_template->_tree = this;
    _obtaining_template->_tree = this;
    _disposal_template->_tree = this;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::binary_search_tree(binary_search_tree<tkey, tvalue> &&) noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue> &binary_search_tree<tkey, tvalue>::operator=(
    binary_search_tree<tkey, tvalue> const &other)
{
    if(this != &other) {
        destroyTree();
        copyTree(other);
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue> &binary_search_tree<tkey, tvalue>::operator=(binary_search_tree<tkey, tvalue> const &)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue> &binary_search_tree<tkey, tvalue>::operator=(
    binary_search_tree<tkey, tvalue> &&other) noexcept
{
    if(this != &other) {
        destroyTree();
        this->_root = other._root;
        other._root = nullptr;
        this->_insertion_template = other._insertion_template;
        other._insertion_template = nullptr;
        this->_obtaining_template = other._obtaining_template;
        other._obtaining_template = nullptr;
        this->_disposal_template = other._disposal_template;
        other._disposal_template = nullptr;
        this->_keys_comparer = other._keys_comparer;
        this->_allocator = other._allocator;
        other._allocator = nullptr;
        this->_logger = other._logger;
        other._logger = nullptr;
        _insertion_template->_tree = this;
        _obtaining_template->_tree = this;
        _disposal_template->_tree = this;
    }
    return *this;
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue> &binary_search_tree<tkey, tvalue>::operator=(binary_search_tree<tkey, tvalue> &&) noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::~binary_search_tree()
{
    destroyTree();
    //throw not_implemented("template<typename tkey, typename tvalue> binary_search_tree<tkey, tvalue>::~binary_search_tree()", "your code should be here...");
}

#pragma endregion construction, assignment, destruction implementation

#pragma region associative_container<tkey, tvalue> contract implementation

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::insert(
    tkey const &key,
    tvalue &value)
{
    if(_insertion_template == nullptr) throw std::logic_error("BST was moved");
    _insertion_template->insert(key, std::forward<tvalue>(value));
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::insert(
    tkey const &key,
    tvalue &&value)
{
    if(_insertion_template == nullptr) throw std::logic_error("BST was moved");
    _insertion_template->insert(key, std::forward<tvalue>(value));
}

template<
    typename tkey,
    typename tvalue>
tvalue const &binary_search_tree<tkey, tvalue>::obtain(
    tkey const &key)
{
    if(_obtaining_template == nullptr) throw std::logic_error("BST was moved");
    return _obtaining_template->obtain(key);
}

template<
    typename tkey,
    typename tvalue>
std::vector<typename associative_container<tkey, tvalue>::key_value_pair> binary_search_tree<tkey, tvalue>::obtain_between(
    tkey const &lower_bound,
    tkey const &upper_bound,
    bool lower_bound_inclusive,
    bool upper_bound_inclusive)
{
    if(_obtaining_template == nullptr) throw std::logic_error("BST was moved");
    auto i = cbegin_infix();
    std::vector<typename associative_container<tkey, tvalue>::key_value_pair> result;
    while(i != cend_infix()) {
        if(this->_keys_comparer((*i)->key, lower_bound) >= 0) break;
        ++i;
    }
    if(i == cend_infix()) throw std::logic_error("Lower bound was not fount");
    if(lower_bound_inclusive) result.push_back({(*i)->key, (*i)->value});
    ++i;
    while(i != cend_infix()) {
        if(this->_keys_comparer((*i)->key, upper_bound) >= 0) break;
        result.push_back({(*i)->key, (*i)->value});
        ++i;
    }
    if(upper_bound_inclusive && i != cend_infix()) result.push_back({(*i)->key, (*i)->value});
    return result;
    //throw not_implemented("template<typename tkey, typename tvalue> std::vector<typename associative_container<tkey, tvalue>::key_value_pair> binary_search_tree<tkey, tvalue>::obtain_between(tkey const &, tkey const &, bool, bool)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
tvalue binary_search_tree<tkey, tvalue>::dispose(
    tkey const &key)
{
    if(_disposal_template == nullptr) throw std::logic_error("BST was moved");
    return _disposal_template->dispose(key);
}

#pragma endregion associative_containers contract implementations

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::set_insertion_strategy(
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy) noexcept
{
    if(_insertion_template == nullptr) throw std::logic_error("BST was moved");
    _insertion_template->set_insertion_strategy(insertion_strategy);
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::set_insertion_strategy(typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_strategy) noexcept", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::set_removal_strategy(
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) noexcept
{
    if(_disposal_template == nullptr) throw std::logic_error("BTS was moved");
    _disposal_template->set_disposal_strategy(disposal_strategy);
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::set_removal_strategy(typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_strategy) noexcept", "your code should be here...");
}

#pragma region iterators requesting implementation

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator binary_search_tree<tkey, tvalue>::begin_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator binary_search_tree<tkey, tvalue>::end_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_const_iterator binary_search_tree<tkey, tvalue>::cbegin_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_const_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_const_iterator binary_search_tree<tkey, tvalue>::cend_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_const_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator binary_search_tree<tkey, tvalue>::rbegin_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_reverse_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_reverse_iterator binary_search_tree<tkey, tvalue>::rend_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator binary_search_tree<tkey, tvalue>::crbegin_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator binary_search_tree<tkey, tvalue>::crend_prefix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_iterator binary_search_tree<tkey, tvalue>::begin_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_iterator binary_search_tree<tkey, tvalue>::end_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_const_iterator binary_search_tree<tkey, tvalue>::cbegin_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_const_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_const_iterator binary_search_tree<tkey, tvalue>::cend_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_const_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator binary_search_tree<tkey, tvalue>::rbegin_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_reverse_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_reverse_iterator binary_search_tree<tkey, tvalue>::rend_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue>::crbegin_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue>::crend_infix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_iterator binary_search_tree<tkey, tvalue>::begin_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_iterator binary_search_tree<tkey, tvalue>::end_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_const_iterator binary_search_tree<tkey, tvalue>::cbegin_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_const_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_const_iterator binary_search_tree<tkey, tvalue>::cend_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_const_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator binary_search_tree<tkey, tvalue>::rbegin_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_reverse_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_reverse_iterator binary_search_tree<tkey, tvalue>::rend_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_reverse_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator binary_search_tree<tkey, tvalue>::crbegin_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator(dynamic_cast<typename binary_search_tree<tkey, tvalue>::node *>(_root));
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator binary_search_tree<tkey, tvalue>::crend_postfix() const noexcept
{
    return binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator(nullptr);
}


#pragma endregion iterators request implementation

#pragma region subtree rotations implementation

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::small_left_rotation(
    binary_search_tree<tkey, tvalue>::node *&subtree_root,
    bool validate) const
{
    if(subtree_root == nullptr || subtree_root->right_subtree == nullptr) {
        if(validate) throw std::logic_error("Small_left_rotation error");
        return;
    }
    auto newRoot = subtree_root->right_subtree;
    subtree_root->right_subtree = newRoot->left_subtree;
    newRoot->left_subtree = subtree_root;
    subtree_root = newRoot;
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::small_left_rotation(binary_search_tree<tkey, tvalue>::node *&, bool) const", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::small_right_rotation(
    binary_search_tree<tkey, tvalue>::node *&subtree_root,
    bool validate) const
{
    if(subtree_root == nullptr || subtree_root->left_subtree == nullptr) {
        if(validate) throw std::logic_error("Small_right_rotation error");
        return;
    }
    auto newRoot = subtree_root->left_subtree;
    subtree_root->left_subtree = newRoot->right_subtree;
    newRoot->right_subtree = subtree_root;
    subtree_root = newRoot;
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::small_right_rotation(binary_search_tree<tkey, tvalue>::node *&, bool) const", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::big_left_rotation(
    binary_search_tree<tkey, tvalue>::node *&subtree_root,
    bool validate) const
{
    if(subtree_root == nullptr || subtree_root->right_subtree == nullptr || subtree_root->right_subtree->left_subtree == nullptr) {
        if(validate) throw std::logic_error("Big_left_rotation error");
        return;
    }
    small_right_rotation(subtree_root->right_subtree);
    small_left_rotation(subtree_root);
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::big_left_rotation(binary_search_tree<tkey, tvalue>::node *&, bool) const", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::big_right_rotation(
    binary_search_tree<tkey, tvalue>::node *&subtree_root,
    bool validate) const
{
    if(subtree_root == nullptr || subtree_root->left_subtree == nullptr || subtree_root->left_subtree->right_subtree == nullptr) {
        if(validate) throw std::logic_error("Big_right_rotation error");
        return;
    }
    small_left_rotation(subtree_root->left_subtree);
    small_right_rotation(subtree_root);
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::big_right_rotation(binary_search_tree<tkey, tvalue>::node *&, bool) const", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::double_left_rotation(
    binary_search_tree<tkey, tvalue>::node *&subtree_root,
    bool at_grandparent_first,
    bool validate) const
{
    if(subtree_root == nullptr || subtree_root->right_subtree == nullptr || subtree_root->right_subtree->right_subtree == nullptr) {
        if(validate) throw std::logic_error("Double_left_rotation error");
        return;
    }
    if(at_grandparent_first) {
        small_left_rotation(subtree_root);
        small_left_rotation(subtree_root);
    } else {
        small_left_rotation(subtree_root->right_subtree);
        small_left_rotation(subtree_root);
    }
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::double_left_rotation(binary_search_tree<tkey, tvalue>::node *&, bool, bool) const", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::double_right_rotation(
    binary_search_tree<tkey, tvalue>::node *&subtree_root,
    bool at_grandparent_first,
    bool validate) const
{
    if(subtree_root == nullptr || subtree_root->left_subtree == nullptr || subtree_root->left_subtree->left_subtree == nullptr) {
        if(validate) throw std::logic_error("Double_right_rotation error");
        return;
    }
    if(at_grandparent_first) {
        small_right_rotation(subtree_root);
        small_right_rotation(subtree_root);
    } else {
        small_right_rotation(subtree_root->left_subtree);
        small_right_rotation(subtree_root);
    }
    //throw not_implemented("template<typename tkey, typename tvalue> void binary_search_tree<tkey, tvalue>::double_right_rotation(binary_search_tree<tkey, tvalue>::node *&, bool, bool) const", "your code should be here...");
}

#pragma endregion subtree rotations implementation

#pragma region myMethods implementation!!!

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::destroyTree() {
    delete _disposal_template;
    _disposal_template = nullptr;
    delete _insertion_template;
    _insertion_template = nullptr;
    delete _obtaining_template;
    _obtaining_template = nullptr;
    destroyNodes(_root);
    _root = nullptr;
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::destroyNodes(node *lRoot) {
    if(lRoot == nullptr) return;
    destroyNodes(lRoot->left_subtree);
    destroyNodes(lRoot->right_subtree);
    this->deallocate_with_guard(lRoot);
}

template<typename tkey, typename tvalue>
std::stack<typename binary_search_tree<tkey, tvalue>::node **> binary_search_tree<tkey, tvalue>::template_method_basics::searchPath(tkey const &key) const {
    std::stack<typename binary_search_tree<tkey, tvalue>::node **> resultStack;
    node **pNow = &_tree->_root;
    while(*pNow != nullptr) {
        resultStack.push(pNow);
        auto compareResult = _tree->_keys_comparer((*pNow)->_key, key);
        if(!compareResult) return resultStack;
        pNow = &(compareResult > 0 ? (*pNow)->left_subtree : (*pNow)->right_subtree);
    }
    resultStack.push(pNow);
    return resultStack;
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::insertion_template_method::balance(std::stack<node **> &) {
    this->trace_with_guard("Баланса не будет");
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::disposal_template_method::balance(std::stack<node **> &) {
    this->trace_with_guard("Баланса не будет");
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::obtaining_template_method::balance(std::stack<node **> &) {
    this->trace_with_guard("Баланса не будет");
}

template<typename tkey, typename tvalue>
size_t binary_search_tree<tkey, tvalue>::insertion_template_method::getSizeOfNode() const {
    return sizeof(typename binary_search_tree<tkey, tvalue>::node);
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::privatePrint(std::ostream &str, node *n, size_t death) const {
    if(n == nullptr) return;
    privatePrint(str, n->left_subtree, death + 1);
    str << n->_value << '(' << death << ')' << ' ';
    privatePrint(str, n->right_subtree, death + 1);
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::printTree(std::ostream &str) const {
    if(_root == nullptr) {
        str << "Tree is empty" << std::endl;
        return;
    }
    privatePrint(str, _root, 0);
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::copyTree(binary_search_tree<tkey, tvalue> const &other) {
    this->_logger = other._logger;
    this->_allocator = other._allocator;
    this->_keys_comparer = other._keys_comparer;
    this->_insertion_template = new insertion_template_method(this, other._insertion_template->_strategy);
    this->_obtaining_template = new obtaining_template_method(this);
    this->_disposal_template = new disposal_template_method(this, other._disposal_template->_strategy);
    this->copyNode(other._root, _root);
}

template<typename tkey, typename tvalue>
void binary_search_tree<tkey, tvalue>::copyNode(node *node, class node *&dest) {
    if(node == nullptr) return;
    dest = reinterpret_cast<class node *>(this->allocate_with_guard(sizeof(class node)));
    new (dest) class node(node->_key, node->_value);
    copyNode(node->left_subtree, dest->left_subtree);
    copyNode(node->right_subtree, dest->right_subtree);
}

template<
    typename tkey,
    typename tvalue>
inline void binary_search_tree<tkey, tvalue>::insertion_template_method::construct_node(
    typename binary_search_tree<tkey, tvalue>::node *at,
    tkey const &key,
    tvalue &&value) const noexcept
{
    allocator::construct(at, key, std::forward<tvalue &&>(value));
}
#pragma endregion myMethods implementation!!!


#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H