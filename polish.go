package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func polishArithmetic(str string, startIndex int) int {
	if str[0] != '(' {
		first, _ := strconv.Atoi(string(str[0]))
		return first
	}

	operation := str[startIndex+1]

	first := 0
	second := 0
	startSecond := startIndex + 3
	if str[startIndex+2] == '(' {
		first = polishArithmetic(str, startIndex+2)

		countParenthesis := 1

		for i := startIndex + 3; countParenthesis > 0; i++ {
			if str[i] == '(' {
				countParenthesis++
			}
			if str[i] == ')' {
				countParenthesis--
				startSecond = i + 1
			}
		}

	} else {
		first, _ = strconv.Atoi(string(str[startIndex+2]))
	}

	if str[startSecond] == '(' {
		second = polishArithmetic(str, startSecond)
	} else {
		second, _ = strconv.Atoi(string(str[startSecond]))
	}

	if operation == '+' {
		return first + second
	}

	if operation == '-' {
		return first - second
	}

	return first * second
}

func main() {
	//fmt.Println(polishArifm("(* 5 (+ (- (* 2 2) (- 9 8)) 4))"))
	scanner := bufio.NewScanner(os.Stdin)
	arifm := ""
	if scanner.Scan() {
		arifm = scanner.Text()
	}
	arifm = strings.ReplaceAll(arifm, " ", "")
	fmt.Println(polishArithmetic(arifm, 0))
}
