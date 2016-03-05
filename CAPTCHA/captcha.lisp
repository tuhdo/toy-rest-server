(defpackage captcha
  (:use :common-lisp))

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
(defparameter *plus-verbs* '("received another" "gifted another" "picked up" "gifted"))
(defparameter *minus-verbs* '("dropped" "ate" "gave away"))
(defparameter *time-verbs* '("times" "multiplied by"))
(defparameter *divide-verbs* '("divided by"))

(defun generate-arith-expression ()
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
  "Calculate expression generated from generate-arith-expr."
  (apply (car expr) (cdr expr)))

(defun answer-correct-p (ans expr)
  "Check whether user answer matched arithmetic expression."
  (= ans (calculate expr)))

(defun op->verb (op)
  (case op
    ('+ (nth (random (length *plus-verbs*)) *plus-verbs*))
    ('- (nth (random (length *minus-verbs*)) *minus-verbs*))
    ('* (nth (random (length *time-verbs*)) *time-verbs*))
    ('/ (nth (random (length *divide-verbs*)) *divide-verbs*))
    (otherwise (error "Operator not supported."))))

(defun op->end-question (op)
  (case op
    ('+ "how many do you have in total?")
    ('- "how many are left?")
    ('* "what is the result?")
    ('/ "what is the result?")
    (otherwise (error "Operator not supported."))))

(defun expression->question (expr)
  "Turn an aritmetic expression into a question."
  (let* ((op (car expr))
         (number1 (cadr expr))
         (number2 (caddr expr))
         (pronoun "of them")
         (start-verb (nth (random (length *first-operand-verbs*)) *first-operand-verbs*))
         (object (nth (random (length *nouns*)) *nouns*))
         (op-verb (op->verb op))
         (end-question (op->end-question op)))
    (format t "~A ~d ~A, ~A ~d ~A, ~a " start-verb number1 object op-verb number2 pronoun end-question)))

(defun start-echo-server (port)
  "Listening on a port for a message, and print the received message."
  (usocket:with-socket-listener (socket "127.0.0.1" port)
    (usocket:wait-for-input socket)
    (usocket:with-connected-socket (connection (usocket:socket-accept socket))
      (format t "~a~%" (read-line (usocket:socket-stream connection))))))
