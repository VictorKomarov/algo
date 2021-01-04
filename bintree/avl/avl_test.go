package avl

import (
	"bintree/bst"
	"testing"

	"github.com/stretchr/testify/require"
)

func TestSmallLeftRotate(t *testing.T) {
	testCases := []struct {
		desc        string
		steps       []int
		rotatedFrom int
		expected    []int
	}{
		{
			desc:        "small left rotate#1",
			steps:       []int{6, 4, 8, 7, 11},
			rotatedFrom: 8,
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

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
	}

	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			a := NewAVL()

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
