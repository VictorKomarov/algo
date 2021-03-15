package graph

type Dijkstra struct {
	edges map[Vertex][]Edge
}

type Tags struct {
	From Vertex
	Cost int
}

func (d Dijkstra) Do(from, to Vertex) []Vertex {
	used := map[Vertex]bool{from: true}
	router := map[Vertex]Tags{from: {
		From: from,
		Cost: 0,
	}}

	for from != to {
		for _, way := range d.edges[from] {
			cost := router[way.From].Cost + way.Cost
			_, ok := router[way.To]
			if !ok || router[way.To].Cost > cost {
				router[way.To] = Tags{
					From: way.From,
					Cost: cost,
				}
			}
		}

		nextV := from
		for v, c := range router {
			if !used[v] && (nextV == from || c.Cost < router[nextV].Cost) {
				nextV = v
			}
		}
		used[from] = true
		from = nextV
	}

	path := make([]Vertex, 0)
	for to != router[to].From {
		path = append(path, to)
		to = router[to].From
	}
	path = append(path, to)

	return path
}
