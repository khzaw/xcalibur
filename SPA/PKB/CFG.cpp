#include "CFG.h"

CFG::CFG(shared_ptr<GNode> rNode)
{
	root = rNode;
}

bool CFG::removeNext(shared_ptr<GNode> prev, shared_ptr<GNode> next)
{
	for(int i = 0; i < 2; i++)
	{
		if(prev->getNextArr()[i] == next)
		{
			prev->getNextArr()[i] = NULL;
		}
		if(next->getPrevArr()[i] == prev)
		{
			next->getPrevArr()[i] = NULL;
		}
	}
	return true;
}

bool CFG::setNext(shared_ptr<GNode> prev, shared_ptr<GNode> next) 
{
	bool result = false;

	if((prev->getNextArr()[0]  != NULL && prev->getNextArr()[1]  != NULL) || (next->getPrevArr()[0]  != NULL && next->getPrevArr()[1]  != NULL)){
		return result;
	}
	for(int n = 0; n <2; n++)
	{
		if(prev->getNextArr()[n] == NULL)
		{

			prev->setNextArr(n , next);
			result = true;
			break;
		}
	
	}

	for(int n = 0; n <sizeof(next->getPrevArr()); n++)
	{
		if(next->getPrevArr()[n] == NULL)
		{	
			next->setPrevArr(n , prev);
			result = true;
			break;
		}
		
	}
	return result;
}


