package treap

import (
	"math/rand"
	"time"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

type Node struct {
	Key, Priority int
	Value         interface{}
	Left, Right   *Node
}

//nolint:gosec
func NewNode(key int, value interface{}) *Node {
	return &Node{
		Key:      key,
		Value:    value,
		Priority: rand.Int(),
	}
}

type Tree struct {
	root *Node
}

func New() *Tree {
	return &Tree{}
}

func split(root *Node, key int) (*Node, *Node) {
	if root == nil {
		return nil, nil
	}

	var other *Node
	if key > root.Key {
		root.Right, other = split(root.Right, key)

		return root, other
	}

	other, root.Left = split(root.Left, key)

	return other, root
}

func merge(less, more *Node) *Node {
	if less == nil {
		return more
	}

	if more == nil {
		return less
	}

	if less.Priority > more.Priority {
		less.Right = merge(less.Right, more)

		return less
	}

	more.Left = merge(less, more.Left)

	return more
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

func (t *Tree) Insert(inserted *Node) {
	if t.root == nil {
		t.root = inserted

		return
	}

	less, other := split(t.root, inserted.Key)
	if other != nil && other.Key == inserted.Key {
		return
	}

	t.root = merge(merge(less, inserted), other)
}

func (t *Tree) Remove(key int) {
	less, other := split(t.root, key)
	if other != nil && other.Key == key {
		other = merge(other.Left, other.Right)
	}

	t.root = merge(less, other)
}
