import Control.Monad.State
import Data.Maybe
import Data.Array
import Control.Applicative
import Data.List

type Position = Int
type Duration = Int
type Note = Position
type Phrase = (Note, Note)
type Score = Int
type OptimalActivation = Maybe Score
type Endpoint = Maybe Note


-- Program main entry point.
main :: IO ()
main = do
    [_, p] <- map read . words <$> getLine
    notes <- map read . words <$> getLine
    phrases <- replicateM p $ do
        [start, end] <- map read . words <$> getLine
        return (start, end)
    print $ optimal notes phrases


optimal :: [Note] -> [Phrase] -> Score
optimal notes phrases =
    length notes + fromPhraseOptimals notes phrases!0


fromPhraseOptimals :: [Note] -> [Phrase] -> Array Int Score
fromPhraseOptimals notes phrases = arr
    where
        size = length phrases
        arr = listArray (0, size) (map optimalFromPhrase [0..])
        startingPoints = listArray (0, size) (songFromEndpoints notes phrases)
        optimalFromPhrase i =
            fromMaybe 0 $ maximum totals
            where
                scores = uncurry singleActivationOptimals (startingPoints!i)
                maybeContinue next = fmap (arr!next +)
                totals = zipWith maybeContinue [i..] scores

songFromEndpoints :: [Note] -> [Phrase] -> [([Note], [Phrase])]
songFromEndpoints notes phrases =
    tail $ scanl toNextEnd (notes, phrases) (endpoints phrases)

toNextEnd :: ([Note], [Phrase]) -> Endpoint -> ([Note], [Phrase])
toNextEnd (notes, phrases) (Just endNote) =
    (dropWhile (< endNote) notes, dropWhile ((< endNote) . fst) phrases)
toNextEnd _ Nothing =
    ([], [])

endpoints :: [Phrase] -> [Endpoint]
endpoints phrases =
    map Just endNotes ++ [Nothing]
    where
        endNotes = map fst phrases

singleActivationOptimals :: [Note] -> [Phrase] -> [OptimalActivation]
singleActivationOptimals notes phrases =
    evalState (mapM optimizeActivationBefore (endpoints phrases)) (toPlayState notes phrases)


data PlayState = PlayState
    { position      :: Position
    , comingNotes   :: [Note]
    , notesAfterSP  :: [Note]
    , comingPhrases :: [Phrase]
    , sp         :: Duration
    , notesUnderSP  :: Score
    }
    deriving (Show, Eq)

-- Initiates PlayState with zero SP from a list of notes and a list of phrases.
toPlayState :: [Note] -> [Phrase] -> PlayState
toPlayState notes phrases = PlayState (head notes) notes notes phrases 0 0


optimizeActivationBefore :: Endpoint -> State PlayState OptimalActivation
optimizeActivationBefore end =
    fmap maximum $ do
        sinceLastEndpoint <- modify (moveTowards end) >> gets bonusScore
        towardsEndpoint <- untilM (gets $ endReached end) $ do
            -- INVARIANT: We must be at a note here. Encode in type somehow?
            modify playNote
            modify (moveTowards end) >> gets bonusScore
        return (sinceLastEndpoint:towardsEndpoint)

endReached :: Endpoint -> PlayState -> Bool
endReached Nothing ps =
    null (notesAfterSP ps) -- Ensure no missed opportunities.
endReached (Just end) ps =
    head (notesAfterSP ps) == end && -- Ensure no missed opportunities,
    position ps + sp ps >= end -- and that we're actually there yet.

-- Advance time and SP as much as possible before we reach a note to hit or
-- reach `end`.
moveTowards :: Endpoint -> PlayState -> PlayState
moveTowards end = backfillSP end . advance

advance :: PlayState -> PlayState
advance ps@(PlayState pos _ _ _ spNow _) =
    ps {
        position = pos + adv,
        sp = spNow + if whammying then adv else 0
    }
    where
        whammying = insidePhrase ps
        adv = advancement ps

advancement :: PlayState -> Duration
advancement (PlayState pos notes _ _ _ _) =
    fromJust $ (subtract pos) <$> listToMaybe notes

insidePhrase :: PlayState -> Bool
insidePhrase playState =
    maybe False ((position playState >=) . fst) $
        listToMaybe $ comingPhrases playState


backfillSP :: Endpoint -> PlayState -> PlayState
backfillSP end ps =
    fromJust $ find (backfilled end) $ iterate passNoteAfterSP ps

backfilled :: Endpoint -> PlayState -> Bool
backfilled end ps =
    maybe True beyondReach nextNote
    where
        beyondReach note =
            note >= spEnd || maybe False (note >=) end
        nextNote = listToMaybe $ notesAfterSP ps
        spEnd = position ps + sp ps

passNoteAfterSP :: PlayState -> PlayState
passNoteAfterSP ps@(PlayState _ _ afterSP _ _ underSP) =
    ps {
        notesAfterSP = tail afterSP,
        notesUnderSP = underSP + 1
    }


-- Assumes `position == head comingNotes`
playNote :: PlayState -> PlayState
playNote = maybeHitSPBonus . passComingNote

maybeHitSPBonus :: PlayState -> PlayState
maybeHitSPBonus ps =
    if atSPBonus ps then
        hitPhraseBonus ps
    else
        ps

atSPBonus :: PlayState -> Bool
atSPBonus (PlayState _ _ _ [] _ _) =
    False
atSPBonus (PlayState pos _ _ ((_, bonusPos):_) _ _) =
    pos == bonusPos

passComingNote :: PlayState -> PlayState
passComingNote ps@(PlayState _ notes _ _ _ underSP) =
    ps {
        comingNotes = tail notes,
        notesUnderSP = underSP - 1
    }


hitPhraseBonus :: PlayState -> PlayState
hitPhraseBonus ps@(PlayState _ _ _ phrases _ _) =
    ps {
        comingPhrases = tail phrases
    }

-- Score a state. Just count bonus points, not base score. Nothing if no SP.
bonusScore :: PlayState -> Maybe Score
bonusScore playState =
    if possibleActivation playState then
        Just $ notesUnderSP playState
    else
        Nothing

possibleActivation :: PlayState -> Bool
possibleActivation playState = sp playState > 0


untilM :: (Applicative m, Monad m) => m Bool -> m a -> m [a]
untilM condition action = do
    test <- condition
    if not test then
        (:) <$> action <*> untilM condition action
    else
        return []
