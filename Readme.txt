* Work done
- Question generator in Lisp and unit tests.
  + A server waits for incoming connection from the C++ web server to
    send/receive question/answer.
  + Generate question on the fly from a simple arithmetic expression.
  + Verify user answer.

- RESTful web server in C++
  + Accept GET request from client.
  + Talk and retrieve captcha question from Lisp server.
  + Respond the client with the question and a simple form for entering answer.
  + Accept POST request from client for answer
  + Talk and retrieve the answer from Lisp server.
  + Respond the result to the client, either 200 OK for correct answer, or 400
    Bad Request for wrong answer.

- All unit tests passed.

- Tested on Fedora Linux 23 and OSX EL Captain version 10.11.14.
