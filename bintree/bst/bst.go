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
	Key                 int
	Value               interface{}
	Height              int
	Left, Right, Parent *Node
}

type Tree struct {
	Root *Node
}

func NewBST() *Tree {
	return &Tree{}
}

func NewNode(key int, val interface{}, parent *Node) *Node {
	return &Node{
		Key:    key,
		Value:  val,
		Height: 1,
		Parent: parent,
	}
}

func (b *Tree) WalkInorder(f func(node *Node)) {
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

func (b *Tree) Insert(key int, val interface{}) error {
	if b.Root == nil {
		b.Root = NewNode(key, val, nil)

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

		node.Right = NewNode(key, val, node)
	} else {
		if node.Left != nil {
			return insert(node.Left, key, val)
		}

		node.Left = NewNode(key, val, node)
	}

	return nil
}

func (b *Tree) Search(key int) bool {
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

func (b *Tree) Remove(key int) {
	removed := search(b.Root, key)
	if removed == nil {
		return
	}

	switch countNodeChilds(removed) {
	case 0:
		b.AdoptNodeInstead(removed, nil)
	case 1:
		сhild := removed.Left
		if сhild == nil {
			сhild = removed.Right
		}

		b.AdoptNodeInstead(removed, сhild)
	case 2:
		prev := prevElem(removed.Left)
		if removed.Left != prev {
			removed.Left.Link(prev.Left, Right)
			prev.Link(removed.Left, Left)
		}

		prev.Link(removed.Right, Right)

		b.AdoptNodeInstead(removed, prev)
	}
}

func (b *Tree) AdoptNodeInstead(removed, node *Node) {
	parent := removed.Parent

	if node != nil {
		node.Parent = parent
	}

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

func (n *Node) Link(child *Node, direction Direction) {
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
