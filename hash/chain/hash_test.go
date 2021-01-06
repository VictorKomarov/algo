package chain

import (
	"testing"

	"github.com/stretchr/testify/require"
)

func TestHashSet(t *testing.T) {
	type pair struct {
		key int
		val interface{}
	}

	testCases := []struct {
		desc               string
		inserted           []pair
		expectedSize       int
		expectedLoadFactor int
		expected           [][]pair
	}{
		{
			desc: "",
		},
	}
	for _, tC := range testCases {
		tC := tC
		t.Run(tC.desc, func(t *testing.T) {
			t.Parallel()

			h := New()

			for _, pair := range tC.inserted {
				h.Set(pair.key, pair.val)
			}

			require.Equal(t, tC.expectedSize, h.size, tC.desc)
			require.Equal(t, tC.expectedLoadFactor, h.loadFactor, tC.desc)

			for i := range h.buckets {
				head := h.buckets[i]
				actual := make([]pair, 0)

				for head != nil {
					actual = append(actual, pair{key: head.key, val: head.value})

				}

				require.Equal(t, tC.expected[i], actual, tC.desc)
			}
		})
	}
}
