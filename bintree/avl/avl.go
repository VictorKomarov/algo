package avl

import (
	"bintree/bst"
)

type AVl struct {
	core *bst.Tree
}

func NewAVL(tree *bst.Tree) *AVl {
	avl := &AVl{core: tree}

	//avl.build()

	return avl
}

func (a *AVl) Insert(key int, val interface{}) error {
	return nil
}

func (a *AVl) normalize(node *bst.Node) {
	if diffHeight(node) > 1 {

	}

	if node.Parent != nil {
		a.normalize(node.Parent)
	}
}

func diffHeight(node *bst.Node) int {
	height := func(node *bst.Node) int {
		if node != nil {
			return node.Height
		}
		return 0
	}

	return height(node.Left) - height(node.Right)
}

func (a *AVl) smallRightRotate(node *bst.Node) {
	right := node.Left.Right
	node.Left.Link(node, bst.Right)
	a.core.AdoptNodeInstead(node, node.Left)
	node.Link(right, bst.Left)
}

func (a *AVl) smallLeftRotate(node *bst.Node) {
	left := node.Right.Left
	node.Right.Link(node, bst.Left)
	a.core.AdoptNodeInstead(node, node.Right)
	node.Link(left, bst.Right)
}

func (a *AVl) bigLeftRotate(node *bst.Node) {
	a.smallRightRotate(node.Right)
	a.smallLeftRotate(node)
}

func (a *AVl) bigRightRotate(node *bst.Node) {
	a.smallLeftRotate(node.Left)
	a.smallRightRotate(node)
}
