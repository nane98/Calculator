#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

struct Node
{
    char operation;
    Node* left;
    Node* right;
    double result;
    Node()
    {
    }
    ~Node()
    {
        if(left)
        {
            delete left;
        }
        if(right)
        {
            delete right;
        }
    }
};
class Calc
{
public: 
    Calc()
    {
        root = new Node;
    }
    ~Calc()
    {
        if(root)
        {
            deleteTree(root);
        }
    }
    double calculate(std::string input)
    {
        return makeTree_(root, input);
    }
private:
    Node* root;
    void deleteTree(Node * current)
    {
        if(current->left)
        {
            deleteTree(current->left);
        }
        if(current->right)
        {
            deleteTree(current->right);
        }
        delete current;
        current = nullptr;
    }
    int jumpBrackets(const std::string & input, int i, bool r = false)
    {
        int closed = 0, opened  = 0;
        if(r)
        {
            while(i >= 0 )
            {
                if(input[i] == ')')
                {
                    ++closed;
                }
                if(input[i] == '(')
                {
                    ++opened;
                    if(opened == closed)
                    {
                        --i;
                        break;
                    }
                }
                --i;
            }
        }
        else
        {
            while(i < input.length() )
            {
                if(input[i] == '(')
                {
                    ++opened;
                }
                if(input[i] == ')')
                {
                    ++closed;
                    if(opened == closed)
                    {
                        ++i;
                        break;
                    }
                }
                ++i;
            }
        
        }
        return i;
    }
    int hasBrackets(const std::string & input, bool r = false)
    {
        if (r)
        {
            for(int i = input.length()-1; i >= 0; --i)
            {
                if(input[i] == ')')
                {
                    return i;
                }
            }
            return -1;
        }
        else
        {
            for(int i = 0; i < input.length(); ++i)
            {
                if(input[i] == '(')
                {
                    return i;
                }
            }
            return -1;
        }
        return -1;
    }
    int hasOperator(const std::string & input, char op1, char op2)
    {
        if (op1 == '+' || op1 == '*')
        {
            int i = input.length()-1;
            int br_index = 0; 
            while(i >= 0)
            {
                if(input[i] == ')')
                {
                    i = jumpBrackets(input, i, true);
                }
                if(i >= 0 && (input[i] == op1 || input[i] == op2))
                {
                    return i;
                }
                --i;
            }
        }
        else
        {
            int i = 0;
            int br_index = 0;
            while(i < input.length())
            {
                if(input[i] == '(')
                {
                    i = jumpBrackets(input, i, false);
                }
                if(i >= 0 && (input[i] == op1 || input[i] == op2))
                {
                    return i;
                }
                ++i;
            }
        }
        return -1;        
    }
    double makeTree_(Node* current, std::string input)
    {
        double result;
        std::string part1;
        std::string part2;
        int i = input.length() - 1;
        int j = 0;
        int k = 0;
        if(input[0] == '(' && input[input.length()-1] == ')')
        {
            k = jumpBrackets(input, k, false);
        }
        if(k == input.length())
        {
            if(!current)
            {
                current = new Node;
            }
            makeTree_(current, input.substr(1, i-1));
        }
        else
        {
            j = hasOperator(input, '+', '-');
            if(j == -1)
            {
                j = hasOperator(input, '*', '/');
            }
            if(j > 0)
            {
                part2 = input.substr(j+1, input.length()-j);
                part1 = input.substr(0, j);
                current->operation = input[j];
                current->left = new Node;
                current->right = new Node;
                double d1 = makeTree_(current->left, part1);
                double d2 = makeTree_(current->right, part2);
                switch (current->operation)
                {
                    case '+':
                        result = d1+d2;
                        break;
                    case '-':
                        result = d1-d2;
                        break;
                    case '*':
                        result = d1*d2;
                        break;
                    case '/':
                        result = d1/d2;
                        break;
                    default :
                        break;
                }                
                return result;
            }
            else
            {

                result = atoi(input.c_str());
                return result;
            }
        }
    }

};
int main()
{
    std::string input;    
    std::cout << "Enter expression: ";
    std::cin >> input;
    Calc obj;
    std::cout << "Res: " << obj.calculate(input) << std::endl;

return 0;
}
