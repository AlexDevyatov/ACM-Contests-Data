u=8mm;

beginfig(1)
  w = 8u;
  h = 4u;
  
  for i = 0 step u until w:
  	draw (i, 0)--(i, h) dashed withdots;
  endfor;
  
  for i = 0 step u until h:
    draw (0, i)--(w, i) dashed withdots;
  endfor;

  draw (0, 0)--(0, 2u);
  draw (0, 2u)--(3u, 2u);
  draw (3u, 2u)--(3u, 0);
  draw (3u, 0)--(0, 0);

  draw (5u, u)--(5u, 4u);
  draw (5u, 4u)--(7u, 4u);
  draw (7u, 4u)--(7u, u);
  draw (7u, u)--(5u, u);

  draw (0, 0) withpen pencircle scaled 4bp;
endfig;

beginfig(2)

  for i = 0 step u until w:
  	draw (i, 0)--(i, h) dashed withdots;
  endfor;
  
  for i = 0 step u until h:
    draw (0, i)--(w, i) dashed withdots;
  endfor;

  draw (2u, 0)--(2u, 2u);
  draw (2u, 2u)--(5u, 2u);
  draw (5u, 2u)--(5u, 0);
  draw (5u, 0)--(2u, 0);

  draw (7u, u)--(7u, 4u);
  draw (7u, 4u)--(8u, 4u);
  draw (8u, 4u)--(8u, u);
  draw (8u, u)--(7u, u);

  draw (0u, u)--(0u, 4u);
  draw (0u, 4u)--(1u, 4u);
  draw (1u, 4u)--(1u, u);
  draw (1u, u)--(0u, u);

  draw (0, 0) withpen pencircle scaled 4bp;
endfig;


end.
