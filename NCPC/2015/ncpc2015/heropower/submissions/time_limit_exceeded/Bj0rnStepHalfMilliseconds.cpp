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
int optimalFromPhrase(Phrase *phrases);

int optimizeFromPhrase(Phrase *phrases)
{
	int maxBonus = -1;
	int doubleSP = 0;
	int *noteAt = phrases->start;
	int *noteAfter = noteAt;
	Phrase *activePhrase = phrases;
	Phrase *phraseAfter = activePhrase + 1;

	// Slow loop - step half a millisecond at a time.
	for (int doublePosition = *phrases->start * 2; *noteAfter < END;
		 doublePosition++,
				 doubleSP += doublePosition > *activePhrase->start * 2 && doublePosition <= *activePhrase->end * 2 ? 1 : 0,
				 activePhrase += doublePosition == *activePhrase->end * 2 ? 1 : 0)
	{
		if (doublePosition > *noteAt * 2)
			noteAt++;
		if (doublePosition + doubleSP > *noteAfter * 2)
			noteAfter++;
		if (doublePosition + doubleSP > *phraseAfter->start * 2)
			phraseAfter++;
		int bonusOnActivation = noteAfter - noteAt + optimalFromPhrase(phraseAfter);
		maxBonus = bonusOnActivation > maxBonus ? bonusOnActivation : maxBonus;
	}
	return maxBonus;
}


int optimalFromPhrase(Phrase *phrases)
{
	int offset = phrases - phraseArray;
	if (fromPhraseOptimals[offset] == -1)
		fromPhraseOptimals[offset] = optimizeFromPhrase(phrases);
	return fromPhraseOptimals[offset];
}

int main()
{
	int n, p;
	scanf("%d%d", &n, &p);
	int *notes = new int[n + 1];
	for (int i = 0; i < n; ++i)
		scanf("%d", &notes[i]);
	notes[n] = END;

	Phrase *phrases = new Phrase[p + 1];
	for (int i = 0; i < p; ++i)
	{
		int start, end;
		scanf("%d%d", &start, &end);
		phrases[i].start = find(notes, &notes[n], start);
		phrases[i].end   = find(notes, &notes[n], end  );
	}
	phrases[p] = { &notes[n], &notes[n] };

	fromPhraseOptimals = new int[p + 1];
	for (int i = 0; i < p; ++i)
		fromPhraseOptimals[i] = -1;
	fromPhraseOptimals[p] = 0;
	phraseArray = phrases;

	printf("%d\n", n + optimalFromPhrase(&phrases[0]));

	return 0;
}
