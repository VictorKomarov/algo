package graph

type Vertex int

type Edge struct {
	From, To Vertex
	Cost     int
}

// for this problem its okey i think
type vGraph struct {
	edges map[Vertex][]Edge
}

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

func (v vGraph) Prim(begin Vertex) []Edge {
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
