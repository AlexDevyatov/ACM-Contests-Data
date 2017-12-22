import Data.List

ins n l i = h ++ [n] ++ t
    where (h, t) = splitAt i l

gen 1 = [[1]]
gen n = concat . zipWith expand flips $ gen (n - 1)
    where expand b x = map (ins n x) $ range b [0..(n-1)]
          range b = if b then id else reverse
          flips = concat . repeat $ [False, True]

solve n = unlines . map (intercalate " " . map show) $ gen n

main = do
    n <- readLn
    putStr $ solve n
