package main

import (
	"fmt"
)

type TriangulationSolver struct {
	matrix [][]int
	N      int
	roots  [][]int
	fl     bool
}

func NewTriangulationSolver(matrix [][]int, N int) *TriangulationSolver {
	return &TriangulationSolver{
		matrix: matrix,
		N:      N,
		roots:  make([][]int, 0),
		fl:     false,
	}
}

func (ts *TriangulationSolver) Solve() {
	ts.triangulate()
	if ts.fl {
		fmt.Println("No solution")
	} else {
		ts.calculateRoots()
		ts.printRoots()
	}
}

func (ts *TriangulationSolver) triangulate() {
	for j := 0; j < ts.N; j++ {
		maxVal := ts.matrix[j][j]
		row := j
		for i := j + 1; i < ts.N; i++ {
			if ts.matrix[i][j] > maxVal {
				maxVal = ts.matrix[i][j]
				row = i
			}
		}
		if maxVal != 0 {
			ts.matrix[j], ts.matrix[row] = ts.matrix[row], ts.matrix[j]
			for i := j + 1; i < ts.N; i++ {
				if ts.matrix[i][j] != 0 {
					q := ts.NOK(ts.matrix[i][j], ts.matrix[j][j]) / ts.matrix[i][j]
					p := ts.NOK(ts.matrix[i][j], ts.matrix[j][j]) / ts.matrix[j][j]
					for k := 0; k < ts.N+1; k++ {
						ts.matrix[i][k] = ts.matrix[i][k]*q - ts.matrix[j][k]*p
					}
				}
			}
		}
	}
}

func (ts *TriangulationSolver) NOD(a, b int) int {
	if a == 0 {
		return b
	}
	return ts.NOD(b%a, a)
}

func (ts *TriangulationSolver) NOK(a, b int) int {
	return a * b / ts.NOD(a, b)
}

func (ts *TriangulationSolver) calculateRoots() {
	for i := ts.N - 1; i >= 0; i-- {
		if ts.matrix[i][i] != 0 {
			q := 0
			m := 1
			for _, r := range ts.roots {
				m = ts.NOK(m, r[1])
			}
			for j := i + 1; j < ts.N; j++ {
				q -= ts.matrix[i][j] * ts.roots[ts.N-1-j][0] * (m / ts.roots[ts.N-1-j][1])
			}
			q += ts.matrix[i][ts.N] * m
			t := ts.NOD(q, m*ts.matrix[i][i])
			if m*ts.matrix[i][i]/t < 0 {
				m *= -1
				q *= -1
			}
			ts.roots = append(ts.roots, []int{q / t, m * ts.matrix[i][i] / t})
		} else {
			ts.fl = true
			break
		}
	}
}

func (ts *TriangulationSolver) printRoots() {
	if ts.fl {
		fmt.Println("No solution")
	} else {
		for i := ts.N - 1; i >= 0; i-- {
			fmt.Printf("%d/%d\n", ts.roots[i][0], ts.roots[i][1])
		}
	}
}

func main() {
	var N int
	fmt.Scanln(&N)

	matrix := make([][]int, N)
	for i := 0; i < N; i++ {
		row := make([]int, N+1)
		for j := 0; j < N+1; j++ {
			fmt.Scan(&row[j])
		}
		matrix[i] = row
	}

	solver := NewTriangulationSolver(matrix, N)
	solver.Solve()
}
