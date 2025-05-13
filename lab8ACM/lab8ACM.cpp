// lab8ACM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Node
{
    public:
        int data;
        Node* leftChild;
        Node* rightChild;

        Node(int data) : data(data), leftChild(nullptr), rightChild(nullptr) {};
};

class BinaryTree
{
    private:
        Node* root;
    
    public:
        BinaryTree() : root(nullptr) {};

        BinaryTree(int data) : root(nullptr) 
        {
            root = new Node(data);
        };

        void handleNoRightChild(Node*& node)
        {
            Node* leftChild = node->leftChild;

            if (leftChild == nullptr)
            {
                node = nullptr;
                return;
            }

            node->data = leftChild->data;
            node->leftChild = leftChild->leftChild;
            node->rightChild = leftChild->rightChild;

            delete node->leftChild;
        };

        void handleRightChild(Node*& node)
        {
            Node** min = &node->rightChild;

            while ((*min)->leftChild != nullptr)
            {
                min = &((*min)->leftChild);
            }

            node->data = (*min)->data;

            if ((*min)->rightChild == nullptr)
            {
                *min = nullptr;
                return;
            }

            (*min)->data = (*min)->rightChild->data;
            (*min)->rightChild = (*min)->rightChild->rightChild;
            delete (*min)->rightChild;
        };

        void inorderTraversal(Node* node)
        {
            if (node == nullptr)
            {
                return;
            }

            inorderTraversal(node->leftChild);

            std::cout << (*node).data << " "; // <=> node->data

            inorderTraversal(node->rightChild);
        };

        void inorderTraversal() 
        {
            inorderTraversal(root);
        };

        //Node* insert(Node*& localRoot, int data)
        //{
        //    if (localRoot == nullptr)
        //    {
        //        return createNode(data);
        //    }

        //    if (data < localRoot->data)
        //    {
        //        insert(localRoot->leftChild, data);
        //    }
        //    else
        //    {
        //        insert(localRoot->rightChild, data);
        //    }

        //    return root;
        //}

        void insert(int data)
        {
            Node* newNode = new Node(data);

            if (root == nullptr)
            {
                root = newNode;
                return;
            }

            Node* current = root;

            while (true)
            {
                if (data < current->data)
                {
                    if (current->leftChild == nullptr)
                    {
                        current->leftChild = newNode;
                        return;
                    }

                    current = current->leftChild;
                }
                else
                {
                    if (current->rightChild == nullptr)
                    {
                        current->rightChild = newNode;
                        return;
                    }

                    current = current->rightChild;
                }
            }
        }

        Node*& findNode(Node*& localRoot, int value)
        {
            if (localRoot == nullptr || localRoot->data == value)
            {
                return localRoot;
            }

            if (value < localRoot->data)
            {
                return findNode(localRoot->leftChild, value);
            }
            else
            {
                return findNode(localRoot->rightChild, value);
            }
        }

        Node*& findNode(int value)
        {
            return findNode(root, value);
        }

        void deleteNode(Node*& node)
        {
            if (node->rightChild == nullptr)
            {
                handleNoRightChild(node);
            }
            else
            {
                handleRightChild(node);
            }
        }

        void deleteNode(int value)
        {
            Node*& node = findNode(value);

            if (node == nullptr)
            {
                return;
            }

            deleteNode(findNode(value));
        }

        // n * logn, but with space complexity O(1)
        void performTask(Node*& node)
        {
            if (node == nullptr)
            {
                return;
            }

            if (node->data % 2 == 0)
            {
                deleteNode(node);
                performTask(node);
                return;
            }

            performTask(node->leftChild);
            performTask(node->rightChild);
        }

        void performTask()
        {
            performTask(root);
        }
};

int main()
{
    BinaryTree tree(4);

    //tree.insert(13);
    //tree.insert(14);
    tree.insert(7);  
    tree.insert(8);  
    tree.insert(1);  
    tree.insert(3);  
    tree.insert(5);  
    tree.insert(2);  
    tree.insert(10); 
    tree.insert(9);  
    tree.insert(11); 
    tree.insert(12); 

    //tree.deleteNode(2);

    //tree.root;
    tree.performTask();

    tree.inorderTraversal();
};