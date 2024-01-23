package main

func qsort(n int, less func(i, j int) bool, swap func(i, j int)) {
	var partition func(left, right int) int
	partition = func(left, right int) int {
		pivotIndex := left
		pivotValue := left

		for i := left + 1; i <= right; i++ {
			if less(i, pivotIndex) {
				pivotValue++
				swap(i, pivotValue)
			}
		}

		swap(pivotIndex, pivotValue)
		return pivotValue
	}

	var sort func(left, right int)
	sort = func(left, right int) {
		if left < right {
			pivot := partition(left, right)
			sort(left, pivot-1)
			sort(pivot+1, right)
		}
	}

	sort(0, n-1)
}

func main() {
	arr := []int{5, 2, 9, 1, 7, 6}
	
	less := func(i, j int) bool {
		return arr[i] < arr[j]
	}

	swap := func(i, j int) {
		arr[i], arr[j] = arr[j], arr[i]
	}

	qsort(len(arr), less, swap)

	for _, x := range arr {
		println(x)
	}
}
