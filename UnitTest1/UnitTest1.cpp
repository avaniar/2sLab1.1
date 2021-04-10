#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Header.h"
#include "../Project1/Header.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		RBTree<int, int>* tree;
		TEST_METHOD_INITIALIZE(TestMethod1)
		{
			tree = new RBTree<int,int>;
		}
		TEST_METHOD(correct_incert)
		{
			tree->insert(5, 9);
			tree->insert(8, 9);
			tree->insert(4, 9);
			int check = tree->root->key;
			Assert::AreEqual(check,5);
			check = tree->root->left->key;
			Assert::AreEqual(check, 4);
			check = tree->root->right->key;
			Assert::AreEqual(check, 8);
		}
		TEST_METHOD(correct_remove)
		{
			tree->insert(5, 9);
			tree->insert(8, 9);
			tree->insert(4, 9);
			tree->remove(5);
			int check = tree->root->key;
			Assert::AreEqual(check, 4);
		}
		TEST_METHOD(correct_find)
		{
			tree->insert(5, 7);
			tree->insert(8, 15);
			tree->insert(4, 64);
			Assert::AreEqual(tree->find(4), 64);
		}
		TEST_METHOD(correct_clear)
		{
			for (int i = 1;i != 1000;i++)
			{
				tree->insert(i, i);
			}
			tree->clear();
			Assert::IsTrue(tree->root == tree->nil);
		}
		TEST_METHOD(correct_get_keys)
		{
			tree->insert(5, 7);
			tree->insert(8, 15);
			tree->insert(4, 64);
			List<int>key_list;
			key_list=tree->get_keys();
			Assert::IsTrue(key_list.head->data==5);
			Assert::IsTrue(key_list.head->next->data == 4);
			Assert::IsTrue(key_list.tail->data == 8);
		}
		TEST_METHOD(correct_get_values)
		{
			tree->insert(5, 7);
			tree->insert(8, 15);
			tree->insert(4, 64);
			List<int> value_list;
			value_list = tree->get_values();
			Assert::IsTrue(value_list.head->data == 7);
			Assert::IsTrue(value_list.head->next->data == 64);
			Assert::IsTrue(value_list.tail->data == 15);
		}

	};
}
