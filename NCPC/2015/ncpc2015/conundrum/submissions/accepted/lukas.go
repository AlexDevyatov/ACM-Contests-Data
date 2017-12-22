package main

import "fmt"

func btoi(b bool) int {
    if b { return 1 }
    return 0
}

func main() {
    var s string
    fmt.Scanf("%s", &s)

    res := 0
    for i := 0; i < len(s); i++ {
        if s[i] != "PER"[i % 3] {
            res++
        }
    }
    fmt.Println(res)
}
