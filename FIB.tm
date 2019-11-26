; This  program checks if the input string is a fib number.
; Input: a string of 0's and 1's, eg '00000000'

; the finite set of states
#Q = {init, cmp, move_2_1, move_2_1_1, move_2_1_2, move_3_2, move_3_2_1, move_3_2_2, mh_cmp, mh_cmp1, add, add1, ready_accept, ready_accept1, ready_accept2, ready_reject, ready_reject1, ready_reject2, ready_reject3, ready_reject4, accept,accept2,accept3, halt_accept,reject,reject2,reject3,reject4,halt_reject}

; the finite set of input symbols
#S = {0}

; the complete set of tape symbols
#G = {0,_,T,r,u,e,F,a,l,s}

; the start state
#q0 = init

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 4 

; the transition functions

; initialize
init ____ ____ **** reject ; empty string
init 0___ 0000 **** cmp ; non empty

; compare
cmp 0**0 **** r**r cmp
cmp _**0 **** l*** ready_reject
cmp 0**_ **** ***l move_2_1
cmp _**_ **** l**l ready_accept

; move 2-tape to 1-tape
move_2_1 *0** **** *l** move_2_1
move_2_1 *_** **** *r** move_2_1_1
move_2_1_1 **0* **** **l* move_2_1_1
move_2_1_1 **_* **** **r* move_2_1_2
move_2_1_2 **0* *00* *rr* move_2_1_2
move_2_1_2 **_* **** *ll* move_3_2

; move 3-tape to 2-tape
move_3_2 **0* **** **l* move_3_2
move_3_2 **_* **** **r* move_3_2_1
move_3_2_1 ***0 **** ***l move_3_2_1
move_3_2_1 ***_ **** ***r move_3_2_2
move_3_2_2 ***0 **00 **rr move_3_2_2
move_3_2_2 ***_ **** **l* add

; add 1-tape to 3-tape
add *0** **** *l** add
add *_** **** *r** add1
add1 *0** *0*0 *r*r add1
add1 *_** **** *l*l mh_cmp

; move 3-tape back to head to compare
mh_cmp ***0 **** ***l mh_cmp
mh_cmp ***_ **** ***r mh_cmp1
mh_cmp1 0*** **** l*** mh_cmp1
mh_cmp1 _*** **** r*** cmp

; ready to accept
ready_accept 0**0 _**_ l**l ready_accept
ready_accept _**_ **** r**r ready_accept1
ready_accept1 *0** *_** *l** ready_accept1
ready_accept1 *_** **** *r** ready_accept2
ready_accept2 **0* **_* **l* ready_accept2
ready_accept2 **_* **** **r* accept

; ready to reject
ready_reject 0*** _*** l*** ready_reject
ready_reject _*** **** r*** ready_reject1
ready_reject1 *0** *_** *l** ready_reject1
ready_reject1 *_** **** *r** ready_reject2
ready_reject2 **0* **_* **l* ready_reject2
ready_reject2 **_* **** **r* ready_reject3
ready_reject3 ***0 **** ***r ready_reject3
ready_reject3 ***_ **** ***l ready_reject4
ready_reject4 ***0 ***_ ***l ready_reject4
ready_reject4 ***_ **** ***r reject

; accept
accept ____ T___ r*** accept1
accept1 ____ r___ r*** accept2
accept2 ____ u___ r*** accept3
accept3 ____ e___ **** halt_accept

; reject
reject ____ F___ r*** reject1
reject1 ____ a___ r*** reject2 
reject2 ____ l___ r*** reject3
reject3 ____ s___ r*** reject4
reject4 ____ e___ **** halt_reject




