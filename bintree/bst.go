package main

var ErrDuplicate = errors.New("key is duplicate")

type Node struct {
	Key         int
	Value       interface{}
	Relationship
}

type Relationship struct {
	Left *Node
	Right *Node
	Parent *Node
}

func NewNode(key int, val interface{}) *Node {
	return &Node{
		Key:   key,
		Value: val,
	}
}

// whar about Value ??
func (n *Node) Clone() &Node{
	return &Node{
		Key: n.Key,
		Value: n.Value,
		Right: n.Right,
		Left: n.Left,
		Parent: n.Parent,
	}
}

func Insert(root *Node, key int, val interface{}) error {
	if root == nil {
		return nil // return error is better strategy
	}

	if root.Key == key {
		return fmt.Errorf("%w %d == %d", ErrDuplicate, root.Key, key)
	}

	if key > root.Key {
		if root.Right != nil {
			Insert(root.Right, key, val)
		}

		root.Right = &Node{
			Key: key,
			Value: val,
			Parent: root,
		}
	} else {
		if root.Left != nil {
			Insert(root.Left, key, val)
		}

		root.Left = &Node{
			Key: key,
			Value: val,
			Parent: root
		}
	}
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

	return Search(node.Right, Key)
}

func Remove(node *Node, key int) {
	removed := Search(node, key)
	if removed == nil {
		return
	}

	parent := removed.Parent
	switch countNodeChilds(removed){
	case 0:
		if parent != nil {
			removed.RemoveChildByKey(removed.Key)
		}
	case 1:
		сhild := removed.Left
		if child == nil {
			child = removed.Right
		}

		if parent != nil {
			isLeft := parent.Left == removed

			if isLeft {
				parent.Left = child
			} else {
				parent.Right = child
			}

			child.Parent = parent
		} else { // case when we delete root
			node = child
			node.Parent = nil
		}
	case 2:		
		prev := prevElem(removed.Left) //always has nil right
		prevRel := prev.Relationship

		if prev == removed.Left {
			if parent != nil {
				prev.Right = removed.Right
				if removed.Right != nil { // to func
					removed.Right.Parent = prev
				}

				prev.Parent = parent
				isLeft := parent.Left == removed
				if isLeft {
					parent.Left = prev
				} else {
					parent.Right = prev
				}
			} else {
				// delete root think about this case
			}
		} else {
			if parent != nil {
				prevRel.Parent.Right = prevRel.Left
				prevRel.Left.Parent = prevRel.Parent //not nill check

				// only swap val and key ??
			}
		}
	}
}

func (n *Node) RemoveChildByKey(key int) {
	if n.Left != nil && n.Left.Key == key {
		n.Left = nil
	}

	if n.Right != nil && n.Right.Key == key {
		n.Right = nil
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
func prevElem(node *Node) *Node{
	if node.Right != nil {
		return prevElem(node.Right)
	}

	return node
}