10 REM Fibonacci sequence
20 REM  each subsequent number is the sum of the previous two
30 REM
40 LET A = 1
50 LET B = 2
60 PRINT Fibonacci Sequence
70 PRINT 1, 2,
80 REM
90 REM  loop
100 REM
110 LET C = A + B
120 PRINT C
130 LET A = B
140 LET B = C
150 IF C < 100 THEN 110
160 STOP
