%.o: %.c
	$(CC) -O2 -Wall -c -o $@ $<

all: cache.o cachesim.o
	$(CC) -Wall -o cachesim $^

submit:
	@if [ -z "`cat STUDENT.ID | awk -F\= '/StudentID/ { gsub(/"/,"",$$2); print $$2 }'`" ]; then echo "*** Student ID not set. Edit STUDENT.ID first"; false; else true; fi
	@tar czf `cat STUDENT.ID | awk -F\= '/StudentID/ { gsub(/"/,"",$$2); print $$2 }'`.tgz STUDENT.ID cachesim.c cache.c cache.h
	@echo "Email your submission (`cat STUDENT.ID | awk -F\= '/StudentID/ { gsub(/"/,"",$$2); print $$2 }'`.tgz) to the TA (comparch@csap.snu.ac.kr)"

clean:
	rm -f *.o cachesim

