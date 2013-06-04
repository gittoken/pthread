test_cond_objs = test_cond.o
test_mutex_objs = test_mutex.o
test_mutex_2_objs = test_no_mutex_and_have_mutex.o

CFLAGS = -g
LIBS = -l pthread

all:test_cond test_mutex test_mutex_2 

test_cond: $(test_cond_objs)
	$(CC) $(CFLAGS)  $(test_cond_objs) $(LIBS) -o $@
test_mutex: $(test_mutex_objs)
	$(CC) $(CFLAGS) $(test_mutex_objs) $(LIBS) -o $@
test_mutex_2: $(test_mutex_2_objs)
	$(CC) $(CFLAGS) $(test_mutex_2_objs) $(LIBS) -o $@

clean:
	rm -f *.o 
	rm -f test_cond
	rm -f test_mutex
	rm -f test_mutex_2
