package bst

import (
	"errors"
	"fmt"
)

var ErrDuplicate = errors.New("key is duplicate")

type Direction string

const (
	Left  Direction = "LEFT"
	Right Direction = "RIGHT"
)

type Node struct {
	Key   int
	Value interface{}
	Relationship
}

type Relationship struct {
	Left   *Node
	Right  *Node
	Parent *Node
}

type BST struct {
	Root *Node
	//size ...
}

func NewBST() *BST {
	return &BST{}
}

func NewNode(key int, val interface{}) *Node {
	return &Node{
		Key:   key,
		Value: val,
	}
}

func (b *BST) WalkInorder(f func(node *Node)) {
	if b.Root != nil {
		walkInorder(b.Root, f)
	}
}

func walkInorder(node *Node, f func(node *Node)) {
	if node.Left != nil {
		walkInorder(node.Left, f)
	}

	f(node)

	if node.Right != nil {
		walkInorder(node.Right, f)
	}
}

func (b *BST) Insert(key int, val interface{}) error {
	if b.Root == nil {
		b.Root = NewNode(key, val)

		return nil
	}

	return insert(b.Root, key, val)
}

func insert(node *Node, key int, val interface{}) error {
	if node.Key == key {
		return fmt.Errorf("%w %d == %d", ErrDuplicate, node.Key, key)
	}

	if key > node.Key {
		if node.Right != nil {
			return insert(node.Right, key, val)
		}

		node.Right = &Node{
			Key:   key,
			Value: val,
			Relationship: Relationship{
				Parent: node,
			},
		}
	} else {
		if node.Left != nil {
			return insert(node.Left, key, val)
		}

		node.Left = &Node{
			Key:   key,
			Value: val,
			Relationship: Relationship{
				Parent: node,
			},
		}
	}

	return nil
}

func (b *BST) Search(key int) bool {
	return search(b.Root, key) != nil
}

func search(node *Node, key int) *Node {
	if node == nil {
		return nil
	}

	if node.Key == key {
		return node
	}

	if node.Key > key {
		return search(node.Left, key)
	}

	return search(node.Right, key)
}

func (b *BST) Remove(key int) {
	removed := search(b.Root, key)
	if removed == nil {
		return
	}

	switch countNodeChilds(removed) {
	case 0:
		parent := removed.Parent
		if parent == nil {
			b.Root = nil
			return
		}

		if parent.Left == removed {
			parent.Left = nil
		}

		if parent.Right == removed {
			parent.Right = nil
		}
	case 1:
		сhild := removed.Left
		if сhild == nil {
			сhild = removed.Right
		}

		b.adoptNodeInstead(removed, сhild)
	case 2:
		prev := prevElem(removed.Left)
		if removed.Left != prev {
			removed.Left.link(prev.Left, Right)
			prev.link(removed.Left, Left)
		}

		prev.link(removed.Right, Right)

		b.adoptNodeInstead(removed, prev)
	}
}

func (b *BST) adoptNodeInstead(removed, node *Node) {
	parent := removed.Parent
	node.Parent = parent

	if parent == nil {
		b.Root = node
		return
	}

	if parent.Left == removed {
		parent.Left = node
	}

	if parent.Right == removed {
		parent.Right = node
	}
}

func (n *Node) link(child *Node, direction Direction) {
	switch direction {
	case Left:
		n.Left = child
	case Right:
		n.Right = child
	default:
		return
	}

	if child != nil {
		child.Parent = n
	}
}

func countNodeChilds(node *Node) int {
	if node == nil {
		return 0
	}

	if node.Left != nil && node.Right != nil {
		return 2
	}

	if node.Left != nil || node.Right != nil {
		return 1
	}

	return 0
}

//TODO::change this func for node without child
func prevElem(node *Node) *Node {
	if node.Right != nil {
		return prevElem(node.Right)
	}

	return node
}
