Beginning
(declare-const y Int)
(assert (and (<= 0 y)(and (and (<= (* y (- 1))(- 4))(<= (- 4)y))(or (<= (- 4)(* y (- 1)))(<= y (- 4))))))
(maximize y)
(check-sat)
(get-objectives)
