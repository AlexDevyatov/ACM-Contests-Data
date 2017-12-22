#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

static int END = INT_MAX / 2;

struct Phrase
{
	int *start, *end;
};

int *fromPhraseOptimals;
Phrase *phraseArray;
int optimalFromPhrase(int *notes, Phrase *phrases);

int playSPLessUntil(int *&notes, int *endNote)
{
	int notesPlayed = endNote - notes;
	notes = endNote;
	return notesPlayed;
}

int optimalScoreIfActivatingNow(int *notes, int *notesAfterActivation, Phrase *endpoint)
{
	int notesUnderActivation = notesAfterActivation - notes;
	int notesBetween = playSPLessUntil(notesAfterActivation, endpoint->start);
	int scoreTillPhrase = notesUnderActivation * 2 + notesBetween;
	return scoreTillPhrase + optimalFromPhrase(notesAfterActivation, endpoint);
}

void goToNextNote(int *&notes, Phrase *&phrases, int &position, int &sp, int *&notesAfterActivation)
{
	// Play note.
	if (notes == phrases->end)
		++phrases;
	++notes;

	// Figure out how much to advance.
	int advancement = *notes - position;

	// Do the advancement.
	if (position >= *phrases->start)
		sp += advancement;
	position += advancement;
}

void propagateSP(int position, int sp, int *&notesAfterActivation, int endBefore)
{
	// Update notesUnderActivation, but not beyond endBefore.
	while (position + sp > *notesAfterActivation && *notesAfterActivation < endBefore)
		++notesAfterActivation;
}

int optimizeFromPhrase(int *notes, Phrase *phrases)
{
	int maxScore = 0;
	int position = *notes;
	int sp = 0;
	int *notesAfterActivation = notes;
	int notesPlayed = 0;

	for (Phrase *phraseToEndBefore = phrases + 1; *phraseToEndBefore[-1].start != END; ++phraseToEndBefore)
	{
		propagateSP(position, sp, notesAfterActivation, *phraseToEndBefore->start);
		maxScore = max(maxScore, notesPlayed + optimalScoreIfActivatingNow(notes, notesAfterActivation, phraseToEndBefore));
		while (notesAfterActivation != phraseToEndBefore->start)
		{
			goToNextNote(notes, phrases, position, sp, notesAfterActivation);
			++notesPlayed;

			propagateSP(position, sp, notesAfterActivation, *phraseToEndBefore->start);
			maxScore = max(maxScore, notesPlayed + optimalScoreIfActivatingNow(notes, notesAfterActivation, phraseToEndBefore));
		}
	}
	return maxScore;
}


int optimalFromPhrase(int *notes, Phrase *phrases)
{
	int offset = phrases - phraseArray;
	if (fromPhraseOptimals[offset] == -1)
		fromPhraseOptimals[offset] = optimizeFromPhrase(notes, phrases);
	return fromPhraseOptimals[offset];
}

int main()
{
	FILE *INPUT = stdin;
	//INPUT = fopen("/home/bj0rn/2015/starpower/data/secret/12.in", "r");

	int n, p;
	fscanf(INPUT, "%d%d", &n, &p);
	int *notes = new int[n + 1];
	for (int i = 0; i < n; ++i)
		fscanf(INPUT, "%d", &notes[i]);
	notes[n] = END;

	Phrase *phrases = new Phrase[p + 1];
	for (int i = 0; i < p; ++i)
	{
		int start, end;
		fscanf(INPUT, "%d%d", &start, &end);
		phrases[i].start = find(notes, &notes[n], start);
		phrases[i].end   = find(notes, &notes[n], end  );
	}
	phrases[p] = { &notes[n], &notes[n] };

	fromPhraseOptimals = new int[p + 1];
	for (int i = 0; i < p; ++i)
		fromPhraseOptimals[i] = -1;
	fromPhraseOptimals[p] = 0;
	phraseArray = phrases;

	int introScore = playSPLessUntil(notes, phrases->start);
	printf("%d\n", introScore + optimalFromPhrase(notes, phrases));

	return 0;
}
