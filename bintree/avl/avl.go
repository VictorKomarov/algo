package avl

import (
	"bintree/bst"
)

type Tree struct {
	core *bst.Tree
}

func New(core *bst.Tree) *Tree {
	avl := &Tree{
		core: core,
	}

	avl.init()
	return avl
}

func (a *Tree) Contain(key int) bool {
	return a.core.Contain(key)
}

func (a *Tree) Search(key int) *bst.Node {
	return bst.Search(a.core.Root, key)
}

func (a *Tree) Remove(key int) {
	a.normalize(a.core.Remove(key))
}

func (a *Tree) Insert(key int, val interface{}) error {
	inserted, err := a.core.Insert(key, val)
	if err != nil {
		return err
	}

	a.normalize(inserted.Parent)
	return nil
}

func (a *Tree) normalize(node *bst.Node) {
	if node == nil {
		return
	}

	next := node.Parent
	fixHeight(node)
	a.balance(node)

	a.normalize(next)
}

func (a *Tree) balance(node *bst.Node) {
	switch diffHeight(node) {
	case -2:
		if diffHeight(node.Right) > 0 {
			a.bigLeftRotate(node)
		} else {
			a.smallLeftRotate(node)
		}
	case 2:
		if diffHeight(node.Left) < 0 {
			a.bigRightRotate(node)
		} else {
			a.smallRightRotate(node)
		}
	default:
		return
	}
}

func (a *Tree) smallRightRotate(node *bst.Node) {
	right := node.Left.Right
	needToRecalculate := []*bst.Node{node, right, node.Left}

	a.core.AdoptNodeInstead(node, node.Left)
	node.Left.Link(node, bst.Right)
	node.Link(right, bst.Left)

	for _, node := range needToRecalculate {
		fixHeight(node)
	}
}

func (a *Tree) smallLeftRotate(node *bst.Node) {
	left := node.Right.Left
	needToRecalculate := []*bst.Node{node, left, node.Right}

	a.core.AdoptNodeInstead(node, node.Right)
	node.Right.Link(node, bst.Left)
	node.Link(left, bst.Right)

	for _, node := range needToRecalculate {
		fixHeight(node)
	}
}

func (a *Tree) bigLeftRotate(node *bst.Node) {
	a.smallRightRotate(node.Right)
	a.smallLeftRotate(node)
}

func (a *Tree) bigRightRotate(node *bst.Node) {
	a.smallLeftRotate(node.Left)
	a.smallRightRotate(node)
}

func (a *Tree) init() {
	nodes := make([]*bst.Node, 0)

	a.core.WalkInorder(func(node *bst.Node) {
		nodes = append(nodes, node)
	})

	a.core.Root = nil
	for i := range nodes {
		a.Insert(nodes[i].Key, nodes[i].Value)
	}
}

func height(node *bst.Node) int {
	if node != nil {
		return node.Height
	}
	return 0
}

func fixHeight(node *bst.Node) {
	if node == nil {
		return
	}

	node.Height = 1
	if height(node.Left) > height(node.Right) {
		node.Height += height(node.Left)
	} else {
		node.Height += height(node.Right)
	}
}

func diffHeight(node *bst.Node) int {
	if node == nil {
		return 0
	}

	return height(node.Left) - height(node.Right)
}
