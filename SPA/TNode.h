#include <cstddef>
#include <vector>

using namespace std;


class TNode {

private:

    string data;
	string nodeType;
	int procIndex;
	int stmtNum;
    TNode *parent;
    vector<TNode*> children;
	

public:
	//Constructor
	TNode();
    TNode(string, string,int,int);
	//Accessor for node
	string getData() ;
	int getStmtNum() ;
    int getProcIndex() ;
	string getNodeType() ;
	TNode* getChild(int) const;
    TNode* getParent() const;
	vector<TNode*> getChildren() const;
	int getNumChildren() const;
	//Mutator for node
    void setData(string data);
	void addParent(TNode* p);
    void addChild(TNode* c);
    //TNode<T>* findChild(const T& data) const;
};