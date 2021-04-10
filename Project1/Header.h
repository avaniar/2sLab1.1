#pragma once
#include"list.h"
template<typename key,typename data>
class RBTree
{
public:
	class Node
	{
	public:
		Node(char color, key key, data data, Node* left = nullptr, Node* right = nullptr, Node* parrent = nullptr)
		{
			this->color = color;
			this->key = key;
			this->data = data;
			this->left = left;
			this->right = right;
			this->parrent = parrent;
		};
		~Node() {};
		char color;
		key key;
		data data;
		Node* left;
		Node* right;
		Node* parrent;
	};
	Node* root;
	Node* nil;
	RBTree();
	void insert(key key,data data); // добавление элемента с ключом и значением
	void restorofprop(Node* Newnode);
	void leftrotate(Node* x);
	void rightrotate(Node* y);
	void remove(key key); // удаление элемента дерева по ключу
	void remrestorofprop(Node* x, Node* px);
	data find(key key); // поиск элемента по ключу
	void clear(); // очищение ассоциативного массива
	class Queue
	{
		class Element
		{
		public:
			Element(Node* data, Element* next = nullptr) {
				this->data = data;
				this->next = next;
			};
			~Element() {};
			Node*data;
			Element* next;
		};
		Element* head;
		Element* tail;
		size_t size;
	public:
		Queue();
		~Queue();
		void reset_queue();
		void push(Node*newelement); // добавление в конец списка
		void pop(); // удаление последнего элемент
		Node* front();
		bool empty();
	};
	List<key> get_keys(); // возвращает список ключей
	List<data> get_values(); // возвращает список значений
	void print(); // вывод в консоль
	
};



