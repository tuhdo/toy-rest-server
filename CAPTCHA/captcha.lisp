(ql:quickload "usocket")

(defpackage captcha
  (:use :common-lisp))

(defparameter *current-expr* nil
  "Latest expression generated by `generate-question'.")

(defconstant +MAX-NUMBER+ 10
  "The upper limit of number for arithmetic calculation.")

(defconstant +MIN-NUMBER+ 1
  "The lower limit of number for arithmetic calculation.")

(defparameter *arith-ops*  '(+ - * /)
  "The number of available arithmetic operations.")

(defparameter *nouns* '("apples" "oranges" "avocados" "bananas" "watermelons" "pumpkins"
                        "strawberries" "blueberries" "guavas" "mangos" "pineapples"))
(defparameter *pronouns* '("of them" "them all"))
(defparameter *first-operand-verbs* '("start with" "having bought" "having" "acquired" "given" "there are" "you have"))
(defparameter *plus-verbs* '("received another" "picked up" "and you was gifted"))
(defparameter *minus-verbs* '("dropped" "ate" "you gave away"))
(defparameter *time-verbs* '("times" "multiplied by"))
(defparameter *divide-verbs* '("divided by"))
(defparameter *number-text* '("one" "two" "three" "four" "five" "six" "seven" "eight" "nine" "ten"))

(defun generate-arith-expression ()
  "Generate a 2-operand arithmetic expression as a list.

Return a list that represent an expression i.e. '(+ 5 6)."
  (let* ((number1  (1+ (random +MAX-NUMBER+)))
         (number2  (1+ (random +MAX-NUMBER+)))
         (op (nth  (random (length *arith-ops*)) *arith-ops*)))
    (append (list op)
            (case op
              ('- (if (> number1 number2) (list number1 number2) (list number2 number1)))
              ('/
               (setf number1 (* number2 (1+ (random +MAX-NUMBER+))))
               (list number1 number2))
              (otherwise (list number1 number2))))))

(defun calculate (expr)
  "Calculate expression generated from generate-arith-expr.
`expr' is a list that represent an expression i.e. '(+ 5 6).

Return result of the expression, which is a number of type integer."
  (apply (car expr) (cdr expr)))

(defun answer-correct-p (ans expr)
  "Check whether user answer matched arithmetic expression.
`ans' is user-supplied answer, sent by the web server.
`expr' is a list that represent an expression i.e. '(+ 5 6).

Return a string, either \"T\" or \"F\"."
  (if  (= ans (calculate expr))
       "T"
       "F"))

(defun number->text (num)
  "Convert a number from 1 to 10 into text form i.e. 1 -> one, 2 -> two....

`num' is an integer.

Return a string."
  (nth (1- num) *number-text*))

(defun op->verb (op)
  "Convert an operation to verb phrase from to make it more meaningful for
a human reader.

`op' is one of four symbols '+, '-, '*, '/

Return a string."
  (case op
    ('+ (nth (random (length *plus-verbs*)) *plus-verbs*))
    ('- (nth (random (length *minus-verbs*)) *minus-verbs*))
    ('* (nth (random (length *time-verbs*)) *time-verbs*))
    ('/ (nth (random (length *divide-verbs*)) *divide-verbs*))
    (otherwise (error "Operation not supported."))))

(defun op->end-question (op)
  "Generate a question clause to be placed at the end, based on an operation.
`op' is one of four symbols '+, '-, '*, '/.

Return a string."
  (case op
    ('+ "how many do you have in total?")
    ('- "how many are left?")
    ('* "what is the result?")
    ('/ "what is the result?")
    (otherwise (error "Operation not supported."))))

(defun expression->question (expr)
  "Turn an arithmetic expression into a question.
A number less than 10 can be either in its numeric form or text form.

`expr' is a list that contains a math expression i.e. '(+ 5 6)"
  (let* ((op (car expr))
         (number1 (list (cadr expr) (number->text (cadr expr))))
         (number2 (list (caddr expr) (number->text (caddr expr))))
         (pronoun "of them")
         (start-verb (nth (random (length *first-operand-verbs*)) *first-operand-verbs*))
         (object (nth (random (length *nouns*)) *nouns*))
         (op-verb (op->verb op))
         (end-question (op->end-question op)))
    (format nil "~A ~d ~A, ~A ~d ~A, ~a"
            start-verb
            (if (< (car number1) 10)
                (nth (random 2) number1)
                (car number1))
            object
            op-verb
            (if (< (car number2) 10)
                (nth (random 2) number2)
                (car number2))
            pronoun
            end-question)))

(defun generate-question ()
  "Top level question for generating a question.

Return a string."
  (setf *current-expr* (generate-arith-expression))
  (expression->question *current-expr*))

(defun start-captcha-server (port)
  "Listening on a port for a message, and response the with a question."
  (usocket:with-socket-listener (socket "127.0.0.1" port)
    (loop
      (usocket:wait-for-input socket)
      (usocket:with-connected-socket (connection (usocket:socket-accept socket))
        (let ((msg (read-line (usocket:socket-stream connection))))
          (print msg)
          (cond
            ((string-equal msg "GET")
             (let ((q (generate-question)))
               (print q)
               (format (usocket:socket-stream connection) q)
               (finish-output (usocket:socket-stream connection))))
            (t
             (format (usocket:socket-stream connection)
                     (answer-correct-p (parse-integer msg) *current-expr*))
             (finish-output (usocket:socket-stream connection)))))))))
