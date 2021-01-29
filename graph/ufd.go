package graph

type UFD struct {
	base map[Vertex]Vertex
}

func NewUFD(vertexs []Vertex) UFD {
	base := make(map[Vertex]Vertex, len(vertexs))

	for i := range vertexs {
		base[vertexs[i]] = vertexs[i]
	}

	return UFD{
		base: base,
	}
}

func (u UFD) Find(v Vertex) (Vertex, bool) {
	if _, ok := u.base[v]; !ok {
		return Vertex(-1), false
	}

	if u.base[v] == v {
		return v, true
	}

	return u.Find(u.base[v])
}

func (u UFD) Merge(v1, v2 Vertex) bool {
	_, ok1 := u.base[v1]
	_, ok2 := u.base[v2]

	if ok1 && ok2 {
		u.base[v1] = v2

		return true
	}

	return false
}
