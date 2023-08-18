package main

/*
#cgo CFLAGS: -I/usr/include
#cgo LDFLAGS: -L. -lsoma

#include<soma.h>
*/
import "C"
import (
	"fmt"
)

func main() {
	fmt.Println("Hello World")
	var result C.int = C.somar(5, 2)
	fmt.Println(result)
	result = C.subtrair(result, 4)
	fmt.Println(result)
}
