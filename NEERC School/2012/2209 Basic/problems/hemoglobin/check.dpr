program TokenCmp;

uses
	testlib, SysUtils;

var
	fpn, l: longint;
	ja, pa: string;
	jv, pv: extended;
	z: longint;

const
	EPS = 2.1e-3;

begin
	l := 0;
	fpn := 0;

	while not ans.seekeof do begin
		inc(l);
		if ouf.seekeof then
			quit(_wa, 'Not enough tokens');
		ja := ans.readword(blanks, blanks);
		pa := ouf.readword(blanks, blanks);
		if (ja = pa) then
			continue;
		val(ja, jv, z);
		if (z <> 0) then
			quit(_wa, 'wrong token ' + inttostr(l) + ' - expected: ' + ja + ', found: ' + pa);
		val(pa, pv, z);
		if (z <> 0) then
			quit(_wa, 'wrong token ' + inttostr(l) + ' - expected: ' + ja + ', found: ' + pa);
		inc(fpn);
		if (abs(jv - pv) > EPS) then
			quit(_wa, 'wrong token ' + inttostr(l) + ' - expected: ' + ja + ', found: ' + pa);
	end;
  	if not ouf.seekeof then
  		quit(_wa, 'Too many tokens');

  	quit(_ok, inttostr(l) + ' tokens');
end.