program different;

uses sysutils, math;

var
    l : longint;
    r : longint;

begin
   read(l);
   read(r);
   if ((l = 0) and (r = 0)) then
      writeln('Not a moose')
   else if (l = r) then
      writeln('Even ' + IntToStr(l+r))
   else
      writeln('Odd ' + IntToStr(2*Max(l, r)));
end.
