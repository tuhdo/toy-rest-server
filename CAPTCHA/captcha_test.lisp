(ql:quickload "fiveam")

(defpackage :captcha-test
  (:use :common-lisp
        :fiveaM))

(fiveam:def-suite captcha-testsuite :description "The test suite for captcha generator.")

(fiveam:in-suite captcha-testsuite)

(fiveam:test generate-arith-expression
  "Test case for `generate-arith-expression'"
  (fiveam:is (listp (generate-arith-expression)))
  (fiveam:is (member (car (generate-arith-expression)) *arith-ops*))
  (fiveam:is (numberp (cadr (generate-arith-expression))))
  (fiveam:is (numberp (caddr (generate-arith-expression))))
  (fiveam:is (numberp (calculate (generate-arith-expression)))))

(fiveam:test number->text
  "Test case for `number->text'"
  (fiveam:is (stringp (number->text 1)))
  (fiveam:is (string-equal (number->text 1) "one"))
  (fiveam:is (string-equal (number->text 2) "two"))
  (fiveam:is (string-equal (number->text 3) "three"))
  (fiveam:is (string-equal (number->text 4) "four"))
  (fiveam:is (string-equal (number->text 5) "five"))
  (fiveam:is (string-equal (number->text 6) "six"))
  (fiveam:is (string-equal (number->text 7) "seven"))
  (fiveam:is (string-equal (number->text 8) "eight"))
  (fiveam:is (string-equal (number->text 9) "nine"))
  (fiveam:is (string-equal (number->text 10) "ten")))

(fiveam:test op->verb
  "Test case for `op->verb'"
  (fiveam:is (member (op->verb '+) *plus-verbs*))
  (fiveam:is (member (op->verb '-) *minus-verbs*))
  (fiveam:is (member (op->verb '*) *time-verbs*))
  (fiveam:is (member (op->verb '/) *divide-verbs*)))

(fiveam:test op->end-question
  "Test case for `op->end-question'"
  (fiveam:is (string-equal "how many do you have in total?" (op->end-question '+)))
  (fiveam:is (string-equal "how many are left?" (op->end-question '-)))
  (fiveam:is (string-equal "what is the result?" (op->end-question '*)))
  (fiveam:is (string-equal "what is the result?" (op->end-question '/))))

(fiveam:test calculate
  "Test case for `calculate'"
  (fiveam:is (= 11 (calculate '(+ 5 6))))
  (fiveam:is (= 4 (calculate '(- 9 5))))
  (fiveam:is (= 20 (calculate '(* 4 5))))
  (fiveam:is (= 4 (calculate '(/ 20 5))))
  (fiveam:is (= 1000000 (calculate '(* 1000 1000)))))

(fiveam:test expression->question
  "Test case for `expression->question'"
  (fiveam:is (stringp (expression->question '(+ 5 6)))))

(fiveam:test generate-question
  "Test case for `generate->question'"
  (let ((*current-expr* nil))
    (fiveam:is (stringp (generate-question)))
    (fiveam:is (listp *current-expr*))
    (fiveam:is (numberp (calculate *current-expr*)))
    (fiveam:is (let ((prev-expr *current-expr*))
                 (generate-question)
                 (not (equal prev-expr *current-expr* ))))))

(fiveam:run! 'captcha-testsuite)
