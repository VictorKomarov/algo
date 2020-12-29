package bst

import (
	"errors"
	"fmt"
)

var ErrDuplicate = errors.New("key is duplicate")

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
		} else {

			if parent.Left == removed {
				parent.Left = nil
			}

			if parent.Right == removed {
				parent.Right = nil
			}
		}
	case 1:
		сhild := removed.Left
		if сhild == nil {
			сhild = removed.Right
		}

		b.adoptNodeInstead(removed.Parent, removed, сhild)
	case 2:
		prev := prevElem(removed.Left)
		prevRel := prev.Relationship
		isRight := removed.Left != prev

		b.adoptNodeInstead(removed.Parent, removed, prev)
		prev.Right = removed.Right
		removed.Right.Parent = prev

		prev.Left = removed.Left
		removed.Left.Parent = prev

		if isRight {
			removed.Left.Right = prevRel.Left
			if prevRel.Left != nil {
				prevRel.Left.Parent = removed.Left
			}
		}
	}
}

func (b *BST) adoptNodeInstead(parent, removed, node *Node) {
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
