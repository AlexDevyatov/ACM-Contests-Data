// I have no idea what I'm doing.

package main

import (
    "fmt"
)

func main() {
    var l, r, val int64

    fmt.Scanf("%d %d", &l, &r)

    if l > r {
       val = 2*l;
    } else {
       val = 2*r;
    }
    if val == 0 {
        fmt.Printf("Not a moose\n")
    } else if l == r {
        fmt.Printf("Even %d\n", val)
    } else {
        fmt.Printf("Odd %d\n", val)
    }

}
