(declare-const i1 Int)
(assert (= i1 6))
(maximize i1)
(check-sat)
(get-objectives)
