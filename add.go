package main

import (
    "fmt"
)

func add(a, b []int32, p int) []int32 {
    var n, m = len(a), len(b)
    var k = max(n, m)
    
    var c = make([]int32, k + 1)
    var carry int32 = 0
    
    for i := 0; i < k; i++ {
        var x, y int32 = 0, 0
        if i < n {
            x = a[i]
        }
        if i < m {
            y = b[i]
        }
        var z = x + y + carry
        c[i] = z % int32(p)
        carry = z / int32(p)
    }
    
    if carry > 0 {
        c[k] = carry
    } else {
        c = c[:k]
    }
    
    return c
}

func max(x, y int) int {
    if x > y {
        return x
    }
    return y
}

func main() {
    var a = []int32{1, 2, 3}
    var b = []int32{4, 5, 6}
    var p = 10
    
    var c = add(a, b, p)
    fmt.Println(a, "+", b, "=", c)
    
    var d = []int32{9, 9}
    var e = []int32{1}
    var f = add(d, e, p)
    fmt.Println(d, "+", e, "=", f)
}
