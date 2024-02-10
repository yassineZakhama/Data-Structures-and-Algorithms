#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>
#include <queue>

using namespace std;

class Tree
{
private:
    TreeNode* anker;
    int currentNodeChronologicalID;

    bool split4Node(TreeNode* node);
    void right_rotate(TreeNode* node);
    void left_rotate(TreeNode* node);
    TreeNode* balance(TreeNode* node, std::string verletzungsart);
    std::string verletzung_art(TreeNode* node);

    bool searchNode(int nodeOrderID, TreeNode*& del_node, TreeNode*& parent_del_node);

    int compute_height(TreeNode* node) const;

public:
    Tree() : anker{ nullptr }, currentNodeChronologicalID{ 0 } {  }
    ~Tree();

    void addNode(std::string name, int age, double income, int postCode);

    bool searchNode(std::string name);
    
    int proofRBCriterion() const;

    void printAllPreorder();
    void preorder(TreeNode* p);
    void levelOrder() const;
    void printLevelOrder() const;
    void printLevelOrder(int niveau) const;
    void printAll();

    friend TreeNode* get_anker(Tree& TN);
};
