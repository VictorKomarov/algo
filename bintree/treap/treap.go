package treap

type Node struct {
	Key, Priority int
	Value         interface{}
	Left, Right   *Node
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
