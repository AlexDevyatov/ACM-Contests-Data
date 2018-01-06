pushd ..\problems\highway\statement\pics
call r.bat
popd

latex problems.tex
dvips problems.dvi
dvipdfmx -p a4 problems.dvi
