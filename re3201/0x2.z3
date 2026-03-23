; add eax, ecx
; shl eax, 0xc
; mul ecx
; mov edx, eax
; xor edx, ecx


; set the logic type
(set-logic QF_BV)
(set-info :smt-lib-version 2.0)

; declare the variables needed
(declare-fun eax_in () (_ BitVec 32))
(declare-fun ecx_in () (_ BitVec 32))

(declare-fun eax1 () (_ BitVec 32))
(declare-fun edx1 () (_ BitVec 32))
(declare-fun edx2 () (_ BitVec 32))
(declare-fun eax2 () (_ BitVec 32))
(declare-fun eax3 () (_ BitVec 32))

; 01 encode CPU instructions and machine code
(assert (and 
  (= eax1 (bvadd eax_in ecx_in))
  (= eax2 (bvshl eax1 (_ bv12 32)))
  (= eax3 (bvmul eax1 ecx_in))
  (= edx1 eax1)
  (= edx2 (bvxor edx1 ecx_in))
))

; check satisfiability
(check-sat)

; retrieve a model
;(get-model)

; constraining the input value
(push)
(assert (= eax_in #xffffffff))
(check-sat)


; constraining more
;(push)
;(assert (= ecx_in #xeeeeeeee))

(check-sat)
(get-model)
