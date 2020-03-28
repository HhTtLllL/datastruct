//##################################################################
// File Name: BST.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年03月27日 星期五 23时07分50秒
//=============================================================
//!/usr/bin/python

#include <iostream>

using namespace std;

template <typename Key,typename Value>
class BST
{
	public:
		BST()
		{
			root = NULL;
			count = 0;
		}
		~BST()
		{
			//TODO:~BST()
		}

		int size() { return count; }

		bool isEmpty() {return count == 0}

		void insert(Key key,Value value)
		{
			root = insert(root,key,value);
		}
	private:
		//向以node 为根的二叉搜索树中，插入结点(key,value)
		//返回插入新节点后的二叉搜索树的根
		//最后都会返回到以 root 为根的结点
		Node* insert(Node *node,Key key,Value value)
		{
			if( node == NULL )
			{
				count++;
				return new Node( key, value);
			}
			if( key == node->key) node->value = value;
			else if(key < node->key )
				node->left = insert( node->left , key , value);
			else node->right = insert( node->left , key , value);


			return node;
		}

	private:
		struct Node
		{
			Key key;
			Value value;
			Node *left;
			Node *right;

			Node(Key key,Value value)
			{
				this->key = key;
				this->value = value;
				this->left = this->right = NULL;
			}
		};
		Node*root;
		int count;



}
