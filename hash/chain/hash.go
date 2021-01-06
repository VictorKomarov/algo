package chain

type bucket struct {
	key   int
	value interface{}
	next  *bucket
}

func newBucket(key int, value interface{}) *bucket {
	return &bucket{
		key:   key,
		value: value,
	}
}

// return current bucket size
func add(head *bucket, inserted *bucket) int {
	i := 2 // current head + inserted
	for ; head.next != nil; i++ {
		head = head.next
	}

	head.next = inserted
	return i
}

type Hash struct {
	buckets    []*bucket
	loadFactor int
	size       int
}

func New() *Hash {
	return &Hash{
		buckets:    make([]*bucket, 10),
		size:       10,
		loadFactor: 7,
	}
}

func (h *Hash) Set(key int, value interface{}) {
	index := key % h.size

	node := newBucket(key, value)
	if h.buckets[index] == nil {
		h.buckets[index] = node

		return
	}

	size := add(h.buckets[index], node)
	if size >= h.loadFactor {
		h.migrate(h.size * 2)
	}
}

func (h *Hash) Get(key int) (interface{}, bool) {
	index := key % h.size
	if index >= len(h.buckets) {
		return nil, false
	}

	head := h.buckets[index]
	for head != nil {
		if head.key == key {
			return head.value, true
		}

		head = head.next
	}

	return nil, false
}

func (h *Hash) migrate(size int) {
	h.size = size
	h.loadFactor = int(float64(size) * 0.75)

	oldBuckets := h.buckets
	h.buckets = make([]*bucket, size)

	for i := range oldBuckets {
		head := oldBuckets[i]
		for head != nil {
			h.Set(head.key, head.value) // is recursion possible?
		}
	}
}
