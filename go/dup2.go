package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	counts := make(map[string]int)
	linein := make(map[string]string)
	files := os.Args[1:]
	if len(files) == 0 {
		countLines(os.Stdin, counts, linein)
	} else {
		for _, arg := range files {
			f, err := os.Open(arg)
			if err != nil {
				fmt.Fprintf(os.Stderr, "dup2:%v\n", err)
				continue
			}
			countLines(f, counts, linein)
			f.Close()
		}
	}
	for line, n := range counts {
		if n > 1 {
			fmt.Printf("%d\t%s\n[%s]\n\n", n, line, linein[line])
		}
	}
}

func countLines(f *os.File, counts map[string]int, infiles map[string]string) {
	hasline := make(map[string]bool)
	input := bufio.NewScanner(f)
	for input.Scan() {
		counts[input.Text()]++
		if !hasline[input.Text()] {
			infiles[input.Text()] += f.Name() + " "
		}
		hasline[input.Text()] = true
	}
}
