#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include "bnode.h"
#include "btree.h"

template <class T>
class btree
{
public:
	TemplateTree(bnode<T>* head);
	~TemplateTree();
	bool pushValue(T value);
	void removeValue(T value);
	void print();

private:
	bool addNode(bnode<T>* curNode, T value);
	void removeNode(bnode<T>* curNode, T value);
	void recPrinting(bnode<T>* startNode, int x, int y);
	void cleanup(bnode<T>* curNode);
	void gotoxy(int x, int y);
	bnode<T>* findMinimumNode(bnode<T>* curNode);
	bnode<T>* head;

};

// ------------------------------------------
// public

template <class T>
btree<T>::btree(bnode<T>* headNode)
{
	head = headNode;
}

template <class T>
btree<T>::~btree()
{
	cleanup(head);
}

template <class T>
bool btree<T>::pushValue(T value)
{
	if (head == NULL)
	{
		head = new TreeNode<T>(NULL, value);
		return true;
	}

	return addNode(head, value);
}

template <class T>
void btree<T>::removeValue(T value)
{
	if (head == NULL)
	{
		return;
	}

	removeNode(head, value);
}

template <class T>
void btree<T>::print()
{
	if (head == NULL)
	{
		std::cout << "tree is empty" << std::endl;
		return;
	}

	system("cls");
	recPrinting(head, 50, 4);
	gotoxy(0, 0);
	std::cout << "press any key to continue..." << std::endl;
	std::getchar();
	system("cls");
	gotoxy(0, 0);
}

// ------------------------------------------
// private

template <class T>
void btree<T>::cleanup(bnode<T>* curNode)
{
	if (curNode)
	{
		if (curNode->lchild) cleanup(curNode->lchild);
		if (curNode->rchild) cleanup(curNode->rchild);

		delete curNode;
		curNode = NULL;
	}
}

template <class T>
btree<T>* TemplateTree<T>::findMinimumNode(bnode<T>* curNode)
{
	while (curNode->lchild != NULL)
	{
		curNode = curNode->lchild;
	}
	return curNode;
}

template <class T>
void btree<T>::removeNode(bnode<T>* curNode, T value)
{
	TreeNode<T>* buff = NULL;
	TreeNode<T>* parent = NULL;
	TreeNode<T>* current = curNode;
	boolean found = false;

	while (!found && current != NULL)
	{
		if (current->getValue() == value)
		{
			found = true;
		}
		else 
		{
			parent = current;
			if (current->getValue() > value)
			{
				current = current->lchild;
			}
			else 
			{
				current = current->rchild;
			}
		}
	}

	if (!found)
	{
		// nothing
	}
	if (parent == NULL) 
	{
		// head

		delete current;
		head = NULL;
	}
	else 
	{
		// child

		if (current->lchild == NULL && current->lchild == NULL)
		{
			// just delete
			current->parent->replaceChildLink(current, NULL);
		}
		else
		if (current->lchild != NULL && current->lchild != NULL)
		{
			// balance tree
			TreeNode<T>* buf = findMinimumNode(curNode->rchild);
			curNode->setValue(buf->getValue());
			removeNode(curNode->rchild, buf->getValue());
		}
		else
		if (current->lchild != NULL)
		{
			current->parent->replaceChildLink(current, current->lchild);
		}
		else
		if (current->rchild != NULL)
		{
			current->parent->replaceChildLink(current, current->rchild);
		}


		delete current;
	}


}

template <class T>
bool btree<T>::addNode(bnode<T>* curNode, T value)
{
	float curNodeValue = curNode->getValue();

	if (curNodeValue == value)
	{
		return false;
	}
	else if (curNodeValue < value)
	{
		if (curNode->rchild == NULL)
		{
			curNode->rchild = new bnode<T>(curNode, value);
			return true;
		}
		else
		{
			return addNode(curNode->rchild, value);
		}
	}
	else if (curNodeValue > value)
	{
		if (curNode->lchild == NULL)
		{
			curNode->lchild = new bnode<T>(curNode, value);
			return true;
		}
		else
		{
			return addNode(curNode->lchild, value);
		}
	}

	return false;
}

template <class T>
void btree<T>::recPrinting(bnode<T>* startNode, int x, int y)
{
	if (startNode != NULL)
	{
		gotoxy(x, y);
		std::cout << startNode->getValue();

		if (startNode->lchild != NULL)
		{
			gotoxy(x - 1, y + 1);
			std::cout << "/";
			recPrinting(startNode->lchild, x - 2, y + 2);
		}

		if (startNode->rchild != NULL)
		{
			gotoxy(x + 1, y + 1);
			std::cout << "\\";
			recPrinting(startNode->rchild, x + 2, y + 2);
		}
	}
}

template <class T>
void btree<T>::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}