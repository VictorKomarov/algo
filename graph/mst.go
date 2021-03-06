package graph

import "sort"

type Vertex int

type Edge struct {
	From, To Vertex
	Cost     int
}

// for this problem its okey i think
type pGraph struct {
	edges map[Vertex][]Edge
}

// in should be priority queue
func minExcluding(in []Edge, used map[Vertex]bool) Edge {
	min := -1

	for i, e := range in {
		if !(used[e.To] && used[e.From]) {
			if min == -1 || e.Cost < in[min].Cost {
				min = i
			}
		}
	}

	return in[min]
}

func (v pGraph) Prim(begin Vertex) []Edge {
	result := make([]Edge, 0, len(v.edges))

	used := map[Vertex]bool{
		begin: true,
	}
	edges := v.edges[begin]

	for len(result) != len(v.edges)-1 {
		next := minExcluding(edges, used)
		result = append(result, next)

		if used[next.To] {
			used[next.From] = true
			edges = append(edges, v.edges[next.From]...)
		} else {
			used[next.To] = true
			edges = append(edges, v.edges[next.To]...)
		}
	}

	return result
}

type bGraph struct {
	vertexs []Vertex
	edges   []Edge
}

func (v bGraph) Boruvka() []Edge {
	ufd := NewUFD(v.vertexs)

	sort.Slice(v.edges, func(i, j int) bool {
		return v.edges[i].Cost < v.edges[j].Cost
	})

	result := make([]Edge, 0, len(v.edges))
	for i := range v.edges {
		from, _ := ufd.Find(v.edges[i].From)
		to, _ := ufd.Find(v.edges[i].To)

		if from != to {
			result = append(result, v.edges[i])
			if len(result) == len(v.vertexs)-1 {
				return result
			}
		}

		ufd.Merge(from, to)
	}

	return result
}

func canAppend(edges []Edge, e Edge) bool {
	from := false
	to := false
	for i := range edges {
		if edges[i].From == e.From {
			from = true
		}

		if edges[i].To == e.To {
			to = true
		}
	}

	return !(from && to)
}

func (v bGraph) Kraskala() []Edge {
	sort.Slice(v.edges, func(i, j int) bool {
		return v.edges[i].Cost < v.edges[j].Cost
	})

	result := make([]Edge, 0, len(v.edges))
	for i := range v.edges {
		if canAppend(result, v.edges[i]) {
			result = append(result, v.edges[i])
			if len(result) == len(v.vertexs)-1 {
				return result
			}
		}
	}

	return result
}
