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

func (b *Tree) Insert(key int, val interface{}) (*Node, error) {
	if b.Root == nil {
		b.Root = NewNode(key, val, nil)

		return b.Root, nil
	}

	return insert(b.Root, key, val)
}

func insert(node *Node, key int, val interface{}) (*Node, error) {
	if node.Key == key {
		return nil, fmt.Errorf("%w %d == %d", ErrDuplicate, node.Key, key)
	}

	if key > node.Key {
		if node.Right != nil {
			return insert(node.Right, key, val)
		}
		node.Right = NewNode(key, val, node)

		return node.Right, nil
	}

	if node.Left != nil {
		return insert(node.Left, key, val)
	}
	node.Left = NewNode(key, val, node)

	return node.Left, nil
}

func (b *Tree) Contain(key int) bool {
	return Search(b.Root, key) != nil
}

func Search(node *Node, key int) *Node {
	if node == nil {
		return nil
	}

	if node.Key == key {
		return node
	}

	if node.Key > key {
		return Search(node.Left, key)
	}

	return Search(node.Right, key)
}

//return Node for rebalance strategy
func (b *Tree) Remove(key int) *Node {
	removed := Search(b.Root, key)
	if removed == nil {
		return nil
	}

	switch countNodeChilds(removed) {
	case 0:
		b.AdoptNodeInstead(removed, nil)

		return removed.Parent
	case 1:
		сhild := removed.Left
		if сhild == nil {
			сhild = removed.Right
		}

		b.AdoptNodeInstead(removed, сhild)

		return сhild
	case 2:
		prev := prevElem(removed.Left)
		if removed.Left != prev {
			removed.Left.Link(prev.Left, Right)
			prev.Link(removed.Left, Left)
		}

		prev.Link(removed.Right, Right)

		b.AdoptNodeInstead(removed, prev)

		return prev
	default:
		return nil
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
