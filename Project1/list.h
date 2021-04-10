#pragma once
template<typename value>
class List
{
public:
	class node1
	{
	public:
		node1(value data, node1* next = nullptr, node1* prev = nullptr) {
			this->data = data;
			this->next = next;
		};
		~node1() {};

		value data;
		node1* next;
	};
	node1* head;
	node1* tail;
	size_t size;
	List();
	void reset_list();
	void push_back(value data);
};