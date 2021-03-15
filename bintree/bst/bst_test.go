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
		{
			Name:     "Delete duplicate key",
			Steps:    []int{5, 2, 5, 2, 6, 6, 6, 5, 7, 2, 1, 5, 1, 4, 3},
			Expected: []int{1, 2, 3, 4, 5, 6, 7},
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

func TestSearch(t *testing.T) {
	cases := []struct { // i think it better to add count of call search for bench
		Name     string
		Inserted []int
		Find     int
		Expected bool
	}{
		{
			Name:     "Empty bst",
			Find:     5,
			Expected: false,
		},
		{
			Name:     "Search root",
			Inserted: []int{5},
			Find:     5,
			Expected: true,
		},
		{
			Name:     "Search Leaf",
			Inserted: []int{4, 2, 6, 1, 3},
			Find:     3,
			Expected: true,
		},
		{
			Name:     "Negatie case",
			Inserted: []int{4, 2, 6, 1, 3},
			Find:     10,
			Expected: false,
		},
	}

	for _, tCase := range cases {
		b := NewBST()

		for _, key := range tCase.Inserted {
			b.Insert(key, key)
		}

		require.Equal(t, tCase.Expected, b.Contain(tCase.Find), tCase.Name)
	}
}

func TestRemove(t *testing.T) {
	testCases := []struct {
		Name     string
		Steps    []int
		Remove   int
		Expected []int
	}{
		{
			Name:     "Empty bst remove",
			Remove:   4,
			Expected: []int{},
		},
		{
			Name:     "Remove one root",
			Steps:    []int{4},
			Remove:   4,
			Expected: []int{},
		},
		{
			Name:     "Remove Leaf",
			Steps:    []int{4, 1, 5, 7, 8},
			Remove:   8,
			Expected: []int{1, 4, 5, 7},
		},
		{
			Name:     "Remove Node With One Child",
			Steps:    []int{4, 1, 5, 7, 8},
			Remove:   7,
			Expected: []int{1, 4, 5, 8},
		},
		{
			Name:     "Remove Root With One Child",
			Steps:    []int{4, 1},
			Remove:   4,
			Expected: []int{1},
		},
		{
			Name:     "Right Son From Remove Node 2 Childs",
			Steps:    []int{8, 4, 10, 3, 6, 5},
			Remove:   8,
			Expected: []int{3, 4, 5, 6, 10},
		},
		{
			Name:     "Left Son From Remove Node 2 Childs",
			Steps:    []int{8, 4, 10, 3, 6, 5},
			Remove:   4,
			Expected: []int{3, 5, 6, 8, 10},
		},
		{
			Name:     "Random case from Google",
			Steps:    []int{15, 10, 20, 8, 12, 18, 25, 16, 19, 30},
			Remove:   20,
			Expected: []int{8, 10, 12, 15, 16, 18, 19, 25, 30},
		},
		{
			Name:     "Root with two child",
			Steps:    []int{6, 4, 8},
			Remove:   6,
			Expected: []int{4, 8},
		},
		{
			Name:     "Random case from Google 2",
			Steps:    []int{7, 5, 4, 13, 11, 19},
			Remove:   7,
			Expected: []int{4, 5, 11, 13, 19},
		},
		{
			Name:     "Random case from Google 3",
			Steps:    []int{7, 5, 4, 13, 11, 19},
			Remove:   13,
			Expected: []int{4, 5, 7, 11, 19},
		},
	}

	for _, tC := range testCases {
		tC := tC
		t.Run(tC.Name, func(t *testing.T) {
			t.Parallel()

			b := NewBST()

			for _, key := range tC.Steps {
				b.Insert(key, key)
			}

			b.Remove(tC.Remove)

			actual := make([]int, 0, len(tC.Expected))

			b.WalkInorder(func(node *Node) {
				val := node.Value.(int)
				actual = append(actual, val)
			})

			require.Equal(t, tC.Expected, actual, tC.Name)
		})
	}
}
