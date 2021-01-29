package graph

import (
	"testing"

	"github.com/stretchr/testify/require"
)

func TestPrim(t *testing.T) {
	testCases := []struct {
		desc        string
		matrix      map[Vertex][]Edge
		expectedMST []Edge
	}{
		{
			desc: "wiki example",
			matrix: map[Vertex][]Edge{
				Vertex(1): {
					{From: Vertex(1), To: Vertex(2), Cost: 3},
					{From: Vertex(1), To: Vertex(3), Cost: 4},
					{From: Vertex(1), To: Vertex(5), Cost: 1},
				},
				Vertex(2): {
					{From: Vertex(2), To: Vertex(1), Cost: 3},
					{From: Vertex(2), To: Vertex(3), Cost: 5},
				},
				Vertex(3): {
					{From: Vertex(3), To: Vertex(1), Cost: 4},
					{From: Vertex(3), To: Vertex(5), Cost: 6},
					{From: Vertex(3), To: Vertex(2), Cost: 5},
					{From: Vertex(3), To: Vertex(4), Cost: 2},
				},
				Vertex(4): {
					{From: Vertex(4), To: Vertex(3), Cost: 2},
					{From: Vertex(4), To: Vertex(5), Cost: 7},
				},
				Vertex(5): {
					{From: Vertex(5), To: Vertex(1), Cost: 1},
					{From: Vertex(5), To: Vertex(3), Cost: 6},
					{From: Vertex(5), To: Vertex(4), Cost: 7},
				},
			},
			expectedMST: []Edge{
				{From: Vertex(1), To: Vertex(5), Cost: 1},
				{From: Vertex(1), To: Vertex(2), Cost: 3},
				{From: Vertex(1), To: Vertex(3), Cost: 4},
				{From: Vertex(3), To: Vertex(4), Cost: 2},
			},
		},
		{
			desc: "pdf example",
			matrix: map[Vertex][]Edge{
				Vertex(1): {
					{From: Vertex(1), To: Vertex(2), Cost: 7},
					{From: Vertex(1), To: Vertex(4), Cost: 5},
				},
				Vertex(2): {
					{From: Vertex(2), To: Vertex(1), Cost: 7},
					{From: Vertex(2), To: Vertex(4), Cost: 9},
					{From: Vertex(2), To: Vertex(3), Cost: 8},
					{From: Vertex(2), To: Vertex(5), Cost: 7},
				},
				Vertex(3): {
					{From: Vertex(3), To: Vertex(2), Cost: 8},
					{From: Vertex(3), To: Vertex(5), Cost: 5},
				},
				Vertex(4): {
					{From: Vertex(4), To: Vertex(1), Cost: 5},
					{From: Vertex(4), To: Vertex(2), Cost: 9},
					{From: Vertex(4), To: Vertex(5), Cost: 15},
					{From: Vertex(4), To: Vertex(6), Cost: 6},
				},
				Vertex(5): {
					{From: Vertex(5), To: Vertex(2), Cost: 7},
					{From: Vertex(5), To: Vertex(3), Cost: 5},
					{From: Vertex(5), To: Vertex(4), Cost: 15},
					{From: Vertex(5), To: Vertex(6), Cost: 8},
					{From: Vertex(5), To: Vertex(7), Cost: 9},
				},
				Vertex(6): {
					{From: Vertex(6), To: Vertex(4), Cost: 6},
					{From: Vertex(6), To: Vertex(5), Cost: 8},
					{From: Vertex(6), To: Vertex(7), Cost: 11},
				},
				Vertex(7): {
					{From: Vertex(7), To: Vertex(5), Cost: 9},
					{From: Vertex(7), To: Vertex(6), Cost: 11},
				},
			},
			expectedMST: []Edge{
				{From: Vertex(1), To: Vertex(4), Cost: 5},
				{From: Vertex(4), To: Vertex(6), Cost: 6},
				{From: Vertex(1), To: Vertex(2), Cost: 7},
				{From: Vertex(2), To: Vertex(5), Cost: 7},
				{From: Vertex(5), To: Vertex(3), Cost: 5},
				{From: Vertex(5), To: Vertex(7), Cost: 9},
			},
		},
	}

	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			graph := pGraph{edges: tC.matrix}

			require.Equal(t, tC.expectedMST, graph.Prim(Vertex(1)), tC.desc)
		})
	}
}
