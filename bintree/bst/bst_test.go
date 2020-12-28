package bst

import (
	"testing"

	"github.com/stretchr/testify/require"
)

func TestInsert(t *testing.T) {
	cases := []struct {
		Name     string
		Steps    []int
		Expected []int
	}{
		{
			Name:     "Only Root",
			Steps:    []int{0},
			Expected: []int{0},
		},
		{
			Name:     "Simple InOrder",
			Steps:    []int{4, 2, 6, 1, 3},
			Expected: []int{1, 2, 3, 4, 6},
		},
	}

	for _, tCase := range cases {
		actual := make([]int, 0, len(tCase.Expected))
		bst := NewBST()

		for _, key := range tCase.Steps {
			bst.Insert(key, key)
		}

		bst.WalkInorder(func(node *Node) {
			val := node.Value.(int)
			actual = append(actual, val)
		})

		require.Equal(t, tCase.Expected, actual, tCase)
	}
}
