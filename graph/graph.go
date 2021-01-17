package graph

type Graph struct {
	matrix [][]int
}

func (g Graph) DFS(f func(v int)) {
	visited := make(map[int]bool, len(g.matrix))
	for i := range g.matrix {
		if !visited[i] {
			g.dfs(i, f, visited)
		}
	}
}

func (g Graph) dfs(current int, f func(v int), visited map[int]bool) {
	visited[current] = true
	for _, val := range g.matrix[current] {
		if !visited[val-1] {
			g.dfs(val-1, f, visited)
		}
	}
	f(current + 1)
}

func (g Graph) Invert() Graph {
	m := make([][]int, len(g.matrix))
	for i := range m {
		m[i] = make([]int, 0) // cap ?
	}

	for i := range g.matrix {
		for _, val := range g.matrix[i] {
			if val != 0 {
				m[val-1] = append(m[val-1], i+1)
			}
		}
	}

	return Graph{matrix: m}
}

func (g Graph) Kosarayu() [][]int {
	inverted := g.Invert()

	invertedDfs := make([]int, 0)
	inverted.DFS(func(n int) {
		invertedDfs = append(invertedDfs, n)
	})

	components := make([][]int, 0)
	visited := make(map[int]bool)
	for i := len(invertedDfs) - 1; i >= 0; i-- {
		if !visited[invertedDfs[i]-1] {
			component := make([]int, 0)
			g.dfs(invertedDfs[i]-1, func(n int) {
				component = append(component, n)
			}, visited)

			components = append(components, component)
		}
	}

	return components
}
