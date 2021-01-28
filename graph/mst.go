package graph

type Vertex int

type Edge struct {
	From, To Vertex
	Cost     int
}

func (e Edge) isSame(e2 Edge) bool {
	return e.From == e2.From && e.To == e2.To || e.From == e2.To && e.To == e2.From
}

// for this problem its okey i think
type vGraph struct {
	edges map[Vertex][]Edge
}

func minExcluding(in []Edge, used map[Vertex]bool) Edge {
	min := -1

	for i, e := range in {
		if !used[e.To] {
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

	for len(result) != len(v.edges) {
		next := minExcluding(v.edges[begin], used)
		used[next.To] = true
		begin = next.To
	}

	return result
}
