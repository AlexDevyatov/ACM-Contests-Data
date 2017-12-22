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
	int sp = 0;
	int *noteAt = phrases->start;
	int *noteAfter = noteAt;
	Phrase *activePhrase = phrases;
	Phrase *phraseAfter = activePhrase + 1;

	while (true)
	{
		noteAt++;
		if (*activePhrase->start < END)
		{
			if (noteAt > activePhrase->start)
				sp += *noteAt - *(noteAt - 1);
			if (noteAt == activePhrase->end)
				activePhrase++;
		}

		while (*noteAfter < *noteAt + sp)
		{
			noteAfter++;
			if (*noteAfter == END)
				return max<int>(maxBonus, noteAfter - noteAt);
		}

		while (noteAfter > phraseAfter->start)
		{
			maxBonus = max<int>(maxBonus, phraseAfter->start - noteAt + optimalFromPhrase(phraseAfter));
			phraseAfter++;
		}
		maxBonus = max<int>(maxBonus, noteAfter - noteAt + optimalFromPhrase(phraseAfter));
	}
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
