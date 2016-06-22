#pragma once

template <class T>
class bnode
{
public:
	bnode(TreeNode<T>* par, T val);
	T getValue();
	void setValue(T val);
	bnode* rchild;
	bnode* lchild;
	bnode* parent;
	void replaceChildLink(bnode<T>* oldNode, TreeNode<T>* newNode);

private:
	T value;
};

template <class T>
bnode<T>::bnode(TreeNode<T>* par, T val)
{
	parent = par;
	value = val;
}

template <class T>
T bnode<T>::getValue()
{
	return value;
}

template <class T>
void bnode<T>::setValue(T val)
{
	value = val;
}

template <class T>
void bnode<T>::replaceChildLink(TreeNode<T>* oldNode, TreeNode<T>* newNode)
{
	if (lchild == oldNode)
	{
		lchild = newNode;
	}
	else if (parent->rchild == oldNode)
	{
		rchild = newNode;
	}
}

