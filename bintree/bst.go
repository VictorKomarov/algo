package main

type Node struct {
	key         int
	Value       interface{}
	Left, Right *Node
	Parent      *Node
}

func NewBST(key int, val interface{}) *Node {
	return &Node{
		Key:   key,
		Value: val,
	}
}

func (n *Node) Search(key int) bool {
	return search(n, key) != nil
}

func (n *Node) Insert(key int, val interface{}) {
	node := Node{key: key, Value: val}
	if n == nil { // very strange case
		n = &node
	} else {
		insert(n, node)
	}
}

func (n *Node) Remove(key int) {
	node := search(n, key)
	if node == nil {
		return
	}

	parent := node.Parent
	switch childsCount(node) {
	case 0:
		if node == n {
			n = nil
		} else {
			parent.removeByKey(node.key)
		}
	case 1:
		child := node.Right
		if node.Left != nil {
			child = node.Left
		}

		if node == n {
			n = node
			n.Parent = nil
		} else {
			parent.adoptGrandson(node, child)
		}
	case 2:

	}
}

func (n *Node) removeByKey(key int) {
	if n.Right != nil && n.Right.key == key {
		n.Right = nil
	}

	if n.Left != nil && n.Left.key == key {
		n.Left = nil
	}
}

func (n *Node) adoptGrandson(child, granChild *Node) {
	if n.Left == child {
		n.Left = granChild
	}

	if n.Right == child {
		n.Right = granChild
	}

	granChild.Parent = n
}

func childsCount(node *Node) int {
	if node.Left != nil && node.Right != nil {
		return 2
	}

	if node.Left == nil && node.Right == nil {
		return 0
	}

	return 1
}

func search(node *Node, key int) *Node {
	if node == nil {
		return nil
	}

	if node.key == key {
		return node
	}

	if node.key < key {
		return search(node.Right, key)
	}

	return search(node.Left, key)
}

func insert(parent *Node, node Node) {
	if node.key > parent.key {
		if parent.Right != nil {
			return insert(parent.Right, node)
		}
		node.Parent = parent
		parent.Right = &node

		return
	}

	if parent.Left != nil {
		return insert(parent.Left, node)
	}

	node.Parent = parent
	parent.Left = &node
}
