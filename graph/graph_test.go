package graph

import (
	"testing"

	"github.com/stretchr/testify/require"
)

func TestInvertGraph(t *testing.T) {
	testCases := []struct {
		desc     string
		matrix   [][]int
		expected [][]int
	}{
		{
			desc:     "simple case",
			matrix:   [][]int{{2, 3, 4}, {4, 5}, {4}, {}, {4}},
			expected: [][]int{{}, {1}, {1}, {1, 2, 3, 5}, {2}},
		},
		{
			desc:     "empty case",
			matrix:   [][]int{},
			expected: [][]int{},
		},
		{
			desc:     "one case",
			matrix:   [][]int{{2}, {}},
			expected: [][]int{{}, {1}},
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			actual := Graph{matrix: tC.matrix}.Invert()

			require.Equal(t, tC.expected, actual.matrix, tC.desc)
		})
	}
}

func TestDFS(t *testing.T) {
	testCases := []struct {
		desc     string
		matrix   [][]int
		expected []int
	}{
		{
			desc:     "simple walk",
			matrix:   [][]int{{2, 3, 4}, {4, 5}, {4}, {}, {4}},
			expected: []int{4, 5, 2, 3, 1},
		},
		{
			desc:     "not connected",
			matrix:   [][]int{{2, 3}, {1, 3}, {1, 2}, {5, 6}, {4, 6}, {4, 5}, {1}},
			expected: []int{3, 2, 1, 6, 5, 4, 7},
		},
		{
			desc:     "more",
			matrix:   [][]int{{2}, {3, 6}, {1, 4}, {5}, {4}, {5, 7}, {6, 8}, {7, 5}},
			expected: []int{5, 4, 3, 8, 7, 6, 2, 1},
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()
			acutal := make([]int, 0, len(tC.expected))

			g := Graph{matrix: tC.matrix}

			g.DFS(func(n int) {
				acutal = append(acutal, n)
			})

			require.Equal(t, tC.expected, acutal, tC.desc)
		})
	}
}

func TestKosarayu(t *testing.T) {
	testCases := []struct {
		desc     string
		matrix   [][]int
		expected [][]int
	}{
		{
			desc:     "One pretty test :)",
			matrix:   [][]int{{2}, {3, 6}, {1, 4}, {5}, {4}, {5, 7}, {6, 8}, {7, 5}},
			expected: [][]int{{5, 4}, {8, 7, 6}, {3, 2, 1}},
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			components := Graph{matrix: tC.matrix}.Kosarayu()
			require.Equal(t, tC.expected, components, tC.desc)
		})
	}
}
