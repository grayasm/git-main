.
                      Cap.7 Input and Output
                      pag. 151 - 168

  1. input redirection is not visible to the program, not included in argv
     prog < infile
  2. input switching via a pipe mechanism is also invisible to the program
     otherprog | prog
  3. a variety of specifications in printing "hello, world" 12 characters.
     :%s:         :hello, world:
     :%10s:       :hello, world:
     :%.10s:      :hello, wor:
     :%-15s:      :hello, world   :
     :%15.10s:    :     hello, wor:
     :%-15.10s:   :hello, wor     :

  4. you should be aware of the difference between these two calls:
     printf(s);          /* fails if s contains % */
     printf("%s", s);    /* safe */
  5. void f(char *fmt, ...) contains a variable-length argument list,
     where ... can only appear at the end of an argument list.
  6. the rest of cap.7 is an index of functions by cathegories: str,mem,sys,etc
