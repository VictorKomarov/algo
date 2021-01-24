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

func TestCana(t *testing.T) {
	testCases := []struct {
		desc     string
		matrix   [][]int
		expected [][]int
	}{
		{
			desc:     "pdf example", //reverse if need
			matrix:   [][]int{{2, 4, 6}, {3}, {4}, {}, {1, 6, 9}, {7}, {}, {6}, {}},
			expected: [][]int{{4}, {7, 3}, {2, 6}, {9, 1}, {8, 5}},
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			g := Graph{matrix: tC.matrix}
			actual := g.Cana()
			for i := range tC.expected {
				sub := actual[:len(tC.expected[i])]
				for _, num := range tC.expected[i] {
					require.Contains(t, sub, num, tC.desc)
				}

				actual = actual[len(tC.expected[i]):]
			}
		})
	}
}

func TestTaryana(t *testing.T) {
	testCases := []struct {
		desc     string
		matrix   [][]int
		expected []int
	}{
		{
			desc:     "pdf example",
			matrix:   [][]int{{2, 4, 6}, {3}, {4}, {}, {1, 6, 9}, {7}, {}, {6}, {}},
			expected: []int{8, 5, 9, 1, 6, 7, 2, 3, 4},
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			g := Graph{matrix: tC.matrix}
			require.Equal(t, tC.expected, g.Taryana(), tC.desc)
		})
	}
}

func TestDemucron(t *testing.T) {
	testCases := []struct {
		desc     string
		matrix   [][]int
		expected []int
	}{
		{
			desc: "pdf example",
			matrix: [][]int{
				{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //1
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //2
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
				{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4
				{0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, //5
				{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, //6
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //7
				{0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, //8
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //9
				{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0}, //10
				{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //11
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //12
				{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //13
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //14
			},
			expected: []int{4, 7, 1, 5, 8, 9, 0, 3, 6, 11, 13, 10, 12, 2},
		},
	}
	for _, tC := range testCases {
		tc := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			m := MatrixAdjacencies(tc.matrix)
			require.Equal(t, tc.expected, m.Demucron(), tc.desc)
		})
	}
}
