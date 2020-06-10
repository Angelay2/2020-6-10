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

// listʵ��: ˫���ͷѭ������
// Vector��������Vector<int>��������

/* list������: ----- ��װ�ڵ�ָ�� (��ֵ -- ��ȡ�ڵ�ָ��, �ƶ� -- ��ȡ��һ���ڵ��λ��
������++����һλ�� �������������õ�Ԫ��, �����Ԫ���Ƿ��ʽ�㵱�д�ŵ�ֵ
 �������Ľ�����: ��ȡ���ڵ��е�ֵ
 ++/--: �ƶ�����һ��ֵ��λ��

 Node*(ԭ��ָ�벻��ʵ�ֵ�������)
 ������: �ǽڵ�, �����ǽڵ��ֵ; 
 ��Node*++/--: ��֪���ƶ���ʲô�ط�ȥ��(λ��Ϊδ֪), ��Ϊ�ڵ㲻��������

 ������ƽ·����˶ɺ� ��������� ���¶�������� (��װ�ڵ�ָ�� -- �Զ����� ��Ա����Ϊָ��)
 *iterator --> Node*->val
 ++: ++iterator --> Node*->next
 --: --iterator --> Node*->prev
 iterator begin() ----> return iterator(header->next) ����ͨ��header��next�����һ��������
 iterator end() ----> return iterator(header) ����ͨ��header(���һ��Ԫ�ص���һ��λ��)�����һ��������

 Date(1,2,3) ��ʵ1,2,3Ҳ�������ĳ�Ա����    �������Ϊ����ʱͨ���ṩ��Ա����������Ķ���

 �費��Ҫ��� ���������Ƿ�ӵ����Դ ������������Ҫ��������������͸�ֵ��������� ��Ϊ����������Դ�������ڵ����� 
 ��List��Ҫд����, ��Ϊ����Դ(�ڵ�)������

 iterator:
	T& operator*(), T* operator->()
 const iterator:
	const T& operator*(), const T* operator->()
	Ref operator*(), Ptr operator->()

ListIterator<T, T&, T*>
const_ListIterator<T, const T&, const T*>
ListIterator<class T, class Ref, class Ptr>

List�������ܽ�:
	1, ԭ��ָ��ʵ�ֲ��˵������Ĺ���
	2. ������ͨ����װ�ڵ�ָ��, ����һ���µ��Զ�������, ʵ�ֵ�����
	3. �����ÿһ������������ԭ��ָ��, ����һ������, ��Ҫͨ�����캯������
	����ʵ��: 
	4. ������: ͨ����ȡ�ڵ��������ɽ����õĹ���  node->value
	5. �ƶ�(++/--): ͨ�����½ڵ��ָ�����, node = node->next/ node = node->prev
	6. ������(!=): ͨ���жϽڵ��ָ���Ƿ���ͬ��� node != iterator.node
	7. ->����: ͨ����ȡ���ݵ�ָ�����  &node->value
	����ʵ��
	8. ͨ��3�����Ͳ������ֵ�������const_iterator������
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

//ͨ����װ�ڵ�ʵ�ֵ�����
template <class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	//��װ�ڵ�
	Node* _node;

	ListIterator(Node* node)
		:_node(node)
	{}

	//*iterator: ������--> ��ȡ���ڵ��е�value
	Ref operator*()
	{
		return _node->_value;
	}

	//++iterator: �ƶ�����һ��ֵ��λ��
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

	//iterator1 != iterator --> ָ���Ƿ���ͬ
	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	// pc->��Ա
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
//	//��װ�ڵ�
//	Node* _node;
//
//	ConstListIterator(Node* node)
//		:_node(node)
//	{}
//
//	//*iterator: ������--> ��ȡ���ڵ��е�value
//	const T& operator*()
//	{
//		return _node->_value;
//	}
//
//	//++iterator: �ƶ�����һ��ֵ��λ��
//	Self& operator++()
//	{
//		_node = _node->_next;
//		return *this;
//	}
//
//	//iterator1 != iterator --> ָ���Ƿ���ͬ
//	bool operator!=(const Self& it)
//	{
//		return _node != it._node;
//	}
//
//	// pc->��Ա
//	const T* operator->()
//	{
//		return &_node->_value;
//	}
//
//};

//listʵ�֣� ˫���ͷѭ������ʵ��
template <class T>
class List
{
public:

	typedef ListNode<T> Node;

	//����һ����List
	List()
		:_header(new Node)
	{
		_header->_prev = _header->_next = _header;
	}

	void pushBack(const T& val)
	{
		//Node* prev = _header->_prev;
		//Node* newNode = new Node(val);

		////��������
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
		//��һ����ЧԪ�ص�λ��
		return iterator(_header->_next);
	}

	iterator end()
	{
		//���һ��Ԫ����һ��λ��
		return iterator(_header);
	}

	const_iterator begin() const
	{
		//��һ����ЧԪ�ص�λ��
		return const_iterator(_header->_next);
	}

	const_iterator end() const
	{
		//���һ��Ԫ����һ��λ��
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

	//���صĵ������� ָ��ǰ��ɾ��Ԫ�ص���һ��Ԫ��λ��
	iterator erase(iterator pos)
	{
		//����ɾ��list��header
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
		//�����Ч�ڵ㣬�����ƻ�ѭ���ṹ���������header
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

	//����������
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