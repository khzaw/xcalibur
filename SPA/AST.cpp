#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <iterator>
#include "AST.h"
using namespace std;


AST::AST(){
}

TNode AST::createNode(string nodeT, string data, int s,int p){
TNode n(nodeT,data,s,p);
return n;
}

void AST::insertRoot(TNode *n){
root.push_back(n);
}

TNode*  AST::getRootNode(){
	return root[0];
}

 TNode* AST::assignChild(TNode *n, TNode *c){
	 n->addChild(c);
	 return n;
}

 TNode* AST::assignParent(TNode *n, TNode *p){
	 n->addParent(p);
	 	 return n;
}

 string AST::getTNodeType(TNode *n){
	return n->getNodeType();
}

string AST::getTNodeValue(TNode *n){
	return n->getData();
}

int AST::getTNodeStmtNum(TNode *n){
	return n->getStmtNum();
}

int AST::getTNodeProcedure(TNode *n){
	return n->getProcIndex();
}

TNode* AST::getTNodeParent(TNode *n){
	return n->getParent();
}

TNode* AST::getTNodeChild(TNode *n, int index){
	return n->getChild(index);
}

vector<TNode*> AST::getTNodeChildren(TNode *n){
	return n->getChildren();
}

bool AST::isNodeType(TNode *n,string s){
	return (n->getNodeType() == s);
}

bool AST::isNodeValue(TNode *n,string v){
	return (n->getData() == v);
}

bool AST::matchPattern(string nodeP,string queryP, int type ){
	
   istringstream stream( nodeP ); 
   istringstream stream2(queryP);
   // make a vector with each word of the text
   vector< string > nodePattern( (istream_iterator<string>( stream )),istream_iterator<string>() ); 
   vector< string > queryPattern( (istream_iterator<string>( stream2 )),istream_iterator<string>() ); 
   // type 1  (_"var"_)
   if(type == 1){
	   for(size_t i =0;i<nodePattern.size();i++){
		   if(nodePattern[i] ==queryPattern[0]){
			   return true;
		   }
	   }
	   return false;
   }// type 2 (_"var1 + var2"_)
   else{
	   for(size_t k=0;k<nodePattern.size();k++){
		   if(nodePattern[k] == queryPattern[0]){
			   //base case
			   if((k+2)>nodePattern.size()){
				   return false;
			   }else{
				   if(nodePattern[k+1] == queryPattern[1]){
					    if(nodePattern[k+2] == queryPattern[2]){
							return true;
						}else{
							continue;
						}
				   }else{
					   continue;
				   }
			   }
		   }
	   }
	   return false;
   }
}