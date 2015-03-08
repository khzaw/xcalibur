#pragma once

#include "GNode.h"

class CFG {
	public:
		
		
		CFG(shared_ptr<GNode> rootNode);
				
		bool setNext(shared_ptr<GNode> prev, shared_ptr<GNode> next);
		bool removeNext(shared_ptr<GNode> prev,shared_ptr<GNode> next);
		bool isRepeatRoute(shared_ptr<GNode> cur,shared_ptr<GNode> next);
				
		shared_ptr<GNode> root;
};
