(define (insert x tree)
    (cond
        ((null? tree) (list x '() '()))
        ((< x (car tree)) (list (car tree) (insert x (cadr tree)) (caddr tree)))
        ((> x (car tree)) (list (car tree) (cadr tree) (insert x (caddr tree))))
        (else tree)))

(define (member? x tree)
    (cond
        ((null? tree) #f)
        ((< x (car tree)) (member? x (cadr tree)))
        ((> x (car tree)) (member? x (caddr tree)))
        (else #t)))

