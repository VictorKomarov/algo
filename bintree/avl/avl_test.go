package avl

import (
	"bintree/bst"
	"testing"

	"github.com/stretchr/testify/require"
)

func TestRotate(t *testing.T) {
	testCases := []struct {
		desc        string
		steps       []int
		rotatedFrom int
		expected    []int
	}{
		{
			desc:        "SmallLeftRotate",
			steps:       []int{6, 4, 8, 7, 11},
			rotatedFrom: 6,
			expected:    []int{4, 6, 7, 8, 11},
		},
		{
			desc:        "BigLeftRotate",
			steps:       []int{4, 2, 8, 6, 11, 5, 7},
			rotatedFrom: 4,
			expected:    []int{2, 4, 5, 6, 7, 8, 11},
		},
		{
			desc:        "SmallRightRotate",
			steps:       []int{6, 4, 8, 2, 5},
			rotatedFrom: 6,
			expected:    []int{2, 4, 5, 6, 8},
		},
		{
			desc:        "BigRightRotate",
			steps:       []int{10, 6, 12, 2, 8, 7, 9},
			rotatedFrom: 10,
			expected:    []int{2, 6, 7, 8, 9, 10, 12},
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			b := bst.NewBST()

			for _, key := range tC.steps {
				b.Insert(key, key)
			}

			node := bst.Search(b.Root, tC.rotatedFrom)

			a := Tree{core: b}
			switch tC.desc {
			case "SmallLeftRotate":
				a.smallLeftRotate(node)
			case "BigLeftRotate":
				a.bigLeftRotate(node)
			case "SmallRightRotate":
				a.smallRightRotate(node)
			case "BigRightRotate":
				a.bigRightRotate(node)
			}

			actual := make([]int, 0, len(tC.expected))
			b.WalkInorder(func(node *bst.Node) {
				actual = append(actual, node.Key)
			})

			require.Equal(t, tC.expected, actual, tC.desc)
		})
	}
}

func TestAVLInsert(t *testing.T) {
	type Node struct {
		Key    int
		Height int
	}

	testCases := []struct {
		desc     string
		steps    []int
		expected []Node
	}{
		{
			desc:     "One node",
			steps:    []int{5},
			expected: []Node{{5, 1}},
		},
		{
			desc:     "No rebalance",
			steps:    []int{6, 4, 10},
			expected: []Node{{4, 1}, {6, 2}, {10, 1}},
		},
		{
			desc:     "Limit case for no rebalance",
			steps:    []int{8, 6, 10, 4, 9, 7, 12},
			expected: []Node{{4, 1}, {6, 2}, {7, 1}, {8, 3}, {9, 1}, {10, 2}, {12, 1}},
		},
		{
			desc:     "Simple rebalance leaf",
			steps:    []int{8, 6, 10, 4, 9, 12, 7, 2, 1},
			expected: []Node{{1, 1}, {2, 2}, {4, 1}, {6, 3}, {7, 1}, {8, 4}, {9, 1}, {10, 2}, {12, 1}},
		},
		{
			desc:     "Big rotate rebalance leaf",
			steps:    []int{8, 6, 10, 4, 9, 12, 7, 2, 1, 5},
			expected: []Node{{1, 1}, {2, 2}, {4, 3}, {5, 1}, {6, 2}, {7, 1}, {8, 4}, {9, 1}, {10, 2}, {12, 1}},
		},
		{
			desc:     "Small left rebalance leaf",
			steps:    []int{8, 6, 10, 4, 9, 12, 7, 2, 1, 5, 13, 14},
			expected: []Node{{1, 1}, {2, 2}, {4, 3}, {5, 1}, {6, 2}, {7, 1}, {8, 4}, {9, 1}, {10, 3}, {12, 1}, {13, 2}, {14, 1}},
		},
		{
			desc:     "Linear test",
			steps:    []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
			expected: []Node{{1, 1}, {2, 2}, {3, 1}, {4, 4}, {5, 1}, {6, 2}, {7, 1}, {8, 3}, {9, 2}, {10, 1}},
		},
	}

	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			a := New(bst.NewBST())

			for _, key := range tC.steps {
				a.Insert(key, key)
			}

			actual := make([]Node, 0, len(tC.expected))
			a.core.WalkInorder(func(node *bst.Node) {
				actual = append(actual, Node{node.Key, node.Height})
			})

			require.Equal(t, tC.expected, actual, tC.desc)
		})
	}
}

func TestSimpleInitTest(t *testing.T) {
	type Node struct {
		Key    int
		Height int
	}

	b := bst.NewBST()
	for _, key := range []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10} {
		b.Insert(key, key)
	}

	avl := New(b)

	actual := make([]Node, 0, 10)
	avl.core.WalkInorder(func(node *bst.Node) {
		actual = append(actual, Node{node.Key, node.Height})
	})

	require.Equal(t, []Node{{1, 1}, {2, 2}, {3, 1}, {4, 4}, {5, 1}, {6, 2}, {7, 1}, {8, 3}, {9, 2}, {10, 1}}, actual, "init test")
}

func TestRemove(t *testing.T) {
	type Node struct {
		Key    int
		Height int
	}

	testCases := []struct {
		desc     string
		steps    []int
		removed  int
		expected []Node
	}{
		{
			desc:     "Remove root",
			steps:    []int{10},
			removed:  10,
			expected: []Node{},
		},
		{
			desc:     "No remove",
			steps:    []int{10},
			removed:  7,
			expected: []Node{{10, 1}},
		},
		{
			desc:     "Remove left leaf",
			steps:    []int{6, 4, 10},
			removed:  10,
			expected: []Node{{4, 1}, {6, 2}},
		},
		{
			desc:     "Remove right leaf",
			steps:    []int{6, 4, 10},
			removed:  4,
			expected: []Node{{6, 2}, {10, 1}},
		},
		{
			desc:     "No rebalance with one child",
			steps:    []int{4, 2, 5, 3},
			removed:  2,
			expected: []Node{{3, 1}, {4, 2}, {5, 1}},
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			avl := New(bst.NewBST())
			for _, key := range tC.steps {
				avl.Insert(key, key)
			}

			avl.Remove(tC.removed)

			actual := make([]Node, 0, len(tC.expected))
			avl.core.WalkInorder(func(node *bst.Node) {
				actual = append(actual, Node{node.Key, node.Height})
			})

			require.Equal(t, tC.expected, actual, tC.desc)
		})
	}
}
