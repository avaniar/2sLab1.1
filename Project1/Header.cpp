#include "Header.h"
#include <iostream>
using namespace std;
template<typename key, typename data>
RBTree<key,data>::RBTree()
{
	root = nullptr;
	nil = new Node('b',NULL,NULL);
	root = nil;
}
template<typename key, typename data>
void RBTree<key, data>::insert(key key, data data)
{
	Node*newroot=new Node('r', key, data);
	if (nil==root)
	{
		newroot->color = 'b';
		root = newroot;
		root->left = nil;
		root->right = nil;
		root->parrent = nil;
	}
	else
	{
		Node* current = root;
		Node* prevcur = nil;
		while (current != nil)
		{
			prevcur = current;
			if (newroot->key > current->key)
				current = current->right;
			else
				current = current->left;
		}
		newroot->parrent = prevcur;
		if (prevcur->key < newroot->key)
			prevcur->right = newroot;
		else
			prevcur->left = newroot;
		newroot->right = nil;
		newroot->left = nil;
		restorofprop(newroot);
	}

}
template<typename key, typename data>
void RBTree<key, data>::restorofprop(Node*Newnode)
{
	Node* current = Newnode;
	Node* gp; Node* p;
	while ((current!=root)&&(current->parrent->color =='r'))
	{
		p = current->parrent;
		gp = p->parrent;
		if (gp->left == p)
		{
			if (gp->right->color == 'r')
			{
				gp->right->color = 'b';
				p->color = 'b';
				gp->color = 'r';
				current = gp;
			}
			else if (current == p->right)
			{
				current = p;
				leftrotate(current);
			}
			else
			{
				p->color = 'b';
				gp->color = 'r';
				rightrotate(gp);
			}
		}
		else
		{
			if ((gp->left!=nil)&&(gp->left->color == 'r'))
			{
				gp->left->color = 'b';
				gp->right->color = 'b';
				gp->color = 'r';
				current = gp;
			}
			else if (current == p->left)
			{
				current = p;
				rightrotate(current);
			}
			else
			{
				p->color = 'b';
				gp->color = 'r';
				leftrotate(gp);
			}
		}
	}
	root->color = 'b';
}
template<typename key, typename data>
void RBTree<key, data>::leftrotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != nil)
	{
		x->right->parrent = x;
	}
	if (x->parrent == nil)
	{
		root = y;
		y->parrent = nil;
	}
	else if ((x->parrent->left == x))
	{
		y->parrent = x->parrent;
		y->parrent->left = y;
	}
	else
	{
		y->parrent = x->parrent;
		y->parrent->right = y;
	}
	y->left = x;
	x->parrent = y;
}

template<typename key, typename data>
void RBTree<key, data>::rightrotate(Node* y)
{
	Node* x = y->left;
	y->left = x->right;
	if (x->right != nil)
	{
		x->right->parrent = y;
	}
	if (y->parrent == nil)
	{
		x = root;
		x->parrent = nil;
	}
	else if (y->parrent->right == y)
	{
		x->parrent = y->parrent;
		x->parrent->right = x;
	}
	else
	{
		x->parrent = y->parrent;
		x->parrent->left = x;
	}
	x->right = y;
	y->parrent = x;
}

template<typename key, typename data>
void RBTree<key, data>::remove(key key)
{
	Node* current = root;
	while (current->key != key)
	{
		if (current->key < key)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}
	}
	if ((current == root) && (current->left == nil) && (current->right == nil))
	{
		root = nil;
	}
	else
	{
		if (((current->color == 'r') || (current->color == 'b')) && (current->left != nil) && (current->right != nil))//removing red or black node with two child
		{
			Node* max = current->left;
			while (max->right != nil)
			{
				max = max->right;
			}
			int help = current->key;
			current->key = max->key;
			max->key = help;
			help = current->data;
			current->data = max->data;
			max->data = help;
			current = max;
		}
		if ((current->color == 'r'))//removing the red node without child
		{
			if (current->parrent->right == current)
			{
				current->parrent->right = nil;
			}
			else
			{
				current->parrent->left = nil;
			}
			delete current;
		}
		else
		{
			if (current->left != nil)//removing a black node with one child.
			{
				current->data = current->left->data;
				current->key = current->left->key;
				delete current->left;
				current->left = nil;
			}
			else if (current->right != nil)//removing a black node with one child.
			{
				current->data = current->right->data;
				current->key = current->right->key;
				delete current->right;
				current->right = nil;
			}
			else//removing a black node without child.
			{
				Node* x;Node* px;
				if (current->parrent->left == current)
				{
					current->parrent->left = nil;
					x = current->parrent->left;
					px = current->parrent;
				}
				else
				{
					current->parrent->right = nil;
					x = current->parrent->right;
					px = current->parrent;
				}
				delete current;
				remrestorofprop(x, px);
			}

		}
	}
}

template<typename key, typename data>
void RBTree<key, data>::remrestorofprop(Node* x, Node* px)//px-parrent x
{
	Node* w;
	while ((x != root) && (x->color == 'b'))
	{
		if (x == px->left)
		{
			w = px->right;
			if (w->color == 'r')
			{
				w->color = 'b';
				px->color = 'r';
				leftrotate(px);
				w = px->right;
			}
			if ((w->left->color == 'b') && (w->right->color == 'b'))
			{
				w->color = 'r';
				x = px;
				px = px->parrent;
			}
			else if  (w->right->color == 'b')
			{
				w->left->color = 'b';
				w->color = 'r';
				rightrotate(w);
				w=px->right;
			}
			else
			{
				w->color = px->color;
				px->color = 'b';
				w->right->color = 'b';
				leftrotate(px);
				x = root;
			}
		}
		else
		{
			w = px->left;
			if (w->color == 'r')
			{
				w->color = 'b';
				px->color = 'r';
				rightrotate(px);
				w = px->left;
			}
			if ((w->left->color == 'b') && (w->right->color == 'b'))
			{
				w->color = 'r';
				x = px;
				px = px->parrent;
			}
			else if (w->left->color == 'b')
			{
				w->right->color = 'b';
				w->color = 'r';
				leftrotate(w);
				w = px->left;
			}
			else
			{
				w->color = px->color;
				px->color = 'b';
				w->left->color = 'b';
				rightrotate(px);
				x = root;
			}
		}
	}
	x->color = 'b';
}

template<typename key, typename data>
data RBTree<key, data>::find(key key)
{
	Node* current = root;
	while ((current->key != key) && (current != nil))
	{
		if (key > current->key)
			current = current->right;
		else
			current = current->left;
	}
	if (current == nil)
		return 0;
	else
		return current->data;
}

template<typename key, typename data>
void RBTree<key, data>::clear()
{
	while (root != nil)
	{
		remove(root->key);
	}
}


template<typename key, typename data>
List<key> RBTree<key, data>::get_keys()
{
	Queue queue; List<key> key_list;
	Node* current = root;
	queue.push(current);
	while (queue.empty())
	{
		current = queue.front();
		if (current->left != nil) queue.push(current->left);
		if (current->right != nil) queue.push(current->right);
		queue.pop();
		key_list.push_back(current->key);
	}
	return key_list;
}

template<typename key, typename data>
List<data> RBTree<key, data>::get_values()
{
	Queue queue; List<data> data_list;
	Node* current = root;
	queue.push(current);
	while (queue.empty())
	{
		current = queue.front();
		if (current->left != nil) queue.push(current->left);
		if (current->right != nil) queue.push(current->right);
		queue.pop();
		data_list.push_back(current->data);
	}
	return data_list;
}

template<typename key, typename data>
void RBTree<key, data>::print()
{
	Queue queue;
	Node* current = root;
	if (current != nil)
	{
		queue.push(current);
		while (queue.empty())
		{
			current = queue.front();
			if (current->left != nil) queue.push(current->left);
			if (current->right != nil) queue.push(current->right);
			queue.pop();
			cout << "(" << current->key << "," << current->data << ") ";
		}
	}
	else
		cout << "no elments";
}

template<typename key, typename data>
RBTree<key, data>::Queue::Queue()
{
	reset_queue();
	size = 0;
}

template<typename key, typename data>
RBTree<key, data>::Queue::~Queue()
{
	while (empty())
	{
		pop();
	}
}

template<typename key, typename data>
void RBTree<key, data>::Queue::reset_queue()
{
	head = nullptr;
	tail = nullptr;
}

template<typename key, typename data>
void RBTree<key, data>::Queue::push(Node* newelement)
{
	if (size == 0)//We add the new element first.
	{
		head = new Element(newelement);
		tail = head;
	}
	else//We add the new element last.
	{
		Element* current = new Element(newelement);
		tail->next = current;
		tail = current;
	}
	size++;
}

template<typename key, typename data>
void RBTree<key, data>::Queue::pop()
{
	if (size == 0) return;//Exit the function.
	if (size == 1)//We remove the first element and reset the list.
	{
		delete head;
		reset_queue();
	}
	else//We remove the first element
	{
		Element* current = head->next;
		head->next = nullptr;
		delete head;
		head = current;
	}
	size--;
}

template<typename key, typename data>
typename RBTree<key, data>::Node* RBTree<key, data>::Queue::front()
{
	return head->data;
}

template<typename key, typename data>
bool RBTree<key, data>::Queue::empty()
{
	if (size == 0)
		return false;
	else
		return true;
}



template<typename value>
List<value>::List()
{
	reset_list();
	size = 0;
}

template<typename value>
void List<value>::reset_list()
{
	head = nullptr;
	tail = nullptr;
}

template<typename value>
void List<value>::push_back(value data)
{
	if (size == 0)//We add the new element first.
	{
		head = new node1(data);
		tail = head;
	}
	else//We add the new element last.
	{
		node1* current = new node1(data);
		tail->next = current;
		tail = current;
	}
	size++;
}


