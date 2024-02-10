#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

Tree::~Tree()
{
	std::queue<TreeNode*> q;
	TreeNode* p = anker;

	q.push(p);
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		if (p->getLeft() != nullptr)
			q.push(p->getLeft());
		if (p->getRight() != nullptr)
			q.push(p->getRight());

		delete p;
	}
}

bool Tree::split4Node(TreeNode* node)
{
	if (node->getLeft() == nullptr || node->getRight() == nullptr)
		return false;

	if (node->getLeft()->getRed() && node->getRight()->getRed())
	{
		node->setRed(true);
		node->getLeft()->setRed(false);
		node->getRight()->setRed(false);

		return true;
	}

	return false;
}

std::string Tree::verletzung_art(TreeNode* node)
{
	TreeNode* first_parent = node->getParent();
	TreeNode* second_parent = first_parent->getParent();

	if (node == first_parent->getRight())
	{
		if (first_parent == second_parent->getRight())
			return "Rechts Rechts";
		else
			return "Links Knick";
	}
	else
	{
		if (first_parent == second_parent->getRight())
			return "Rechts Knick";
		else
			return "Links Links";
	}
}

TreeNode* Tree::balance(TreeNode* node, std::string verletzungsart)
{
	TreeNode* first_parent = node->getParent();
	TreeNode* second_parent = first_parent->getParent();

	if(verletzungsart == "Rechts Rechts")
	{ 
		left_rotate(second_parent);

		first_parent->setRed(0);
		second_parent->setRed(1);

		return first_parent; // new parent
	}
	else if(verletzungsart == "Links Links")
	{
		right_rotate(second_parent);

		first_parent->setRed(0);
		second_parent->setRed(1);

		return first_parent; // new parent
	}
	else if(verletzungsart == "Rechts Knick")
	{ 
		right_rotate(first_parent);
		left_rotate(second_parent);

		node->setRed(0);
		second_parent->setRed(1);

		return node; // new parent
	}
	else if(verletzungsart == "Links Knick")
	{ 
		left_rotate(first_parent);
		right_rotate(second_parent);

		node->setRed(0);
		second_parent->setRed(1);

		return node; // new parent
	}
}

void Tree::right_rotate(TreeNode* node)
{
	if (node == anker)
	{
		TreeNode* left_child = node->getLeft();

		anker = left_child;

		if (left_child->getRight() != nullptr)
		{
			left_child->getRight()->setParent(node);
			node->setLeft(left_child->getRight());
		}
		else
		{
			node->setLeft(nullptr);
		}
		left_child->setRight(node);
		node->setParent(left_child);

		left_child->setParent(nullptr);
		return;
	}
	TreeNode* parent = node->getParent();
	TreeNode* left_child = node->getLeft();

	// Set Parent
	if (node == parent->getRight())
		parent->setRight(left_child);
	else
		parent->setLeft(left_child);
	left_child->setParent(parent);

	// Set Node
	if (left_child->getRight() != nullptr)
	{
		node->setLeft(left_child->getRight());
		left_child->getRight()->setParent(node);
	}
	else
	{
		node->setLeft(nullptr);
	}
	// Set right child
	left_child->setRight(node);
	node->setParent(left_child);
}
void Tree::left_rotate(TreeNode* node)
{
	if (node == anker)
	{
		TreeNode* right_child = node->getRight();

		anker = right_child;

		if (right_child->getLeft() != nullptr)
		{
			right_child->getLeft()->setParent(node);
			node->setRight(right_child->getLeft());
		}
		else
			node->setRight(nullptr);

		right_child->setLeft(node);
		node->setParent(right_child);

		right_child->setParent(nullptr);
		return;
	}

	TreeNode* parent = node->getParent();
	TreeNode* right_child = node->getRight();

	// Set Parent
	if (node == parent->getLeft())
		parent->setLeft(right_child);
	else
		parent->setRight(right_child);
	right_child->setParent(parent);

	// Set Node
	if (right_child->getLeft() != nullptr)
	{
		node->setRight(right_child->getLeft());
		right_child->getLeft()->setParent(node);
	}
	else
		node->setRight(nullptr);
	// Set right child
	right_child->setLeft(node);
	node->setParent(right_child);
}

void Tree::addNode(std::string name, int age, double income, int postCode)
{
	int nodeOrderID = age + postCode + income;
	TreeNode* new_node = new TreeNode(nodeOrderID, currentNodeChronologicalID, name, age, income, postCode);

	if (anker == nullptr)
	{
		anker = new_node;
		++currentNodeChronologicalID;
		return;
	}

	TreeNode* ptr_parent = anker;
	TreeNode* ptr = anker;

	while (ptr != nullptr)
	{
		if (!ptr->getRed()) // Top-Down Aufsplitten
			split4Node(ptr);

		ptr_parent = ptr;
		if (nodeOrderID < ptr->getNodeOrderID())
			ptr = ptr->getLeft();

		else
			ptr = ptr->getRight();
	}

	// add the new node
	if (nodeOrderID < ptr_parent->getNodeOrderID())
		ptr_parent->setLeft(new_node);
	else
		ptr_parent->setRight(new_node);

	new_node->setParent(ptr_parent);
	++currentNodeChronologicalID;

	// Bottom-Up balance
		
	ptr = new_node;
	// when parent is anchor //or Tree with only 2 levels -> do nothing
	if (!(ptr->getParent() == anker) /* || ptr->getParent()->getParent() == anker)*/)
	{
		while (ptr->getParent() != nullptr)
		{
			if (!ptr->getParent()->getRed())
			{
				ptr = ptr->getParent();
			}
			else
			{
				if (ptr->getRed()) // 2 red nodes -> balance
				{
					ptr = balance(ptr, verletzung_art(ptr));
					if(ptr->getParent()!=nullptr)
						ptr = ptr->getParent();
				}
				else // only parent red 
					ptr = ptr->getParent();
			}
		}
	}
	// Wurzel immer schwarz
	anker->setRed(false);
}

bool Tree::searchNode(std::string name)
{
	TreeNode* ptr = anker;

	std::queue<TreeNode*> q;

	q.push(ptr);

	while (!q.empty())
	{
		ptr = q.front();

		if (ptr->getName() == name)
		{
			std::cout << "NodeID: " << ptr->getNodeChronologicalID() <<
				", Name: " << ptr->getName() <<
				", Alter: " << ptr->getAge() <<
				", Einkommen: " << ptr->getIncome() <<
				", PLZ: " << ptr->getPostCode() <<
				", posID: " << ptr->getNodeOrderID() << std::endl;
			return true;
		}


		q.pop();

		if (ptr->getLeft() != nullptr)
			q.push(ptr->getLeft());

		if (ptr->getRight() != nullptr)
			q.push(ptr->getRight());
	}

	return false;
}

bool Tree::searchNode(int _nodeOrderID, TreeNode*& del_node, TreeNode*& parent_del_node)
{
	TreeNode* ptr = anker;

	while (ptr->getNodeOrderID() != _nodeOrderID)
	{
		parent_del_node = ptr;

		if (_nodeOrderID < ptr->getNodeOrderID())
			ptr = ptr->getLeft();

		else
			ptr = ptr->getRight();

		if (ptr == nullptr)
			return false;
	}

	del_node = ptr;
	return true;
}

void Tree::preorder(TreeNode* p)
{
	std::cout << std::setw(3) << p->getNodeChronologicalID() <<
		std::setw(12) << p->getName() <<
		std::setw(6) << p->getAge() <<
		std::setw(12) << p->getIncome() <<
		std::setw(9) << p->getPostCode() <<
		std::setw(9) << p->getNodeOrderID() << std::endl << std::endl;

	if (p->getLeft() != nullptr)
		preorder(p->getLeft());
	if (p->getRight() != nullptr)
		preorder(p->getRight());
}

void Tree::printAllPreorder()
{
	if (anker == nullptr)
		std::cout << "Baum ist leer." << std::endl;
	else
	{
		std::cout << "Ausgabe in Levelorder als binaerer Suchbaum:" << std::endl << std::endl;

		std::cout << "ID |    Name    | Age | Income |  PostCode  | OrderID " << std::endl
				  << "---+------------+-----+--------+------------+---------" << std::endl;
		preorder(anker);
	}
}

void Tree::printAll()
{
	std::cout << "Ausgabe in Levelorder als binaerer Suchbaum:" << std::endl << std::endl;
	this->levelOrder();
	std::cout << std::endl;

	std::cout << "Ausgabe in Levelorder als 2-3-4-Baum:" << std::endl;
	this->printLevelOrder();
}

void Tree::levelOrder() const
{
	if (anker == nullptr)
	{
		std::cout << "Baum ist leer." << std::endl;
		return;
	}

	bool einmal = true;
	if (einmal)
	{
		std::cout << "ID |    Name    | Age | Income |  PostCode  | OrderID |  Red  " << std::endl
			      << "---+------------+-----+--------+------------+---------+-------" << std::endl;
		einmal = false;
	}

	std::queue<TreeNode*> q;

	q.push(anker);

	int pop_old = 1;
	int pop_new = 0;
	int niveau = 0;

	while (true)
	{

		for (int i = 0; i < pop_old; ++i)
		{
			TreeNode* p = q.front();
			std::cout << std::setw(3) << p->getNodeChronologicalID() <<
				std::setw(12) << p->getName() <<
				std::setw(4) << p->getAge() <<
				std::setw(12) << p->getIncome() <<
				std::setw(9) << p->getPostCode() <<
				std::setw(9) << p->getNodeOrderID() <<
				std::setw(8) << p->getRed() << endl;

			if (p->getLeft() != nullptr)
			{
				pop_new++;
				q.push(p->getLeft());
			}
			if (p->getRight() != nullptr)
			{
				pop_new++;
				q.push(p->getRight());
			}

			q.pop();
		}

		if (pop_new == 0) // Queue empty
		{
			std::cout << std::endl;
			return;
		}

		pop_old = pop_new;
		pop_new = 0;
		++niveau;
	}

}

void Tree::printLevelOrder() const
{
	if (anker == nullptr)
	{
		std::cout << "Baum ist leer." << std::endl;
		return;
	}

	std::queue<int> levels;
	std::queue<TreeNode*> nodes;

	levels.push(0);
	nodes.push(anker);
	int current_level = 0;
	while (!nodes.empty())
	{
		std::cout << "Niv. " << current_level << " : ";

		while (levels.front() == current_level)
		{
			std::cout << "( ";

			if (nodes.front()->getLeft() != nullptr)
			{
				TreeNode* left_child = nodes.front()->getLeft();

				if (left_child->getRed())
				{
					std::cout << left_child->getNodeOrderID() << " , ";

					if (left_child->getLeft() != nullptr)
					{
						nodes.push(left_child->getLeft());
						levels.push(current_level + 1);
					}
					if (left_child->getRight() != nullptr)
					{
						nodes.push(left_child->getRight());
						levels.push(current_level + 1);
					}
				}
				else
				{
					nodes.push(left_child);
					levels.push(current_level + 1);
				}
			}

			std::cout << nodes.front()->getNodeOrderID() << " ";

			if (nodes.front()->getRight() != nullptr)
			{
				TreeNode* right_child = nodes.front()->getRight();
				
				if (right_child->getRed())
				{
					std::cout << ", " << right_child->getNodeOrderID() << " ";

					if (right_child->getLeft() != nullptr)
					{
						nodes.push(right_child->getLeft());
						levels.push(current_level + 1);
					}
					if (right_child->getRight() != nullptr)
					{
						nodes.push(right_child->getRight());
						levels.push(current_level + 1);
					}
				}
				else
				{
					nodes.push(right_child);
					levels.push(current_level + 1);
				}
			}
			std::cout << ") ";
			nodes.pop();

			levels.pop();
			if (levels.empty())
				break;
		}
		++current_level;
		std::cout << std::endl;
	}
}

void Tree::printLevelOrder(int niveau) const
{
	if (anker == nullptr)
	{
		std::cout << "Baum ist leer." << std::endl;
		return;
	}
	if (niveau == 0)
	{
		std::cout << "Niv. 0 : ( ";
		if (anker->getLeft() != nullptr && anker->getLeft()->getRed())
			std::cout << anker->getLeft()->getNodeOrderID() << " , ";
		
		std::cout << anker->getNodeOrderID();
		
		if (anker->getRight() != nullptr && anker->getRight()->getRed())
			std::cout << " , " << anker->getRight()->getNodeOrderID();

		std::cout << " )" << std::endl;
	}

	std::queue<int> levels;
	std::queue<TreeNode*> nodes;

	levels.push(0);
	nodes.push(anker);
	int current_level = 0;

	while (!nodes.empty())
	{
		while (levels.front() == current_level)
		{
			//std::cout << "( ";

			if (nodes.front()->getLeft() != nullptr)
			{
				TreeNode* left_child = nodes.front()->getLeft();

				if (left_child->getRed())
				{
					//std::cout << left_child->getNodeOrderID() << " , ";

					if (left_child->getLeft() != nullptr)
					{
						nodes.push(left_child->getLeft());
						levels.push(current_level + 1);
					}
					if (left_child->getRight() != nullptr)
					{
						nodes.push(left_child->getRight());
						levels.push(current_level + 1);
					}
				}
				else
				{
					nodes.push(left_child);
					levels.push(current_level + 1);
				}
			}

			// std::cout << nodes.front()->getNodeOrderID() << " ";

			if (nodes.front()->getRight() != nullptr)
			{
				TreeNode* right_child = nodes.front()->getRight();

				if (right_child->getRed())
				{
					//std::cout << ", " << right_child->getNodeOrderID() << " ";

					if (right_child->getLeft() != nullptr)
					{
						nodes.push(right_child->getLeft());
						levels.push(current_level + 1);
					}
					if (right_child->getRight() != nullptr)
					{
						nodes.push(right_child->getRight());
						levels.push(current_level + 1);
					}
				}
				else
				{
					nodes.push(right_child);
					levels.push(current_level + 1);
				}
			}
			//std::cout << ") ";
			nodes.pop();

			levels.pop();
			if (levels.empty())
				break;
		}

		++current_level;
		if (current_level == niveau)
		{
			std::cout << "Niv. " << current_level << " : ";

			while (!nodes.empty())
			{
				std::cout << "( ";

				if (nodes.front()->getLeft() != nullptr && nodes.front()->getLeft()->getRed())
					std::cout << nodes.front()->getLeft()->getNodeOrderID() << " , ";

				std::cout << nodes.front()->getNodeOrderID() << " ";

				if (nodes.front()->getRight() != nullptr && nodes.front()->getRight()->getRed())
					std::cout << ", " << nodes.front()->getRight()->getNodeOrderID() << " ";

				std::cout << ") ";
				nodes.pop();
			}
			std::cout << std::endl;
			return;
		}
	}
}

int Tree::compute_height(TreeNode* node) const
{
	if (node->getLeft() == nullptr && node->getRight() == nullptr)
		return 0;
	// ein nachfolger existiert nicht
	else if (node->getLeft() == nullptr && node->getRight() != nullptr)
	{
		if (node->getRight()->getRed())
			return compute_height(node->getRight());
		else
			return compute_height(node->getRight()) + 1;
	}
	else if (node->getLeft() != nullptr && node->getRight() == nullptr)
	{
		if (node->getLeft()->getRed())
			return compute_height(node->getLeft());
		else
			return compute_height(node->getLeft()) + 1;
	}

	int left_height = compute_height(node->getLeft());
	int right_height = compute_height(node->getRight());

	// beide rot
	if (node->getLeft()->getRed() && node->getRight()->getRed())
	{
		if (left_height != right_height)
		{
			std::cout << "Fehler gefunden: Beide Nachfolger rot aber Hoehe nicht gleich : " << left_height << " != " << right_height << std::endl;
			return -1;
		}
		return left_height;
	}

	// einer rot einer schwarz
	if(node->getLeft()->getRed() && !node->getRight()->getRed())
	{ 
		if(left_height != right_height + 1)
		{
			std::cout << "Fehler gefunden: linker Nachfolger rot, rechter Nachfolger shwarz aber h(left) = "<< left_height
				<< " != h(right + 1) = " << right_height + 1 << std::endl;
			return - 1;
		}
		return left_height;
	}
	else if(!node->getLeft()->getRed() && node->getRight()->getRed())
	{ 
		if (left_height +1 != right_height)
		{
			std::cout << "Fehler gefunden: linker Nachfolger shwarz, rechter Nachfolger rot aber h(left + 1) = " << left_height +1
				<< " != h(right) = " << right_height << std::endl;
			return - 1;
		}
		return right_height;
	}

	// beide schwarz
	if (!(node->getLeft()->getRed() && node->getRight()->getRed()))
	{
		if (left_height != right_height)
		{
			std::cout << "Fehler gefunden: beide Nachfolger shwarz aber Hoehe ungleich : " << left_height << " != " << right_height << std::endl;
			return - 1;
		}
		return left_height + 1;
	}

	
}

int Tree::proofRBCriterion() const
{
	return compute_height(anker);
}
