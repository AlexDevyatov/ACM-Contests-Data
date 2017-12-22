solve:: Int -> Int -> String
solve l r
   | l + r == 0 = "Not a moose"
   | l == r     = "Even " ++ show(2*l)
   | otherwise  = "Odd " ++ show(2 * (max l r))

parse :: String -> (Int, Int)
parse str = (vals !! 0, vals !! 1)
   where vals = (map read) $ words str

main = interact (uncurry solve . parse)
