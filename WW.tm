; This program checks if the input string is a WW.
; Input: a string of 0's and 1's, eg '0101'

; the finite set of states
#Q = {init, halt_accept, halt_reject, even, odd, fm_mh, fm1, fm2, fm3, find_mid, cmp, mid_reject, mid_reject1, mid_reject2, mid_accept, mid_rm, cp, even_accept, accept, accept1, accept2, accept3, even_reject, reject1, reject2, reject3, reject4}

; the finite set of input symbols
#S = {0,1}

; the complete set of tape symbols
#G = {0,1,_,T,r,u,e,F,a,l,s}

; the start state
#q0 = init

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2 

; the transition functions

; is empty
init __ __ ** accept

; is even
init 0_ ** r* even
init 1_ ** r* even
even 0_ ** r* odd
even 1_ ** r* odd
even __ ** l* even_reject
odd 0_ ** r* even
odd 1_ ** r* even
odd __ ** l* even_accept
even_accept 0_ ** l* even_accept
even_accept 1_ ** l* even_accept
even_accept __ ** r* cp

; copy tape
cp 0_ 00 rr cp
cp 1_ 11 rr cp
cp __ ** ll fm_mh

; move head to find mid
fm_mh 00 ** ll fm_mh
fm_mh 11 ** ll fm_mh
fm_mh __ ** rr fm1

; find mid
fm1 _0 ** l* find_mid
fm1 _1 ** l* find_mid
fm1 *0 ** *r fm2
fm1 *1 ** *r fm2
fm2 0* ** r* fm3
fm2 1* ** r* fm3
fm3 0* ** r* fm1
fm3 1* ** r* fm1

; if find mid first tape move to head
find_mid 0* ** l* find_mid
find_mid 1* ** l* find_mid
find_mid _* ** r* cmp

; compare ww
cmp 00 ** rr cmp
cmp 11 ** rr cmp
cmp 01 ** ** mid_reject
cmp 10 ** ** mid_reject
cmp *_ ** r* mid_accept

; if mid reject
mid_reject 0* ** r* mid_reject
mid_reject 1* ** r* mid_reject
mid_reject _* ** l* mid_reject1
mid_reject1 *0 ** *r mid_reject1
mid_reject1 *1 ** *r mid_reject1
mid_reject1 *_ ** *l mid_reject2
mid_reject2 __ ** rr even_reject
mid_reject2 ** __ ll mid_reject2

; if  mid accept
mid_accept 1_ ** r* mid_accept
mid_accept 0_ ** r* mid_accept
mid_accept __ ** ll mid_rm

; clean tape
mid_rm 11 __ ll mid_rm
mid_rm 00 __ ll mid_rm
mid_rm __ ** rr accept

; accept
accept __ T_ r* accept1
accept1 __ r_ r* accept2
accept2 __ u_ r* accept3
accept3 __ e_ ** halt_accept

; reject
even_reject 0_ __ l* even_reject
even_reject 1_ __ l* even_reject
even_reject __ F_ r* reject1
reject1 __ a_ r* reject2 
reject2 __ l_ r* reject3
reject3 __ s_ r* reject4
reject4 __ e_ ** halt_reject




