package main

import (
	"fmt"
)

func encode(utf32 []rune) []byte {
	var res []byte
	for _, c := range utf32 {
		if c < 128 {
			res = append(res, byte(c))
		} else if c < 2048 {
			res = append(res, byte(192+c/64))
			res = append(res, byte(128+c%64))
		} else if c < 65536 {
			res = append(res, byte(224+c/4096))
			res = append(res, byte(128+(c/64)%64))
			res = append(res, byte(128+c%64))
		} else {
			res = append(res, byte(240+c/262144))
			res = append(res, byte(128+(c/4096)%64))
			res = append(res, byte(128+(c/64)%64))
			res = append(res, byte(128+c%64))
		}
	}
	return res
}

func decode(utf8 []byte) []rune {
	var (
		res []rune
		i   int
	)
	for i < len(utf8) {
		c := utf8[i]
		switch {
		case c < 128:
			res = append(res, rune(c))
			i++
		case c < 224:
			r := (int(c&31) << 6) | int(utf8[i+1]&63)
			res = append(res, rune(r))
			i += 2
		case c < 240:
			r := (int(c&15) << 12) | (int(utf8[i+1]&63) << 6) | int(utf8[i+2]&63)
			res = append(res, rune(r))
			i += 3
		default:
			r := (int(c&7) << 18) | (int(utf8[i+1]&63) << 12) | (int(utf8[i+2]&63) << 6) | int(utf8[i+3]&63)
			res = append(res, rune(r))
			i += 4
		}
	}
	return res
}

func main() {
	s := "∏ηж$😀工寫_∏¥"
	//fmt.Println("Original string:", s)

	utf32 := []rune(s)
	utf8 := encode(utf32)
	fmt.Println(utf8)

	decoded_utf32 := decode(utf8)
	decoded_string := string(decoded_utf32)
	fmt.Println(decoded_string)
}
