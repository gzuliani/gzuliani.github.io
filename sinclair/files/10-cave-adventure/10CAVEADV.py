#  1 LET X$="100CANNOT DOYOU WALK OPENED   CLOSED   A SWORD  A KEY    NOTHING  A CHEST  A DRAGON A CORPSE "
x="100CANNOT DOYOU WALK OPENED   CLOSED   A SWORD  A KEY    NOTHING  A CHEST  A DRAGON A CORPSE "

while True:

#  2 PRINT TAB USR 3086+USR 3086;"YOU ARE IN A ";"CAVEPIT HALLLAKE"(VAL X$(1)*4-3 TO VAL X$(1)*4)
    print("YOU ARE IN A "+"CAVEPIT HALLLAKE"[(eval(x[0])-1)*4:(eval(x[0]))*4])

#  3 INPUT U$
    u=input()

#  4 LET M=2*(U$="NORTH")*(X$(1)<"3")-2*(U$="SOUTH")*(X$(1)>"2")+(X$(1)+U$="2WEST")-(X$(1)+U$="3EAST")
    m=2*(u=="NORTH")*(x[0]<"3")-2*(u=="SOUTH")*(x[0]>"2")+(x[0]+u=="2WEST")-(x[0]+u=="3EAST")

#  5 LET A=(3+VAL X$(2)+2*(X$(3)="2"))*(X$(1)+U$="2LOOK CHEST")+(11+(X$(3)="2"))*(X$(1)+U$="3KILL DRAGON")+(M<>0)
    a=(3+eval(x[1])+2*(x[2]=="2"))*(x[0]+u=="2LOOK CHEST")+(11+(x[2]=="2"))*(x[0]+u=="3KILL DRAGON")+(m!=0)

#  6 LET A=A+(5+VAL X$(1))*(U$="LOOK")+(6-VAL X$(3))*(U$="INVENTORY")+(6-(X$(3)="0"))*(X$(1)+U$="4LOOK CORPSE")
    a=a+(5+eval(x[0]))*(u=="LOOK")+(6-eval(x[2]))*(u=="INVENTORY")+(6-(x[2]=="0"))*(x[0]+u=="4LOOK CORPSE")

#  7 LET A=A+10*(X$( TO 3)+U$="400GET KEY")+2*(X$( TO 3)+U$="201OPEN CHEST")+10*(X$( TO 3)+U$="211GET SWORD")
    a=a+10*(x[:3]+u=="400GET KEY")+2*(x[:3]+u=="201OPEN CHEST")+10*(x[:3]+u=="211GET SWORD")

#  8 LET X$( TO 3)=STR$ (VAL X$(1)+M)+STR$ (VAL X$(2)+(A=2))+STR$ (VAL X$(3)+(A=10))
    x=chr(ord(x[0])+m)+chr(ord(x[1])+(a==2))+chr(ord(x[2])+(a==10))+x[3:]

#  9 PRINT TAB USR 3086;"> ";U$;TAB USR 3086;(X$+"TAKEN    YOU DIED YOU WON. ")(A*9+4 TO A*9+12)
    print((x+"TAKEN    YOU DIED YOU WON. ")[a*9+3:a*9+12])

# 10 IF A<11 THEN GOTO 2
    if a>=11: break
