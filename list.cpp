#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

// list实现: 双向带头循环链表
// Vector是类名，Vector<int>才是类型

/* list迭代器: ----- 封装节点指针 (拿值 -- 获取节点指针, 移动 -- 获取下一个节点的位置
迭代器++到下一位置 迭代器解引用拿到元素, 链表的元素是访问结点当中存放的值
 迭代器的解引用: 获取到节点中的值
 ++/--: 移动到下一个值的位置

 Node*(原生指针不能实现迭代器了)
 解引用: 是节点, 并不是节点的值; 
 对Node*++/--: 不知道移动到什么地方去了(位置为未知), 因为节点不是连续的

 就像走平路变成了渡河 需借助其他 重新定义迭代器 (封装节点指针 -- 自定义类 成员变量为指针)
 *iterator --> Node*->val
 ++: ++iterator --> Node*->next
 --: --iterator --> Node*->prev
 iterator begin() ----> return iterator(header->next) 返回通过header的next构造的一个迭代器
 iterator end() ----> return iterator(header) 返回通过header(最后一个元素的下一个位置)构造的一个迭代器

 Date(1,2,3) 其实1,2,3也是这个类的成员变量    可以理解为构造时通过提供成员变量来构造的对象

 需不需要深拷贝 看迭代器是否拥有资源 迭代器并不需要拷贝构造和析构和赋值运算符重载 因为迭代器的资源并不属于迭代器 
 而List需要写析构, 因为其资源(节点)是属于

 iterator:
	T& operator*(), T* operator->()
 const iterator:
	const T& operator*(), const T* operator->()
	Ref operator*(), Ptr operator->()

ListIterator<T, T&, T*>
const_ListIterator<T, const T&, const T*>
ListIterator<class T, class Ref, class Ptr>

List迭代器总结:
	1, 原生指针实现不了迭代器的工作
	2. 迭代器通过封装节点指针, 定义一个新的自定义类型, 实现迭代器
	3. 这里的每一个迭代器不是原生指针, 而是一个对象, 需要通过构造函数创建
	功能实现: 
	4. 解引用: 通过获取节点的数据完成解引用的功能  node->value
	5. 移动(++/--): 通过更新节点的指向完成, node = node->next/ node = node->prev
	6. 不等于(!=): 通过判断节点的指向是否相同完成 node != iterator.node
	7. ->操作: 通过获取数据的指针完成  &node->value
	具体实现
	8. 通过3个泛型参数区分迭代器和const_iterator迭代器
		Iterator<T, T&, T*>, Iterator<T, const T&, const T*>
	9. begin(): iterator(_header->next)
	10. end(): iterator(_header)
 */

template <class T>
struct ListNode
{
	T _value;
	ListNode<T>* _prev;
	ListNode<T>* _next;

	ListNode(const T& val = T())
		:_value(val)
		, _prev(nullptr)
		, _next(nullptr)
	{}
};

struct C
{
	int _a = 1;
	int _b = 2;
	int _c = 3;
};

//通过封装节点实现迭代器
template <class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	//封装节点
	Node* _node;

	ListIterator(Node* node)
		:_node(node)
	{}

	//*iterator: 解引用--> 获取到节点中的value
	Ref operator*()
	{
		return _node->_value;
	}

	//++iterator: 移动到下一个值的位置
	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	//iterator1 != iterator --> 指向是否相同
	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	// pc->成员
	Ptr operator->()
	{
		return &_node->_value;
	}

};

//template <class T>
//struct ConstListIterator
//{
//	typedef ListNode<T> Node;
//	typedef ConstListIterator<T> Self;
//
//	//封装节点
//	Node* _node;
//
//	ConstListIterator(Node* node)
//		:_node(node)
//	{}
//
//	//*iterator: 解引用--> 获取到节点中的value
//	const T& operator*()
//	{
//		return _node->_value;
//	}
//
//	//++iterator: 移动到下一个值的位置
//	Self& operator++()
//	{
//		_node = _node->_next;
//		return *this;
//	}
//
//	//iterator1 != iterator --> 指向是否相同
//	bool operator!=(const Self& it)
//	{
//		return _node != it._node;
//	}
//
//	// pc->成员
//	const T* operator->()
//	{
//		return &_node->_value;
//	}
//
//};

//list实现： 双向带头循环链表实现
template <class T>
class List
{
public:

	typedef ListNode<T> Node;

	//创建一个空List
	List()
		:_header(new Node)
	{
		_header->_prev = _header->_next = _header;
	}

	void pushBack(const T& val)
	{
		//Node* prev = _header->_prev;
		//Node* newNode = new Node(val);

		////重新链接
		//prev->_next = newNode;
		//newNode->_prev = prev;

		//newNode->_next = _header;
		//_header->_prev = newNode;
		insert(end(), val);
	}

	typedef ListIterator<T, T&, T*> iterator;
	typedef ListIterator<T, const T&, const T*> const_iterator;

	iterator begin()
	{
		//第一个有效元素的位置
		return iterator(_header->_next);
	}

	iterator end()
	{
		//最后一个元素下一个位置
		return iterator(_header);
	}

	const_iterator begin() const
	{
		//第一个有效元素的位置
		return const_iterator(_header->_next);
	}

	const_iterator end() const
	{
		//最后一个元素下一个位置
		return const_iterator(_header);
	}

	void pushFront(const T& val)
	{
		insert(begin(), val);
	}

	void popBack()
	{
		erase(--end());
	}

	void popFront()
	{
		erase(begin());
	}

	void insert(iterator pos, const T& val)
	{
		Node* prev = pos._node->_prev;
		Node* newNode = new Node(val);

		prev->_next = newNode;
		newNode->_prev = prev;

		newNode->_next = pos._node;
		pos._node->_prev = newNode;
	}

	//返回的迭代器： 指向当前被删除元素的下一个元素位置
	iterator erase(iterator pos)
	{
		//不能删除list的header
		if (pos != end())
		{
			Node* curNode = pos._node;
			Node* prev = curNode->_prev;
			Node* next = curNode->_next;

			delete curNode;

			prev->_next = next;
			next->_prev = prev;

			return iterator(next);
		}
		return pos;
	}

	void clear()
	{
		//清空有效节点，不能破坏循环结构，不能清空header
		Node* start = _header->_next;
		while (start != _header)
		{
			Node* next = start->_next;
			delete _start;
			start = next;
		}
	}

	~List()
	{
		if (_header)
		{
			clear();
			delete _header;
			_header = nullptr;
		}
	}

private:
	Node* _header;
};

template <class T>
void printList(const List<T>& lst)
{
	List<T>::const_iterator it = lst.begin();
	while (it != lst.end())
	{
		cout << *it << " ";
		//*it = T();
		++it;
	}
	cout << endl;
}

void test()
{
	List<int> lst;
	lst.pushBack(1);
	lst.pushBack(2);
	lst.pushBack(3);
	lst.pushBack(4);

	//迭代器遍历
	List<int>::iterator it = lst.begin();
	while (it != lst.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test2()
{
	C c;
	C* pc = &c;
	pc->_a = 10;
	pc->_b = 20;
}

void test3()
{
	List<C> lst;
	lst.pushBack(C());
	lst.pushBack(C());
	lst.pushBack(C());
	lst.pushBack(C());

	List<C>::iterator it = lst.begin();
	while (it != lst.end())
	{
		cout << (*it)._a << (*it)._b << (*it)._c << endl;
		cout << it->_a << it.operator->()->_b << it->_c << endl;
		++it;
	}
}

void test4()
{
	List<int> lst;
	lst.pushBack(1);
	lst.pushBack(2);
	lst.pushBack(3);
	lst.pushBack(4);

	printList(lst);
}

void test5()
{
	List<int> lst;
	lst.insert(lst.begin(), 1);
	lst.insert(lst.end(), 2);
	List<int>::iterator it = lst.begin();
	cout << *it << endl;
	lst.insert(it, 0);
	cout << *it << endl;
	lst.insert(it, -1);
	cout << *it << endl;

	printList(lst);
}

void test6()
{
	List<int> lst;
	lst.pushBack(5);
	lst.pushBack(6);
	lst.pushBack(7);
	lst.pushFront(4);
	lst.pushFront(3);
	lst.pushBack(8);
	lst.pushFront(2);
	printList(lst);
}

void test7()
{
	List<int> lst;
	lst.pushBack(5);
	lst.pushBack(6);
	lst.pushBack(7);
	lst.pushFront(4);
	lst.pushFront(3);
	lst.pushBack(8);
	lst.pushFront(2);
	printList(lst);
	List<int>::iterator it = lst.begin();
	List<int>::iterator it2 = lst.end();

	it = lst.erase(it);
	cout << *it << endl;
	printList(lst);
	it2 = lst.erase(--it2);
	/*cout << *it2 << endl;*/
	printList(lst);

	lst.popBack();
	printList(lst);
	lst.popFront();
	printList(lst);
}

int main()
{
	//test();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();
	return 0;
}