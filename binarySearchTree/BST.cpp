//##################################################################
// File Name: BST.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年03月27日 星期五 23时07分50秒
//=============================================================
//!/usr/bin/python

#include <iostream>
#include <cassert>
#include <queue>


using namespace std;

template <typename Key,typename Value>
class BST
{
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
                Node* root;
                int count;


	public:
		BST()
		{
			root = NULL;
			count = 0;
		}
		~BST()
		{
			//释放空间
			destroy(root);
		}

		int size() { return count; }

		bool isEmpty() { return count == 0; }

		void insert(Key key,Value value)
		{
			root = insert(root,key,value);
		}

		bool contain(Key key)
		{
			return contain(root,key);
		};

		//返回值也可以为 Value，如果返回值是Value,就需要确保search这个元素一定存在
		//也可以将contain 在search中调用。
		//
		//返回值也可以为Node*　结点，不过这样就需要将结点设为共有的
		Value* search(Key key)
		{
			return search(root,key);
		};
		//前序遍历
		void preOrder()
		{
			preOrder(root);
		}

		//中序遍历
		void inOrder()
		{
			inOrder(root);
		}
		//后序遍历
		void postOrder()
		{
			postOrder(root);
		}

		//层序遍历
		void levelOrder()
		{
			queue<Node*> q;
			q.push(root);

			while(!q.empty())
			{
				Node* node = q.front();
				q.pop();
				cout << node->key << endl;

				if(node->left) q.push(node->left);
				if(node->right) q.push(node->right);
			}
		}

		//寻找最小的键值
		Key minimum()
		{
			assert(count != 0);
			Node* minNode = minimum(root);
			return minNode->key;
		}
		
		//寻找最大的键值
		Key maximum()
		{
			assert(count != 0);

			Node* maxNode = maximum(root);
			
			return maxNode->key;
		}

		//从二叉树中删除最小值所在结点
		void removeMin()
		{
			if( root ) root = removeMin( root );
		}

		//从二叉树中删除最大值所在结点

		void removeMax()
		{

			if( root )
				root = removeMax(root);
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

		//查看以node为根的二叉搜索树中是否包含键值为key的结点
		bool contain(Node* node,Key key)
		{
			//如果没有找到
			if( node == NULL) return false;
			
			if( node->key == key ) return true;

			if( key < node->key)
			{
				return contain(node->left,key);
			}
			else 
				return contain(node->right,key);
		}

		//在以node为根的二叉搜索树中查找key所对应的value
		Value* search( Node* node,Key key)
		{
			if( node == NULL) return NULL;

			if( key == node->key ) 
				return &(node->value);
			else if( key < node->key) 
				return search(node->left,key);
			else 
				return search(node->right,key);
		}
		
		//对以node为根的二叉搜索树进行前序遍历
		void preOrder(Node* node)
		{
			if(node == NULL)  return ;
			cout << node->key << endl;

			preOrder(node->left);
			preOrder(node->right);
		}

		//对以node为根的二叉搜索树进行前序遍历
		void inOrder(Node* node)
		{
			if( node == NULL ) return ;

			inOrder(node->left);

			cout << node->key << endl;

			inOrder(node->right);
		}
		
		//对以node为根的二叉搜索树进行前序遍历
		void postOrder(Node* node)
		{
			if( node == NULL) return ;
			postOrder(node->left);
			postOrder(node->right);

			cout << node->key << endl;
		}


		void destroy(Node* node)
		{
			if( node != NULL )
			{
				destroy(node->left);
				destroy(node->right);

				delete node;
				count--;
			}
		}
		
		//在以node为根的二叉搜索树中，返回最小键值的结点
		Node* minimum(Node* node)
		{
			 if(node->left == NULL) return node;

			 return minimum(node->left);

		}
		
		//在以node为根的二叉搜索树中，返回最大键值的结点
		Node* maximum(Node* node)
		{
			if(node->right == NULL) return node;

			return maximum(node->right);
		}

		//删除掉以node为根的二分搜索树中的最小结点
		//返回删除结点后新的二分搜索树的根
		Node* removeMin(Node* node)
		{
			if( NULL == node->left )
			{
				Node* rightNode = node->right;

				delete node;
				count-- ;
				
				return rightNode;
			}

			node->left = removeMin(node->left);

			return node;
		}

		Node* removeMax(Node* node)
		{
			//如果右子树为空,则当前结点为最大值的结点
			if( NULL == node->right)
			{
				//即使左孩子为空也没有关系,
				Node* leftNode = node->left; 

				delete node;
				count--;


				return leftNode;
			}

			node->right = removeMax(node->right);


			return node;
		}








		
		


//数据在下面编译失败
/*	private:
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
		Node* root;
		int count;*/
};

int main()
{
	BST<int,int> B;



	
	return 0;
}
