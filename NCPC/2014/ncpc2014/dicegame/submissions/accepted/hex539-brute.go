//usr/bin/go run "$0"; exit
package main

/**
 * Author
 *   Robin Lee (hex539)
 *
 * Solution
 *   Brute-force simulate a million games. If the score difference is
 *   within 0.5% of break-even, assume that the two players will tie.
 *
 *   Otherwise, output the name of the player who won the most games.
 */

import (
  "fmt"
  "math/rand"
)

type die struct {
  a int
  b int
}

type player struct {
  dice [2]die
  wins int
}

func simulate(p player) (score int) {
  for _, d := range p.dice {
    score += d.a + rand.Intn(d.b - d.a + 1)
  }
  return
}

func main() {
  var p [2]player
  for i := 0; i < 2; i++ {
    for j := 0; j < 2; j++ {
      fmt.Scanf("%d %d", &p[i].dice[j].a, &p[i].dice[j].b)
    }
  }

  var iterations = 1000000
  for i := 0; i < iterations; i++ {
    var a = simulate(p[0])
    var b = simulate(p[1])
    switch true {
      case a > b:
        p[0].wins++
      case b > a:
        p[1].wins++
    }
  }

  switch true {
    case p[0].wins > p[1].wins + iterations / 200:
      fmt.Printf("Gunnar\n")
    case p[1].wins > p[0].wins + iterations / 200:
      fmt.Printf("Emma\n")
    default:
      fmt.Printf("Tie\n")
  }
}
