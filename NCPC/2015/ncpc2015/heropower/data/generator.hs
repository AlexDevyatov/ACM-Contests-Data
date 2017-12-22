import System.Random
import Data.List

maxNotes = 50000
maxPhrases = 100
maxPosition = 5000000

notes r = takeWhile (<= maxPosition) $ take maxNotes $ scanl (+) 0 $ randomRs (1, maxPosition `div` maxNotes * 2 - 1) r
phraseAlternations noteCount r = takeWhile (< noteCount) $ take (maxPhrases * 2) $ scanl (+) 0 $ randomRs (1, noteCount `div` (maxPhrases * 2) * 2 - 1) r

pairwise [] = []
pairwise ([_]) = []
pairwise (s:e:alternations) = (s, e) : pairwise alternations

phrasesFromAlternations myNotes alternations = pairwise $ map (myNotes!!) alternations

main = do
    gen <- newStdGen
    let myNotes = notes gen
    let myPhraseAlternations = phraseAlternations (length myNotes) gen
    let myPhrases = phrasesFromAlternations myNotes myPhraseAlternations
    putStrLn $ unwords [show $ length myNotes, show $ length myPhrases]
    putStrLn $ unwords $ map show myNotes
    mapM_ (\(s, e) -> putStrLn $ show s ++ " " ++ show e) myPhrases
