all: 01_class_fundamentals \
     02_create_objects \
     03_references \
     04_methods \
     05_constructors \
     06_operator_new \
     07_destructors_and_gc \
     08_keyword_this


01_class_fundamentals: 01_class_fundamentals.cs Makefile
	mcs 01_class_fundamentals.cs

02_create_objects: 02_create_objects.cs Makefile
	mcs 02_create_objects.cs

03_references: 03_references.cs Makefile
	mcs 03_references.cs

04_methods: 04_methods.cs Makefile
	mcs 04_methods.cs

05_constructors: 05_constructors.cs Makefile
	mcs 05_constructors.cs

06_operator_new: 06_operator_new.cs Makefile
	mcs 06_operator_new.cs

07_destructors_and_gc: 07_destructors_and_gc.cs Makefile
	mcs 07_destructors_and_gc.cs

08_keyword_this: 08_keyword_this.cs Makefile
	mcs 08_keyword_this.cs


clear:
	rm -v  01_class_fundamentals.exe \
           02_create_objects.exe \
           03_references.exe \
           04_methods.exe \
           05_constructors.exe \
           06_operator_new.exe \
           07_destructors_and_gc.exe \
           08_keyword_this.exe
