package graph

type Color int

const (
	White Color = iota
	Grey
	Black
)

type Graph struct {
	matrix [][]int
}

type MatrixAdjacencies [][]int

func (g Graph) DFS(f func(v int)) {
	visited := make(map[int]bool, len(g.matrix))
	for i := range g.matrix {
		if !visited[i] {
			g.dfs(i, f, visited)
		}
	}
}

func (g Graph) Clone() Graph {
	cl := make([][]int, len(g.matrix))
	for i := range cl {
		cl[i] = make([]int, len(g.matrix[i]))
		copy(cl[i], g.matrix[i])
	}
	return Graph{
		matrix: cl,
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

func (g Graph) minDegree(deleted map[int]bool) []int {
	mins := make(map[int]int)
	for i := range g.matrix {
		if deleted[i] {
			continue
		}

		if _, ok := mins[i]; !ok {
			mins[i] = 0
		}

		for _, n := range g.matrix[i] {
			mins[n-1]++
		}
	}

	result := make([]int, 0, len(mins))
	for v, degree := range mins {
		if deleted[v] {
			continue
		}

		if degree == 0 {
			result = append(result, v)
		}
	}

	return result
}

func (g Graph) Cana() []int {
	n := g.Clone()

	actual := len(n.matrix) - 1
	reversed := make([]int, len(n.matrix))
	deleted := make(map[int]bool)
	for {
		mins := n.minDegree(deleted)
		if len(mins) == 0 {
			return reversed
		}

		for _, v := range mins {
			reversed[actual] = v + 1
			deleted[v] = true
			actual--
		}
	}
}

func (g Graph) iterColor(m map[int]Color, begin int, f func(v int)) {
	m[begin] = Grey

	for _, vertex := range g.matrix[begin] {
		if m[vertex-1] == White {
			g.iterColor(m, vertex-1, f)
		}
	}
	m[begin] = Black
	f(begin)
}

func reverse(nums []int) []int {
	result := make([]int, 0, len(nums))

	for i := len(nums) - 1; i >= 0; i-- {
		result = append(result, nums[i])
	}

	return result
}

func (g Graph) Taryana() []int {
	colors := make(map[int]Color) // think about reuse classic dfs

	topSort := make([]int, 0)
	for i := range g.matrix {
		if colors[i] == White {
			g.iterColor(colors, i, func(vertex int) {
				topSort = append(topSort, vertex+1)
			})
		}
	}

	return reverse(topSort)
}

func (m MatrixAdjacencies) sumByColumns() []int {
	sum := make([]int, len(m))

	for i := range m {
		for j := range m[i] {
			if m[i][j] != 0 {
				sum[j]++
			}
		}
	}

	return sum
}

func zeroIdx(v []int, used map[int]bool) []int {
	result := make([]int, 0)
	for i, s := range v {
		if used[i] {
			continue
		}

		if s == 0 {
			result = append(result, i)
		}
	}

	return result
}

func columndDiff(from []int, args []int) []int {
	for i := range from {
		if from[i] == 0 {
			continue
		}

		from[i] -= args[i]

	}

	return from
}

func (m MatrixAdjacencies) Demucron() []int {
	result := make([]int, 0)
	used := make(map[int]bool)
	sums := m.sumByColumns()

	for {
		level := zeroIdx(sums, used)
		if len(level) == 0 {
			return result
		}

		result = append(result, level...)
		for _, index := range level {
			used[index] = true
			sums = columndDiff(sums, m[index])
		}
	}
}
