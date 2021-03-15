package graph

import (
	"testing"

	"github.com/stretchr/testify/require"
)

func TestDijkstra(t *testing.T) {
	testCases := []struct {
		desc     string
		edges    map[Vertex][]Edge
		expected []Vertex
		from, to Vertex
	}{
		{
			desc: "google example",
			edges: map[Vertex][]Edge{
				Vertex(0): {{From: Vertex(0), To: Vertex(1), Cost: 3}, {From: Vertex(0), To: Vertex(2), Cost: 3}, {From: Vertex(0), To: Vertex(3), Cost: 6}},
				Vertex(1): {{From: Vertex(1), To: Vertex(2), Cost: 5}, {From: Vertex(1), To: Vertex(4), Cost: 9}},
				Vertex(2): {{From: Vertex(2), To: Vertex(4), Cost: 7}, {From: Vertex(2), To: Vertex(5), Cost: 5}, {From: Vertex(2), To: Vertex(3), Cost: 1}},
				Vertex(3): {{From: Vertex(3), To: Vertex(5), Cost: 4}},
				Vertex(4): {{From: Vertex(4), To: Vertex(6), Cost: 4}},
				Vertex(5): {{From: Vertex(5), To: Vertex(6), Cost: 6}},
				Vertex(6): {},
			},
			expected: []Vertex{Vertex(6), Vertex(5), Vertex(2), Vertex(0)},
			from:     Vertex(0),
			to:       Vertex(6),
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			s := Dijkstra{edges: tC.edges}

			require.Equal(t, tC.expected, s.Do(tC.from, tC.to), tC.desc)
		})
	}
}
