import Data.List

perper = concat $ repeat "PER"

count s = length . filter id $ zipWith (/=) perper s

solve lin = show(count message) ++ "\n"
    where message:xm = lines lin

main = interact solve
