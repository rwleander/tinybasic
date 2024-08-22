10 REM  NEWTON'S METHOD
20 REM
30 REM  y = x^2, so y is square root  of X
40 REM  DY = 2X DX  and  dy = y - x^2  SO
50 REM   DX = (Y - X ^ 2) / 2* X
60 REM
70 PRINT "NEWTON's METHOD"
80 PRINT
90 PRINT "Enter value ",
100 INPUT Y
110 LET X = Y / 4
120 REM
130 REM  LOOP
140 REM
150 LET D = (Y - X * X) / (2 * X)
160 LET X = X + D
170 PRINT X, D
180 IF D >= 0.0001 THEN 150
190 IF D <= -0.0001 THEN 150
200 PRINT "Square root is: ", X
210 STOP

 