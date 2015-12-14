package main

import (
	"fmt"
	"os"
)

func main() {
	fmt.Println("asdf")

	fi, err := os.Open("in")
	if err != nil {
		panic(err)
	}

	fmt.Prin

}
