(ql:quickload "fiveam")

(defpackage :captcha-test
  (:use :common-lisp
        :fiveaM))

(load "captcha.lisp")

(fiveam:def-suite captcha-testsuite :description "The test suite for captcha generator.")

(fiveam:in-suite captcha-testsuite)

(fiveam:test generate-arith-expression
  ""
  (fiveam:is (listp (generate-arith-expression)))
  (fiveam:is (member (car (generate-arith-expression)) *arith-ops*))
  (fiveam:is (numberp (cadr (generate-arith-expression))))
  (fiveam:is (numberp (caddr (generate-arith-expression)))))

(fiveam:test op->verb
  ""
  (fiveam:is (member (op->verb '+) *plus-verbs*))
  (fiveam:is (member (op->verb '-) *minus-verbs*))
  (fiveam:is (member (op->verb '*) *time-verbs*))
  (fiveam:is (member (op->verb '/) *divide-verbs*)))

(fiveam:test op->end-question
  ""
  (fiveam:is (string-equal "how many do you have in total?" (op->end-question '+)))
  (fiveam:is (string-equal "how many are left?" (op->end-question '-)))
  (fiveam:is (string-equal "what is the result?" (op->end-question '*)))
  (fiveam:is (string-equal "what is the result?" (op->end-question '/))))

(fiveam:test calculate
  "Test the `calculate' function"
  (fiveam:is (= 11 (calculate '(+ 5 6))))
  (fiveam:is (= 4 (calculate '(- 9 5))))
  (fiveam:is (= 20 (calculate '(* 4 5))))
  (fiveam:is (= 4 (calculate '(/ 20 5)))))

(fiveam:run! 'captcha-testsuite)
