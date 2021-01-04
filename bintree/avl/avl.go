package avl

import (
	"bintree/bst"
)

type AVl struct {
	core *bst.Tree
}

func NewAVL() *AVl {
	avl := &AVl{
		core: bst.NewBST(),
	}

	// avl.init()

	return avl
}

func (a *AVl) Contain(key int) bool {
	return a.core.Contain(key)
}

func (a *AVl) Insert(key int, val interface{}) error {
	inserted, err := a.core.Insert(key, val)
	if err != nil {
		return err
	}

	a.normalize(inserted.Parent)
	return nil
}

func (a *AVl) normalize(node *bst.Node) {
	if node == nil {
		return
	}

	fixHeight(node)
	next := node.Parent
	a.balance(node)

	a.normalize(next)
}

func (a *AVl) balance(node *bst.Node) {
	switch diffHeight(node) {
	case 2:
		if node.Right != nil && height(node.Right.Left) > height(node.Right.Right) {
			a.smallLeftRotate(node)
		} else {
			a.bigLeftRotate(node)
		}
	case -2:
		//if node.Left != nil && height(node.Left.Right) > height(node.Left.Left) {
		a.smallRightRotate(node)
		//} else {
		//a.bigRightRotate(node)
		//}
	default:
		return
	}
}

func (a *AVl) smallRightRotate(node *bst.Node) {
	a.core.AdoptNodeInstead(node, node.Left)
	right := node.Left.Right
	node.Left.Link(node, bst.Right)
	node.Link(right, bst.Left)
	fixHeight(node)
	fixHeight(right)
}

func (a *AVl) smallLeftRotate(node *bst.Node) {
	a.core.AdoptNodeInstead(node, node.Right)
	left := node.Right.Left
	node.Right.Link(node, bst.Left)
	node.Link(left, bst.Right)
	fixHeight(node)
	fixHeight(left)
}

func (a *AVl) bigLeftRotate(node *bst.Node) {
	a.smallRightRotate(node.Right)
	a.smallLeftRotate(node)
}

func (a *AVl) bigRightRotate(node *bst.Node) {
	a.smallLeftRotate(node.Left)
	a.smallRightRotate(node)
}

func (a *AVl) init() {
	nodes := make([]*bst.Node, 0)

	a.core.WalkInorder(func(node *bst.Node) {
		nodes = append(nodes, node)
	})

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
	return height(node.Right) - height(node.Left)
}
