#include "operationnode.h"

OperationNode::OperationNode()
{
}

void OperationNode::setName(QString n)
{
	name=n;
}

QString OperationNode::getName() const
{
	return name;
}

void OperationNode::accept(NodeVisitor& v)
{
	v.visit(this);
}
