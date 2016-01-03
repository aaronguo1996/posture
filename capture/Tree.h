/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once

#ifndef TREE_H
#define	TREE_H

#include <vector>

#include "pxcsensemanager.h"

template <class T>
class Node
{
public:
	Node(T nodeValue);
	Node();
	void add(Node<T> node);
	T getNodeValue();
	std::vector<Node<T>> getChildNodes();
	~Node();
private:
	T m_nodeValue;
	std::vector<Node<T>> m_nodes;
};

template <class T>
class Tree
{
public:
	Tree(Node<T> rootNode);
	Tree();
	void setRoot(Node<T> rootNode);
	Node<T> getRoot();
	~Tree();

private:
	Node<T> m_root;
};




#endif	/* TREE_H */