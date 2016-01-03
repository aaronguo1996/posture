#include "Tree.h"

Node<PXCHandData::JointData>::Node(PXCHandData::JointData jointData)
{
	m_nodeValue = jointData;
}
//===========================================================================//

Node<PXCHandData::JointData>::Node() {}

//===========================================================================//

Node<PXCHandData::JointData>::~Node() {}

//===========================================================================//

void Node<PXCHandData::JointData>::add(Node<PXCHandData::JointData> node)
{
	m_nodes.push_back(node);
}

//===========================================================================//

PXCHandData::JointData Node<PXCHandData::JointData>::getNodeValue()
{
	return m_nodeValue;
}

//===========================================================================//

std::vector<Node<PXCHandData::JointData>> Node<PXCHandData::JointData>::getChildNodes()
{
	return m_nodes;
}

//===========================================================================//

Tree<PXCHandData::JointData>::Tree(Node<PXCHandData::JointData> rootNode)
{
	m_root = rootNode;
}

//===========================================================================//

void Tree<PXCHandData::JointData>::setRoot(Node<PXCHandData::JointData> rootNode)
{
	m_root = rootNode;
}

//===========================================================================//

Node<PXCHandData::JointData> Tree<PXCHandData::JointData>::getRoot()
{
	return m_root;
}

//===========================================================================//

Tree<PXCHandData::JointData>::Tree() {}

//===========================================================================//

Tree<PXCHandData::JointData>::~Tree() {}