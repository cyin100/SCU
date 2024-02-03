; vi:ai:lisp:sm

(define (filter f lst)
    (cond
        ((null? lst) lst)
        ((f (car lst)) (cons (car lst) (filter f (cdr lst))))
        (else (filter f (cdr lst)))))

(define (quicksort lst)
    (cond 
        ((null? lst) lst)
        (else
            (let* 
                ((x (car lst))
                (xs (cdr lst))
                (above (lambda (y) (>= y x)))
                (below (lambda (y) (< y x))))
            (append (quicksort (filter below xs)) (cons x (quicksort (filter above xs))))
        ))))


