#pragma once
#include <string>

using namespace std;

class TreeNode
{
private:
    int nodeOrderID;
    int nodeChronologicalID;
    std::string name;
    int age;
    double income;
    int postCode;

    bool red;

    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode(int _nodeOrderID, int _nodeChronologicalID, std::string _name, int _age, double _income, int _postCode)
        : nodeOrderID{ _nodeOrderID }, nodeChronologicalID{ _nodeChronologicalID }, name{ _name }, age{ _age }, income{ _income }, postCode{ _postCode }
    {
        parent = left = right = nullptr;
        red = true;
    }

    int getNodeOrderID() const { return nodeOrderID; }
    void setNodeOrderID(int _nodeOrderID) { nodeOrderID = _nodeOrderID; }

    int getNodeChronologicalID() const { return nodeChronologicalID; }
    void setNodeChronologicalID(int _nodeChronologicalID) { nodeChronologicalID = _nodeChronologicalID; }

    std::string getName() const { return name; }
    void setName(std::string _name) { name = _name; }

    int getAge() const { return age; }
    void setAge(int _age) { age = _age; }

    double getIncome() const { return income; }
    void setIncome(double _income) { income = _income; }

    int getPostCode() const { return postCode; }
    void setPostCode(int _postCode) { postCode = _postCode; }

    TreeNode* getLeft() const { return left; }
    void setLeft(TreeNode* _left) { left = _left; }

    TreeNode* getRight() const { return right; }
    void setRight(TreeNode* _right) { right = _right; }

    TreeNode* getParent() const { return parent; }
    void setParent(TreeNode* _parent) { parent = _parent; }

    bool getRed() const { return red; }
    void setRed(bool b) { red = b; }
};
