package treap

import (
	"bintree/avl"
	"bintree/bst"
	"testing"
)

func BenchmarkBst_Insert(b *testing.B) {
	keys := make([]int, 0, 10000)
	for i := 1; i <= 10000; i++ {
		keys = append(keys, i)
	}
	tree := bst.NewBST()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		for _, key := range keys {
			tree.Insert(key, key)
		}
	}
}

func BenchmarkAVL_Insert(b *testing.B) {
	keys := make([]int, 0, 10000)
	for i := 1; i <= 10000; i++ {
		keys = append(keys, i)
	}
	tree := avl.New(bst.NewBST())
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		for _, key := range keys {
			tree.Insert(key, key)
		}
	}
}

func BenchmarkTreap_Insert(b *testing.B) {
	keys := make([]int, 0, 10000)
	for i := 1; i <= 10000; i++ {
		keys = append(keys, i)
	}
	tree := New()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		for _, key := range keys {
			tree.Insert(NewNode(key, key))
		}
	}
}
